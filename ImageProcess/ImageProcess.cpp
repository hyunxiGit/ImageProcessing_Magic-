// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "tst.h"
#include "textureSetManager.h"
#include "log.h"
#include "fileManager.h"
#include "objectSet.h"
//#include <wchar.h>  
//json temp , should be removed
//#include "rapidjson/document.h"
//#include "rapidjson/filereadstream.h"
//#include "rapidjson/filewritestream.h"
//#include "rapidjson/prettywriter.h"
//#include "rapidjson/writer.h"

#include <stdio.h> //json file读
#include <map>

#include <string.h>
#include <string.h>

#include "Asset2D.h"
#include "image_w.h"

using namespace std;

static FileManager * _FM;
static KeywordManager * _KM;
static Log * _Log;
static TextureSetManager * _TM;

bool init()
{
	bool result;

	_KM = KeywordManager::getInstance();
	_FM = FileManager::getInstance();
	_Log = Log::getInstance();
	_TM = TextureSetManager::getInstance();

	locale loc("chs");
	wcout.imbue(loc);

	result = _FM->initDirectory(SUBFOLDER);
	return(result);
}

void testFunction()
{
}

void generateObjectSet(vector<ObjectSet> & myResult)
{
	//result vectors
	vector < wstring > myResultFolders;
	vector < wstring > myResultFiles;
	_FM->iterateFolder(myResultFiles, myResultFolders, _FM->getBatchInputPath());

	//analyse targetPath ID and generate json File
	map < wstring ,wstring > myIDMap;
	_KM->analyseID(myResultFolders, myIDMap);

	wcout << L"--megascane source folder analyse success." << endl;
	//generate objectSet for each Folder
	//内存操作
	for (map <wstring, wstring>::iterator it = myIDMap.begin(); it != myIDMap.end(); it++)
	{
		ObjectSet _objSet;
			if (_objSet.init(*it, _FM, _KM,_TM))
			{
				myResult.push_back(_objSet);
				
			}
	}
	wcout << L"--target asset info generation success." << endl;
}

void makeTextet(vector<ObjectSet> & myResult , wstring myTstName)
{
	for (vector<ObjectSet>::iterator itr = myResult.begin(); itr != myResult.end(); itr++)
	{
		if ((*itr).setTst(myTstName))
		{
			(*itr).makeTextet();
		}
	}
}

void assetProcess(vector<ObjectSet> & myObjectsSet)
//generate object set from source dir
{	
	//generate object set from source dir
	generateObjectSet(myObjectsSet);
	//make tst
	makeTextet(myObjectsSet, L"MetalRough02");
}

void exportTextet(vector<ObjectSet> myObjSets)
{
	wstring textetExportDir = _FM->getTextetExportDir();
	for (vector<ObjectSet> ::iterator itr = myObjSets.begin(); itr != myObjSets.end(); itr++)
	{
		wcout << L"--export asset to : " << (*itr).getTargetPath() << endl;
		wcout << L"--object ID : " << (*itr).getObjectID() << endl;
		//这里可以开关导出2D素材，是否把textet分开存储
		(*itr).exportTextet(textetExportDir);
	}
}

void export2DAsset(vector<ObjectSet> myObjSets)
{
	for (vector<ObjectSet> ::iterator itr = myObjSets.begin(); itr != myObjSets.end(); itr++)
	{
		wcout << L"--export asset to : " << (*itr).getTargetPath() << endl;
		wcout << L"--object ID : " << (*itr).getObjectID() << endl;
		wcout << L"--object ID : " << (*itr).megaScanId << endl;
		(*itr).makeObjectTargetFolder();
		(*itr).export2D(L".tga");
	}
}


int main()
{
	//testFunction();
	bool initSucess = init();
	if (initSucess)
	{
		wcout << L"--tool initialize success." << endl;
		vector<ObjectSet> objectsSetVector;
		assetProcess(objectsSetVector);
		//export the textet
		exportTextet(objectsSetVector);
		//export 2D asset
		//export2DAsset(objectsSetVector);
	}

	Log::exportLog();
	return 0;
}
