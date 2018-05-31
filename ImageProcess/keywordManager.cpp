﻿#pragma once
#include "stdafx.h"

KeywordManager * KeywordManager::instance = nullptr;
KeywordManager::KeywordManager()
{
	strcpy_s(dictionaryPath, MAX_PATH,"d:/en-dictionary.txt");
}
KeywordManager * KeywordManager::getInstance()
{
	KeywordManager * result; 
	if (instance == nullptr)
	{
		instance = new KeywordManager();
	}
	result = instance;
	return (instance);
}

bool KeywordManager::dictionarySearch(std::wstring myCheck)
{
	std::transform(myCheck.begin(), myCheck.end(), myCheck.begin(), ::tolower);

	wstring line;
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
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);

			if (line == myCheck)
			{
				//cout << "found" << endl;
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
	std::wstring subStr;
	do
	{
		findPos = mySource.find(L"_", startPos);
		
		if (findPos != string::npos)
		{
			subStr = mySource.substr(startPos, (findPos - startPos));
			myKeywordmyKeyword.push_back(subStr);
			//wcout << subStr << endl;
		}
		else if (startPos != 0)
		{
			//last substring
			subStr = mySource.substr(startPos, (mySource.length() - startPos));
			if (subStr != L"")
			{
				//the last char is not '_'
				myKeywordmyKeyword.push_back(subStr);
				//wcout << subStr << endl;
			}
		}
		startPos = findPos + 1;
	} while (startPos != (mySource.length() + 1) && findPos != string::npos);
	
}

void KeywordManager::generateObjectID(std::wstring mySource, std::wstring & myID)
{
	//todo:支持查找中文
	//提高查找效率
	//两个英语单词拼接
	//objectID.json

	myID = L"";
	bool isKey;
	wcout << mySource << L", ";
	//get all the keyword from source in order
	std::vector <std::wstring> _keywordVector;
	getKeywords(mySource, _keywordVector);
	
	int megaIDCount = 0;
	for (std::vector <std::wstring>::iterator it = _keywordVector.begin(); it != _keywordVector.end(); it++)
	{
		//check all of them through dictionary
		
		isKey =  dictionarySearch(*it) ;
		if (isKey)
		{
			//make new temp ID
			if (myID == L"")
			{
				myID = myID + *it;
			}
			else
			{
				myID = myID + L"_" + *it;
			}	
		}
		else
		{
			megaIDCount++;
		}
	}
	
	wcout << myID << endl;
	
	if (megaIDCount != 1)
	{
		wcout << "< problematic asset >: " << mySource << endl;
	}

	//check keyword.txt see if exist and add index number 


	
}