#include "logger.h"
#include "common.h"

Logger::Logger() : pFile(NULL)
{
	OpenLogFile("mm.log", true);
}

Logger::~Logger()
{
	char dt[64];
	GetDateTime(dt);
	Log("==========Log stopped: %s==========\n\n", dt);
	fclose(pFile);
}	

void Logger::OpenLogFile(const char *fileName, bool replaceExisting)
{
	pFile = fopen(fileName, replaceExisting ? "w" : "a");
	assert(NULL != pFile);
	char dt[64];
	GetDateTime(dt);
	Log("==========Log started: %s==========\n", dt);
}

void Logger::Log(const char *fmt, ...)
{
	assert(NULL != pFile);
	
	va_list args;
	va_start(args, fmt);
	vfprintf(pFile, fmt, args);
	va_end(args);
	fflush(pFile);
}
