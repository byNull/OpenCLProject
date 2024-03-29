#include "stdafx.h"
#include "OpenCL_Base_.h"
#include <CL/cl.h>

COpenCL_Base_::COpenCL_Base_(void)
{
	initAllResources();
}

void COpenCL_Base_::initOpenCLPlatformLayer()
{
	m_status = clGetPlatformIDs(0, NULL, &m_numPlatforms);
	if(m_status != CL_SUCCESS || m_numPlatforms <= 0){
		printf("No install Opencl platform, please install or reintall intel OpenCL!\n");
		exit(-1);
	}

	m_platforms = new cl_platform_id[m_numPlatforms];
	m_status    = clGetPlatformIDs(m_numPlatforms, m_platforms, NULL);
	if(m_status != CL_SUCCESS) exit(-1);

	m_status = clGetDeviceIDs(m_platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &m_numDevices);
	if(m_status != CL_SUCCESS) exit(-1);

	m_devices = new cl_device_id[m_numDevices];
	m_status  = clGetDeviceIDs(m_platforms[0], CL_DEVICE_TYPE_ALL, m_numDevices, m_devices, NULL);
	if(m_status != CL_SUCCESS) exit(-1);
	
	bool bGpu = false;
	for (unsigned int i = 0; i < m_numDevices; i++) {
		cl_device_type devType;
		clGetDeviceInfo(m_devices[i], CL_DEVICE_TYPE, sizeof(devType), &devType, NULL);
		if(devType == CL_DEVICE_TYPE_GPU){
			devType = true; break;
		}
	}

	//create a context
	cl_context_properties ctxtProper[] = {CL_CONTEXT_PLATFORM, (cl_context_properties)m_platforms[0], 0};
	m_clContext = clCreateContextFromType(ctxtProper, (bGpu == true) ? CL_DEVICE_TYPE_GPU : CL_DEVICE_TYPE_CPU, NULL, NULL, &m_status);
	//m_clContext = clCreateContext(NULL, m_numDevices, m_devices, NULL, NULL, &m_status);
	if(m_status != CL_SUCCESS) {
		printErrorTypeInfo(FunType_clCreateContextFromType, m_status);
		exit(-1);
	}
}

cl_device_id COpenCL_Base_::getGpuDeviceId()
{
	cl_device_id di = NULL;
	bool bGpu = false;
	for (unsigned int i = 0; i < m_numDevices; i++) {
		cl_device_type devType;
		clGetDeviceInfo(m_devices[i], CL_DEVICE_TYPE, sizeof(devType), &devType, NULL);
		if(devType == CL_DEVICE_TYPE_GPU){
			devType = true; 
			di = m_devices[i];
			break;
		}
	}
	return di;
}
void COpenCL_Base_::initAllResources()
{
	initOpenCLPlatformLayer();
	initOtherResources();
}

void COpenCL_Base_::initOtherResources()
{

}

void COpenCL_Base_::destoryPlatformLayerResouces()
{
	clReleaseContext(m_clContext);
	if(NULL != m_devices)   delete[] m_devices;
	if(NULL != m_platforms) delete[] m_platforms;
}

void COpenCL_Base_::releaseALLResources()
{
	destoryOtherResource();
	destoryPlatformLayerResouces();
}

void COpenCL_Base_::destoryOtherResource()
{

}

COpenCL_Base_::~COpenCL_Base_(void)
{
	releaseALLResources();
}

