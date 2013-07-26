#include "stdafx.h"
#include "OpenCL_MM.h"
#include <sstream>
#include "mm_mul.h"
#include "common.h"

//extern "C" int R_Size;
//extern "C" int C_Size;

OpenCL_MM::OpenCL_MM(void)
{

}

// status = false, str = src string, or str = fileName
OpenCL_MM::OpenCL_MM(std::string str, bool status)
{
	if(!status){
		m_src = str;
	}else{
		m_src = readSrcFromFile(str);
	}
}

void OpenCL_MM::setOpenCLSourceProgram(std::string src)
{
	m_src = src;
}

void OpenCL_MM::setFileName(std::string fileName)
{
	m_src = readSrcFromFile(fileName);
}

std::string OpenCL_MM::readSrcFromFile(std::string fileName)
{
	std::string strSrc;
	std::ifstream ifHandler(fileName.c_str());
	if(!ifHandler){
		//output error information
		printf("Open File %s error!\n", fileName);
		exit(-1);
	}
	//std::sstream inFileBuf()
	/*istreambuf_iterator<char> beg(inFileHandler), end;
	std::string strSrc(beg, end);
	*/
	std::stringstream buffer;
	buffer << ifHandler.rdbuf();
	strSrc = buffer.str();
	ifHandler.close();

	return (strSrc);
}

void OpenCL_MM::writeDataToFile(int *r, unsigned int n, std::string fileName)
{

	std::ofstream ofHandler(fileName.c_str());
	if(!ofHandler){
		printf("Open file %s failure !\n", fileName.c_str());
		exit(-1);
	}

	for (unsigned int i = 0; i < n; i++)
	{
		if((i % 32) == 0 && (i != 0)){
			ofHandler << "\n" << r[i] <<"\t";
		}else{
			ofHandler << r[i] << "\t";
		}
	}

	ofHandler.close();
}


