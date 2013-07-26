#include "stdafx.h"

//#include <CL/cl.h>
//#include <iostream>
//
//#define  LEN(var) (sizeof(var) / sizeof(int*))
//
//int main()
//{
//	/*int *a = new int[5];
//	for(int i = 0; i < 5; i++){
//	a[i] = i;
//	}
//
//	for (int i = 0; i < 5; i++){
//	printf("a[%d] = %d\t", i, a[i]);
//	}
//	printf("\n");
//
//	delete[] a;*/
//
//	cl_uint        nPlatforms;
//	cl_platform_id *platforms = NULL;
//	cl_int         status;
//	char           *platformInfo = new char[1024];
//
//	status        = clGetPlatformIDs(0, NULL, &nPlatforms);
//	platforms     = new cl_platform_id[nPlatforms];
//	status        = clGetPlatformIDs(nPlatforms, platforms, 0);
//
//
//	for(unsigned int i = 0; i < nPlatforms; i++){
//		clGetPlatformInfo(platforms[i], CL_PLATFORM_VENDOR, 1024, platformInfo, NULL);
//		printf("platform info [CL_PLATFORM_VENDOR] = %s \n", platformInfo);
//
//		clGetPlatformInfo(platforms[i], CL_PLATFORM_VERSION, 1024, platformInfo, NULL);
//		printf("platform info [CL_PLATFORM_VERSION] = %s \n", platformInfo);
//
//		clGetPlatformInfo(platforms[i], CL_PLATFORM_NAME, 1024, platformInfo, NULL);
//		printf("platform info [CL_PLATFORM_NAME] = %s \n", platformInfo);
//
//		clGetPlatformInfo(platforms[i], CL_PLATFORM_PROFILE, 1024, platformInfo, NULL);
//		printf("platform info [CL_PLATFORM_PROFILE] = %s \n", platformInfo);
//
//		clGetPlatformInfo(platforms[i], CL_PLATFORM_EXTENSIONS, 1024, platformInfo, NULL);
//		printf("platform info [CL_PLATFORM_EXTENSIONS] = %s \n", platformInfo);
//	}
//
//	cl_uint      numDevices;
//	cl_device_id *devices = NULL;
//	char         deviceInfo[1024];
//
//	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_CPU, 0, NULL, &numDevices);
//	printf("The number of CL_DEVICE_TYPE_CPU is %d \n", numDevices);
//
//	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
//	printf("The number of CL_DEVICE_TYPE_GPU is %d \n", numDevices);
//
//
//	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ACCELERATOR, 0, NULL, &numDevices);
//	printf("The number of CL_DEVICE_TYPE_ACCELERATOR is %d \n", numDevices);
//
//
//	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_DEFAULT, 0, NULL, &numDevices);
//	printf("The number of CL_DEVICE_TYPE_DEFAULT is %d \n", numDevices);
//
//	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_CUSTOM, 0, NULL, &numDevices);
//	printf("The number of CL_DEVICE_TYPE_CUSTOM is %d \n", numDevices);
//
//	clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, 0, NULL, &numDevices);
//	printf("The number of CL_DEVICE_TYPE_ALL is %d \n", numDevices);
//
//	if(numDevices > 0){
//		devices = new cl_device_id[numDevices];
//		clGetDeviceIDs(platforms[0], CL_DEVICE_TYPE_ALL, numDevices, devices, NULL);
//		
//		printf("\n------------------------Device information is below -----------------------\n\n");
//		for(unsigned int i = 0; i < numDevices; i++){
//			cl_device_type deviceType;
//			clGetDeviceInfo(devices[i], CL_DEVICE_TYPE, sizeof(deviceType), &deviceType, NULL);
//			switch(deviceType)
//			{
//			case CL_DEVICE_TYPE_CPU:
//				printf("Device information [CL_DEVICE_TYPE] is : CL_DEVICE_TYPE_CPU \n");
//				break;
//			case CL_DEVICE_TYPE_GPU:
//				printf("Device information [CL_DEVICE_TYPE] is : CL_DEVICE_TYPE_GPU \n");
//				break;
//			default:
//				printf("Device information [CL_DEVICE_TYPE] is : unknown \n");
//			}
//
//			cl_platform_id platformId;
// 			clGetDeviceInfo(devices[i], CL_DEVICE_PLATFORM, sizeof(platformId), &platformId, NULL);
//			//printf("Device information [CL_DEVICE_PLATFORM] is : %s \n", platformId);
//
//			clGetDeviceInfo(devices[i], CL_DEVICE_NAME, sizeof(deviceInfo), deviceInfo, NULL);
//			printf("Device information [CL_DEVICE_NAME] is : %s \n", deviceInfo);
//
//
//			clGetDeviceInfo(devices[i], CL_DEVICE_VENDOR, sizeof(deviceInfo), deviceInfo, NULL);
//			printf("Device information [CL_DEVICE_VENDOR] is : %s \n", deviceInfo);
//
//			cl_uint vendorId;
//			clGetDeviceInfo(devices[i], CL_DEVICE_VENDOR_ID, sizeof(vendorId), &vendorId, NULL);
//			printf("Device information [CL_DEVICE_VENDOR_ID] is : %d \n", vendorId);
//
//
//			clGetDeviceInfo(devices[i], CL_DEVICE_VERSION, sizeof(deviceInfo), deviceInfo, NULL);
//			printf("Device information [CL_DEVICE_VERSION] is : %s \n", deviceInfo);
//
//			clGetDeviceInfo(devices[i], CL_DEVICE_PROFILE, sizeof(deviceInfo), deviceInfo, NULL);
//			printf("Device information [CL_DEVICE_PROFILE] is : %s \n", deviceInfo);
//
//			cl_uint uUnits;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_COMPUTE_UNITS, sizeof(uUnits), &uUnits, NULL);
//			printf("Device information [CL_DEVICE_MAX_COMPUTE_UNITS] is : %d \n", uUnits);
//
//			cl_uint uItemDim;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS, sizeof(uItemDim), &uItemDim, NULL);
//			printf("Device information [CL_DEVICE_MAX_WORK_ITEM_DIMENSIONS] is : %d \n", uItemDim);
//
//			cl_uint uItemSize;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(uItemSize), &uItemSize, NULL);
//			printf("Device information [CL_DEVICE_MAX_WORK_GROUP_SIZE] is : %d \n", uItemSize);
//
//			cl_uint uGroupSize;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WORK_GROUP_SIZE, sizeof(uGroupSize), &uGroupSize, NULL);
//			printf("Device information [CL_DEVICE_MAX_WORK_GROUP_SIZE] is : %d \n", uGroupSize);
//
//			cl_uint uVectorWidth;
//			clGetDeviceInfo(devices[i], CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT, sizeof(uVectorWidth), &uVectorWidth, NULL);
//			printf("Device information [CL_DEVICE_PREFERRED_VECTOR_WIDTH_INT] is : %d \n", uVectorWidth);
//
//			cl_uint uNativeVectorWidth;
//			clGetDeviceInfo(devices[i], CL_DEVICE_NATIVE_VECTOR_WIDTH_INT, sizeof(uNativeVectorWidth), &uNativeVectorWidth, NULL);
//			printf("Device information [CL_DEVICE_NATIVE_VECTOR_WIDTH_INT] is : %d \n", uNativeVectorWidth);
//
//			cl_uint uClockFreq;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_CLOCK_FREQUENCY, sizeof(uClockFreq), &uClockFreq, NULL);
//			printf("Device information [CL_DEVICE_MAX_CLOCK_FREQUENCY] is : %d \n", uClockFreq);
//
//			cl_uint uAddrBits;
//			clGetDeviceInfo(devices[i], CL_DEVICE_ADDRESS_BITS, sizeof(uAddrBits), &uAddrBits, NULL);
//			printf("Device information [CL_DEVICE_ADDRESS_BITS] is : %d \n", uAddrBits);
//
//			cl_ulong uAllocSize;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_MEM_ALLOC_SIZE, sizeof(uAllocSize), &uAllocSize, NULL);
//			printf("Device information [CL_DEVICE_MAX_MEM_ALLOC_SIZE] is : %ld \n", uAllocSize);
//
//			cl_bool bImageSupport;
//			clGetDeviceInfo(devices[i], CL_DEVICE_IMAGE_SUPPORT, sizeof(bImageSupport), &bImageSupport, NULL);
//			printf("Device information [CL_DEVICE_IMAGE_SUPPORT] is : %d \n", bImageSupport);
//
//			cl_uint uReadImageArgs;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_READ_IMAGE_ARGS, sizeof(uReadImageArgs), &uReadImageArgs, NULL);
//			printf("Device information [CL_DEVICE_MAX_READ_IMAGE_ARGS] is : %d \n", uReadImageArgs);
//	
//			cl_uint uWriteImageArgs;
//			clGetDeviceInfo(devices[i], CL_DEVICE_MAX_WRITE_IMAGE_ARGS, sizeof(uWriteImageArgs), &uWriteImageArgs, NULL);
//			printf("Device information [CL_DEVICE_MAX_WRITE_IMAGE_ARGS] is : %d \n", uWriteImageArgs);
//
//			cl_bool bAvail;
//			clGetDeviceInfo(devices[i], CL_DEVICE_AVAILABLE, sizeof(bAvail), &bAvail, NULL);
//			printf("Device information [CL_DEVICE_AVAILABLE] is : %d \n", bAvail);
//
//			cl_bool bComAvail;
//			clGetDeviceInfo(devices[i], CL_DEVICE_COMPILER_AVAILABLE, sizeof(bComAvail), &bComAvail, NULL);
//			printf("Device information [CL_DEVICE_COMPILER_AVAILABLE] is : %d \n", bComAvail);
//
//			cl_bool uLinkAvail;
//			clGetDeviceInfo(devices[i], CL_DEVICE_LINKER_AVAILABLE, sizeof(uLinkAvail), &uLinkAvail, NULL);
//			printf("Device information [CL_DEVICE_LINKER_AVAILABLE] is : %d \n", uLinkAvail);
//
//			cl_bool uExeAvail;
//			clGetDeviceInfo(devices[i], CL_DEVICE_EXECUTION_CAPABILITIES, sizeof(uExeAvail), &uExeAvail, NULL);
//			printf("Device information [CL_DEVICE_EXECUTION_CAPABILITIES] is : %d \n", uExeAvail);
//
//			cl_command_queue_properties comQueueProperty;
//			clGetDeviceInfo(devices[i], CL_DEVICE_QUEUE_PROPERTIES, sizeof(comQueueProperty), &comQueueProperty, NULL);
//			switch(comQueueProperty)
//			{
//			case CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE:
//				printf("Device information [CL_DEVICE_QUEUE_PROPERTIES] is : CL_QUEUE_OUT_OF_ORDER_EXEC_MODE_ENABLE \n");
//				break;
//			case CL_QUEUE_PROFILING_ENABLE:
//				printf("Device information [CL_DEVICE_QUEUE_PROPERTIES] is : CL_QUEUE_PROFILING_ENABLE \n");
//				break;
//			default:
//				printf("Device information [CL_DEVICE_QUEUE_PROPERTIES] is : unknown \n");
//
//			}
//
//			printf("\n\n");
//		}
//		
//	}
//
//	delete[] platformInfo;
//	if(NULL != devices)		delete[] devices;
//	if(NULL != platforms)	delete[] platforms;
//
//	return 0;
//}
//
//void InitOpenCLInfo()
//{
//	cl_int         status;
//	cl_platform_id *platforms = NULL;
//	cl_device_id   *devices   = NULL;
//	
//	cl_uint        numPlatforms;
//	cl_uint        numDevices;
//
//	status = clGetPlatformIDs(0, NULL, numPlatforms);
//	if(status != CL_SUCCESS)	exit(-1); 
//
//	platforms = new cl_platform_id[numPlatforms];
//	status = clGetPlatformIDs(numPlatforms, platforms, NULL);
//
//	for(unsigned i = 0; i < numPlatforms; i++){
//		status = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, 0, NULL, &numDevices);
//		if(status != CL_SUCCESS)	exit(-1);
//	
//		devices = new cl_device_id[numDevices];
//		status = clGetDeviceIDs(platforms[i], CL_DEVICE_TYPE_GPU, numDevices, devices, NULL);
//		if(status != CL_SUCCESS)	exit(-1);
//
//		clCreateContextFromType(CL_CONTEXT_PLATFORM, CL_DEVICE_TYPE_GPU, NULL, NULL, NULL);
//	}
//}
