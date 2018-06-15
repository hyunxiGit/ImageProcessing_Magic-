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



bool init();
void testFunction();
void getFolderObjectID();
static FileManager * myFM;
static KeywordManager * myKM;
static Log * myLog;
int main()
{
	bool initSucess = init();
	if (initSucess)
	{
		getFolderObjectID();
		//testFunction();
	}
	Log::exportLog();
	return 0;
}

bool init()
{
	short result;

	myKM  = KeywordManager::getInstance();
	myFM  = FileManager::getInstance();
	myLog = Log::getInstance();

	locale loc("chs");
	wcout.imbue(loc);

	result = myFM->initDirectory(OFFICE_SOURCE_FOLDER, OFFICE_TARGET_FOLDER, OFFICE_TOOL_FOLDER);
	return(result!=-1);
}

void testFunction()
{
}

void getFolderObjectID()
//batch process one image folder
{
	//result vectors
	std::vector < std::wstring > myResultFolders;
	std::vector < std::wstring > myResultFiles;

	myFM->iterateFolder(myResultFiles, myResultFolders, myFM->getBatchInputPath());

	bool _updateJson = false;
	for (std::vector < std::wstring >::iterator it = myResultFolders.begin(); it != myResultFolders.end(); it++)
	{
		//create objectID for subfolder  : _objectID 就是新id
		wstring  _megaScanId = *it;
		wstring  _objectID = L"";
		//wcout << _megaScanId;
		short idState = myKM->getObjectID(myKM->idMap,_megaScanId, _objectID);
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
		myFM->createFolder(myFM->getBatchOutputPath(), _objectID);

		////object folder
		//wstring _folderRoot = myFM->getBatchInputPath() + *it+L"/";
		//std::vector < std::wstring > _subFolders;
		//std::vector < std::wstring > _files;
		////迭代所有的图片文件
		//myFM->iterateFolder(_files, _subFolders, _folderRoot);
		//for (std::vector < std::wstring >::iterator it2 = _files.begin(); it2 != _files.end(); it2++)
		//{
		//	//generate files ID
		//	fileKWStr myKWStr;
		//	wstring _fileName = myKM->getFileName(_objectID, *it2 , myKWStr);

		//	//建立对应的2D asset
		//	if (myKWStr.extension != L".json")
		//	{
		//		Asset2D my2DAsset(_folderRoot, *it2, _newfolderPath, _fileName, myKWStr);
		//		
		//		if (myKWStr.use != L"")
		//		{
		//			
		//			//转存图片
		//			my2DAsset.reformat(L".tga");
		//			my2DAsset.exportAsset();
		//			
		//		}
		//	}

		//}

		
	}
	//update json file
	if (_updateJson)
	{
		Serialize::exportObjectID(myKM->idMap,myFM->getIDJasonPath());
	}
}
