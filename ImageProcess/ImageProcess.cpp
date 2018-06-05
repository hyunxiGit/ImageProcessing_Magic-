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
FileManager * myFM;
KeywordManager * myKM;
int main()
{
	init();
	
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

	std::vector < std::wstring > myFolders;
	myFM->iterateFolder(myFolders, myFM->getRoot());
	for (std::vector < std::wstring >::iterator it = myFolders.begin(); it != myFolders.end(); it++)
	{
		//wcout << *it << endl;
		wstring  myS = *it;
		wstring  myT;
		myKM->generateObjectID(myS, myT);
	}
	//Serialize::exportMap(myKM->idMap);
	
	/*std::map <std::wstring, short> _result;
	Serialize::importMap(_result);

	for (std::map <std::wstring, short>::iterator itr = _result.begin(); itr != _result.end(); itr++)
	{
		wcout << itr->first << " , " << itr->second << endl;
	}*/

	

}
