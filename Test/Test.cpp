// Test.cpp : Defines the entry point for the console application.


#include "stdafx.h"
#include <stdlib.h>
#include <iostream>
#include <memory.h>

#pragma warning (disable : 4996)
struct A{
	union B{
		int m1;
		int m2;
		char *p1;
		//int[] arr;
	};
private:
	B v;
	int index;

public:
	void setCurValue(int id, void *pv)
	{
		index = id;
		switch (index)
		{
		case 0:
			std::memcpy(&v.m1, pv, sizeof(int));
			break;
		case 1:
			std::memcpy(&v.m2, pv, sizeof(int));
			break;
		case 2:
			v.p1 = new char[strlen((char*)pv) + 1];
			std::memcpy(v.p1, pv, sizeof(char) * (strlen((char*)pv) + 1));
			break;
		default:
			break;
		}
	}
	void getCurValue(void *value)
	{
		if(index == 0)
			std::memcpy(value, &v.m1, sizeof(int));
		else if(index == 1)
			std::memcpy(value, &v.m2, sizeof(int));
		else
			std::memcpy(value, v.p1, sizeof(char) * (strlen(v.p1) + 1));
	}
};
int _tmain(int argc, _TCHAR* argv[])
{
	int i[3];
	std::cout<<sizeof(i)<<std::endl;

	char *pArr;
	char arr[10] = {'a', 'b', 'c', 'd'};
	std::cout<<strlen(arr)<<std::endl;

	pArr = new char[strlen(arr) + 1];
	//strcpy(pArr, arr);
	//std::cout<<pArr<<std::endl;
	//printf("%s\n", pArr);

	int id    = 0;
	int value = 3;
	int ret;
	A   a;
	
	a.setCurValue(2, arr);
	a.getCurValue(pArr);
	std::cout<<pArr<<std::endl;

	//a.setCurValue(id, &value);
	//a.getCurValue(&ret);
	//std::cout<<ret<<std::endl;
	
	return 0;
}

