#pragma once

class Log
{
public:
	static void logFileIn   ( WCHAR ** myNames, int nameCount , int & recorded);
	static void logFilesOut(WCHAR ** myNames, int nameCount);
};