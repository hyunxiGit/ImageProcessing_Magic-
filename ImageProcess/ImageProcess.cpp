// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <vector>

void setLocale();

int main()
{
	setLocale();

	//从log里面读出 folder nmae 并且 切分关键字

	//wchar_t ** _pathArray = Utils::make2dArray(MAX_PATH, MAX_PROCESS_FOLDER_NUMBER);
	//int count = 0;
	//Log::logFileIn(_pathArray , MAX_PROCESS_FOLDER_NUMBER , count);

	//for (int i = 0; i < count; i++)
	//{
	//	//wcout << _pathArray [i] << endl;
	//	wchar_t ** _keywordArray = Utils::make2dArray(MAX_PATH, MAX_KEYWORD_SIZE);
	//	KeywordManager::getKeywords(_pathArray[i], _keywordArray, MAX_KEYWORD_SIZE);
	//	Utils::release2dArray(_keywordArray, MAX_KEYWORD_SIZE);
	//}

	// 字符串 vecor 的测试
	//const wchar_t *  mychar = L"我的";
	//wstring myString = mychar;
	//vector< wstring > v2;

	//v2.push_back(myString);
	//v2.push_back(L"dddd");

	//wcout << v2.at(0) << endl;

	//wchar_t myChar[260];
	//wcscpy_s(myChar, L"humidity");
	//
	//KeywordManager::dictionarySearch(myChar);

	system("pause");
	return 0;
}

void setLocale()
{
	static locale loc("chs");
	wcout.imbue(loc);
}