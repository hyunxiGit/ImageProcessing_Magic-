#pragma once
#include "stdafx.h"
void KeywordManager::dictionarySearch()
{
	//dictionary feature test
	string search = "humidity";
	string line;
	ifstream inFile;
	bool found = false;
	unsigned int curLine = 0;

	inFile.open("d:/en-dictionary.txt");
	if (!inFile)
	{
		cout << "unable to open file" << endl;
	}
	else
	{
		while (getline(inFile, line))
		{
			curLine++;
			if (line.find(search) != string::npos)
			{
				cout << "found" << endl;
				found = true;
				break;
			}
		}
		cout << found << endl;
	}
}

//用法：
//#define MAX_KEYWORD_SIZE 20
//wchar_t ** _keywordArray = (wchar_t **)malloc(sizeof(wchar_t *) * MAX_KEYWORD_SIZE);
//for (int i = 0; i < MAX_KEYWORD_SIZE; i++)
//{
//	*(_keywordArray + i) = (wchar_t *)malloc(sizeof(wchar_t) * MAX_PATH);
//}
//wchar_t * mySource = (wchar_t *)malloc(sizeof(wchar_t) * MAX_PATH);
//
//
//wcscpy_s(mySource, MAX_PATH, L"j喵jl_asldfkl_汪汪_lkjh_");
//KeywordManager::getKeywords(mySource, _keywordArray, MAX_KEYWORD_SIZE);
//
////释放内存
//for (int i = 0; i < MAX_KEYWORD_SIZE; i++)
//{
//	free(*(_keywordArray + i));
//}
//free(_keywordArray);

void KeywordManager::getKeywords(wchar_t * mySource, wchar_t ** myKeywordArray, int maxKeyword)
{
	int recoded = 0;
	int newChar = 0;
	for (int i = 0; i < MAX_PATH; i++)
	{
		// 存储空间不够
		if (recoded > maxKeyword)
		{
			break;
		}
		//不是第一个字符
		if (mySource[i] == '\0')
		{
			if (newChar != 0)
			{
				myKeywordArray[recoded][newChar] = '\0';
				newChar = 0;
				recoded++;
			}
			break;
		}
		//不是第一个字符
		if (mySource[i] == '_')
		{
			if (newChar != 0)
			{
				myKeywordArray[recoded][newChar] = '\0';
				newChar = 0;
				recoded++;
			}
		}
		else
		{
			myKeywordArray[recoded][newChar] = mySource[i];
			newChar++;
		}
		//std :: wcout << mySource[i] << endl;
	}

	for (int i = 0; i < recoded; i++)
	{
		std::wcout << myKeywordArray[i] << endl;
	}
}