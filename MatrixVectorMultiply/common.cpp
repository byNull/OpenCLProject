#include "stdafx.h"
#include "common.h"
#include "logger.h"


void GetDateTime(char *buffer) 
{
	struct tm *ptm;
	time_t    t;

	t   = time(NULL);
	ptm = localtime(&t);
	strftime(buffer, sizeof(char) * MAXSIZE, "%Y-%m-%d : %H-%M-%S", ptm);
}

void LogInternal(LogLevel level, const char *format, va_list args)
{
	//static WORD consoleMode[] = {
	//	FOREGROUND_GREEN,
	//	FOREGROUND_GREEN | FOREGROUND_INTENSITY,
	//	//FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_INTENSITY,
	//	FOREGROUND_RED | FOREGROUND_INTENSITY,
	//	FOREGROUND_RED | FOREGROUND_INTENSITY | BACKGROUND_BLUE,
	//};
	static const char *logFormat[] = {
		"[*][%s] %s",
		"[-][%s] %s",
		"[?][%s] %s",
		"[!][%s] %s",
	};
	static const char *prompt[] = {
		"[*] ", "[-] ", "[?] ", "[!] ",
	};

	//WORD wOldMode;
	char dtBuffer[MAXSIZE];
	char buffer[16384];

	GetDateTime(dtBuffer);

	int ncount = 0;
	ncount += sprintf(buffer + ncount, "%s\t", __FILE__);
	ncount += sprintf(buffer + ncount, "%ld\t", __FUNCTION__);
	ncount += sprintf(buffer + ncount, "%ld\t", __LINE__);
	vsprintf(buffer + ncount, format, args);

	//wOldMode = ChangeConsoleMode(consoleMode[level]);
	//printf(prompt[level]);
	//LxChangeConsoleMode( FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
	//printf(buffer);
	//fflush(stdout);
	//ChangeConsoleMode( wOldMode );

	/*
	* Log to file even not in debug mode
	*/
	Log::Instance()->Log(logFormat[level], dtBuffer, buffer);
}

void Info(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	LogInternal(LOG_LEVEL_INFO, format, args);
	va_end(args);
}

void Debug(const char *format, ...) 
{
	va_list args;
	va_start(args, format);
	LogInternal(LOG_LEVEL_DEBUG, format, args);
	va_end(args);
}

void Warning(const char *format, ...) 
{
	va_list args;
	va_start(args, format);
	LogInternal(LOG_LEVEL_WARNING, format, args);
	va_end(args);
}

void Error(const char *format, ...)
{
	va_list args;
	va_start(args, format);
	LogInternal(LOG_LEVEL_FATAL, format, args);
	va_end(args);
}

void Fatal(const char *format, ...) 
{
	va_list args;
	va_start(args, format);
	LogInternal(LOG_LEVEL_FATAL, format, args);
	va_end(args);

	assert(0);
	exit(EXIT_FAILURE);
}


//bool WideToByte(wchar_t* w, char* b, int len)
//{
//	int lenW = wcslen(w);
//	assert( lenW <= len );
//	int lenA = WideCharToMultiByte(CP_ACP, 0, w, lenW, 0, 0, NULL, NULL);
//	assert( lenA <= len );
//	if (lenA > 0) {
//		WideCharToMultiByte(CP_ACP, 0, w, lenW, b, lenA, NULL, NULL);
//		b[lenA] = 0;
//	} else {
//		Fatal("Unable to convert to ANSI string\n");
//		return false;
//	}
//	return true;
//}
//
//bool ByteToWide(char* b, wchar_t* w, int len)
//{
//	int lenA = strlen(b);
//	assert( lenA <= len );
//	int lenW = MultiByteToWideChar(CP_ACP, 0, b, lenA, 0, 0);
//	assert( lenW <= len );
//	if (lenW > 0) {
//		MultiByteToWideChar(CP_ACP, 0, b, lenA, w, lenW);
//		w[lenW] = 0;
//	} else {
//		Fatal("Unable to convert to wide string\n");
//		return false;
//	}
//	return true;
//}
//
//
//WORD ChangeConsoleMode( WORD mode )
//{
//	WORD wOldMode;
//	/*HANDLE hStdOut;
//	CONSOLE_SCREEN_BUFFER_INFO csbiInfo;
//
//	hStdOut = GetStdHandle( STD_OUTPUT_HANDLE );
//	if ( INVALID_HANDLE_VALUE == hStdOut ) {
//		exit( 1 );
//	}
//	if ( !GetConsoleScreenBufferInfo( hStdOut, &csbiInfo ) ) {
//		exit( 1 );
//	}
//	wOldMode = csbiInfo.wAttributes;
//	if ( !SetConsoleTextAttribute( hStdOut, mode ) ) {
//		exit( 1 );
//	}*/
//	return wOldMode;
//}
