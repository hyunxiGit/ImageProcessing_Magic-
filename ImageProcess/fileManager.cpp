#pragma once
#include "stdafx.h"

#define MAX_PROCESS_FOLDER_NUMBER 300
using namespace std;
//empty pointer assignment
void logFilesOut(WCHAR **, int);
FileManager* FileManager::instance = nullptr;

FileManager::FileManager()
{
	////todo : 不使用常量使用传入值
	////公司环境
	wstring myroot = L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/";	
	////家里环境
	////wstring myroot = L"F:/我的/surfaces/";
	setRoot(myroot);
}

FileManager* FileManager:: getInstance()
{
	FileManager* result;
	if (instance == nullptr)
	{
		instance = new FileManager();
	}
	result = instance;
	return(instance);
}

bool FileManager::setRoot(wstring myPath)
{
	root = myPath;
	return (true);
}

wstring FileManager::getRoot()
{
	return (root);
}

//vector string
void FileManager::iterateFolder(vector < wstring > & myFiles, vector < wstring > & myFolders , wstring myTargetFolder )
{
	const TCHAR *t = myTargetFolder.c_str();
	HANDLE hFind = INVALID_HANDLE_VALUE;
	TCHAR szDir[MAX_PATH];
	WIN32_FIND_DATA ffd;
	DWORD dwError = 0;

	//set root
	StringCchCopy(szDir, MAX_PATH, t);

	//set search path
	StringCchCat(szDir, MAX_PATH, L"*.*");
	hFind = FindFirstFile(szDir, &ffd);

	if (INVALID_HANDLE_VALUE == hFind)
	{
		cout << "path can not be found" << endl;
	}

	do
	{
		std::wstring myString = ffd.cFileName;
		if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{
			//folders
			if (lstrcmpW(ffd.cFileName, L".") == 0 || lstrcmpW(ffd.cFileName, L"..") == 0) { continue; }
			myFolders.push_back(myString);
		}
		else
		{
			//files
			myFiles.push_back(myString);
		}

	} while (FindNextFile(hFind, &ffd) != 0);

	//输出 iterate 结果到 log
}

//todo 需要成为filemanager 的成员函数
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