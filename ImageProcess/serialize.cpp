#pragma once
#include "stdafx.h"
#include "serialize.h"
#include <fstream>
#define EXPORT_PATH "d:/JsonFile.Json"
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

void Serialize::importJsonFeil()
{
	cout << "读json file___________________________________________" << endl;
	//support both ASKII and Unicode
	
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, EXPORT_PATH, "r ");
	if (err == 0)
	{
		printf("The file 'd:/myTestJson.json' was opened\n");
	}
	else
	{
		printf("The file 'd:/myTestJson.json' was not opened\n");
	}
	char readBuffer[65536];
	rapidjson :: FileReadStream is(fp, readBuffer, sizeof(readBuffer));
	rapidjson :: Document d;
	d.ParseStream(is);
	fclose(fp);

	assert(d["Brick_Mud"].IsInt());
	printf("Brick_Mud = %i\n", d["Brick_Mud"].GetInt());
	
}


void Serialize :: exportJsonFile(rapidjson::Document & myDoc)
{
	// Serialize::exportJsonFile(document);
	StringBuffer buffer;
	PrettyWriter<StringBuffer>  writer(buffer);
	myDoc.Accept(writer);

	std::string strJson = buffer.GetString();

	wofstream myLog;
	myLog.open(EXPORT_PATH, ios::app);
	if (myLog.is_open())
	{
		myLog << buffer.GetString() << endl;
	}
}

void Serialize::makeJsonObj()
{
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


void makeJsonObj() 
{
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