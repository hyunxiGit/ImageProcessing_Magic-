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

bool TextureSetManager::initFile(wstring myTstDir , wstring myTextetSourceImgDir , wstring myTextetDestImgDir)
//myTstDir ： tst文件在磁盘上的位置  ， myTextetSourceImgDir 和 myTextetDestImgDir为固定的需要写入textet source img 和 dest img 的相对路径
{
	vector <std::wstring> _files;
	vector <std::wstring> _folders;
	_FM->iterateFolder(_files, _folders, myTstDir);
	for (vector<wstring> ::iterator itr = _files.begin(); itr != _files.end(); itr++)
	{
		//wcout << *itr << endl;
		wstring _path = myTstDir + L"/" + *itr;
		parseTstFile(_path);
	}
	if (myTextetSourceImgDir != L"")
	{
		textetSourceDir = myTextetSourceImgDir;
	}
	if (myTextetDestImgDir != L"")
	{
		textetDestDir = myTextetDestImgDir;
	}
}

bool TextureSetManager::parseTstFile(wstring myPath)
{
	//wcout << myPath.rfind(L"/") << "," << myPath.rfind(L".")<<endl;
	wstring::size_type _pos1 = myPath.rfind(L"/") + 1;
	wstring::size_type _pos2 = myPath.rfind(L".") ;
	wstring _tstName = myPath.substr(_pos1, _pos2-_pos1);
	Tst _tst = Tst();
	_tst.tstName = _tstName;
	Serialize::importTst(myPath, _tst);
	tsts.push_back( _tst);
}

bool TextureSetManager::checkTstByName(wstring myTstName)
{
	bool result = false;
	for (vector<Tst>::iterator itr = tsts.begin(); itr != tsts.end(); itr++)
	{
		if (myTstName == (*itr).tstName)
		{
			result = true;
			break;
		}
	}
	return(result);
}

Textet TextureSetManager::makeTextset(wstring objId, vector<Asset2D>  & myAsset, wstring tstName)
{
	Tst _tst = getTstByName(tstName);
	Textet _textet = makeEmptyTextet(_tst);

	for (vector<Asset2D>::iterator itr = myAsset.begin(); itr != myAsset.end(); itr++)
	{
		Asset2D _asset = *itr;
		wstring _assetPath = _asset.getTargetPath();
		wstring::size_type _pos = _assetPath.find(textetSourceDir);
		if (_pos != wstring::npos)
		{
			//textet source Name项
			wstring sName = _asset.getTextetImgName();
			int nodeIndex = getTexetSNodeIndxByName(sName, _textet);

			if (nodeIndex != -1)
			{
				wstring _fileName = _asset.getTargetName() + _asset.getStruct().extension;
				wstring sFilePath = textetSourceDir + L"/" + _FM->getSubFolder() + L"/" + objId + L"/" + _fileName;
				_textet.sourceNodes[nodeIndex].FilePath = sFilePath;
			}
		}
	}

	//todo ： need to add default image when there's no image for the node
	for (vector<TextetSource>::iterator itr = _textet.sourceNodes.begin(); itr != _textet.sourceNodes.end(); itr++)
	{
		if ((*itr).FilePath == L"")
		{
			//wcout << "source  file Name : " << (*itr).Name << endl;
		}
	}

	for (vector<TextetDest>::iterator itr = _textet.destNodes.begin(); itr != _textet.destNodes.end(); itr++)
	{
		(*itr).FilePath = textetDestDir + L"/" + _FM->getSubFolder() + L"/" + objId + L"/" + objId +(*itr).FilePath+ L".dds";
	}

	return(_textet);
}

Tst TextureSetManager::getTstByName(wstring myTstName)
{
	for (vector<Tst>::iterator itr = tsts.begin(); itr != tsts.end(); itr++)
	{
		if (myTstName == (*itr).tstName)
		{
			return(*itr);
		}
	}
}

Textet TextureSetManager::makeEmptyTextet(Tst myTst)
{
	Textet _textet;
	_textet.version = myTst.version;
	_textet.textureSetType = myTst.tstName;

	for (vector<TstSource> ::iterator itr = myTst.sourceNodes.begin(); itr != myTst.sourceNodes.end(); itr++)
	{
		TextetSource sTextet;
		TstSource sTst = *itr;
		sTextet.Name = sTst.name;
		sTextet.FilePath = L"";
		_textet.sourceNodes.push_back(sTextet);
	}

	for (vector<TstDest> ::iterator itr = myTst.destNodes.begin(); itr != myTst.destNodes.end(); itr++)
	{
		TextetDest dTextet;
		TstDest dTst = *itr;
		dTextet.FilePath = dTst.NameSuffix;
		dTextet.ID = dTst.ID;
		dTextet.Scale = L"0.5";
		_textet.destNodes.push_back(dTextet);
	}
	return(_textet);
}

int TextureSetManager::getTexetSNodeIndxByName( wstring myName , Textet myTextet)
{
	int i = 0;
	int result = -1;
	for (vector<TextetSource> ::iterator itr = myTextet.sourceNodes.begin(); itr != myTextet.sourceNodes.end(); itr++)
	{
		if ((*itr).Name == myName)
		{
			result = i;
			break;
		}
		i++;
	}
	return(result);
}


bool TextureSetManager::exportTextet(wstring path, Textet) {}

TextureSetManager::TextureSetManager()
{
	_FM = FileManager::getInstance();
}
