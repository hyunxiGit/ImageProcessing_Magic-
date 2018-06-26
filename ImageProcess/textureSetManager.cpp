#pragma once
#include "stdafx.h"
#include "textureSetManager.h"
#include "asset2D.h"


TextureSetManager * TextureSetManager:: instance = nullptr;
TextureSetManager * TextureSetManager::getInstance()
{
	if (instance == nullptr)
	{
		instance = new TextureSetManager();
	}
	return(instance);
}
bool TextureSetManager::initTstFile(wstring _dir)
{
	vector <std::wstring> _files;
	vector <std::wstring> _folders;
	FileManager * myFM = FileManager::getInstance();
	myFM->iterateFolder(_files, _folders, _dir);
	for (vector<wstring> ::iterator itr = _files.begin(); itr != _files.end(); itr++)
	{
		//wcout << *itr << endl;
		wstring _path = _dir + L"/" + *itr;
		parseTstFile(_path);
	}
}
bool TextureSetManager::parseTstFile(wstring myPath)
{
	//wcout << myPath.rfind(L"/") << "," << myPath.rfind(L".")<<endl;
	wstring::size_type _pos1 = myPath.rfind(L"/") + 1;
	wstring::size_type _pos2 = myPath.rfind(L".") ;
	wstring _tstName = myPath.substr(_pos1, _pos2-_pos1);
	Tst _tst = Tst();
	Serialize::importTst(myPath, _tst);
	tstFileMap.insert(std::pair<wstring, Tst>(_tstName, _tst));
}
bool TextureSetManager::checkTstByName(wstring myTstName)
{
	bool result = false;
	for (map<wstring, Tst>::iterator itr = tstFileMap.begin(); itr != tstFileMap.end(); itr++)
	{
		if (myTstName == itr->first)
		{
			result = true;
			break;
		}
	}
	return(result);
}

Tst TextureSetManager::getTstByName(wstring myTstName)
{
	for (map<wstring, Tst>::iterator itr = tstFileMap.begin(); itr != tstFileMap.end(); itr++)
	{
		if (myTstName == itr->first)
		{
			return(itr->second);
		}
	}
}

Textet TextureSetManager::makeTextset(wstring objId, vector<Asset2D>  & myAsset, wstring tstName)
{
	Textet _textet();
	for (vector<Asset2D>::iterator itr = myAsset.begin(); itr != myAsset.end(); itr++)
	{
		wcout << "new name : " << (*itr).getTargetName() << endl;
		wcout << "new source path : " << (*itr).getFullTargetPath() << endl;
	}
	//按照tstName 取得tst
	//取得tstdest node 的 ID , NameSuffix
	//按照objectID NameSuffix 生成img名字
	// 取imgDir相应的image 按照objectID 转化filePath信息 
	//写dest node

	//按照imgDir 以及 约定的path生成新source Path
	//按照tstsource node 取得 name生成Name
	//写入sourceNode
}
bool TextureSetManager::exportTextet(wstring path, Textet) {}
TextureSetManager::TextureSetManager()
{

}
TextureSetManager::~TextureSetManager()
{

}