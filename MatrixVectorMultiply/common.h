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


#endif
