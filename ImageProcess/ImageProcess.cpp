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
void fileManagement_iterateFolder();
void convertImage();
//输出Unicode
void fileManagement_outputUnicode();
void fileManagement_createFolder();
void jsonIO();

int main()
{
	//dictionarySearch();
	//fileManagement_iterateFolder();

	//fileManagement_outputUnicode();
	//fileManagement_createFolder();
	//jsonIO();
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

void fileManagement_outputUnicode()
{
	//method 1 : 使用wprintf
	
	char scp[16];
	int cp = GetACP();
	sprintf_s(scp, ".%d", cp);
	setlocale(LC_ALL, scp);
	wprintf(L"测试1234");

	//method 2 : 使用wcout
	/*
	locale loc("chs");
	//locale loc( "Chinese-simplified" );
	//locale loc( "ZHI" );
	//locale loc( ".936" );
	wcout.imbue(loc);
	std::wcout << L"中国" << endl;
	*/
}
 
void fileManagement_iterateFolder()
{
	//输出 unicode
	//这段代码保证Unicode的输出啊
	char scp[16];
	int cp = GetACP();
	sprintf_s(scp, ".%d", cp);
	setlocale(LC_ALL, scp);
	//wprintf(L"测试1234");

	//输出 Unicode 啊

	//iterate folder part
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	WIN32_FIND_DATA ffd;
	DWORD dwError = 0;

	StringCchCopy(szDir, MAX_PATH, L"d:/");
	hFind = FindFirstFile(szDir, &ffd);
	//找所有 文件夹
	//hFind = FindFirstFile(L"d:\\*.*", &ffd);
	//找特定的文件
	hFind = FindFirstFile(L"d:\\我的.txt", &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		//DisplayErrorBox(TEXT("FindFirstFile"));
		cout << "incorrect" << endl;
	}
	do
	{
		cout << "find" << endl;
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			/*cout << ffd.cFileName;
			cout << " ";
			cout << "<DIR>" << endl;*/
			_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
		}
		else
		{
			//cout << ffd.cFileName <<endl;
			_tprintf(TEXT("  %s   \n"), ffd.cFileName);
		}
	} while (FindNextFile(hFind, &ffd) != 0);

}

void fileManagement_createFolder()
{
	//support Unicode
	//CreateDirectory part

	TCHAR szDirName[] = L"D:\\我test";
	bool flag = CreateDirectory(szDirName, NULL);
	DWORD ERROR_File_Exist = 183;
	DWORD err = GetLastError();
	if (err == ERROR_File_Exist)
	{
		cout << "the file already exist" << endl;
	}
	cout << "flag: " << flag << endl;
	cout << "err: " << err << endl;
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

