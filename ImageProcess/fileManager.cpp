#pragma once
#include "stdafx.h"
#include "textureSetManager.h"
#include <string>
#include <direct.h>  
#include <stdlib.h>  
#include <stdio.h>
#include <algorithm>  

#define MAX_PROCESS_FOLDER_NUMBER 300

using namespace std;
FileManager* FileManager::instance = nullptr;

FileManager::FileManager(): sourceDir(L""), targetDir(L""), batchInputPath(L""), batchOutputPath(L""), IDJsonPath(L""), keyWordJsonPath(L""), logPath(L"")
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


short FileManager::initDirectory(wstring myFolderNAme)
//after instantiate must call this function
{
	//1 : success
	//-1: source failed
	//-2 : target failed
	//-3 : tool failed

	//取得config位置


	short result = 0;
	bool toolDirSet = setToolConfigPath();
	readIni();

	if (toolDirSet)
	{
		readIni();
		bool sourceCheck;
		bool targetCheck;
		if (sourceDir != L"" && targetDir != L"")
		{
			batchInputPath = sourceDir + L"/" + myFolderNAme;
			batchOutputPath = targetDir + L"/" + myFolderNAme;
			sourceCheck = setBatchInputPath(batchInputPath);
			targetCheck = setBatchExportPath(batchOutputPath);
		}
		if (sourceCheck && targetCheck)
		{
			result = initFile();
		}
	}
	
	return(result);
}

short FileManager::initFile()
//initialize all needed objects from file
{
	short result = 1;
	IDJsonPath = getToolFileStoragePath() +L"/" + IDMAP_JSON;
	keyWordJsonPath = getToolFileStoragePath() +L"/" + KEYWORD_JSON;
	dictionJsonPath = getToolFileStoragePath() + L"/" + DICTION_TXT;
	logPath = getToolFileStoragePath() + L"/" + LOG_TXT;

	
	bool logExist = (checkPath(logPath) == FILE_EXIST);
	bool keyWordExist = (checkPath(keyWordJsonPath) == FILE_EXIST);
	bool idExist = (checkPath(IDJsonPath) == FILE_EXIST);
	bool dictionartExist = (checkPath(dictionJsonPath) == FILE_EXIST);



	if (!logExist)
	{
		createFile(logPath);
	}

	if(!keyWordExist)
	{
		Log::log(L"<error> < FileManager::initFile> <missing file> : " + keyWordJsonPath);
		//outputLog this file 必须存在
		result = -1;
	}

	if (!dictionartExist)
	{
		//outputLog this file 必须存在
		Log::log(L"<error> < FileManager::initFile> <missing file> : " + dictionJsonPath);
		result = -1;
	}
		
	if (!idExist)
	{
		createFile(IDJsonPath);
	}



	if (logExist && keyWordExist && idExist && dictionartExist )
	{
		KeywordManager * myKM = KeywordManager::getInstance();
		Log * myLog = Log::getInstance();
		TextureSetManager * myTM = TextureSetManager::getInstance();

		myKM->initJsonMap(IDJsonPath, keyWordJsonPath, dictionJsonPath);
		myLog->setLogPath(logPath);
		myTM->initTstFile(tstPath);
	}

	return(result);
}

bool  FileManager::readIni()
{

	const wchar_t * _path = (wchar_t *)initDir.c_str();
	string line;
	ifstream inFile;
	bool found = false;

	vector<wstring> myInitVector;

	inFile.open(_path);
	//初始init
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile >> line;
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);

			myInitVector.push_back(Serialize::UTF8ToWString(line));
		}
	}
	inFile.close();
	paseInitFile(myInitVector);
}

bool  FileManager::setToolConfigPath()
{

	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	GetModuleFileName(NULL, szFilePath, MAX_PATH);
	(_tcsrchr(szFilePath, _T('\\')))[1] = 0; // 删除文件名，只获得路径字串
	wstring _path(szFilePath);
	_path += L"config";

	bool result = false;
	if (checkPath(_path) == ILLEGAL_PATH)
	{
		wstring info = L"<error> < FileManager::setInitPath> <ilegal path> : " + _path;
		Log::log(info);
	}
	else
	{

		Log::log(L"set tool folder : " + _path);
		configPath = _path;

		initDir = getToolFileStoragePath() + L"/" + PATH_INI;
		if (checkPath(initDir) == FILE_EXIST)
		{
			result = true;
		}
	}
	return(result);
}

