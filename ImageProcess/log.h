#pragma once
#include <vector>
#include <string>

class Log
{
public:
	static Log * getInstance();
	static void logFileIn  (std::vector <std::wstring> &);
	static void logFilesOut (std::vector <std::wstring> &);
	static void log(std::wstring);
	static void printLog();
	static void exportLog();

private:
	char toolLogPath[MAX_PATH];
	std::vector<std::wstring> toolLog;
	Log();
	static Log * instance;
};