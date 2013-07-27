#ifndef __COMMON_H__
#define __COMMON_H__

#pragma once

#include "stdafx.h"

#define MAXSIZE 1024

typedef unsigned short uint16;
typedef uint16         WORD;

enum LogLevel {
	LOG_LEVEL_DEBUG     = 0,
	LOG_LEVEL_INFO      = 1,
	LOG_LEVEL_WARNING   = 2,
	LOG_LEVEL_FATAL     = 3,
};

void GetDateTime(char *buffer);
void LogInternal(LogLevel level, const char *format, va_list args);
//WORD ChangeConsoleMode( WORD mode );

void  Info   (const char *format, ...);
void  Debug  (const char *format, ...);
void  Warning(const char *format, ...);
void  Error  (const char *format, ...);
void  Fatal  (const char *format, ...);

//bool ByteToWide(char* b, wchar_t* w, int len);
//bool WideToByte(wchar_t* w, char* b, int len);


typedef struct _TypeDeviceInfoValue{
public:
	typedef union _TypeDeviceInfo{
		cl_device_type                 devType;                     //0
		cl_uint                        devVendorId;                 //1
		cl_uint                        devMaxCmpUnits;				//2
		cl_uint                        devMaxWorkItemDims;			//3
		size_t                         devMaxWorkGroupSize;			//4
		//size_t[]                       devMaxWorkItemSize;			//5		
		cl_uint                        devPreferredVectorWidth;		//6
		cl_uint                        devNativeVectorWidth;		//7
		cl_uint                        devMaxClockFreq;				//8
		cl_uint                        devAddrBits;					//9
		cl_uint                        devMaxReadImgArgs;			//10
		cl_uint                        devMaxWriteImgArgs;			//11
		cl_ulong                       devMaxMemAllocSize;			//12
		size_t                         devImg2MaxWidth;				//13
		size_t                         devImg2MaxHeight;			//14
		size_t                         devImg3MaxWidth;				//15
		size_t                         devImg3MaxHeight;			//16
		size_t                         devImg3MaxDepth;				//17
		cl_bool                        devImgSupport;				//18
		size_t                         devMaxArgsSize;				//19
		cl_uint                        devMaxSamples;				//20
		cl_uint                        devMemBaseAddrAlign;			//21
		cl_device_fp_config            devFpConfig;					//22
		cl_device_fp_config            devDFpConfig;				//23
		cl_device_mem_cache_type       devGMemCacheType;			//24
		cl_uint                        devGMemCacheLineSize;		//25
		cl_ulong                       devGMemCacheSize;			//26
		cl_ulong                       devGMemSize;					//27
		cl_ulong                       devMaxConstBufSize;			//28
		cl_uint                        devMaxConstArgs;				//29
		cl_device_local_mem_type       devLocalMemType;				//30
		cl_ulong                       devLocalMemSize;				//31
		cl_bool                        devErrCorrectSupport;		//32
		size_t                         devProfileTimerResolution;	//33
		cl_bool                        devEndianLittle;				//34
		cl_bool                        devAvailable;				//35
		cl_bool                        devCompilerAvail;			//36             
		cl_device_exec_capabilities    devExeCaps;					//37
		cl_command_queue_properties    devQueueProps;				//38
		char*                          devName;						//39
		char*                          devVendor;					//40
		char*                          devDrvVersion;				//41
		char*                          devProfile;					//42
		char*                          devVersion;					//43
		char*                          devExtentions;				//44
		cl_platform_id                 devPlatformId;				//45
		cl_bool                        devHostUniMem;				//46
		char*                          devOpenClCVer;				//47
		cl_bool                        devLinkerAvail;				//48
		char*                          devBuiltInKerl;				//49
		size_t                         devImgMaxBufSize;			//50
		size_t                         devImgMaxArraySize;			//51
		cl_device_id                   devParentDev;				//52
		cl_uint                        devPartMaxSubDevs;			//53
		//cl_device_partition_property[] devPartProps;				//54
		cl_device_affinity_domain      devPartAffiDomain;			//55
		//cl_device_partition_property[] devPartType;					//56
		cl_uint                        devReferenceCnts;			//57
		cl_bool                        devPreferredInteropUserSync;	//58
		size_t                         devPrintfBufSize;			//59
	}clTypeDeviceInfo;
	typedef clTypeDeviceInfo TypeDeviceInfo;

private:
	int            index;//记录当前代表是哪个变量
	TypeDeviceInfo devInfo;

public:
	void getCurValue(void *pValue)
	{
		switch(index)
		{
		case 0:
			std::memcpy(pValue, &devInfo.devType, sizeof(cl_device_type));
			break;
		case 1:
			std::memcpy(pValue, &devInfo.devVendorId, sizeof(cl_uint));
			break;
		case 2:
			std::memcpy(pValue, &devInfo.devMaxCmpUnits, sizeof(cl_uint));
			break;
		case 3:
			std::memcpy(pValue, &devInfo.devMaxWorkItemDims, sizeof(cl_uint));
			break;
		case 4:
			std::memcpy(pValue, &devInfo.devMaxWorkGroupSize, sizeof(size_t));
			break;
			//case 5:
			//	std::memcpy(pValue, devInfo.devMaxWorkItemSize, sizeof(size_t));
			//	break;
		case 6:
			std::memcpy(pValue, &devInfo.devPreferredVectorWidth, sizeof(cl_uint));
			break;
		case 7:
			std::memcpy(pValue, &devInfo.devNativeVectorWidth, sizeof(cl_uint));
			break;
		case 8:
			std::memcpy(pValue, &devInfo.devMaxClockFreq, sizeof(cl_uint));
			break;
		case 9:
			std::memcpy(pValue, &devInfo.devAddrBits, sizeof(cl_uint));
			break;
		case 10:
			std::memcpy(pValue, &devInfo.devMaxReadImgArgs, sizeof(cl_uint));
			break;
		case 11:
			std::memcpy(pValue, &devInfo.devMaxWriteImgArgs, sizeof(cl_uint));
			break;
		case 12:
			std::memcpy(pValue, &devInfo.devMaxMemAllocSize, sizeof(cl_ulong));
			break;
		case 13:
			std::memcpy(pValue, &devInfo.devImg2MaxWidth, sizeof(size_t));
			break;
		case 14:
			std::memcpy(pValue, &devInfo.devImg2MaxHeight, sizeof(size_t));
			break;
		case 15:
			std::memcpy(pValue, &devInfo.devImg3MaxWidth, sizeof(size_t));
			break;
		case 16:
			std::memcpy(pValue, &devInfo.devImg3MaxHeight, sizeof(size_t));
			break;
		case 17:
			std::memcpy(pValue, &devInfo.devImg3MaxDepth, sizeof(size_t));
			break;
		case 18:
			std::memcpy(pValue, &devInfo.devImgSupport, sizeof(cl_bool));
			break;
		case 19:
			std::memcpy(pValue, &devInfo.devMaxArgsSize, sizeof(size_t));
			break;
		case 20:
			std::memcpy(pValue, &devInfo.devMaxSamples, sizeof(cl_uint));
			break;
		case 21:
			std::memcpy(pValue, &devInfo.devMemBaseAddrAlign, sizeof(cl_uint));
			break;
		case 22:
			std::memcpy(pValue, &devInfo.devFpConfig, sizeof(cl_device_fp_config));
			break;
		case 23:
			std::memcpy(pValue, &devInfo.devDFpConfig, sizeof(cl_device_fp_config));
			break;
		case 24:
			std::memcpy(pValue, &devInfo.devGMemCacheType, sizeof(cl_device_mem_cache_type));
			break;
		case 25:
			std::memcpy(pValue, &devInfo.devGMemCacheLineSize, sizeof(cl_uint));
			break;
		case 26:
			std::memcpy(pValue, &devInfo.devGMemCacheSize, sizeof(cl_ulong));
			break;
		case 27:
			std::memcpy(pValue, &devInfo.devGMemSize, sizeof(cl_ulong));
			break;
		case 28:
			std::memcpy(pValue, &devInfo.devMaxConstBufSize, sizeof(cl_ulong));
			break;
		case 29:
			std::memcpy(pValue, &devInfo.devMaxConstArgs, sizeof(cl_uint));
			break;
		case 30:
			std::memcpy(pValue, &devInfo.devLocalMemType, sizeof(cl_device_local_mem_type));
			break;
		case 31:
			std::memcpy(pValue, &devInfo.devLocalMemSize, sizeof(cl_ulong));
			break;
		case 32:
			std::memcpy(pValue, &devInfo.devErrCorrectSupport, sizeof(cl_bool));
			break;
		case 33:
			std::memcpy(pValue, &devInfo.devProfileTimerResolution, sizeof(size_t));
			break;
		case 34:
			std::memcpy(pValue, &devInfo.devEndianLittle, sizeof(cl_bool));
			break;
		case 35:
			std::memcpy(pValue, &devInfo.devAvailable, sizeof(cl_bool));
			break;
		case 36:
			std::memcpy(pValue, &devInfo.devCompilerAvail, sizeof(cl_bool));
			break;
		case 37:
			std::memcpy(pValue, &devInfo.devExeCaps, sizeof(cl_device_exec_capabilities));
			break;
		case 38:
			std::memcpy(pValue, &devInfo.devQueueProps, sizeof(cl_command_queue_properties));
			break;
		case 39:
			std::memcpy(pValue, devInfo.devName, sizeof(char) * (strlen(devInfo.devName) + 1));
			break;
		case 40:
			std::memcpy(pValue, devInfo.devVendor, sizeof(char) * (strlen(devInfo.devVendor) + 1));
			break;
		case 41:
			std::memcpy(pValue, devInfo.devDrvVersion, sizeof(char) * (strlen(devInfo.devDrvVersion) + 1));
			break;
		case 42:
			std::memcpy(pValue, devInfo.devProfile, sizeof(char) * (strlen(devInfo.devProfile) + 1));
			break;
		case 43:
			std::memcpy(pValue, devInfo.devVersion, sizeof(char) * (strlen(devInfo.devVersion) + 1));
			break;
		case 44:
			std::memcpy(pValue, devInfo.devExtentions, sizeof(char) * (strlen(devInfo.devExtentions) + 1));
			break;
		case 45:
			std::memcpy(pValue, &devInfo.devPlatformId, sizeof(cl_platform_id));
			break;
		case 46:
			std::memcpy(pValue, &devInfo.devHostUniMem, sizeof(cl_bool));
			break;
		case 47:
			std::memcpy(pValue, devInfo.devOpenClCVer, sizeof(char) * (strlen(devInfo.devOpenClCVer) + 1));
			break;
		case 48:
			std::memcpy(pValue, &devInfo.devEndianLittle, sizeof(cl_bool));
			break;
		case 49:
			std::memcpy(pValue, devInfo.devBuiltInKerl, sizeof(char) * (strlen(devInfo.devBuiltInKerl) + 1));
			break;
		case 50:
			std::memcpy(pValue, &devInfo.devImgMaxBufSize, sizeof(size_t));
			break;
		case 51:
			std::memcpy(pValue, &devInfo.devImgMaxArraySize, sizeof(size_t));
			break;
		case 52:
			std::memcpy(pValue, &devInfo.devParentDev, sizeof(cl_device_id));
			break;
		case 53:
			std::memcpy(pValue, &devInfo.devPartMaxSubDevs, sizeof(cl_uint));
			break;
			//case 54:
			//	break;
		case 55:
			std::memcpy(pValue, &devInfo.devPartAffiDomain, sizeof(cl_device_affinity_domain));
			break;
			//case 56:
			//	break;
		case 57:
			std::memcpy(pValue, &devInfo.devReferenceCnts, sizeof(cl_uint));
			break;
		case 58:
			std::memcpy(pValue, &devInfo.devPreferredInteropUserSync, sizeof(cl_bool));
			break;
		case 59:
			std::memcpy(pValue, &devInfo.devPrintfBufSize, sizeof(size_t));
			break;
		}
	}

	void setCurValue(int id, void *pValue)
	{
		this->index  = id;
		switch(index)
		{
		case 0:
			std::memcpy(&devInfo.devType, pValue, sizeof(cl_device_type));
			break;
		case 1:
			std::memcpy(&devInfo.devVendorId, pValue, sizeof(cl_uint));
			break;
		case 2:
			std::memcpy(&devInfo.devMaxCmpUnits, pValue, sizeof(cl_uint));
			break;
		case 3:
			std::memcpy(&devInfo.devMaxWorkItemDims, pValue, sizeof(cl_uint));
			break;
		case 4:
			std::memcpy(&devInfo.devMaxWorkGroupSize, pValue, sizeof(size_t));
			break;
			//case 5:
			//	std::memcpy(pValue, devInfo.devMaxWorkItemSize, sizeof(size_t));
			//	break;
		case 6:
			std::memcpy(&devInfo.devPreferredVectorWidth, pValue, sizeof(cl_uint));
			break;
		case 7:
			std::memcpy(&devInfo.devNativeVectorWidth, pValue, sizeof(cl_uint));
			break;
		case 8:
			std::memcpy(&devInfo.devMaxClockFreq, pValue, sizeof(cl_uint));
			break;
		case 9:
			std::memcpy(&devInfo.devAddrBits, pValue, sizeof(cl_uint));
			break;
		case 10:
			std::memcpy(&devInfo.devMaxReadImgArgs, pValue, sizeof(cl_uint));
			break;
		case 11:
			std::memcpy(&devInfo.devMaxWriteImgArgs, pValue, sizeof(cl_uint));
			break;
		case 12:
			std::memcpy(&devInfo.devMaxMemAllocSize, pValue, sizeof(cl_ulong));
			break;
		case 13:
			std::memcpy(&devInfo.devImg2MaxWidth, pValue, sizeof(size_t));
			break;
		case 14:
			std::memcpy(&devInfo.devImg2MaxHeight, pValue, sizeof(size_t));
			break;
		case 15:
			std::memcpy(&devInfo.devImg3MaxWidth, pValue, sizeof(size_t));
			break;
		case 16:
			std::memcpy(&devInfo.devImg3MaxHeight, pValue, sizeof(size_t));
			break;
		case 17:
			std::memcpy(&devInfo.devImg3MaxDepth, pValue, sizeof(size_t));
			break;
		case 18:
			std::memcpy(&devInfo.devImgSupport, pValue, sizeof(cl_bool));
			break;
		case 19:
			std::memcpy(&devInfo.devMaxArgsSize, pValue, sizeof(size_t));
			break;
		case 20:
			std::memcpy(&devInfo.devMaxSamples, pValue, sizeof(cl_uint));
			break;
		case 21:
			std::memcpy(&devInfo.devMemBaseAddrAlign, pValue, sizeof(cl_uint));
			break;
		case 22:
			std::memcpy(&devInfo.devFpConfig, pValue, sizeof(cl_device_fp_config));
			break;
		case 23:
			std::memcpy(&devInfo.devDFpConfig, pValue, sizeof(cl_device_fp_config));
			break;
		case 24:
			std::memcpy(&devInfo.devGMemCacheType, pValue, sizeof(cl_device_mem_cache_type));
			break;
		case 25:
			std::memcpy(&devInfo.devGMemCacheLineSize, pValue, sizeof(cl_uint));
			break;
		case 26:
			std::memcpy(&devInfo.devGMemCacheSize, pValue, sizeof(cl_ulong));
			break;
		case 27:
			std::memcpy(&devInfo.devGMemSize, pValue, sizeof(cl_ulong));
			break;
		case 28:
			std::memcpy(&devInfo.devMaxConstBufSize, pValue, sizeof(cl_ulong));
			break;
		case 29:
			std::memcpy(&devInfo.devMaxConstArgs, pValue, sizeof(cl_uint));
			break;
		case 30:
			std::memcpy(&devInfo.devLocalMemType, pValue, sizeof(cl_device_local_mem_type));
			break;
		case 31:
			std::memcpy(&devInfo.devLocalMemSize, pValue, sizeof(cl_ulong));
			break;
		case 32:
			std::memcpy(&devInfo.devErrCorrectSupport, pValue, sizeof(cl_bool));
			break;
		case 33:
			std::memcpy(&devInfo.devProfileTimerResolution, pValue, sizeof(size_t));
			break;
		case 34:
			std::memcpy(&devInfo.devEndianLittle, pValue, sizeof(cl_bool));
			break;
		case 35:
			std::memcpy(&devInfo.devAvailable, pValue, sizeof(cl_bool));
			break;
		case 36:
			std::memcpy(&devInfo.devCompilerAvail, pValue, sizeof(cl_bool));
			break;
		case 37:
			std::memcpy(&devInfo.devExeCaps, pValue, sizeof(cl_device_exec_capabilities));
			break;
		case 38:
			std::memcpy(&devInfo.devQueueProps, pValue, sizeof(cl_command_queue_properties));
			break;
		case 39:
			devInfo.devName = new char[strlen((char *)pValue)  + 1];
			std::memcpy(devInfo.devName, pValue, sizeof(char) * (strlen((char *)pValue) + 1));
			break;
		case 40:
			devInfo.devVendor = new char[strlen((char *)pValue) + 1];
			std::memcpy(devInfo.devVendor, pValue, sizeof(char) * (strlen((char *)pValue) + 1));
			break;
		case 41:
			devInfo.devDrvVersion = new char[strlen((char *)pValue) + 1];
			std::memcpy(devInfo.devDrvVersion, pValue, sizeof(char) * (strlen((char *)pValue) + 1));
			break;
		case 42:
			devInfo.devProfile = new char[strlen((char *)pValue)];
			std::memcpy(devInfo.devProfile, pValue, sizeof(char) * strlen((char *)pValue));
			break;
		case 43:
			devInfo.devVersion = new char[strlen((char *)pValue) + 1];
			std::memcpy(devInfo.devVersion, pValue, sizeof(char) * (strlen((char *)pValue) + 1));
			break;
		case 44:
			devInfo.devExtentions = new char[strlen((char *)pValue) + 1];
			std::memcpy(devInfo.devExtentions, pValue, sizeof(char) * (strlen((char *)pValue) + 1));
			break;
		case 45:
			std::memcpy(&devInfo.devPlatformId, pValue, sizeof(cl_platform_id));
			break;
		case 46:
			std::memcpy(&devInfo.devHostUniMem, pValue, sizeof(cl_bool));
			break;
		case 47:
			devInfo.devOpenClCVer = new char[strlen((char *)pValue) + 1];
			std::memcpy(devInfo.devOpenClCVer, pValue, sizeof(char) * (strlen((char *)pValue) + 1));
			break;
		case 48:
			std::memcpy(&devInfo.devEndianLittle,pValue,  sizeof(cl_bool));
			break;
		case 49:
			devInfo.devBuiltInKerl = new char[strlen((char*)pValue) + 1];
			std::memcpy(devInfo.devBuiltInKerl, pValue, sizeof(char) * (strlen((char*)pValue) + 1));
			break;
		case 50:
			std::memcpy(&devInfo.devImgMaxBufSize, pValue, sizeof(size_t));
			break;
		case 51:
			std::memcpy(&devInfo.devImgMaxArraySize, pValue, sizeof(size_t));
			break;
		case 52:
			std::memcpy(&devInfo.devParentDev, pValue, sizeof(cl_device_id));
			break;
		case 53:
			std::memcpy(&devInfo.devPartMaxSubDevs, pValue, sizeof(cl_uint));
			break;
			//case 54:
			//	break;
		case 55:
			std::memcpy(&devInfo.devPartAffiDomain, pValue, sizeof(cl_device_affinity_domain));
			break;
			//case 56:
			//	break;
		case 57:
			std::memcpy(&devInfo.devReferenceCnts, pValue, sizeof(cl_uint));
			break;
		case 58:
			std::memcpy(&devInfo.devPreferredInteropUserSync, pValue, sizeof(cl_bool));
			break;
		case 59:
			std::memcpy(&devInfo.devPrintfBufSize, pValue, sizeof(size_t));
			break;
		}
	}

	void setCurrentIndex(int id){ index = id;}

	int getCurrentSize()
	{
		int len = -1;

		switch(index)
		{
		case 0:
			len = sizeof(cl_device_type);
			break;
		case 1:
			len = sizeof(cl_uint);
			break;
		case 2:
			len = sizeof(cl_uint);
			break;
		case 3:
			len = sizeof(cl_uint);
			break;
		case 4:
			len = sizeof(size_t);
			break;
			//case 5:
			//	std::memcpy(pValue, devInfo.devMaxWorkItemSize, sizeof(size_t));
			//	break;
		case 6:
			len = sizeof(cl_uint);
			break;
		case 7:
			len = sizeof(cl_uint);
			break;
		case 8:
			len = sizeof(cl_uint);
			break;
		case 9:
			len = sizeof(cl_uint);
			break;
		case 10:
			len = sizeof(cl_uint);
			break;
		case 11:
			len = sizeof(cl_uint);
			break;
		case 12:
			len = sizeof(cl_ulong);
			break;
		case 13:
			len = sizeof(size_t);
			break;
		case 14:
			len = sizeof(size_t);
			break;
		case 15:
			len = sizeof(size_t);
			break;
		case 16:
			len = sizeof(size_t);
			break;
		case 17:
			len = sizeof(size_t);
			break;
		case 18:
			len = sizeof(cl_bool);
			break;
		case 19:
			len = sizeof(size_t);
			break;
		case 20:
			len = sizeof(cl_uint);
			break;
		case 21:
			len = sizeof(cl_uint);
			break;
		case 22:
			len = sizeof(cl_device_fp_config);
			break;
		case 23:
			len = sizeof(cl_device_fp_config);
			break;
		case 24:
			len = sizeof(cl_device_mem_cache_type);
			break;
		case 25:
			len = sizeof(cl_uint);
			break;
		case 26:
			len = sizeof(cl_ulong);
			break;
		case 27:
			len = sizeof(cl_ulong);
			break;
		case 28:
			len = sizeof(cl_ulong);
			break;
		case 29:
			len = sizeof(cl_uint);
			break;
		case 30:
			len = sizeof(cl_device_local_mem_type);
			break;
		case 31:
			len = sizeof(cl_ulong);
			break;
		case 32:
			len = sizeof(cl_bool);
			break;
		case 33:
			len = sizeof(size_t);
			break;
		case 34:
			len = sizeof(cl_bool);
			break;
		case 35:
			len = sizeof(cl_bool);
			break;
		case 36:
			len = sizeof(cl_bool);
			break;
		case 37:
			len = sizeof(cl_device_exec_capabilities);
			break;
		case 38:
			len = sizeof(cl_command_queue_properties);
			break;
		case 39:
			len = sizeof(char) * MAXSIZE;
			break;
		case 40:
			len = sizeof(char) * MAXSIZE;
			break;
		case 41:
			len = sizeof(char) * MAXSIZE;
			break;
		case 42:
			len = sizeof(char) * MAXSIZE;
			break;
		case 43:
			len = sizeof(char) * MAXSIZE;
			break;
		case 44:
			len = sizeof(char) * MAXSIZE;
			break;
		case 45:
			len = sizeof(cl_device_type);
			break;
		case 46:
			len = sizeof(cl_bool);
			break;
		case 47:
			len = sizeof(char) * MAXSIZE;
			break;
		case 48:
			len = sizeof(cl_bool);
			break;
		case 49:
			len = sizeof(char) * MAXSIZE;
			break;
		case 50:
			len = sizeof(size_t);
			break;
		case 51:
			len = sizeof(size_t);
			break;
		case 52:
			len = sizeof(cl_device_id);
			break;
		case 53:
			len = sizeof(cl_uint);
			break;
			//case 54:
			//	break;
		case 55:
			len = sizeof(cl_device_affinity_domain);
			break;
			//case 56:
			//	break;
		case 57:
			len = sizeof(cl_uint);
			break;
		case 58:
			len = sizeof(cl_bool);
			break;
		case 59:
			len = sizeof(size_t);
			break;
		}
		return (len);
	}

}TypeDeviceInfoValue;


