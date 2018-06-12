#pragma once
#include "stdafx.h"

#include <direct.h>  
#include <stdlib.h>  
#include <stdio.h>  

#define MAX_PROCESS_FOLDER_NUMBER 300
using namespace std;
//empty pointer assignment
void logFilesOut(WCHAR **, int);
FileManager* FileManager::instance = nullptr;

FileManager::FileManager()
{
	//todo : 不使用常量使用传入值
	////公司环境
	wstring myroot = L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/";	
	LPCWSTR myTarget = L"d:/MegascansExport/";
	//家里环境
	//wstring myroot = L"F:/我的/surfaces/";
	//LPCWSTR myTarget = L"d:/MegascansExport/";
	setRoot(myroot , myTarget);
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

bool FileManager::setRoot(wstring myPath , wstring myTargetPath)
{
	//检测是否合法
	root = myPath;
	targetRoot = myTargetPath;
	return (true);
}

wstring FileManager::getRoot()
{
	return (root);
}

wstring FileManager::getTargetRoot()
{
	return (targetRoot);
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

short FileManager::createFolder(wstring myFoldersPath)
{
	short result = -1;
	//-1:失败
	//0：已经存在
	//1：成功创建
	const wchar_t * myPath = (wchar_t *)myFoldersPath.data();
	WIN32_FIND_DATA ffd;
	bool rValue = false;
	HANDLE hFind = FindFirstFile(myPath, &ffd);
	if ((hFind != INVALID_HANDLE_VALUE) && (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
	{
		//folder exist
		result = 0;
		wcout << L"this file exists : "<< myFoldersPath  << endl;
	}
	else
	{
		FindClose(hFind);
		//can not find folder, make the folder
		if (_wmkdir(myPath) == 0)
		{
			wcout << L"successfully created : " << myFoldersPath << endl;
			result = 1;
			//system("dir \\testtmp");
			//删除文件夹
			/*if (_wrmdir("\\testtmp") == 0)
			printf("Directory '\\testtmp' was successfully removed\n");
			else
			printf("Problem removing directory '\\testtmp'\n");*/
		}
		else
		{
			printf("Problem creating directory '\\testtmp'\n");
		}
	}
	
	return(result);
}