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

bool KeywordManager::generateObjectID(std::wstring mySource, std::wstring & result)
{
	//todo:支持查找中文
	//两个英语单词拼接
	//objectID.json..以后要读...2次使用的时候要有以前id的记录

	bool success = true;

	result = L"";
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
			if (result == L"")
			{
				result = result + *it;
			}
			else
			{
				result = result + L"_" + *it;
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
		//todo:这一步在最开始就应该有，先查找存在再生成ID
		short number = getIndexNumber(result, mySource);
		result = result +L"_"+ std::to_wstring(number-1);
		//wstring _info = L"success generate object ID : " + mySource;
		//Log::log(_info);
	}
	return(success);
}

short KeywordManager::getIndexNumber(wstring myObjectID , wstring myMegaScaneID)
{	
	short result;

	//读入已经存在的jsonfile进入idMap
	map<wstring, vector<wstring>> _iDMap;
	Serialize::importObjectID(_iDMap);

	map<wstring, vector<wstring>>::iterator itr = _iDMap.find(myObjectID);
	if (itr == _iDMap.end())
	{
		cout << "There's no such object ID" << endl;
		//create new key,  在最后加入idMap
		vector<wstring> _newMegaID;
		_newMegaID.push_back(myMegaScaneID);
		_iDMap[myObjectID] = _newMegaID;
		result = 0;
	}
	else
	{
		cout << "object ID found " <<endl;
		//查找对应 megascan ID Vector 然后 ，查找 是否已经存在
		vector<wstring> _megaScanVector = itr->second ;
		vector<wstring>::iterator itr1;

		std::find(_megaScanVector.begin(), _megaScanVector.end(), myMegaScaneID);
		if (itr1 == _megaScanVector.end())
		{
			//找不到，添加本megascaneID
			_megaScanVector.push_back(myMegaScaneID);
			result = _megaScanVector.size()-1;
			//替换
			_iDMap[myObjectID] = _megaScanVector;
		}
		else
		{
			//找到,取得index
			result = std::distance(_megaScanVector.begin(), itr1);
		}
	}
	 
	//更新json文档
	Serialize::exportObjectID(_iDMap);

	return(result);
}

KeywordManager::~KeywordManager()
{
	dictionary.clear();
	this->idMap.clear();
}