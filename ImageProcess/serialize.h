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
	static void makeJsonObj();
	static void exportMap(std::map <std::wstring, short>);
	static void exportJsonFile(rapidjson::Document &);
	static void importJsonFeil();
	static std::string wStringToUTF8(std::wstring);
	static void printUTF8(std::string);
};