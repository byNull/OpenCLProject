#ifndef __OPENCL_MATRIXMULTIPLY_H__
#define __OPENCL_MATRIXMULTIPLY_H__

#pragma once

#include "opencl_base_.h"

//typedef struct _TypeDeviceValue{
//	int index;//记录当前代表是哪个变量
//	typedef union _TypeDeviceInfo{
//		cl_device_type                 devType; //0
//		cl_uint                        devVendorId;//1
//		cl_uint                        devMaxCmpUnits;//2
//		cl_uint                        devMaxWorkItemDims;//3
//		size_t[]                       devMaxWorkItemSize;//4
//		size_t                         devMaxWorkGroupSize;//5
//		cl_uint                        devPreferredVectorWidth;//6
//		cl_uint                        devNativeVectorWidth;//7
//		cl_uint                        devMaxClockFreq;//8
//		cl_uint                        devAddrBits;//9
//		cl_ulong                       devMaxMemAllocSize;//10
//		cl_bool                        devImgSupport;//11
//		cl_uint                        devMaxReadImgArgs;//12
//		cl_uint                        devMaxWriteImgArgs;//13
//		size_t                         devImg2MaxWidth;//14
//		size_t                         devImg2MaxHeight;//15
//		size_t                         devImg3MaxWidth;//16
//		size_t                         devImg3MaxHeight;//17
//		size_t                         devImg3MaxDepth;//18
//		size_t                         devImgMaxBufSize;//19
//		size_t                         devImgMaxArraySize;//20
//		cl_uint                        devMaxSamples;//21
//		size_t                         devMaxArgsSize;//22
//		cl_uint                        devMemBaseAddrAlign;//23
//		cl_device_fp_config            devFpConfig;//24
//		cl_device_fp_config            devDFpConfig;//25
//		cl_device_mem_cache_type       devGMemCacheType;//26
//		cl_uint                        devGMemCacheLineSize;//27
//		cl_ulong                       devGMemCacheSize;//28
//		cl_ulong                       devGMemSize;//29
//		cl_ulong                       devMaxConstBufSize;//30
//		cl_uint                        devMaxConstArgs;//31
//		cl_device_local_mem_type       devLocalMemType;//32
//		cl_ulong                       devLocalMemSize;//33
//		cl_bool                        devErrCorrectSupport;//34
//		cl_bool                        devHostUniMem;//35
//		size_t                         devProfileTimerResolution;//36
//		cl_bool                        devEndianLittle;//37
//		cl_bool                        devAvailable;//38
//		cl_bool                        devCompilerAvail;//39             
//		cl_bool                        devLinkerAvail;//40
//		cl_device_exec_capabilities    devExeCaps;//41
//		cl_command_queue_properties    devQueueProps;//42
//		char[]                         devBuiltInKerl;//43
//		cl_platform_id                 devPlatformId;//44
//		char[]                         devName;//45
//		char[]                         devVendor;//46
//		char[]                         devDrvVersion;//47
//		char[]                         devProfile;//48
//		char[]                         devVersion;//49
//		char[]                         devOpenClCVer;//50
//		char[]                         devExtentions;//51
//		size_t                         devPrintfBufSize;//52
//		cl_bool                        devPreferredInteropUserSync;//53
//		cl_device_id                   devParentDev;//54
//		cl_uint                        devPartMaxSubDevs;//55
//		cl_device_partition_property[] devPartProps;//56
//		cl_device_affinity_domain      devPartAffiDomain;//57
//		cl_device_partition_property[] devPartType;//58
//		cl_uint                        devReferenceCnts;//59
//	}clTypeDeviceInfo;
//	typedef clTypeDeviceInfo TypeDeviceInfo;
//}TypeDeviceValue;
//
//
//const int[] clDeviceType = {
//	CL_DEVICE_TYPE, CL_DEVICE_VENDOR_ID, CL_DEVICE_MAX_COMPUTE_UNITS, CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, CL_DEVICE_MAX_WORK_ITEM_SIZES, CL_DEVICE_MAX_WORK_GROUP_SIZE,
//	CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, CL_DEVICE_MAX_CLOCK_FREQUENCY, CL_DEVICE_ADDRESS_BITS, CL_DEVICE_MAX_MEM_ALLOC_SIZE, CL_DEVICE_IMAGE_SUPPORT,
//	
//} ;

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
	//TypeDeviceInfo getSpecifiedDeviceInfo(cl_device_id dev, cl_device_info devInfo);
private:
	std::string    readSrcFromFile(std::string fileName);
	void           clearResources(cl_command_queue cmdQueue, cl_program pro, cl_kernel ker, cl_mem bufferA, cl_mem bufferB, cl_mem bufferR, cl_mem bufferMatWidth);
};

#endif