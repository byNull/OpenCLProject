#ifndef __LOGGER_H__
#define __LOGGER_H__

#pragma once

#include "stdafx.h"

template <typename T>
class Singleton
{
private:
	static std::auto_ptr<T> instance;
	//static CResGuard   _rs;

protected:
	Singleton(void){}
	Singleton(const Singleton &){}
	~Singleton(void){}
	Singleton& operator= (const Singleton &){}

public:
	static inline T* Instance();
};

template<typename T>
std::auto_ptr<T> Singleton<T>::instance;

//static CResGuard   Singleton<T>::_rs;

template <typename T>
inline T* Singleton<T>::Instance()
{
	if(NULL == instance.get()){
		//CResGuard::CGuard gd(_rs);
		if(NULL == instance.get()){
			instance.reset ( new T);
		}
	}
	assert(NULL != instance.get());
	return instance.get();
}

class Logger //: public Singleton<Logger>
{
private:
	FILE *pFile;

public:
	Logger();
	~Logger();
	void OpenLogFile(const char *fileName, bool replaceExisting);
	void Log(const char *msg, ...);

};

typedef Singleton<Logger> Log;

#endif