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
	std::vector < std::wstring > myFiles;
	//TCHAR _root[MAX_PATH] = myFM->getRoot();
	wstring _root = L"e:/nicholas_rwc_jx4_data/depot/JX4_SourceData/Graphics/Megascans/surfaces/";
	myFM->iterateFolder(myFiles, myFolders, _root);

	bool _updateJson = false;
	for (std::vector < std::wstring >::iterator it = myFolders.begin(); it != myFolders.end(); it++)
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
		
		//object folder
		wstring _folderRoot = myFM->getRoot() + *it+L"/";
		std::vector < std::wstring > _subFolders;
		std::vector < std::wstring > _files;

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
		Serialize::exportObjectID(_ObjectIDMap);
	}
}