void OpenCL_MM::executeMM(char Matrix[2048][2048], unsigned char* Vector, int* r, unsigned int n)
{
	if(m_src.empty()){
		Error("OpenCl source program is NULL"); exit(-1);
	}

	//create a command queue, associated with device you want to execute on
	unsigned int     numElements = n;
	cl_int           status = -1;
	cl_mem           bufferA = NULL; //matrix
	cl_mem           bufferB = NULL; //vector
	cl_mem           bufferR = NULL; //result
	cl_mem           bufferMatWidth = NULL;//the number of row or column of matrixc
	cl_program       clProgram = NULL;
	cl_kernel        clKernel = NULL;
	cl_command_queue clCmdQueue = NULL;
	size_t           nDeviceBufferSize = -1;
	cl_device_id     selDevice = NULL;

	//Get Device id that is used to create context
	status = clGetContextInfo(m_clContext, CL_CONTEXT_DEVICES, 0, NULL, &nDeviceBufferSize);
	if(nDeviceBufferSize < 0){
		printErrorTypeInfo(FunType_clGetContextInfo, status);
		printf("No Device Available!\n");
		exit(-1);
	}
	cl_device_id*  devices = new cl_device_id[nDeviceBufferSize / sizeof(cl_device_id)];
	status     = clGetContextInfo(m_clContext, CL_CONTEXT_DEVICES, nDeviceBufferSize, devices, NULL);
	selDevice  = devices[0];
	delete[]   devices;

	//create command queue 
	clCmdQueue = clCreateCommandQueue(m_clContext, selDevice, 0, &status);
	if(status != CL_SUCCESS) {
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		printErrorTypeInfo(FunType_clCreateCommandQueue, status);
		Error("clCreateCommandQueue Failure");
		exit(-1);
	}

	//create device buffer objects
	bufferA = clCreateBuffer(m_clContext, CL_MEM_READ_ONLY, sizeof(char) * numElements * numElements , NULL, &status);
	if(status != CL_SUCCESS) {
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		printErrorTypeInfo(FunType_clCreateBuffer, status);
		Error("clCreateBuffer Failure");
		exit(-1);
	}

	bufferB = clCreateBuffer(m_clContext, CL_MEM_READ_ONLY, sizeof(char) * numElements, NULL, &status);
	if(status != CL_SUCCESS) {
		printErrorTypeInfo(FunType_clCreateBuffer, status);
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		Error("clCreateBuffer Failure");
		exit(-1);
	}

	bufferR = clCreateBuffer(m_clContext, CL_MEM_WRITE_ONLY, sizeof(int) * numElements, NULL, &status);
	if(status != CL_SUCCESS) {
		printErrorTypeInfo(FunType_clCreateBuffer, status);
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		Error("clCreateBuffer Failure");
		exit(-1);
	}

	bufferMatWidth = clCreateBuffer(m_clContext, CL_MEM_READ_ONLY | CL_MEM_COPY_HOST_PTR, sizeof(int), &numElements, &status);
	if(status != CL_SUCCESS) {
		printErrorTypeInfo(FunType_clCreateBuffer, status);
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		Error("clCreateBuffer Failure");
		exit(-1);
	}

	//write host buffer memory to device memory
	status =  clEnqueueWriteBuffer(clCmdQueue, bufferA, CL_FALSE, 0, sizeof(char) * numElements * numElements, Matrix, 0, NULL, NULL);
	status |= clEnqueueWriteBuffer(clCmdQueue, bufferB, CL_FALSE, 0, sizeof(char) * numElements, Vector, 0, NULL, NULL);
	if(status != CL_SUCCESS) {
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		printErrorTypeInfo(FunType_clEnqueueWriteBuffer, status);
		Error("clEnqueueWriteBuffer Failure");
		exit(-1);
	}

	//create cl_program
	const char *strSrc = m_src.c_str();
	clProgram = clCreateProgramWithSource(m_clContext, 1, (const char **)&strSrc, NULL, &status);
	if(status != CL_SUCCESS) {
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		printErrorTypeInfo(FunType_clCreateProgramWithSource, status);
		Error("clEnqueueNDRangeKernel Failure");
		exit(-1);
	}

	//build program
	status = clBuildProgram(clProgram, 0, NULL, NULL, NULL, NULL);
	if(status != CL_SUCCESS) {
		char buildLog[16384];
		clGetProgramBuildInfo(clProgram, selDevice, CL_PROGRAM_BUILD_LOG, sizeof(buildLog), buildLog, NULL);
		std::cout << "Error in kernel: " << buildLog << std::endl;

		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		
		printErrorTypeInfo(FunType_clBuildProgram, status);
		Error("clEnqueueNDRangeKernel Failure");

		exit(-1);
	}

	//create kernel
	clKernel = clCreateKernel(clProgram, "matrixVectorMultiply", &status);
	if(status != CL_SUCCESS){
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		Error("clEnqueueNDRangeKernel Failure");
		exit(-1);
	}

	//set kernel arguments
	status =  clSetKernelArg(clKernel, 0, sizeof(cl_mem), &bufferA);
	status |= clSetKernelArg(clKernel, 1, sizeof(cl_mem), &bufferB);
	status |= clSetKernelArg(clKernel, 2, sizeof(cl_mem), &bufferR);
	status |= clSetKernelArg(clKernel, 3, sizeof(cl_mem), &bufferMatWidth);
	if(status != CL_SUCCESS) {
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		Error("clEnqueueNDRangeKernel Failure");
		exit(-1);
	}

	//configure the work-item structure
	//define an index space of work item for execution.
	//A workgroup size is not required
	size_t globalWorkSize[1] = {numElements};
	size_t localWorkSize [1] = {1};

	//Enqueue the kernel for execution
	boost::timer t;
	for(int i = 0; i < MAXSIZE; i++){
		status = clEnqueueNDRangeKernel(clCmdQueue, clKernel, 1, NULL, globalWorkSize, localWorkSize, 0, NULL, NULL);
	}
	std::cout<<t.elapsed()<<" s\n";

	if (status != CL_SUCCESS) {
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		Error("clEnqueueNDRangeKernel Failure");
		exit(-1);
	}

	//read result from output buffer queue, and return results to host buffer memory
	status = clEnqueueReadBuffer(clCmdQueue, bufferR, CL_TRUE, 0, sizeof(int) * numElements, r, 0, NULL, NULL);
	if(status != CL_SUCCESS){
		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
		Error("clearResources Failure");
		exit(-1);
	}

	//Free Opencl resource
	clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
}

