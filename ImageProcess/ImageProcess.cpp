// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "tst.h"
#include "textureSetManager.h"
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

using namespace std;

bool init();
void testFunction();
void getFolderObjectID();
static FileManager * myFM;
static KeywordManager * myKM;
static Log * myLog;
static TextureSetManager * myTM;
int main()
{
	bool initSucess = init();
	if (initSucess)
	{


		//testFunction();
		getFolderObjectID();
	}

	Log::exportLog();
	return 0;
}

bool init()
{
	short result;

	myKM = KeywordManager::getInstance();
	myFM = FileManager::getInstance();
	myLog = Log::getInstance();
	myTM = TextureSetManager::getInstance();

	locale loc("chs");
	wcout.imbue(loc);

	result = myFM->initDirectory(SUBFOLDER);
	return(result != -1);
}

void testFunction()
{
	//wcout <<"my version: "<< myTM->getTstByName(L"MetalRough01").sourceNodes[0].name << endl;

}

void getFolderObjectID()
//batch process one image folder
{
	//result vectors
	std::vector < std::wstring > myResultFolders;
	std::vector < std::wstring > myResultFiles;

	myFM->iterateFolder(myResultFiles, myResultFolders, myFM->getBatchInputPath());
	
	//analyse targetPath ID and generate json File
	std::vector < std::wstring > myObjectID;
	myKM->analyseID(myResultFolders, myObjectID);
	
	//generate objectSet for each Folder
	vector<ObjectSet> objectsSetVector;
	//内存操作
	for (std::vector < std::wstring >::iterator it = myResultFolders.begin(); it != myResultFolders.end(); it++)
	{
		ObjectSet _objSet;
		if (_objSet.init(*it, myFM->getBatchInputPath(), myFM->getBatchOutputPath()))
		{
			if (_objSet.setTst(L"MetalRough01"))
			{
				_objSet.makeTextet();
			}
			objectsSetVector.push_back(_objSet);
		}
	}

	//磁盘操作

	for (vector<ObjectSet> ::iterator itr = objectsSetVector.begin(); itr != objectsSetVector.end(); itr++)
	{
		(*itr).makeObjectTargetFolder();
		(*itr).exportAsset(true,true);
	}
}
