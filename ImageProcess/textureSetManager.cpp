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
	FileManager * myFM = FileManager::getInstance();
	myFM->iterateFolder(_files, _folders, myTstDir);
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
	Textet _textet;
	_textet.version = 1.0;
	for (vector<Asset2D>::iterator itr = myAsset.begin(); itr != myAsset.end(); itr++)
	{
		Asset2D _asset = *itr;
		/*wcout << "name : " << _asset.getTargetName() << endl;
		wcout << "extension : " << _asset.getStruct().extension << endl;*/
		wstring _assetPath = _asset.getTargetPath();
	/*	wcout << _assetPath << endl;
		wcout << textetSourceDir << endl;*/
		wstring::size_type _pos = _assetPath.find(textetSourceDir);
		if (_pos != wstring::npos)
		{
			wstring _fileName = _asset.getTargetName() + _asset.getStruct().extension;
			//得到写入textet的Name
			wstring sourceName = _asset.getTextetImgName();
			wcout << "sourceName " << sourceName << endl;
			//得到写入textet的相对路径
			wstring sourceFilePath = _assetPath.substr(_pos, _assetPath.size())+ L"/" + _fileName;
			wcout << "sourceFilePath: " << sourceFilePath << endl;
			wstring destFilePath = textetDestDir + sourceFilePath.substr(textetSourceDir.size(), sourceFilePath.size()) ;
			wcout << "new string 2: " << destFilePath << endl;
		}

		//Tst _tst = getTstByName(tstName);
		//for (vector<TstDest> itr = _tst.destNodes.begin(); itr != _tst.destNodes.end(); itr++)
		//{

		//}

	}
	//按照tstName 取得tst
	//取得tstdest node 的 ID , NameSuffix
	//按照objectID NameSuffix 生成img名字
	// 取imgDir相应的image 按照objectID 转化filePath信息 
	//写dest node

	//按照imgDir 以及 约定的path生成新source Path
	//按照tstsource node 取得 name生成Name
	//写入sourceNode
	return(_textet);
}
bool TextureSetManager::exportTextet(wstring path, Textet) {}

TextureSetManager::TextureSetManager()
{
	_FM = FileManager::getInstance();
}

TextureSetManager::~TextureSetManager()
{

}