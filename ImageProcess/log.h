#pragma once
#define LOG_PATH  "d:/test.txt"
class Log
{
public:
	static void logFileIn   ( WCHAR ** myNames, int nameCount );
	static void logFilesOut(WCHAR ** myNames, int nameCount);
};