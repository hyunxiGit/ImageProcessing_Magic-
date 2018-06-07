﻿#pragma once
#include "stdafx.h"
#include "serialize.h"
#include <fstream>
#define EXPORT_PATH "d:/JsonFile.Json"

void Serialize::exportObjectID(map<wstring, vector<wstring>> myObjectIDMap)
{
	//把指定的<objectID : [megaID, megaID, ...]> 输出为 json格式
	//todo : debug 检测， keywordmanager 输出相应的 map格式
	//<Vector>
	Document _document;
	Document::AllocatorType &allocator = _document.GetAllocator();
	_document.SetObject();

	for (map<wstring, vector<wstring>>::iterator itr = myObjectIDMap.begin(); itr != myObjectIDMap.end(); itr++)
	{
		Value _objectId;
		string _objectIdString = Serialize::wStringToUTF8(itr->first);
		//todo: 找一下更简洁的方法
		//产生一个json能用的string value
		//string 转 字符串数组
		const char * _cha = _objectIdString.c_str();
		char buffer[260];
		int _len = sprintf_s(buffer, "%s", _cha);
		_objectId.SetString(buffer, _len, allocator);
		
		Value _array(kArrayType);

		for (vector<wstring>::iterator itr2 = itr->second.begin(); itr2 != itr->second.end(); itr2++)
		{
			Value _megaScaneID;
			string _megaScaneId = Serialize::wStringToUTF8(*itr2);
			const char * _cha = _megaScaneId.c_str();
			char buffer[260];
			int _len = sprintf_s(buffer, "%s", _cha);
			_megaScaneID.SetString(buffer, _len, allocator);
			_array.PushBack(_megaScaneID, allocator);
		}

		_document.AddMember(_objectId, _array, allocator);
	}

	
	//for (Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr)
	//{
	//	const char * _key = itr->name.GetString();
	//	cout << _key << endl;

	//	const Value& b = _document[_key];
	//	assert(b.IsArray());
	//	for (SizeType i = 0; i < b.Size(); i++) // 使用 SizeType 而不是 size_t
	//	{
	//		cout << b[i].GetString() << endl;
	//	}
	//}
	//todo : 输出位置
	Serialize::exportJsonFile(_document,"d:/test.Json");
}

void Serialize::importObjectID(map<wstring, vector<wstring>> & result, const char * myFilePath)
{
	//import json 到 <objectID : [megaID, megaID, ...]> 
	//<Vector>

	rapidjson::Document _document;
	//todo : path 修改
	Serialize::importJsonFile(_document, myFilePath);

	for (Value::ConstMemberIterator itr = _document.MemberBegin(); itr != _document.MemberEnd(); ++itr)
	{
		wstring _wObjectID = Serialize::UTF8ToWString(itr->name.GetString());
		vector<wstring> _megaScanID;

		const Value& _a = itr->value;
		for (Value::ConstValueIterator itrA = _a.Begin(); itrA != _a.End(); itrA++)
		{
			wstring _megaID = Serialize::UTF8ToWString((itrA->GetString()));
			_megaScanID.push_back(_megaID);
		}
		result[_wObjectID] = _megaScanID;
	}
}

void Serialize::exportMap(std::map <std::wstring, short> myMap)
{
	Document document;
	Document::AllocatorType &allocator = document.GetAllocator();
	document.SetObject();
	for (std::map <std::wstring, short>::iterator it = myMap.begin(); it != myMap.end(); it++)
	{
		Value objectId;
		string myID = Serialize::wStringToUTF8(it->first);	
		const char * myCha = myID.c_str();//string 转 字符串数组
		char buffer[260];
		int len = sprintf_s(buffer, "%s", myCha);

		short myIndex = it->second;
		//document.AddMember(myID, myIndex, allocator);
		objectId.SetString(buffer, len, document.GetAllocator());
		document.AddMember(objectId, myIndex, document.GetAllocator());
	}
	Serialize ::exportJsonFile(document);
}

void Serialize::importMap(std::map <std::wstring, short> & result)
{
	//todo : 现在这个东西还只支持  string : int 的格式，以后可能需要转换为多type支持
	rapidjson::Document _document;
	Serialize::importJsonFile(_document);

	printf ("_document.IsObject() : %i", _document.IsObject());

	for (Value::ConstMemberIterator itr = _document.MemberBegin(); itr!= _document.MemberEnd(); ++itr)
	{
		string _key = itr->name.GetString();
		short _value = itr->value.GetInt();

		wstring _wKey = Serialize::UTF8ToWString(_key);
		result[_wKey] = _value;
	}
}

