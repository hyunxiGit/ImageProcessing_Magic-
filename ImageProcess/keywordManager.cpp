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


short KeywordManager::getObjectID(map<wstring, vector<wstring>> & myObjectIDMap , std::wstring myMegaScaneID, wstring & result )
{
	//todo:支持查找中文
	//两个英语单词拼接
	
	//0: failed , 1: get the id , 2, make new ID
	short success = 1;

	//检测当前megaScan ID 在 map里是否存在
	map<wstring, vector<wstring>>::iterator _IDMapItr;
	
	bool _idExist = false;
	if (myObjectIDMap.empty()){	}
	for (_IDMapItr = myObjectIDMap.begin(); _IDMapItr != myObjectIDMap.end(); _IDMapItr++)
	{
		vector<wstring> _megaIDVector = _IDMapItr->second;
		vector<wstring>::iterator _megaIDVectorItr = std::find(_megaIDVector.begin(), _megaIDVector.end(), myMegaScaneID);
		if (_megaIDVectorItr == _megaIDVector.end()){}
		else
		{
			//found			
			short _index = distance(_megaIDVector.begin(), _megaIDVectorItr)-1;
			result = *_megaIDVectorItr+L"_"+ std::to_wstring(_index) ;
			_idExist = true;
			break;
		}
	}

	if (_idExist == false)
	{
		success = 2;
		//can not be found generate ID

		result = L"";
		bool isKey;

		//get all the keyword from source in order
		std::vector <std::wstring> _keywordVector;
		getKeywords(myMegaScaneID, _keywordVector);

		int megaIDCount = 0;
		for (std::vector <std::wstring>::iterator it = _keywordVector.begin(); it != _keywordVector.end(); it++)
		{
			//check all of them through dictionary

			isKey = dictionarySearch(*it);
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
			success = 0;
			wstring _info = L"KeywordManager :: generateObjectID : < problematic asset >: " + myMegaScaneID;
			Log::log(_info);
		}
		else
		{
			//succesful asset, generate number
			generateObjectID(myObjectIDMap, myMegaScaneID, result);
			//result = result + L"_" + std::to_wstring(number - 1);
			//wstring _info = L"success generate object ID : " + myMegaScaneID;
			//Log::log(_info);
		}
	}
	

	return(success);
}

void KeywordManager::generateObjectID(map<wstring, vector<wstring>> & myObjectIDMap , wstring myMegaScaneID, wstring & myObjectID )
{	
	short _index;

	map<wstring, vector<wstring>>::iterator itr = myObjectIDMap.find(myObjectID);
	if (itr == myObjectIDMap.end())
	{
		//cout << "There's no such object ID" << endl;
		//create new key,  在最后加入idMap
		vector<wstring> _newMegaID;
		_newMegaID.push_back(myMegaScaneID);
		myObjectIDMap[myObjectID] = _newMegaID;
		_index = 0;
	}
	else
	{
		//cout << "object ID found " <<endl;
		//查找对应 megascan ID Vector 然后 ，查找 是否已经存在
		vector<wstring> _megaScanVector = itr->second ;
		vector<wstring>::iterator itr1 = std::find(_megaScanVector.begin(), _megaScanVector.end(), myMegaScaneID);
		if (itr1 == _megaScanVector.end())
		{
			//找不到，添加本megascaneID
			_megaScanVector.push_back(myMegaScaneID);
			_index = _megaScanVector.size()-1;
			/*wcout << myObjectID << endl;
			wcout << myMegaScaneID << endl;
			wcout << _megaScanVector.size() << endl;*/
			//替换megascen vector
			myObjectIDMap[myObjectID] = _megaScanVector;
		}
		//else
		//{
		//	//找到,取得index
		//	_index = std::distance(_megaScanVector.begin(), itr1);
		//}
	}
	myObjectID = myObjectID + L"_" + std::to_wstring(_index - 1);
}

KeywordManager::~KeywordManager()
{
	dictionary.clear();
	this->idMap.clear();
}