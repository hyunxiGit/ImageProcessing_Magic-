#pragma once
#include "stdafx.h"
bool KeywordManager::dictionarySearch(wchar_t * myCheck)
{

	//const wchar_t * search = L"humidity";

	wchar_t line[MAX_PATH];
	wifstream inFile;
	bool found = false;

	inFile.open("d:/en-dictionary.txt");
	if (!inFile.is_open())
	{ 
		std :: cout << "unable to open file" << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			inFile >> line;
			//wcout << line << endl;

			if (std::wcscmp(line, myCheck) == 0)
			{
				cout << "found" << endl;
				found = true;
				break;
			}
		}
	}

	return (found);
}

void KeywordManager::getKeywords( wstring mySource, std::vector <std::wstring> & myKeywordmyKeyword)
{
	int startPos = 0;
	int findPos = 0;

	do
	{
		findPos = mySource.find(L"_", startPos);
		
		if (findPos != string::npos)
		{
			std::wstring subStr = mySource.substr(startPos, (findPos - startPos));
			wcout << subStr << endl;
		}
		else if (startPos != 0)
		{
			std::wstring subStr = mySource.substr(startPos, (mySource.length() - startPos));
			wcout << subStr << endl;
		}
		startPos = findPos + 1;
		//cout<< "find pos :"<< findPos<<endl;
	} while (startPos != (mySource.length() + 1) && findPos != string::npos);
	
}

//用法：
//wchar_t ** _keywordArray = Utils::make2dArray(MAX_PATH, MAX_KEYWORD_SIZE);
//wchar_t * mySource = (wchar_t *)malloc(sizeof(wchar_t) * MAX_PATH);
//wcscpy_s(mySource, MAX_PATH, L"j喵jl_asldfkl_汪汪_lkjh_");
//KeywordManager::getKeywords(mySource, _keywordArray, MAX_KEYWORD_SIZE);
//Utils::release2dArray(_keywordArray, MAX_KEYWORD_SIZE);


void getKeywords(wchar_t * mySource, wchar_t ** myKeywordArray, int maxKeyword)
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