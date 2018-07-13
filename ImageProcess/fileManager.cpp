#pragma once
#include "stdafx.h"
#include "textureSetManager.h"
#include "fileManager.h"
#include "serialize.h"
#include "log.h"
#include <direct.h>   
#include <algorithm>  

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

bool FileManager::initDirectory()
{
	//1 : success
	//-1: source failed
	//-2 : target failed
	//-3 : tool failed

	//取得config位置
	bool result = false;
	bool toolDirSet = setToolConfigPath();
	if (!toolDirSet)
	{
		wcout << L"-- config Path initialize failed." << endl;
		return(result);
	}
	wcout << "toolDirSet : " << toolDirSet << endl;
	if (toolDirSet)
	{
		readIni();
	}

	//检测从 initFile 里面读入的信息的正确性
	bool sourceDirGood = checkPath(sourceDir) == FOLDER_EXIST;
	bool targetDirGood = checkPath(targetDir) == FOLDER_EXIST;
	bool tstDirGood = checkPath(tstPath) == FOLDER_EXIST;
	bool textetExportGood = checkPath(textetExportDir) == FOLDER_EXIST;
	bool textetDirGood = sourceDir.find(textetSourceDir) != wstring::npos;
	if (!sourceDirGood)
	{
		Log::log(L"<error> < FileManager::initDirectory> <dir not exist > : WorkingPath.ini -> sourceDir ");
	}
	else
	{
		Log::log(L"set source path");
	}
	Log::log(L"--"+sourceDir);
	if (!targetDirGood)
	{
		Log::log(L"<error> < FileManager::initDirectory> <dir not exist > : WorkingPath.ini -> targetDir" );
	}
	else
	{
		Log::log(L"set asset target path");
	}
	Log::log(L"--" + targetDir);
	if (!tstDirGood)
	{
		Log::log(L"<error> < FileManager::initDirectory> <dir not exist > : WorkingPath.ini -> tstPath" );
	}
	else
	{
		Log::log(L"set tst folder path");
	}
	Log::log(L"--" + tstPath);
	if (!textetExportGood)
	{
		Log::log(L"<error> < FileManager::initDirectory> <dir not exist > : WorkingPath.ini -> textetExportDir");
	}
	else
	{
		Log::log(L"set textet file export path ");
	}
	Log::log(L"--" + textetExportDir);
	if (!textetDirGood)
	{
		Log::log(L"<error> < FileManager::initDirectory> <illegal path> : WorkingPath.ini -> textetSourceDir" );
	}
	else
	{
		Log::log(L"set textet relative source path");
	}
	Log::log(L"--" + textetSourceDir);
	if (sourceDirGood && targetDirGood && tstDirGood && textetExportGood)
	{
		bool sourceCheck;
		bool targetCheck;
		bool keyWordExist;
		bool logExist;
		bool idExist;
		bool dictionartExist;
		bool nameUsageExist;

		if (sourceDir != L"" && targetDir != L"")
		{
			batchInputPath = sourceDir;
			batchOutputPath = targetDir;
			if (checkPath(batchOutputPath) == ILLEGAL_PATH)
			{
				createFolder(batchOutputPath);
				Log::log(L"Create folder for asset output : "+ batchOutputPath);
			}
			sourceCheck = setBatchInputPath(batchInputPath);
			targetCheck = setBatchExportPath(batchOutputPath);
		}
		if (sourceCheck && targetCheck)
		{
			keyWordExist = (checkPath(keyWordJsonPath) == FILE_EXIST);
			idExist = (checkPath(IDJsonPath) == FILE_EXIST);
			dictionartExist = (checkPath(dictionJsonPath) == FILE_EXIST);
			nameUsageExist = (checkPath(usageNamePath) == FILE_EXIST);


			if (!idExist)
			{
				createFile(IDJsonPath);
				idExist = true;
			}

			if (!keyWordExist)
			{
				Log::log(L"<error> < FileManager::initFile> <missing file> : " + keyWordJsonPath);
				//outputLog this file 必须存在
				result = false;
			}

			if (!dictionartExist)
			{
				//outputLog this file 必须存在
				Log::log(L"<error> < FileManager::initFile> <missing file> : " + dictionJsonPath);
				result = false;
			}

			if (!nameUsageExist)
			{
				//name usage file 必须存在
				Log::log(L"<error> < FileManager::initFile> <missing file> : " + usageNamePath);
				result = false;
			}


			if (keyWordExist && idExist && dictionartExist && nameUsageExist)
			{
				KeywordManager * myKM = KeywordManager::getInstance();
				Log * myLog = Log::getInstance();
				TextureSetManager * myTM = TextureSetManager::getInstance();

				myKM->initJsonMap(IDJsonPath, keyWordJsonPath, dictionJsonPath, usageNamePath);

				myTM->initFile(tstPath, textetSourceDir, textetDestDir);

				result = true;
			}
		}
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
			//这里有个路径转化大小写。。。
			//std::transform(line.begin(), line.end(), line.begin(), ::tolower);
			myInitVector.push_back(Serialize::UTF8ToWString(line));
		}
	}
	inFile.close();
	paseInitFile(myInitVector);
}

