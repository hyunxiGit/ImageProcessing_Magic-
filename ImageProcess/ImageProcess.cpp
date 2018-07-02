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
#include <map>

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
	//wcout <<"my version: "<< myTM->getTstByName(L"MetalRough01").sourceNodes[0].name << endl;
	vector<wstring> resultFolder;
	vector<wstring> resultFile;

	wstring _path = L"D:/我的";

	_FM->iterateFolder(resultFile , resultFolder , _path,true );

	for (vector<wstring>::iterator itr = resultFile.begin(); itr != resultFile.end(); itr++)
	{
		wcout << "file : " << *itr << endl;
	}

	for (vector<wstring>::iterator itr = resultFolder.begin(); itr != resultFolder.end(); itr++)
	{
		wcout << "folder : " << *itr << endl;
	}
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

void exportAsset(vector<ObjectSet> myObjSets)
//export target object set,磁盘操作
{
	for (vector<ObjectSet> ::iterator itr = myObjSets.begin(); itr != myObjSets.end(); itr++)
	{
		wcout << L"--export asset to : " << (*itr).getTargetPath() << endl;
		wcout << L"--object ID : " << (*itr).getObjectID() << endl;
		wcout << L"--object ID : " << (*itr).megaScanId << endl;
		(*itr).makeObjectTargetFolder();
		(*itr).exportAsset(true, true);
	}
}

void assetProcess()
//generate object set from source dir
{
	vector<ObjectSet> objectsSetVector;
	//generate object set from source dir
	generateObjectSet(objectsSetVector);
	//make tst
	makeTextet(objectsSetVector, L"MetalRough01");
	//export asset
	exportAsset(objectsSetVector);
}

int main()
{
	bool initSucess = init();
	if (initSucess)
	{
		wcout << L"--tool initialize success." << endl;
		//testFunction();
		assetProcess();
	}

	Log::exportLog();
	return 0;
}
