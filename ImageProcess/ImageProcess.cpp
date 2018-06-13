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

#include "Asset2D.h"
#include "image_w.h"

//公司环境
#define OFFICE_SOURCE_FOLDER L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/"
#define OFFICE_TARGET_FOLDER L"d:/我的/"
//家里环境
#define HOME_SOURCE_FOLDER L"F:/我的/surfaces/"
#define HOME_TARGET_FOLDER L"d:/MegascansExport/"


void init();
void testFunction();
void getFolderObjectID();
static FileManager * myFM;
static KeywordManager * myKM;
int main()
{
	init();
	//getFolderObjectID();
	testFunction();
	
	return 0;
}

void init()
{
	myKM = KeywordManager::getInstance();
	myFM = FileManager::getInstance();

	locale loc("chs");
	wcout.imbue(loc);

	myFM->init(OFFICE_SOURCE_FOLDER, OFFICE_TARGET_FOLDER);
}

void testFunction()
{
	myFM->checkPath(L"D:/work");
}

void getFolderObjectID()
//batch process one image folder
{
	//getHistory  初始化idmap todo : 这个似乎应该放在kwmanager的singleton里面
	map<wstring, vector<wstring>> _ObjectIDMap;
	Serialize::importObjectID(_ObjectIDMap , "d:/test.Json");

	//初始化 KeywordManager -> fileKWMap 
	Serialize::importObjectID(myKM->fileKWMap, "d:/fileKW.json");

	//result vectors
	std::vector < std::wstring > myResultFolders;
	std::vector < std::wstring > myResultFiles;

	//这里看看能不能不用最后一个参数，而在类里面取得实例
	myFM->iterateFolder(myResultFiles, myResultFolders, myFM->getBatchInputPath());

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

		wstring _newfolderPath = myFM->getBatchOutputPath() + _objectID +L"/" ;
		myFM->createFolder(_newfolderPath);

		//object folder
		wstring _folderRoot = myFM->getBatchInputPath() + *it+L"/";
		std::vector < std::wstring > _subFolders;
		std::vector < std::wstring > _files;
		//迭代所有的图片文件
		myFM->iterateFolder(_files, _subFolders, _folderRoot);
		for (std::vector < std::wstring >::iterator it2 = _files.begin(); it2 != _files.end(); it2++)
		{
			//generate files ID
			fileKWStr myKWStr;
			wstring _fileName = myKM->getFileName(_objectID, *it2 , myKWStr);

			//建立对应的2D asset
			if (myKWStr.extension != L".json")
			{
				Asset2D my2DAsset(_folderRoot, *it2, _newfolderPath, _fileName, myKWStr);
				
				if (myKWStr.use != L"")
				{
					
					//转存图片
					my2DAsset.reformat(L".tga");
					my2DAsset.exportAsset();
					
				}
			}

		}

		
	}
	//update json file
	if (_updateJson)
	{
		Serialize::exportObjectID(_ObjectIDMap,"d:/test.json");
	}
}
