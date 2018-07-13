#pragma once
#include "stdafx.h"
#include "tst.h"
#include "textet.h"
//json
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/writer.h"

#define EXPORT_PATH "d:/JsonFile.Json"
using namespace std;
using namespace rapidjson;

class Serialize
{
public:
	
	static void exportJson(map<wstring, vector<wstring>> , wstring);
	static bool importJson(map<wstring, vector<wstring>> &, wstring);
	static void exportWstringMapJson(map<wstring, wstring> , wstring);
	static void importWstringMapJson(map<wstring, wstring> &, wstring);
	static bool importTst(wstring, Tst &);
	static void exportTextet(wstring, Textet);
	static void exportJsonFile(Document & , wstring);
	static bool importJsonFile(Document & result, wstring);
	static void setWstring(Value & myValue, Document & doc, wstring myWStr);
	//todo: 这里用不用分出去一个类
	static string wStringToUTF8(std::wstring);
	static wstring UTF8ToWString(std::string);
	static wstring mbToWcs(const string &myString);
	static void printUTF8(std::string);
};