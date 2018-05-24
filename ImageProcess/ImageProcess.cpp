// ImageProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
//json
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/writer.h"
#include <stdio.h> //json file读


#pragma comment(lib, "User32.lib")

void dictionarySearch();
void convertImage();
//输出Unicode

void jsonIO();

int main()
{
	//dictionarySearch();
	//fileManagement_iterateFolder();

	//fileManagement_outputUnicode();
	//fileManagement_createFolder();
	//jsonIO();
	fileManager*  myFileManager = fileManager::getInstance();
	cout << myFileManager->test << endl;
	system("pause");
	return 0;
}

void jsonIO()
{
	//字符串建立Json Object___________________________________________
	/*
	rapidjson :: Document document;
	//建立char的json object
	const char json[] = " { \"hello\" : \"world\", \"t\" : true , \"f\" : false, \"n\": null, \"i\":123, \"pi\": 3.1416, \"a\":[1, 2, 3, 4] } ";
	//建立Json文档
	document.Parse(json);
	assert(document.IsObject());
	//取得字符串方法
	assert(document["hello"].IsString());
	printf("hello = %s\n", document["hello"].GetString());
	// 取得bool方法
	assert(document["t"].IsBool());
	printf("t = %s\n", document["t"].GetBool() ? "true" : "false");
	*/


	//读json file___________________________________________
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
	
	//写Json file___________________________________________
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

//	stringSearch();
void dictionarySearch()
{
	//dictionary feature test
	string search = "humidity";
	string line;
	ifstream inFile;
	bool found = false;
	unsigned int curLine = 0;

	inFile.open("d:/en-dictionary.txt");
	if (!inFile)
	{
		cout << "unable to open file" << endl;
	}
	else
	{
		while (getline(inFile, line))
		{
			curLine++;
			if (line.find(search) != string::npos)
			{
				cout << "found" << endl;
				found = true;
				break;
			}
		}
		cout << found << endl;
	}
}

void convertImage()
{
	Image myImg("d:\\oebei_4K_Albedo.jpg");
	myImg.write("d:/oebei_4K_Albedo.tga");
}

