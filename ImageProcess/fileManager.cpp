#pragma once
#include "stdafx.h"

FileManager* FileManager::theFileManager = nullptr;

FileManager::FileManager()
{
	test = 10;
}

FileManager* FileManager:: getInstance()
{
	FileManager* result;
	if (theFileManager == nullptr)
	{
		theFileManager = new FileManager();
	}
	result = theFileManager;
	return(theFileManager);
}

//
//void fileManagement_outputUnicode()
//{
//	//method 1 : 使用wprintf
//
//	char scp[16];
//	int cp = GetACP();
//	sprintf_s(scp, ".%d", cp);
//	setlocale(LC_ALL, scp);
//	wprintf(L"测试1234");
//
//	//method 2 : 使用wcout
//	/*
//	locale loc("chs");
//	//locale loc( "Chinese-simplified" );
//	//locale loc( "ZHI" );
//	//locale loc( ".936" );
//	wcout.imbue(loc);
//	std::wcout << L"中国" << endl;
//	*/
//}
//
//void fileManagement_iterateFolder()
//{
//	//输出 unicode
//	//这段代码保证Unicode的输出啊
//	char scp[16];
//	int cp = GetACP();
//	sprintf_s(scp, ".%d", cp);
//	setlocale(LC_ALL, scp);
//	//wprintf(L"测试1234");
//
//	//输出 Unicode 啊
//
//	//iterate folder part
//	HANDLE hFind = INVALID_HANDLE_VALUE;
//	TCHAR szDir[MAX_PATH];
//	WIN32_FIND_DATA ffd;
//	DWORD dwError = 0;
//
//	StringCchCopy(szDir, MAX_PATH, L"d:/");
//	hFind = FindFirstFile(szDir, &ffd);
//	//找所有 文件夹
//	//hFind = FindFirstFile(L"d:\\*.*", &ffd);
//	//找特定的文件
//	hFind = FindFirstFile(L"d:\\我的.txt", &ffd);
//
//	if (INVALID_HANDLE_VALUE == hFind)
//	{
//		//DisplayErrorBox(TEXT("FindFirstFile"));
//		cout << "incorrect" << endl;
//	}
//	do
//	{
//		cout << "find" << endl;
//		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
//		{
//			/*cout << ffd.cFileName;
//			cout << " ";
//			cout << "<DIR>" << endl;*/
//			_tprintf(TEXT("  %s   <DIR>\n"), ffd.cFileName);
//		}
//		else
//		{
//			//cout << ffd.cFileName <<endl;
//			_tprintf(TEXT("  %s   \n"), ffd.cFileName);
//		}
//	} while (FindNextFile(hFind, &ffd) != 0);
//
//}
//
//void fileManagement_createFolder()
//{
//	//support Unicode
//	//CreateDirectory part
//
//	TCHAR szDirName[] = L"D:\\我test";
//	bool flag = CreateDirectory(szDirName, NULL);
//	DWORD ERROR_File_Exist = 183;
//	DWORD err = GetLastError();
//	if (err == ERROR_File_Exist)
//	{
//		cout << "the file already exist" << endl;
//	}
//	cout << "flag: " << flag << endl;
//	cout << "err: " << err << endl;
//}