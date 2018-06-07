﻿#pragma once
#include "stdafx.h"
#include <map>
#include <string>
//json
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/writer.h"
#include <stdio.h> //json file读

#define EXPORT_PATH "d:/JsonFile.Json"
using namespace std;
using namespace rapidjson;

class Serialize
{
public:
	static void exportObjectID(map<wstring, vector<wstring>> );
	static void importObjectID(map<wstring, vector<wstring>> &, const char *);
	static void exportMap(map <wstring, short>);
	static void importMap(map <wstring, short> & );
	static void exportJsonFile(Document & , const char *  myPath = EXPORT_PATH);
	static void importJsonFile(Document & result, const char *  myPath = EXPORT_PATH);
	//todo: 这里用不用分出去一个类
	static std::string wStringToUTF8(std::wstring);
	static std::wstring UTF8ToWString(std::string);
	static void printUTF8(std::string);
};