#ifndef __OPENCL_BASE_H___
#define __OPENCL_BASE_H___

#pragma once

#include <CL/cl.h>

typedef enum clFuncType{
	FunType_clGetPlatformIDs          = 0,
	FunType_clGetPlatformInfo         = 1,
	FunType_clGetDeviceIDs            = 2,
	FunType_clGetDeviceInfo           = 3,
	FunType_clRetainDevice            = 4,
	FunType_clCreateContext           = 5,
	FunType_clCreateContextFromType   = 6,
	FunType_clRetainContext           = 7,
	FunType_clCreateBuffer            = 8,
	FunType_clCreateSubBuffer         = 9,
	FunType_clCreateCommandQueue      = 10,
	FunType_clCreateProgramWithSource = 11,
	FunType_clCreateProgramWithBinary = 12,
	FunType_clBuildProgram            = 13,
	FunType_clCreateKernel            = 14,
	FunType_clCreateKernelsInProgram  = 15,
	FunType_clSetKernelArg            = 16,
	FunType_clEnqueueWriteBuffer      = 17,
	FunType_clEnqueueReadBuffer       = 18,
	FunType_clEnqueueNDRangeKernel    = 19,
	FunType_clReleaseMemObject        = 20,
	FunType_clReleaseKernel           = 21,
	FunType_clReleaseProgram          = 22,
	FunType_clReleaseCommandQueue     = 23,
	FunType_clReleaseContext          = 24,
	FunType_clGetContextInfo          = 25,

} clFuncType;

//////////////////////////////////////////////////////////////////////////
class COpenCL_Base_
{
protected:
	cl_int           m_status;
	cl_platform_id*  m_platforms;
	cl_uint          m_numPlatforms;
	cl_device_id*    m_devices;
	cl_uint          m_numDevices;
	cl_context       m_clContext;
	//cl_command_queue m_clCmdQueue;
	//cl_program       m_clProgram;
	//cl_kernel        m_clKernel;

public:
	COpenCL_Base_(void);
	virtual ~COpenCL_Base_(void);

	//init OpenCL resources
	void         initAllResources();
	void         initOpenCLPlatformLayer();
	virtual void initOtherResources();

	//release OpenCL resources
	virtual void destoryOtherResource();//can be used to override to release other resources
	void         destoryPlatformLayerResouces();
	void         releaseALLResources();//release all resources

protected:
	cl_device_id getGpuDeviceId();
	void         printErrorTypeInfo(clFuncType funcType, cl_int status);
};


#endif