const int clDeviceType[] = {
	CL_DEVICE_TYPE                           ,    //0
	CL_DEVICE_VENDOR_ID                      ,    //1
	CL_DEVICE_MAX_COMPUTE_UNITS              ,    //2
	CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS       ,    //3
	CL_DEVICE_MAX_WORK_GROUP_SIZE            ,    //4
	//CL_DEVICE_MAX_WORK_ITEM_SIZES            ,    //5	
	CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT     ,    //6
	CL_DEVICE_NATIVE_VECTOR_WIDTH_INT		 ,	  //7
	CL_DEVICE_MAX_CLOCK_FREQUENCY            ,    //8
	CL_DEVICE_ADDRESS_BITS                   ,    //9
	CL_DEVICE_MAX_READ_IMAGE_ARGS            ,    //10
	CL_DEVICE_MAX_WRITE_IMAGE_ARGS           ,    //11
	CL_DEVICE_MAX_MEM_ALLOC_SIZE             ,    //12
	CL_DEVICE_IMAGE2D_MAX_WIDTH              ,    //13
	CL_DEVICE_IMAGE2D_MAX_HEIGHT             ,    //14
	CL_DEVICE_IMAGE3D_MAX_WIDTH              ,    //15
	CL_DEVICE_IMAGE3D_MAX_HEIGHT             ,    //16
	CL_DEVICE_IMAGE3D_MAX_DEPTH              ,    //17
	CL_DEVICE_IMAGE_SUPPORT                  ,    //18
	CL_DEVICE_MAX_PARAMETER_SIZE             ,    //19
	CL_DEVICE_MAX_SAMPLERS                   ,    //20
	CL_DEVICE_MEM_BASE_ADDR_ALIGN            ,    //21
	CL_DEVICE_SINGLE_FP_CONFIG               ,    //22
	CL_DEVICE_DOUBLE_FP_CONFIG				 ,	  //23
	CL_DEVICE_GLOBAL_MEM_CACHE_TYPE          ,    //24
	CL_DEVICE_GLOBAL_MEM_CACHELINE_SIZE      ,    //25
	CL_DEVICE_GLOBAL_MEM_CACHE_SIZE          ,    //26
	CL_DEVICE_GLOBAL_MEM_SIZE                ,    //27
	CL_DEVICE_MAX_CONSTANT_BUFFER_SIZE       ,    //28
	CL_DEVICE_MAX_CONSTANT_ARGS              ,    //29
	CL_DEVICE_LOCAL_MEM_TYPE                 ,    //30
	CL_DEVICE_LOCAL_MEM_SIZE                 ,    //31
	CL_DEVICE_ERROR_CORRECTION_SUPPORT       ,    //32
	CL_DEVICE_PROFILING_TIMER_RESOLUTION     ,    //33
	CL_DEVICE_ENDIAN_LITTLE                  ,    //34
	CL_DEVICE_AVAILABLE                      ,    //35
	CL_DEVICE_COMPILER_AVAILABLE             ,    //36 
	CL_DEVICE_EXECUTION_CAPABILITIES         ,    //37
	CL_DEVICE_QUEUE_PROPERTIES               ,    //38
	CL_DEVICE_NAME                           ,    //39
	CL_DEVICE_VENDOR                         ,    //40
	CL_DRIVER_VERSION                        ,    //41
	CL_DEVICE_PROFILE                        ,    //42
	CL_DEVICE_VERSION                        ,    //43
	CL_DEVICE_EXTENSIONS                     ,    //44
	CL_DEVICE_PLATFORM                       ,    //45
	CL_DEVICE_HOST_UNIFIED_MEMORY            ,    //46
	CL_DEVICE_OPENCL_C_VERSION               ,    //47
	CL_DEVICE_LINKER_AVAILABLE               ,    //48
	CL_DEVICE_BUILT_IN_KERNELS               ,    //49
	CL_DEVICE_IMAGE_MAX_BUFFER_SIZE          ,    //50
	CL_DEVICE_IMAGE_MAX_ARRAY_SIZE           ,    //51
	CL_DEVICE_PARENT_DEVICE                  ,    //52
	CL_DEVICE_PARTITION_MAX_SUB_DEVICES      ,    //53
	//CL_DEVICE_PARTITION_PROPERTIES           ,    //54
	CL_DEVICE_PARTITION_AFFINITY_DOMAIN      ,    //55
	//CL_DEVICE_PARTITION_TYPE                 ,    //56
	CL_DEVICE_REFERENCE_COUNT                ,    //57
	CL_DEVICE_PREFERRED_INTEROP_USER_SYNC    ,    //58
	CL_DEVICE_PRINTF_BUFFER_SIZE             ,    //59
} ;


#endif
