#pragma once
#include "stdafx.h"
#include "keywordManager.h"
#include <algorithm>
using namespace std;

KeywordManager * KeywordManager::instance = nullptr;

KeywordManager::KeywordManager()
{
	//strcpy_s(dictionaryPath, MAX_PATH,"d:/en-dictionary.txt");
	//wstring line;
	//wifstream inFile;
	//bool found = false;

	//inFile.open(dictionaryPath);
	////初始化字典
	//if (!inFile.is_open())
	//{
	//	std::cout << "KeywordManager :: KeywordManager() : <illegal dictionary path>" << dictionaryPath  << endl;
	//}
	//else
	//{
	//	while (!inFile.eof())
	//	{
	//		inFile >> line;
	//		std::transform(line.begin(), line.end(), line.begin(), ::tolower);

	//		this->dictionary.insert(line);
	//	}
	//}
	//inFile.close();
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

bool KeywordManager::initJsonMap(wstring myIDPath, wstring myKWPath, wstring myDiction)
{
	Serialize::importJson(idMap, myIDPath);
	Serialize::importJson(kWMap, myKWPath);
	initDictionary(myDiction);
	for (vector<wstring> ::iterator itr = kWMap[L"extension2D"].begin(); itr != kWMap[L"extension2D"].end(); itr++)
	{
		extension2D.push_back(*itr);
	}
	for (vector<wstring> ::iterator itr = kWMap[L"extension3D"].begin(); itr != kWMap[L"extension3D"].end(); itr++)
	{
		extension3D.push_back(*itr);
	}
	for (vector<wstring> ::iterator itr = kWMap[L"extensionOther"].begin(); itr != kWMap[L"extensionOther"].end(); itr++)
	{
		extensionOther.push_back(*itr);
	}
}

bool KeywordManager :: initDictionary(wstring myDictionPath)
{
	const wchar_t * _path = (wchar_t *)myDictionPath.c_str();
	//strcpy_s(dictionaryPath, MAX_PATH, "d:/en-dictionary.txt");
	wstring line;
	wifstream inFile;
	bool found = false;

	inFile.open(_path);
	//初始化字典
	if (inFile.is_open())
	{
		while (!inFile.eof())
		{
			inFile >> line;
			std::transform(line.begin(), line.end(), line.begin(), ::tolower);

			dictionary.insert(line);
		}
	}
	inFile.close();
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

void KeywordManager::analyseID(vector <std::wstring> myMegaIDs, vector <std::wstring> & myObjIds)
{
	bool _updateJson = false;
	FileManager * myFM = FileManager::getInstance();
	for (vector < wstring >::iterator it = myMegaIDs.begin(); it != myMegaIDs.end(); it++)
	{
		wstring  _megaScanId = *it;
		wstring  _objectID = L"";
		short idState = instance->getObjectID(_megaScanId, _objectID);
		if (idState == 2)
		{
			_updateJson = true;
		}
		if (_objectID != L"")
		{
			myObjIds.push_back(_objectID);
		}
	}
	if (_updateJson)
	{
		Serialize::exportJson(idMap, myFM->getIDJasonPath());
	}
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
		subStr = mySource.substr(_extensionPos, mySource.length()-_extensionPos);//".jpg"
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

short KeywordManager::getObjectID(std::wstring myMegaScaneID, wstring & result )
//按照读入的objectIDMap 查询 或者 为 myMegaScaneID 产生object ID ，如果是产生ID  myObjectIDMap 更新
{
	//todo:支持查找中文
	//两个英语单词拼接
	
	//0: failed , 1: get the id , 2, make new ID
	short success = 1;

	//检测当前megaScan ID 在 map里是否存在
	map<wstring, vector<wstring>>::iterator _IDMapItr;
	
	bool _idExist = false;
	if (idMap.empty()){	}
	for (_IDMapItr = idMap.begin(); _IDMapItr != idMap.end(); _IDMapItr++)
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

		// problematic keyword
		if (result == L"")
		{
			//can not generate the keyword according to megaScane ID
			Log::log(L"<error> <KeywordManager::generateObjectID> <2Dasset> can not generate ID for :" + myMegaScaneID);
			success = 0;
		}

		else
		{
			//succesful asset, generate number
			generateObjectID(myMegaScaneID, result);
		}
	}
	

	return(success);
}

void KeywordManager::generateObjectID( wstring myMegaScaneID, wstring & myObjectID )
{	
	short _index;

	map<wstring, vector<wstring>>::iterator itr = idMap.find(myObjectID);
	if (itr == idMap.end())
	{
		//cout << "There's no such object ID" << endl;
		//create new key,  在最后加入idMap
		vector<wstring> _newMegaID;
		_newMegaID.push_back(myMegaScaneID);
		idMap[myObjectID] = _newMegaID;
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
			idMap[myObjectID] = _megaScanVector;
		}
	}
	myObjectID = myObjectID + L"_" + std::to_wstring(_index);
}

wstring KeywordManager::getFileName(wstring myObjectID, wstring mySourceFile , fileKWStr  & resultKWStr)
{
	wstring result = L"";
	fileKWStr _kwStr;
	//get keyword vector
	vector <std::wstring> _kwVector;
	vector <std::wstring> _wrongKwVector;
	getKeywords(mySourceFile, _kwVector);

	for (vector <std::wstring> ::iterator itr = _kwVector.begin(); itr != _kwVector.end(); itr++)
	{
		//analysis keyword usage
		wstring _kwType = getfileKWType(*itr , resultKWStr);

		if (_kwType == L"")
		{
			_wrongKwVector.push_back(*itr);
		}
	}

	if (resultKWStr.extension != L".json" && (resultKWStr.extension == L"" || resultKWStr.use == L""))
	{
		for (vector<wstring>::iterator itr = _wrongKwVector.begin(); itr != _wrongKwVector.end(); itr++)
		{
			//wcout << *itr <<endl;
		}
	}

	//gelete megaScaneID
	result = makeFileName(myObjectID , resultKWStr);
	return(result);
}

wstring KeywordManager::getfileKWType(wstring myKW, fileKWStr & myKWStr)
{
	//result 为 L"" 则是 wrongKW;
	wstring result = L"";
	bool _idExist = false;
	std::transform(myKW.begin(), myKW.end(), myKW.begin(), ::tolower);
	for (map<wstring, vector<wstring>>::iterator itr = kWMap.begin(); itr != kWMap.end(); itr++)
	{
		vector<wstring> kWVector = itr->second;
		vector<wstring>::iterator itr2 = std::find(kWVector.begin(), kWVector.end(), myKW);
		if (itr2 == kWVector.end()) {}
		else
		{
			//found			
			_idExist = true;
			result = itr->first;

			if (result == L"size")
			{
				myKWStr.size = myKW;
			}
			else if (result == L"use")
			{
				myKWStr.use = myKW;
			}
			else if (result == L"extension2D")
			{
				myKWStr.extension = myKW;
			}
			else if (result == L"extension3D")
			{
				myKWStr.extension = myKW;
			}
			else if (result == L"extensionOther")
			{
				myKWStr.extension = myKW;
			}
			else if (result == L"lod")
			{
				myKWStr.lod = myKW;
			}
			else if (result == L"variation")
			{
				myKWStr.variation = myKW;
			}

			return(result);
			break;
		}
	}
	if (_idExist == false)
	{
		//遍历完整个fileKWMap找不到关键字的所属
		//wcout << "wrong keywor *******************************************:" << myKW << endl;
	}
	return(result);
}

bool KeywordManager::makeFileKeyword()
{
	map<wstring, vector<wstring>> _fileKWMap;
	vector<wstring> size;
	vector<wstring> use;
	vector<wstring> extension;
	vector<wstring> lod;
	vector<wstring> variation;
	
	size.push_back(L"2k");
	size.push_back(L"4k");

	use.push_back(L"albedo");
	use.push_back(L"atlas");
	use.push_back(L"ao");
	use.push_back(L"billboard");
	use.push_back(L"bump");
	use.push_back(L"cavity");
	use.push_back(L"displacement");
	use.push_back(L"fuzz");
	use.push_back(L"gloss");
	use.push_back(L"normal");
	use.push_back(L"opacity");
	use.push_back(L"preview");
	use.push_back(L"roughness");
	use.push_back(L"specular");
	use.push_back(L"translucency");

	extension.push_back(L".exr");
	extension.push_back(L".jpg");
	extension.push_back(L".png");
	extension.push_back(L".json");

	lod.push_back(L".lod0");
	lod.push_back(L".lod1");
	lod.push_back(L".lod2");

	variation.push_back(L".var1");
	variation.push_back(L".var2");
	variation.push_back(L".var3");

	_fileKWMap[L"size"] = size;
	_fileKWMap[L"use"] = use;
	_fileKWMap[L"extension"] = extension;
	_fileKWMap[L"lod"] = lod;
	_fileKWMap[L"variation"] = variation;

	Serialize::exportJson(_fileKWMap , L"d:/fileKW.json");
}

wstring KeywordManager::makeFileName(wstring myObjectID, fileKWStr myKWStr)
{
	wstring result;
	vector<wstring> _fileKWResultVector;
	result = myObjectID;
	if (myKWStr.variation != L"")
	{
		result += (L"_");
		result += myKWStr.variation;
	}
	if (myKWStr.use != L"")
	{
		result += (L"_");
		result += myKWStr.use;
	}
	if (myKWStr.size != L"")
	{
		result += (L"_");
		result += myKWStr.size;
	}

	if (myKWStr.lod != L"")
	{
		result += (L"_");
		result += myKWStr.lod;
	}
	if (myKWStr.extension != L"")
	{
		//result += myKWStr.extension;
	}
	return(result);
}

void KeywordManager::exportObjectID()
{
	Serialize::exportJson(idMap, FileManager::getInstance()->getIDJasonPath());
}

short KeywordManager::getFileType(wstring myFileName)
//0：unknown, 1:other, 2 : 2D , 3:3d
{
	short result = 0;
	FileManager * _FM = FileManager::getInstance();
	wstring ext = _FM->getFileExtion(myFileName);
	vector<wstring>::iterator itr;
	itr = find(extension2D.begin(), extension2D.end(), ext);
	if (itr != extension2D.end())
	{
		result = 2;
	}
	else
	{
		itr = find(extension3D.begin(), extension3D.end(), ext);
		if (itr != extension3D.end())
		{
			result = 3;
		}
		else
		{
			itr = find(extensionOther.begin(), extensionOther.end(), ext);
			if (itr != extensionOther.end())
			{
				result = 1;
			}
		}
	}
	return(result);
}

KeywordManager::~KeywordManager()
{
	set<wstring>().swap(dictionary);
	map<wstring, vector<wstring>>().swap(idMap);
	map<wstring, vector<wstring>>().swap(kWMap);
}