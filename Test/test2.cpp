#include "stdafx.h"
//#include <iostream>
//#include <stdio.h>
//#include <CL/cl.h>
//
////get work_item's unique ID
//const char *proSrc[] ={
//"__kernel void vecAdd(__global const int *a, __global const int *b, __global int *r)",
//"{",
//"int index = get_global_id(0);",	
//"r[index] = a[index] + b[index];",	
//"}"
//};
//
////const char *proSrc  =
////"__kernel                                                      \n" 
////"void vecAdd(__global int *A, __global int *B, __global int *C)\n" 
////			" {                                                \n" 
////			"  int idx = get_global_id(0);                     \n" 
////			"  C[idx] = A[idx] + B[idx];                       \n" 
////			"}                                                 \n"
////			 ; 
//
//const int NumElements = 1024;
//
//int main()
//{
//	std::cout<< sizeof(proSrc) / sizeof(int)<<std::endl;
//
//	int *a = NULL;
//	int *b = NULL;
//	int *r = NULL;
//
//	a = new int[NumElements];
//	b = new int[NumElements];
//	r = new int[NumElements];
//	
//	//init host buffer data
//	for(int i = 0; i < NumElements; i++){
//		a[i] = i + 1;
//		b[i] = i + 2;
//	}
//
//	cl_int         status;
//	cl_uint        numPlatforms = 0;
//	cl_uint        numDevices   = 0;
//	cl_platform_id *platforms   = NULL;
//	cl_device_id   *devices     = NULL;
//
//	status = clGetPlatformIDs(0, NULL, &numPlatforms);
//	if(status != CL_SUCCESS) exit(-1);
//
//	platforms = new cl_platform_id[numPlatforms];
//	status    = clGetPlatformIDs(numPlatforms, platforms, NULL);
//	if(status != CL_SUCCESS) exit(-1);
//
//	status = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
//	if(status != CL_SUCCESS) exit(-1);
//
//	devices = new cl_device_id[numDevices];
//	status  = clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);
//	if(status != CL_SUCCESS) exit(-1);
//
//	//create a context
//	cl_context context = NULL;
//	context = clCreateContext(NULL, numDevices, devices, NULL, NULL, &status);
//	if(status != CL_SUCCESS) exit(-1);
//
//	//// Discover platforms 
//	//cl::vector<cl::Platform> platforms; 
//	//cl::Platform::get(&platforms); 
//
//	//// Create a context with the first platform 
//	//cl_context_properties cps[3]  =  {CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0}; 
//
//	//// Create a context using this platform for a GPU type device 
//	//cl::Context context(CL_DEVICE_TYPE_ALL, cps); 
//
//	//// Get device list from the context 
//	//cl::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES> (); 
//
//	//// Create a command queue on the first device 
//	//cl::CommandQueue queue  = cl::CommandQueue(context, devices[0], 0); 
//
//	//create a command queue, associated with device you want to execute on
//	cl_command_queue cmdQueue;
//	cmdQueue = clCreateCommandQueue(context, devices[0], 0, &status);
//	if(status != CL_SUCCESS) exit(-1);
//
//	//create device buffer
//	cl_mem bufferA;
//	cl_mem bufferB;
//	cl_mem bufferR;
//
//	bufferA = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * NumElements, NULL, &status);
//	if(status != CL_SUCCESS) exit(-1);
//
//	bufferB = clCreateBuffer(context, CL_MEM_READ_ONLY, sizeof(int) * NumElements, NULL, &status);
//	if(status != CL_SUCCESS) exit(-1);
//
//	bufferR = clCreateBuffer(context, CL_MEM_WRITE_ONLY, sizeof(int) * NumElements, NULL, &status);
//	if(status != CL_SUCCESS) exit(-1);
//
//
//	//write host buffer memory to device memory
//	clEnqueueWriteBuffer(cmdQueue, bufferA, CL_FALSE, 0, sizeof(int) * NumElements, a, 0, NULL, NULL);
//	clEnqueueWriteBuffer(cmdQueue, bufferB, CL_FALSE, 0, sizeof(int) * NumElements, b, 0, NULL, NULL);
//	//clEnqueueWriteBuffer(cmdQueue, bufferR, CL_FALSE, 0, sizeof(int) * NumElements, r, 0, NULL, NULL);
//
//	//create cl_program
//	cl_program clProgram = clCreateProgramWithSource(context, sizeof(proSrc) / sizeof(int), (const char **)&proSrc, NULL, &status);
//	if(status != CL_SUCCESS) exit(-1);
//
//	//build program
//	status = clBuildProgram(clProgram, numDevices, devices, NULL, NULL, NULL);
//	if(status != CL_SUCCESS) exit(-1);
//
//	//create kernel
//	cl_kernel clKernel = NULL;
//	clKernel = clCreateKernel(clProgram, "vecAdd", &status);
//	if(status != CL_SUCCESS) exit(-1);
//
//	//set kernel arguments
//	status =  clSetKernelArg(clKernel, 0, sizeof(cl_mem), &bufferA);
//	status |= clSetKernelArg(clKernel, 1, sizeof(cl_mem), &bufferB);
//	status |= clSetKernelArg(clKernel, 2, sizeof(cl_mem), &bufferR);
//	if(status != CL_SUCCESS) exit(-1);
//
//	//configure the work-item structure
//	//define an index space of work item for execution.
//	//A workgroup size is not required
//	size_t globalWorkSize[1] = {NumElements};
//
//	//Enqueue the kernel for execution
//	status = clEnqueueNDRangeKernel(cmdQueue, clKernel, 1, NULL, globalWorkSize, NULL, 0, NULL, NULL);
//	if (status != CL_SUCCESS) exit(-1);
//
//	//read output buffer , and return content to host buffer memory
//	clEnqueueReadBuffer(cmdQueue, bufferR, CL_TRUE, 0, sizeof(int) * NumElements, r, 0, NULL, NULL);
//
//
//	//verify the result 
//	bool bRet = true;
//	for(int i = 0; (i < NumElements) && (bRet == true); i ++){
//		if(r[i] != 2 * i + 3)
//			bRet = false;
//	}
//
//	if(bRet == false) printf("The result is incorrect\n");
//
//	for (int i = 0; i < NumElements; i ++){
//		std::cout<<r[i]<<"\t";
//	}
//	std::cout<<std::endl;
//
//	//Free Opencl resource
//	clReleaseKernel(clKernel);
//	clReleaseProgram(clProgram);
//	clReleaseCommandQueue(cmdQueue);
//	clReleaseMemObject(bufferA);
//	clReleaseMemObject(bufferB);
//	clReleaseMemObject(bufferR);
//	clReleaseContext(context);
//
//	//Free host resource
//	if(NULL != a)		  delete[] a;
//	if(NULL != b)         delete[] b;
//	if(NULL != r)         delete[] r;
//	if(NULL != platforms) delete[] platforms;
//	if(NULL != devices)   delete[] devices;
//
//	return 0;
//}
