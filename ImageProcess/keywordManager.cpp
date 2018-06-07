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

void KeywordManager::getKeywords( wstring mySource, std::vector <std::wstring> & myKeyword)
{
	int startPos = 0;
	int findPos = 0;
	std::wstring subStr;

	short _extensionPos = 0;  //L"."
	_extensionPos = mySource.rfind(L".");

	//文件 etension
	if (_extensionPos != string::npos)
	{
		subStr = mySource.substr(_extensionPos+1, mySource.length()-_extensionPos);
		myKeyword.push_back(subStr);
		mySource = mySource.substr(0,_extensionPos);
	}

	do
	{
		findPos = mySource.find(L"_");
		if (findPos != string::npos)
		{
			subStr = mySource.substr(0, findPos);
			myKeyword.push_back(subStr);
			int newLength = mySource.length() - findPos;
			mySource = mySource.substr(findPos+1, newLength);
		}
		else
		{
			subStr = mySource.substr(findPos + 1, mySource.length());
			myKeyword.push_back(subStr);
			mySource = L"";
		}
	} while (mySource != L"");
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
			short _index = distance(_megaIDVector.begin(), _megaIDVectorItr);
			result = _IDMapItr->first+L"_"+ std::to_wstring(_index) ;
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
			// problematic keyword
			if (result == L"")
			{
				//can not generate the keyword according to megaScane ID
				success = 0;
				result = L"";
				wstring _info = L"KeywordManager :: generateObjectID : < problematic asset >: " + myMegaScaneID;
				Log::log(_info);
			}
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
			//替换megascen vector
			myObjectIDMap[myObjectID] = _megaScanVector;
		}
	}
	myObjectID = myObjectID + L"_" + std::to_wstring(_index - 1);
}

wstring KeywordManager::getFileName(wstring myObjectID, wstring mySourceFile )
{
	wstring result = L"";
	//get keyword vector
	vector <std::wstring> _keywordVector;
	getKeywords(mySourceFile, _keywordVector);
	wcout << "_________________________________________" << endl;
	wcout << "objectID : " << myObjectID << endl;
	wcout << "mySourceFile : " << mySourceFile << endl;
	for (vector <std::wstring> ::iterator itr = _keywordVector.begin(); itr != _keywordVector.end(); itr++)
	{
		wcout << *itr ;
		bool isKey = dictionarySearch(*itr);
		if (isKey)
		{
			wcout << " : true" << endl;
		}
		else
		{
			wcout << " : false" << endl;
		}
	}
	//analysis keyword usage
	//gelete megaScaneID
	//
	return(result);
}

KeywordManager::~KeywordManager()
{
	dictionary.clear();
	this->idMap.clear();
}