// ImageProcess.cpp : Defines the entry point for the console application.
//
#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void wchatTestFunction();
void localization();

int main()
{
	localization();
	//fileManager 的 singleton 
	FileManager*  myFileManager = FileManager::getInstance();
	myFileManager->iterateFolder();


	//测试查找char*中的 "_"
	//最多支持20个keyword
	//#define MAX_KEYWORD_SIZE 20
	//wchar_t ** _keywordArray = (wchar_t **)malloc(sizeof(wchar_t *) * MAX_KEYWORD_SIZE);
	//for (int i = 0; i < MAX_KEYWORD_SIZE; i++)
	//{
	//	*(_keywordArray + i) = (wchar_t *)malloc(sizeof(wchar_t) * MAX_PATH);
	//}
	//wchar_t * mySource = (wchar_t *)malloc(sizeof(wchar_t) * MAX_PATH);
	//wcscpy_s(mySource, MAX_PATH, L"j喵jl_asldfkl_汪汪_lkjh_");
	//KeywordManager :: getKeywords(mySource, _keywordArray, MAX_KEYWORD_SIZE);
	////释放内存
	//for (int i = 0; i < MAX_KEYWORD_SIZE; i++)
	//{
	//	free(*(_keywordArray + i));
	//}
	//free(_keywordArray);


	//wchatTestFunction();
	system("pause");
	return 0;
}

void localization()
{
	locale loc("chs");
	wcout.imbue(loc);
}
