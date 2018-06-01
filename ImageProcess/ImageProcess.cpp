// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <wchar.h>  
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
	std::map <std::wstring, short> myMap;
	myMap[L"第一个"] = 0;
	myMap[L"lala"] = 123;
	Serialize :: exportSet(myMap);
	//std::vector < std::wstring > myFolders;
	//myFM->iterateFolder(myFolders, myFM->getRoot());
	//for (std::vector < std::wstring >::iterator it = myFolders.begin(); it != myFolders.end(); it++)
	//{
	//	//wcout << *it << endl;
	//	wstring  myS = *it;
	//	wstring  myT;
	//	myKM->generateObjectID(myS, myT);
	//}
}
