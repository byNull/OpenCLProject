#ifndef __OPENCL_MATRIXMULTIPLY_H__
#define __OPENCL_MATRIXMULTIPLY_H__

#pragma once

#include "opencl_base_.h"
#include "common.h"


//////////////////////////////////////////////////////////////////////////
//Opencl_MatrixMultiply
class OpenCL_MM : public COpenCL_Base_
{
private:
	std::string m_src;

public:
	OpenCL_MM(void);
	// status = false, str = src string, or str = fileName
	OpenCL_MM(std::string str, bool status = false);
	virtual ~OpenCL_MM(void);

	void         setOpenCLSourceProgram(std::string src);
	void         setFileName(std::string fileName);

	//override
	//virtual void initOtherResources();
	//virtual void destoryOtherResource();

	static void    writeDataToFile(int *r, unsigned int n, std::string fileName = "openclMM.txt");
	void           executeMM(char Matrix[2048][2048], unsigned char* Vector, int* r, unsigned int n);
	TypeDeviceInfoValue getSpecifiedDeviceInfo(cl_device_id dev, cl_device_info devInfo);
private:
	std::string    readSrcFromFile(std::string fileName);
	void           clearResources(cl_command_queue cmdQueue, cl_program pro, cl_kernel ker, cl_mem bufferA, cl_mem bufferB, cl_mem bufferR, cl_mem bufferMatWidth);
};

#endif