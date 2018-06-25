#pragma once
#include "stdafx.h"
#include "TextureSetManager.h"

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
TextureSetManager::TextureSetManager()
{

}
TextureSetManager::~TextureSetManager()
{

}