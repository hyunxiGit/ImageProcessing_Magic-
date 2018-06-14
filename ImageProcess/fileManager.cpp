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

FileManager::FileManager(): batchInputPath(L""), batchOutputPath(L""), toolFileStorePath(L""), IDJsonPath(L""), keyWordJsonPath(L"")
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

short FileManager::initDirectory(wstring mySource, wstring myTarget , wstring myToolStoragePath)
//after instantiate must call this function
{
	//1 : success
	//-1: source failed
	//-2 : target failed
	//-3 : tool failed
	short result = 0;
	bool setSource = setBatchInputPath(mySource);
	bool setTarget = setBatchExportPath(myTarget);
	bool setTool = setToolFileStoragePath(myToolStoragePath);
	if (setSource && setTarget && setTool)
	{
		result = 1;
	}
	else if (!setSource)
	{
		result = -1;
	}
	else if (!setTarget)
	{
		result = -2;
	}
	else if (!setTool)
	{
		result = -3;
	}
	return(result);
}

short FileManager::initFile()
{
	short result = -1;
	IDJsonPath = getToolFileStoragePath() +L"/" + IDMAP_JSON;
	keyWordJsonPath = getToolFileStoragePath() +L"/" + KEYWORD_JSON;
	dictionJsonPath = getToolFileStoragePath() + L"/" + DICTION_TXT;
	if (checkPath(IDJsonPath) != FILE_EXIST)
	{
		createFile(IDJsonPath);
	}

	if (checkPath(keyWordJsonPath) == FILE_EXIST && checkPath(IDJsonPath) == FILE_EXIST && checkPath(dictionJsonPath) == FILE_EXIST)
	{
		result = 1;
	}
	return(result);
}

bool  FileManager::setToolFileStoragePath(wstring myStoragePath)
{
	bool result = false;
	if (checkPath(myStoragePath) == ILLEGAL_PATH)
	{
		wcout << L"This path does not exist" << endl;
	}
	else
	{
		toolFileStorePath = myStoragePath;
		result = true;
	}
	return(result);
}

bool FileManager::setBatchInputPath(wstring myPath )
{
	bool result = false;
	if (checkPath(myPath) == ILLEGAL_PATH)
	{
		wcout << L"The source path does not exist" << endl;
	}
	else
	{
		batchInputPath = myPath;
		result = true;
	}	
	return (result);
}

bool FileManager::setBatchExportPath(wstring myTargetPath)
{
	bool result = false;
	if (checkPath(myTargetPath) == ILLEGAL_PATH)
	{
		wcout << L"The target export path does not exist" << endl;
	}
	else
	{
		batchOutputPath = myTargetPath;
		result = true;
	}
	return(true);
}

wstring FileManager :: getToolFileStoragePath()
{
	return(toolFileStorePath);
}

wstring FileManager::getBatchInputPath()
{
	return (batchInputPath);
}

wstring FileManager::getBatchOutputPath()
{
	return (batchOutputPath);
}

wstring FileManager::getIDJasonPath()
{
	return(IDJsonPath);
}

wstring FileManager::getKeywordJsonPath()
{
	return(keyWordJsonPath);
}

wstring FileManager::getDictionTxtPath()
{
	return(dictionJsonPath);
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

short FileManager::createFolder(wstring myPath, wstring myFolderName)
{
	short result = -1;
	//-1:失败
	//0：已经存在
	//1：成功创建
	wstring _targetPath = myPath + L"/"+myFolderName;
	if (checkPath(myPath) != 2)
	{
		//ilegal target path
	}
	else if (checkPath(_targetPath) == 2)
	{
		//folder exist
	}
	else 
	{
		const wchar_t * _path = (wchar_t *)_targetPath.c_str();
		//create 
		if (_wmkdir(_path) == 0)
		{
			//created
		}
		else
		{
			// can not create
		}
	}
	
	return(result);
}

short FileManager::checkPath(wstring myPath)
{
	short result = -1;
	//-1:路径不存在
	//0：
	//1：文件存在
	//2: 文件夹存在
	//3: 文件夹，文件都存在
	//处理字符串
	if (myPath.rfind(L"/") == myPath.size() - 1)
	{
		myPath = myPath.substr(0, myPath.size() - 1);
	}
	const wchar_t * _path = (wchar_t *)myPath.c_str();
	WIN32_FIND_DATA ffd;
	HANDLE hFind = FindFirstFile(_path, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		//ilegal path
		result = -1;
	}
	else if (ffd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
	{
		//path exist
		wcout << L"directory found : " << myPath << endl;
		result = 2;
	}
	else
	{
		//file exist
		wcout << L"file found : " << myPath<< endl;
		result = 1;
	}
	FindClose(hFind);
	return(result);
}

bool FileManager::createFile(wstring myPath)
{
	if (checkPath(myPath) == ILLEGAL_PATH)
	{
		wofstream myFile;
		myFile.open(myPath);
		if(myFile.is_open())
		{
			myFile <<L" ";
		}
		myFile.close();
	}
}