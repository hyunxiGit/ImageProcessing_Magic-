#pragma once
#include "stdafx.h"

using namespace rapidjson;
void Serialize::makeJsonObj()
{
	Document document;
	document.SetObject();
	Document::AllocatorType &allocator = document.GetAllocator(); //获取分配器
	document.SetObject();
	document.AddMember("ID", 1, allocator);

	printf("%i", document["ID"].GetInt());
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
void Serialize :: exportJsonFile() 
{
	cout << "写Json file___________________________________________" << endl;
	/*
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "d:/我的Json.json", "w");
	if (err == 0)
	{
	printf("The file 'd:/我的Json.json\n");
	}
	else
	{
	printf("The file 'd:/我的Json.json\n");
	}
	rapidjson :: Document d;
	const char json[] = " { \"hello\" : \"世界噜\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	d.Parse(json);
	char writeBuffer[65536];
	rapidjson::FileWriteStream os(fp, writeBuffer, sizeof(writeBuffer));
	rapidjson::Writer<rapidjson::FileWriteStream> writer(os);
	d.Accept(writer);
	fclose(fp);
	*/
}
void Serialize ::importJsonFeil()
{
	cout << "读json file___________________________________________" << endl;
	//support both ASKII and Unicode
	/*
	errno_t err;
	FILE *fp;
	err = fopen_s(&fp, "d:/我的Json.json", "r ");
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
	assert(d["hello"].IsString());
	printf("hello = %s\n", d["hello"].GetString());
	*/
}