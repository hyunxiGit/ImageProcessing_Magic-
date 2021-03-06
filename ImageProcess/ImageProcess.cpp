// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include "tst.h"
#include "textureSetManager.h"
#include "log.h"
#include "fileManager.h"
#include "objectSet.h"
#include "Asset2D.h"
#include "image_w.h"
#include "serialize.h"

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

	Log::log(L"This is my first log");

	locale loc("chs");
	wcout.imbue(loc);

	result = _FM->initDirectory();
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
	wstring targetFolderName = _FM->getBatchInputPath();
	wcout << L"--taget folder is : " << targetFolderName << endl;
	_FM->iterateFolder(myResultFiles, myResultFolders, targetFolderName);

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
	wcout << L"--export asset to : " << textetExportDir << endl;

	for (vector<ObjectSet> ::iterator itr = myObjSets.begin(); itr != myObjSets.end(); itr++)
	{
		//wcout << L"--object ID : " << (*itr).getObjectID() << endl;
		//这里可以开关导出2D素材，是否把textet分开存储
		(*itr).exportTextet(textetExportDir);
		wcout << endl;
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



int main(int argc, char**argv)
{
	//命令行参数
	//wstring sourcePath;
	//wstring targetPath;
	//string myArg;

	//locale loc("chs");
	//wcout.imbue(loc);

	//if (argc > 0)
	//{
	//	wcout << L"use 参数" << endl;
	//	for (int i = 0; i < argc; i++)
	//	{
	//		//wcout << argv[i] << endl;
	//		wstring _value = Serialize::mbToWcs(string(argv[i + 1]));
	//		if (string(argv[i]) == "-sp")//source path
	//		{
	//			sourcePath = _value;
	//			wcout << L"source : " << sourcePath << endl;
	//		}
	//		if (string(argv[i]) == "-srp")//source relative Path
	//		{
	//			sourcePath = _value;
	//			wcout << L"source : " << sourcePath << endl;
	//		}
	//		else if (string(argv[i]) == "-ttp")//target texet save path
	//		{
	//			targetPath = _value;
	//			wcout << L"target : " << targetPath << endl;
	//		}
	//	}
	//}
	//else
	//{
	//	wcout << L"use init" << endl;
	//}


	testFunction();
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
	//}
	}
	else
	{
		wcout << L"--tool initialize failed , check log.txt for more detail ";
	}
	Log::exportLog();
	return 0;
}
