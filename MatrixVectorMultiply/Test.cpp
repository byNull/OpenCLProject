#include "stdafx.h"
#include "mm_mul.h"
#include "mm_vector.h"
#include "mm_weight.h"
#include "OpenCL_MM.h"
#include "common.h"
//#include "logger.h"

extern "C" int R_Size;
extern "C" int C_Size;
extern "C" __declspec(align(32)) char          Matrix[2048][2048];
extern "C" __declspec(align(32)) unsigned char Vector[2048];

//global function declaration
bool compareFileData(std::string fName1, std::string fName2);

int _tmain(int argc, _TCHAR* argv[])
{
	//use to store results
	int r[2048];

	//run on host cpu 
	boost::timer t;
	for(int i = 0; i < MAXSIZE; i++){
		SpMV_NONE(Matrix, Vector, r);
	}
	std::cout << t.elapsed() << " s\n";
	OpenCL_MM::writeDataToFile(r, 2048, "mm.txt");

	//run on Opencl Gpu
	OpenCL_MM mm("openclMM.cl", true);
	mm.executeMM(Matrix, Vector, r, 2048);
	OpenCL_MM::writeDataToFile(r, 2048, "cl_mm.txt");

	bool bEquel = compareFileData("mm.txt", "cl_mm.txt");
	printf("%s\n", (bEquel == true) ? "Equel":"Not equel");

	return 0;
}


bool compareFileData(std::string fName1, std::string fName2)
{
	bool          bEquel = true;
	int           data1 = -1, data2 = -1;
	std::ifstream if1(fName1.c_str());
	std::ifstream if2(fName1.c_str());
	if(!if1.is_open() || !if1.is_open()){
		printf("Can't open file or file is not existed!\n");
		return bEquel;
	}

	while(!if1.eof() && !if2.eof() && (bEquel == true)){
		if1>>data1;
		if2>>data2;
		if(data1 != data2){
			bEquel = false;
		}
	}
	return bEquel;
}

