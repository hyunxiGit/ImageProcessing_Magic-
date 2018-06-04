#pragma once
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

using namespace rapidjson;

class Serialize
{
public:
	static void exportObjectID(std::map<std::wstring, std::vector<std::wstring>>);
	static void exportMap(std::map <std::wstring, short>);
	static void importMap(std::map <std::wstring, short> & );
	static void exportJsonFile(rapidjson::Document &);
	static void importJsonFeil(rapidjson::Document & result);
	//todo: 这里用不用分出去一个类
	static std::string wStringToUTF8(std::wstring);
	static std::wstring UTF8ToWString(std::string);
	static void printUTF8(std::string);
};