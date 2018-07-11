#pragma once
#include "stdafx.h"

//todo : This class better use vector
using namespace std;
Log * Log::instance = nullptr;
Log * Log::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Log();
	}
	return(instance);
}

Log::Log(){}

void Log::log(std::wstring info)
{
	instance->toolLog.push_back(info);
}

int Log::setLogPath(wstring myPath)
{
	bool result = false;
	if (myPath !=L"")
	{
		logPath = myPath;
		result = true;
	}
	return (result);
}

wstring Log::getLogPath()
{
	return(logPath);
}

void Log::printLog()
{
	Log * _log = getInstance();
	for (std::vector<std::wstring>::iterator it = instance->toolLog.begin(); it != instance->toolLog.end(); it++)
	{
		wcout << *it << endl;
	}
}

void Log::exportLog()
{
	Log * _log = getInstance();

	std::locale chs("chs");
	wofstream outFile;
	outFile.imbue(chs);

	outFile.open(instance->logPath);
	if (outFile.is_open())
	{
		std::vector<std::wstring>::iterator it;
		for (it = instance->toolLog.begin(); it != instance->toolLog.end(); it++)
		{	
			outFile<< *it << endl;
		}
		outFile.close();
	}
}