void Serialize::importJsonFile(Document & result , const char * myPath)
{
	//support both ASKII and Unicode
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, myPath, "r ");
	if (err == 0)
	{
		//printf("File open: %s\n", myPath);
	}
	else
	{
		printf("[error] File open: %s\n", myPath);
	}
	char readBuffer[65536];
	rapidjson :: FileReadStream is(fp, readBuffer, sizeof(readBuffer));

	result.ParseStream(is);
	fclose(fp);
}

void Serialize :: exportJsonFile(rapidjson::Document & myDoc, const char * myPath)
{
	// Serialize::exportJsonFile(document);
	StringBuffer buffer;
	PrettyWriter<StringBuffer>  writer(buffer);
	myDoc.Accept(writer);

	std::string strJson = buffer.GetString();

	wofstream myLog;
	myLog.open(myPath, ios::trunc);
	if (myLog.is_open())
	{
		myLog << buffer.GetString() << endl;
	}
}

void makeJsonObj()
{
	//处理使用 string variable 的例子
	Document document;
	Document::AllocatorType &allocator = document.GetAllocator();

	Value author;
	string myStr = "lalaji";
	const char * myCha = myStr.c_str();//string 转 字符串数组
	char buffer[10];
	int len = sprintf_s(buffer, "%s", myStr);
	cout << myCha << endl;

	author.SetString(buffer, len, document.GetAllocator());

	cout << author.GetString() << endl;
	printf("__________");

	Value val(42);                             // 某 Value
	document.AddMember(author, val, document.GetAllocator());
	printf("%i", document[author].GetInt());
	printf("%i", document["lalaji"].GetInt());

}


void makeJsonObj2() 
{
	//字符串建立 json object的例子
	rapidjson :: Document document;
	//建立char的json object
	//const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	const WCHAR* wc = L" { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[\"辣\", \"的\"] } ";
	//转换wchar_t为 char
	_bstr_t b(wc);
	const char* json = b;

	//建立Json文档 这里只能接受char
	document.Parse(json);
	assert(document.IsObject());

	//取得字符串方法
	assert(document["hello"].IsString());
	printf("hello = %s\n", document["hello"].GetString());
	// 取得bool方法
	assert(document["t"].IsBool());
	printf("t = %s\n", document["t"].GetBool() ? "true" : "false");
	const rapidjson :: Value& a = document["a"];
	assert(a.IsArray());
	cout << (a.IsArray());
	for (rapidjson::SizeType i = 0; i < a.Size(); i++) // Uses SizeType instead of size_t
	{
		//wstring myWS = "你好";
		wcout << a[i].GetString() << endl;
		//printf("a[%d] = %d\n", i, a[i].GetInt());
		
	}
}

std::string Serialize::wStringToUTF8(wstring myWString)
{
	wchar_t * lpwcszWString = (wchar_t *)(myWString).c_str();
	char* pElementText;
	int iTextLen = ::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, NULL, 0, NULL, NULL);
	pElementText = new char[iTextLen + 1];
	memset((void*)pElementText, 0, (iTextLen + 1) * sizeof(char));
	::WideCharToMultiByte(CP_UTF8, 0, (LPWSTR)lpwcszWString, -1, pElementText, iTextLen, NULL, NULL);
	std::string strReturn(pElementText);
	delete[] pElementText;
	return strReturn;
}

std::wstring Serialize::UTF8ToWString(string myString)
{
	char * lpcszString = (char *)(myString).c_str();
	int len = strlen(lpcszString);
	int unicodeLen = ::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, NULL, 0);
	wchar_t* pUnicode;
	pUnicode = new wchar_t[unicodeLen + 1];
	memset((void*)pUnicode, 0, (unicodeLen + 1) * sizeof(wchar_t));
	::MultiByteToWideChar(CP_UTF8, 0, lpcszString, -1, (LPWSTR)pUnicode, unicodeLen);
	wstring wstrReturn(pUnicode);
	delete[] pUnicode;
	return wstrReturn;
}


void Serialize::printUTF8(string myUTF8String)
{
	system("chcp 65001"); //设置字符集 （使用SetConsoleCP(65001)设置无效，原因未知）  

	CONSOLE_FONT_INFOEX info = { 0 }; // 以下设置字体  
	info.cbSize = sizeof(info);
	info.dwFontSize.Y = 16; // leave X as zero  
	info.FontWeight = FW_NORMAL;
	wcscpy_s(info.FaceName, L"Consolas");
	SetCurrentConsoleFontEx(GetStdHandle(STD_OUTPUT_HANDLE), NULL, &info);
	printf("%s\n", myUTF8String);
}