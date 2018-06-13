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

FileManager::FileManager(): batchInputPath(L""), batchOutputPath(L""), toolFileStorePath(L"")
{}

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

short FileManager::init(wstring mySource, wstring myTarget)
//after instantiate must call this function
{
	//1 : success
	//-1: source failed
	//-2 : target failed
	//-3 : both failed
	//todo : 检测路径是否合法
	short result = 1;
	bool setSource = setBatchInputPath(mySource);
	bool setTarget = setBatchExportPath(myTarget);
	if (!setSource && !setTarget)
	{
		result = -3;
	}
	else if (!setSource)
	{
		result = -1;
	}
	else if (!setTarget)
	{
		result = -2;
	}
	else
	{

	}
	return(result);
}

bool  FileManager::setToolFileStoragePath(wstring myStoragePath)
{
	bool result = false;
	toolFileStorePath = myStoragePath;
	return(result);
}

bool FileManager::setBatchInputPath(wstring myPath )
{
	batchInputPath = myPath;
	
	return (true);
}

bool FileManager::setBatchExportPath(wstring myTargetPath)
{
	batchOutputPath = myTargetPath;
	return(true);
}

wstring FileManager::getBatchInputPath()
{
	return (batchInputPath);
}

wstring FileManager::getBatchOutputPath()
{
	return (batchOutputPath);
}

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
		}
		else
		{
			printf("Problem creating directory '\\testtmp'\n");
		}
	}
	
	return(result);
}

bool FileManager::checkPath(wstring myPath)
{
	short result = -1;
	//-1:路径不存在
	//0：已经存在
	//1：成功创建
	const wchar_t * _path = (wchar_t *)myPath.data();
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(_path, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		//ilegal path
		result = -1;
	}
	else if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		//this is a folder
		wcout << L"directory found" << endl;
	}
	else
	{
		//this is a file
		wcout << L"file found" << endl;
	}
}