bool  FileManager::setToolConfigPath()
{
	wstring configFolderName = L"config";
	//取得本工具下config folder

	TCHAR szFilePath[MAX_PATH + 1] = { 0 };
	_wgetcwd(szFilePath, MAX_PATH);

	wstring _path(szFilePath);

	//get module path
	//GetModuleFileName(NULL, szFilePath, MAX_PATH);
	//wstring _path(szFilePath);
	
	_path = _path + L"\\config" ;

	bool result = false;
	if (checkPath(_path) == ILLEGAL_PATH)
	{
		wstring info = L"<error> < FileManager::setInitPath> <ilegal path> : \n--" + _path;
		Log::log(info);
	}
	else
	{
		Log::log(L"set tool folder : " + _path);
		configPath = _path;

		//init log
		logPath = configPath + L"\\" + L"log.txt";
		bool logExist = (checkPath(logPath) == FILE_EXIST);
		if (!logExist)
		{
			logExist = createFile(logPath);
		}
		if (logExist)
		{
			Log* _myLog = Log::getInstance();
			_myLog->setLogPath(logPath);
		}
		else
		{
			wcout << "--can not create Log file :" << logPath << endl;
		}

		initDir = getToolFileStoragePath() + L"/" + PATH_INI;
		if (checkPath(initDir) == FILE_EXIST)
		{
			Log::log(L"set tool folder : " + _path);
			result = true;
		}
		else
		{
			wstring info = L"<error> < FileManager::setInitPath> <missing file> : \n--" + initDir;
			Log::log(info);
		}	
	}
	return(result);
}

bool FileManager::setBatchInputPath(wstring myPath )
{
	bool result = false;
	if (checkPath(myPath) == ILLEGAL_PATH)
	{
		wstring info = L"< FileManager::setBatchInputPath> ilegal path : \n-- "+ batchInputPath;
		Log::log(info);
	}
	else
	{
		batchInputPath = myPath;
		result = true;
		Log::log(L"set source folder : \n--" + batchInputPath);
	}	
	return (result);
}

bool FileManager::setBatchExportPath(wstring myTargetPath)
{
	bool result = false;
	if (checkPath(myTargetPath) == ILLEGAL_PATH)
	{
		wstring info = L"< FileManager::myTargetPath> ilegal path : \n--" + myTargetPath;
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

wstring FileManager :: getToolFileStoragePath() {		return(configPath);		}

wstring FileManager::getBatchInputPath(){	return (batchInputPath);	}

wstring FileManager::getBatchOutputPath(){   return (batchOutputPath);	}

wstring FileManager::getIDJasonPath(){	return(IDJsonPath);		}

wstring FileManager::getKeywordJsonPath(){	return(keyWordJsonPath); }

wstring FileManager::getDictionTxtPath(){	return(dictionJsonPath);	}

wstring FileManager::getUsageNameJsonPath(){	return(usageNamePath);}

wstring FileManager::getTextetExportDir() { return(textetExportDir); }

wstring FileManager::getTextetSourceDir() { return(textetSourceDir); }

wstring FileManager::getTextetDestDir() { return(textetDestDir); }

wstring FileManager::getSubFolder() {return(subFolder);}

//todo: 加读ini的api不使用自己解析
void FileManager::paseInitFile(vector<wstring> myInit)
{
	for (vector<wstring>::iterator itr = myInit.begin(); itr != myInit.end(); itr++)
	{
		wstring _line = *itr ;
		if (_line.find(L"--") == wstring::npos)
		{
			wstring::size_type _equalPos = _line.find(L"=");
			if (_equalPos != wstring::npos)
			{	
				wstring para = _line.substr(0, _equalPos);
				wstring _value = _line.substr(_equalPos+1, _line.size());
				if (para == L"sourceDir")
				{
					sourceDir = _value;
				}
				else if (para == L"targetDir")
				{
					targetDir = _value;
				}
				else if (para == L"tstDir")
				{
					tstPath = _value;
				}
				else if (para == L"P4root")
				{
					p4Root = _value;
				}
				else if (para == L"textetSourceDir")
				{
					textetSourceDir = _value;
				}
				else if (para == L"textetDestDir")
				{
					textetDestDir = _value;
				}
				else if (para == L"textetExport")
				{
					textetExportDir = _value;
				}
				else if (para == L"kwJson")
				{
					keyWordJsonPath = configPath + L"/" + _value;
				}
				else if (para == L"idMapJson")
				{
					IDJsonPath = configPath + L"/" + _value;
				}
				else if (para == L"dictTxt")
				{
					dictionJsonPath = configPath + L"/" + _value;
				}
				else if (para == L"usageNameJson")
				{
					usageNamePath = configPath + L"/" + _value;
				}
				else if (para == L"logTxt")
				{
					logPath = configPath + L"/" + _value;
				}
			}
		}

	}
}

void FileManager::iterateFolder(vector < wstring > & myFiles, vector < wstring > & myFolders,  wstring myTargetDir, bool mySubFolder , wstring subPath)
//mySubFolder == true : iterate subfolder
{
	if ((myTargetDir.rfind(L"/") != myTargetDir.size() - 1)&&((myTargetDir.rfind(L"\\") != myTargetDir.size() - 1)))
	{
		myTargetDir = myTargetDir + L"/";
	}

	const TCHAR *t = myTargetDir.c_str();
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
			
			if (mySubFolder != true)
			{
				myFolders.push_back(myString);
			}
			else
			{
				myFolders.push_back(subPath + myString);
				subPath = subPath + myString + L"/";
				wstring mySubTargetFolder = myTargetDir + myString + L"/";
				iterateFolder(myFiles, myFolders, mySubTargetFolder, mySubFolder, subPath);
			}
		}
		else
		{
			//files
			if (mySubFolder != true)
			{
				myFiles.push_back(myString);
			}
			else
			{
				myFiles.push_back(subPath + myString);
			}
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
			result = true;
		}
		myFile.close();
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