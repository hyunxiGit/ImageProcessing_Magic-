#pragma once
#include "stdafx.h"
#include <map>
#include <string>

class Serialize
{
public:
	static void makeJsonObj();
	static void exportSet(std::map <std::wstring, short>);
	static void exportJsonFile();
	static void importJsonFeil();
	static std::string WStringToUTF8(const wchar_t*);
	static void printUTF8(std::string);
};