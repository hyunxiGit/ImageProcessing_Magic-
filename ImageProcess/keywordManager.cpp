#pragma once
#include "stdafx.h"
#include "keywordManager.h"

KeywordManager * KeywordManager::instance = nullptr;
KeywordManager::KeywordManager()
{
	strcpy_s(dictionaryPath, MAX_PATH,"d:/en-dictionary.txt");
	wstring line;
	wifstream inFile;
	bool found = false;

	inFile.open(dictionaryPath);
	if (!inFile.is_open())
	{
		std::cout << "KeywordManager :: KeywordManager() : <illegal dictionary path>" << dictionaryPath  << endl;
	}
	else
	{
		while (!inFile.eof())
		{
			inFile >> line;
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);

			this->dictionary.insert(line);
		}
	}
	inFile.close();
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
	bool found = false;

	for (std::set<std::wstring>::iterator it = dictionary.begin(); it != dictionary.end(); it++)
	{
		if (*it == myCheck)
		{
			found = true;
			break;
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

bool KeywordManager::generateObjectID(std::wstring mySource, std::wstring & myID)
{
	//todo:支持查找中文
	//两个英语单词拼接
	//objectID.json..以后要读...2次使用的时候要有以前id的记录

	bool success = true;

	myID = L"";
	bool isKey;
	//wcout << mySource << L", ";
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
	
	if (megaIDCount != 1)
	{
		// problematic asset
		success = false;
		wstring _info = L"KeywordManager :: generateObjectID : < problematic asset >: " + mySource;
		Log::log(_info);
	}
	else
	{
		//succesful asset, generate number
		short number = addId(myID);
		myID = myID +L"_"+ std::to_wstring(number-1);
		//wstring _info = L"success generate object ID : " + mySource;
		//Log::log(_info);
	}
	return(success);
}

short KeywordManager::addId(wstring mySource)
{	
	idMap[mySource] = idMap[mySource] + 1;
	return(idMap[mySource]);
}

KeywordManager::~KeywordManager()
{
	dictionary.clear();
	this->idMap.clear();
}