bool FileManager::setBatchInputPath(wstring myPath )
{
	bool result = false;
	if (checkPath(myPath) == ILLEGAL_PATH)
	{
		wstring info = L"< FileManager::setBatchInputPath> ilegal path : "+ batchInputPath;
		Log::log(info);
	}
	else
	{
		batchInputPath = myPath;
		result = true;
		Log::log(L"set source folder : " + batchInputPath);
	}	
	return (result);
}

bool FileManager::setBatchExportPath(wstring myTargetPath)
{
	bool result = false;
	if (checkPath(myTargetPath) == ILLEGAL_PATH)
	{
		wstring info = L"< FileManager::myTargetPath> ilegal path : " + myTargetPath;
		Log::log(info);
	}
	else
	{
		batchOutputPath = myTargetPath;
		Log::log(L"set target folder : " + myTargetPath);
		result = true;
	}
	return(true);
}

wstring FileManager :: getToolFileStoragePath()
{
	return(configPath);
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

//todo: 这里需要换成G2312编码
void FileManager::paseInitFile(vector<wstring> myInit)
{
	for (vector<wstring>::iterator itr = myInit.begin(); itr != myInit.end(); itr++)
	{
		wstring _line = *itr ;
		if (_line.find(L"--") == wstring::npos)
		{
			//wcout << "comment : " << _line;
			//wcout << _line << endl;
			wstring::size_type _equalPos = _line.find(L"=");
			if (_equalPos != wstring::npos)
			{	
				wstring para = _line.substr(0, _equalPos);
				wstring _value = _line.substr(_equalPos+1, _line.size());
				if (para == L"sourcedir")
				{
					sourceDir = _value;
				}
				else if (para == L"targetdir")
				{
					targetDir = _value;
				}
				else if (para == L"tstdir")
				{
					tstPath = _value;
					//targetDir = para;
				}
			}
		}

	}
}

void FileManager::iterateFolder(vector < wstring > & myFiles, vector < wstring > & myFolders,  wstring myTargetFolder, bool mySubFolder)
//mySubFolder == true : iterate subfolder
{
	if ((myTargetFolder.rfind(L"/") != myTargetFolder.size() - 1)&&((myTargetFolder.rfind(L"\\") != myTargetFolder.size() - 1)))
	{
		myTargetFolder = myTargetFolder + L"/";
	}

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
			if (mySubFolder == true)
			{
				wstring mySubTargetFolder = myTargetFolder + myString + L"/";
				iterateFolder(myFiles, myFolders, mySubTargetFolder, mySubFolder);
			}
		}
		else
		{
			//files
			myFiles.push_back(myString);
		}

	} while (FindNextFile(hFind, &ffd) != 0);

	//输出 iterate 结果到 log
}

short FileManager::createFolder(wstring myullPath)
{
	short result = -1;
	//-1:失败
	//0：已经存在
	//1：成功创建
	wstring _targetPath = myullPath;
	if (checkPath(_targetPath) == 2)
	{
		//folder exist
		result = 0;
	}
	else
	{
		const wchar_t * _path = (wchar_t *)_targetPath.c_str();
		//create 
		if (_wmkdir(_path) == 0)
		{
			//created
			result = 1;
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
		result = 2;
	}
	else
	{
		//file exist
		result = 1;
	}
	FindClose(hFind);
	return(result);
}

bool FileManager::createFile(wstring myPath)
{
	bool result = false;
	if (checkPath(myPath) == ILLEGAL_PATH)
	{
		wofstream myFile;
		myFile.open(myPath);
		if(myFile.is_open())
		{
			//myFile <<L" ";
		}
		myFile.close();
		result = true;
	}
	return(result);
}

wstring FileManager::getFileExtion(wstring myFileName)
{
	wstring result = L"";
	transform(myFileName.begin(), myFileName.end(), myFileName.begin(), ::tolower);
	int pos = myFileName.rfind(L".");
	if (pos != string::npos)
	{
		result = myFileName.substr(pos, myFileName.size() - pos);
	}
	return(result);
}