//void OpenCL_MatrixMultiply::buildProgramAndSetArg(char** Matrix, unsigned char* Vector, int* r, unsigned int n)
//{
//	if(m_src.empty()){
//		Error("OpenCl source program is NULL");
//		exit(-1);
//	}
//
//	//create a command queue, associated with device you want to execute on
//	unsigned int     NumElements = n;
//	cl_int           status;
//	cl_command_queue clCmdQueue = NULL;
//	cl_mem           bufferA = NULL; //matrix
//	cl_mem           bufferB = NULL;; //vector
//	cl_mem           bufferR = NULL;; //result
//	cl_mem           bufferMatWidth = NULL;;//the number of row or column of matrixc
//	cl_program       clProgram = NULL;;
//	cl_kernel        clKernel = NULL;;
//
//	clCmdQueue = clCreateCommandQueue(m_clContext, m_devices[0], 0, &status);
//	if(status != CL_SUCCESS) {
//		exit(-1);
//	}
//
//	//create device buffer
//	bufferA = clCreateBuffer(m_clContext, CL_MEM_READ_ONLY, sizeof(char) * NumElements * NumElements , NULL, &status);
//	if(status != CL_SUCCESS) {
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//
//	bufferB = clCreateBuffer(m_clContext, CL_MEM_READ_ONLY, sizeof(char) * NumElements, NULL, &status);
//	if(status != CL_SUCCESS) {
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//
//	bufferR = clCreateBuffer(m_clContext, CL_MEM_WRITE_ONLY, sizeof(int) * NumElements, NULL, &status);
//	if(status != CL_SUCCESS) {
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//
//	bufferMatWidth = clCreateBuffer(m_clContext, CL_MEM_READ_ONLY | CL_MEM_ALLOC_HOST_PTR, sizeof(int), &NumElements, &status);
//	if(status != CL_SUCCESS) {
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//
//
//	//write host buffer memory to device memory
//	clEnqueueWriteBuffer(clCmdQueue, bufferA, CL_FALSE, 0, sizeof(char) * NumElements, Matrix, 0, NULL, NULL);
//	clEnqueueWriteBuffer(clCmdQueue, bufferB, CL_FALSE, 0, sizeof(char) * NumElements, Vector, 0, NULL, NULL);
//
//	//create cl_program
//	const char *strSrc = m_src.c_str();
//	clProgram = clCreateProgramWithSource(m_clContext, 1, (const char **)&m_src, NULL, &status);
//	if(status != CL_SUCCESS) {
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//
//	//build program
//	status = clBuildProgram(clProgram, m_numDevices, m_devices, NULL, NULL, NULL);
//	if(status != CL_SUCCESS) {
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//
//	//create kernel
//	clKernel = clCreateKernel(clProgram, "matrixMultiply", &status);
//	if(status != CL_SUCCESS){
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//
//	//set kernel arguments
//	status =  clSetKernelArg(clKernel, 0, sizeof(cl_mem), &bufferA);
//	status |= clSetKernelArg(clKernel, 1, sizeof(cl_mem), &bufferB);
//	status |= clSetKernelArg(clKernel, 2, sizeof(cl_mem), &bufferR);
//	status |= clSetKernelArg(clKernel, 3, sizeof(cl_mem), &bufferMatWidth);
//	if(status != CL_SUCCESS) {
//		clearResources(clCmdQueue, clProgram, clKernel, bufferA, bufferB, bufferR, bufferMatWidth);
//		exit(-1);
//	}
//}


void OpenCL_MM::clearResources(cl_command_queue cmdQueue, cl_program pro, cl_kernel ker,
										   cl_mem bufferA, cl_mem bufferB, cl_mem bufferR, cl_mem bufferMatWidth)
{
	if(NULL != bufferA) clReleaseMemObject(bufferA);
	if(NULL != bufferB) clReleaseMemObject(bufferB);
	if(NULL != bufferR) clReleaseMemObject(bufferR);
	if(NULL != bufferMatWidth) clReleaseMemObject(bufferMatWidth);
	if(NULL != ker) clReleaseKernel(ker);
	if(NULL != pro) clReleaseProgram(pro);
	if(NULL != cmdQueue) clReleaseCommandQueue(cmdQueue);
}

OpenCL_MM::~OpenCL_MM(void)
{

}

//TypeDeviceInfo OpenCL_MM::getSpecifiedDeviceInfo(cl_device_id dev, cl_device_info devInfo)
//{
//
//}