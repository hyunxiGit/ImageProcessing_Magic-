// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <wchar.h>  
//json temp , should be removed
#include "rapidjson/document.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/filewritestream.h"
#include "rapidjson/prettywriter.h"
#include "rapidjson/writer.h"
#include <stdio.h> //json file读


void init();
void testFunction();
void getFolderObjectID();
static FileManager * myFM;
static KeywordManager * myKM;
int main()
{
	init();
	getFolderObjectID();
	//testFunction();
	
	return 0;
}

void init()
{
	myKM = KeywordManager::getInstance();
	myFM = FileManager::getInstance();

	locale loc("chs");
	wcout.imbue(loc);

	//公司环境
	wstring myroot = L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/";
	wstring myTarget = L"d:/我的/";
	//家里环境
	//LPCWSTR myroot = L"F:/我的/surfaces/";
	//LPCWSTR myTarget = L"d:/MegascansExport/";
	myFM->setRoot(myroot , myTarget);
}

void testFunction()
{

}

void getFolderObjectID()
{
	//getHistory  初始化idmap todo : 这个似乎应该放在kwmanager的singleton里面
	map<wstring, vector<wstring>> _ObjectIDMap;
	Serialize::importObjectID(_ObjectIDMap , "d:/test.Json");

	//初始化 KeywordManager -> fileKWMap 
	// todo :这里还有点问题 : 现在所有的json读入，输出都是UTF8、不能手动修改，需要支持手动修改
	Serialize::importObjectID(myKM->fileKWMap, "d:/fileKW.json");

	//iterate folder
	std::vector < std::wstring > myResultFolders;
	std::vector < std::wstring > myResultFiles;
	//TCHAR _root[MAX_PATH] = myFM->getRoot();
	//wstring _root = L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/";
	myFM->iterateFolder(myResultFiles, myResultFolders, myFM->getRoot());

	bool _updateJson = false;
	for (std::vector < std::wstring >::iterator it = myResultFolders.begin(); it != myResultFolders.end(); it++)
	{
		//create objectID for subfolder  : _objectID 就是新id
		wstring  _megaScanId = *it;
		wstring  _objectID = L"";
		//wcout << _megaScanId;
		short idState = myKM->getObjectID(_ObjectIDMap,_megaScanId, _objectID);
		wcout << "[" << _megaScanId << " , " << _objectID << " ]" << endl;
		if (idState == 2)
		{
			_updateJson = true;
		}

		if (idState == 0)
		{
			wcout << "***************** error ID *****************" << endl;
		}
		//产生对应的objectID 的文件夹

		wstring _newfolderPath = myFM->getTargetRoot() + _objectID;
		wcout << "_newfolderPath : " << _newfolderPath << endl;
		myFM->createFolder(_newfolderPath);

		//object folder
		wstring _folderRoot = myFM->getRoot() + *it+L"/";
		std::vector < std::wstring > _subFolders;
		std::vector < std::wstring > _files;
		wcout << "here" << endl;
		//迭代所有的图片文件
		myFM->iterateFolder(_files, _subFolders, _folderRoot);
		for (std::vector < std::wstring >::iterator it2 = _files.begin(); it2 != _files.end(); it2++)
		{
			//generate files ID
			wstring _fileName = myKM->getFileName(_objectID, *it2);
		}

		
	}
	//update json file
	if (_updateJson)
	{
		Serialize::exportObjectID(_ObjectIDMap,"d:/test.json");
	}
}