void COpenCL_Base_::printErrorTypeInfo(clFuncType funcType, cl_int status)
{
	char strErr[2048];
	switch (funcType)
	{
	//////////////////////////////////////////////////////////////////////////
	case FunType_clCreateProgramWithSource:
		{
			switch(status)
			{
			case  CL_SUCCESS:
				sprintf(strErr, "%s\n", "CL_SUCCESS");
				break;
			case  CL_INVALID_VALUE:
				sprintf(strErr, "%s, %s\n", "CL_INVALID_VALUE", "if count is zero or if strings or any entry in strings is NULL");
				break;
			case  CL_OUT_OF_RESOURCES:
				sprintf(strErr, "%s, %s\n", "CL_OUT_OF_RESOURCES", "if there is a failure to allocate resources required by the \
																   OpenCL implementation on the device");
				break;
			case  CL_OUT_OF_HOST_MEMORY:
				sprintf(strErr, "%s, %s\n", "CL_OUT_OF_HOST_MEMORY", "if there is a failure to allocate resources required by the \
																	 OpenCL implementation on the host");
				break;
			default:
				sprintf(strErr, "%s\n", "Unknown type");
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case FunType_clCreateContextFromType:
		{
			switch(status)
			{
			case  CL_INVALID_PLATFORM:
				sprintf(strErr, "%s", "CL_INVALID_PLATFORM", "");
				break;
			case  CL_INVALID_VALUE:
				sprintf(strErr, "%s\n", "CL_INVALID_VALUE");
				break;
			case  CL_INVALID_PROPERTY:
				sprintf(strErr, "%s\n", "CL_INVALID_PROPERTY");
				break;
			case  CL_INVALID_DEVICE_TYPE:
				sprintf(strErr, "%s\n", "CL_INVALID_DEVICE_TYPE");
				break;
			case CL_DEVICE_NOT_AVAILABLE:
				sprintf(strErr, "%s\n", "CL_DEVICE_NOT_AVAILABLE");
				break;
			case CL_DEVICE_NOT_FOUND:
				sprintf(strErr, "%s\n", "CL_DEVICE_NOT_FOUND");
				break;
			case CL_OUT_OF_RESOURCES:
				sprintf(strErr, "%s\n", "CL_OUT_OF_RESOURCES");
				break;
			case CL_OUT_OF_HOST_MEMORY:
				sprintf(strErr, "%s\n", "CL_OUT_OF_HOST_MEMORY");
				break;
			default:
				sprintf(strErr, "%s\n", "Unknown type");
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case FunType_clGetContextInfo:
		{
			switch(status)
			{
			case  CL_INVALID_CONTEXT:
				sprintf(strErr, "%s", "CL_INVALID_CONTEXT", "");
				break;
			case  CL_INVALID_VALUE:
				sprintf(strErr, "%s\n", "CL_INVALID_VALUE");
				break;
			case  CL_OUT_OF_RESOURCES :
				sprintf(strErr, "%s\n", "CL_OUT_OF_RESOURCES ");
				break;
			case  CL_OUT_OF_HOST_MEMORY:
				sprintf(strErr, "%s\n", "CL_OUT_OF_HOST_MEMORY");
				break;
			default:
				sprintf(strErr, "%s\n", "Unknown type");
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case FunType_clBuildProgram:
		{
			switch(status)
			{
			case  CL_INVALID_PROGRAM:
				sprintf(strErr, "%s", "CL_INVALID_PROGRAM", "");
				break;
			case  CL_INVALID_VALUE:
				sprintf(strErr, "%s\n", "CL_INVALID_VALUE");
				break;
			case  CL_INVALID_DEVICE :
				sprintf(strErr, "%s\n", "CL_INVALID_DEVICE ");
				break;
			case  CL_INVALID_BINARY:
				sprintf(strErr, "%s\n", "CL_INVALID_BINARY");
				break;
			case  CL_INVALID_BUILD_OPTIONS:
				sprintf(strErr, "%s\n", "CL_INVALID_BUILD_OPTIONS");
				break;
			case  CL_INVALID_OPERATION :
				sprintf(strErr, "%s\n", "CL_INVALID_OPERATION ");
				break;
			case  CL_COMPILER_NOT_AVAILABLE:
				sprintf(strErr, "%s\n", "CL_COMPILER_NOT_AVAILABLE");
				break;
			case  CL_BUILD_PROGRAM_FAILURE:
				sprintf(strErr, "%s\n", "CL_BUILD_PROGRAM_FAILURE");
				break;
			case  CL_OUT_OF_RESOURCES :
				sprintf(strErr, "%s\n", "CL_OUT_OF_RESOURCES ");
				break;
			case  CL_OUT_OF_HOST_MEMORY:
				sprintf(strErr, "%s\n", "CL_OUT_OF_HOST_MEMORY");
				break;
			default:
				sprintf(strErr, "%s\n", "Unknown type");
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case FunType_clEnqueueReadBuffer:
	case FunType_clEnqueueWriteBuffer:
		{
			switch(status)
			{
			case  CL_INVALID_COMMAND_QUEUE:
				sprintf(strErr, "%s", "CL_INVALID_COMMAND_QUEUE", "");
				break;
			case  CL_INVALID_CONTEXT:
				sprintf(strErr, "%s\n", "CL_INVALID_CONTEXT");
				break;
			case  CL_INVALID_MEM_OBJECT :
				sprintf(strErr, "%s\n", "CL_INVALID_MEM_OBJECT ");
				break;
			case  CL_INVALID_VALUE:
				sprintf(strErr, "%s\n", "CL_INVALID_VALUE");
				break;
			case  CL_INVALID_EVENT_WAIT_LIST :
				sprintf(strErr, "%s\n", "CL_INVALID_EVENT_WAIT_LIST ");
				break;
			case  CL_MISALIGNED_SUB_BUFFER_OFFSET :
				sprintf(strErr, "%s\n", "CL_MISALIGNED_SUB_BUFFER_OFFSET ");
				break;
			case  CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST:
				sprintf(strErr, "%s\n", "CL_EXEC_STATUS_ERROR_FOR_EVENTS_IN_WAIT_LIST");
				break;
			case  CL_MEM_OBJECT_ALLOCATION_FAILURE:
				sprintf(strErr, "%s\n", "CL_MEM_OBJECT_ALLOCATION_FAILURE");
				break;
			case  CL_INVALID_OPERATION :
				sprintf(strErr, "%s\n", "CL_INVALID_OPERATION ");
				break;
			case  CL_OUT_OF_RESOURCES:
				sprintf(strErr, "%s\n", "CL_OUT_OF_RESOURCES");
				break;
			case  CL_OUT_OF_HOST_MEMORY:
				sprintf(strErr, "%s\n", "CL_OUT_OF_HOST_MEMORY");
				break;
			default:
				sprintf(strErr, "%s\n", "Unknown type");
			}
		}
		break;

	//////////////////////////////////////////////////////////////////////////
	case FunType_clCreateBuffer:
		{
			switch(status)
			{
			case  CL_INVALID_CONTEXT:
				sprintf(strErr, "%s", "CL_INVALID_CONTEXT", "");
				break;
			case  CL_INVALID_VALUE:
				sprintf(strErr, "%s\n", "CL_INVALID_VALUE");
				break;
			case  CL_INVALID_BUFFER_SIZE :
				sprintf(strErr, "%s\n", "CL_INVALID_BUFFER_SIZE ");
				break;
			case  CL_INVALID_HOST_PTR:
				sprintf(strErr, "%s\n", "CL_INVALID_HOST_PTR");
				break;
			case  CL_MEM_OBJECT_ALLOCATION_FAILURE :
				sprintf(strErr, "%s\n", "CL_MEM_OBJECT_ALLOCATION_FAILURE ");
				break;
			case  CL_OUT_OF_RESOURCES :
				sprintf(strErr, "%s\n", "CL_OUT_OF_RESOURCES ");
				break;
			case  CL_OUT_OF_HOST_MEMORY:
				sprintf(strErr, "%s\n", "CL_OUT_OF_HOST_MEMORY");
				break;
			default:
				sprintf(strErr, "%s\n", "Unknown type");
			}
		}
		break;
	}

	std::cout<<__FILE__<<":"<<__FUNCTION__<<":"<<__LINE__<<", Error info : "<<strErr<<std::endl;
}
