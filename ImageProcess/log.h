#pragma once
#include <vector>
#include <string>

class Log
{
public:
	static void logFileIn  (std::vector <std::wstring> &);
	static void logFilesOut (std::vector <std::wstring> &);
};