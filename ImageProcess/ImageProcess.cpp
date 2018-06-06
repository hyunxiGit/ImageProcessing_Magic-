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
FileManager * myFM;
KeywordManager * myKM;
int main()
{
	init();
	getFolderObjectID();
	testFunction();
	
	system("pause");
	return 0;
}

void init()
{
	myKM = KeywordManager::getInstance();
	myFM = FileManager::getInstance();

	//公司环境
	LPCWSTR myroot = L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/";
	//家里环境
	//LPCWSTR myroot = L"F:/我的/surfaces/";
	myFM->setRoot(myroot);
}

void testFunction()
{
	//Serialize::exportMap(myKM->idMap);
	
	/*std::map <std::wstring, short> _result;
	Serialize::importMap(_result);

	for (std::map <std::wstring, short>::iterator itr = _result.begin(); itr != _result.end(); itr++)
	{
		wcout << itr->first << " , " << itr->second << endl;
	}*/
}

void getFolderObjectID()
{
	//getHistory 
	map<wstring, vector<wstring>> _ObjectIDMap;
	Serialize::importObjectID(_ObjectIDMap);
	
	//iterate folder
	std::vector < std::wstring > myFolders;
	myFM->iterateFolder(myFolders, myFM->getRoot());

	bool _updateJson = false;
	for (std::vector < std::wstring >::iterator it = myFolders.begin(); it != myFolders.end(); it++)
	{
		wstring  _megaScanId = *it;
		wstring  _objectID = L"";
		wcout << _megaScanId;
		short idState = myKM->getObjectID(_ObjectIDMap,_megaScanId, _objectID);
		if (idState == 2)
		{
			_updateJson = true;
		}
	}
	//update json file
	if (_updateJson)
	{
		Serialize::exportObjectID(_ObjectIDMap);
	}
}
