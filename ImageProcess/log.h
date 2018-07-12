#pragma once
#include "stdafx.h"

class Log
{
public:
	static Log * getInstance();
	static void log(std::wstring);
	static void printLog();
	static void exportLog();
	int setLogPath(std::wstring);
	std::wstring getLogPath();
	

private:
	std::vector<std::wstring> toolLog;
	wstring logPath;
	Log();
	static Log * instance;
};