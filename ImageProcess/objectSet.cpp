#pragma once
#include "stdafx.h"
#include "objectSet.h"
#include "TextureSetManager.h"
//#include "asset3D.h"

using namespace std;

ObjectSet::ObjectSet():megaScanId(L""), objectId(L""), sourcePath(L""), targetPath(L"")
{}

bool ObjectSet::init(wstring megaScanID, wstring mySourcePath, wstring myTargetPath)
//init 函数里面只能使用内存操作，不能使用磁盘操作
{
	bool result = false;
	sourcePath = mySourcePath;
	targetPath = myTargetPath;

	_FM = FileManager::getInstance();
	_KM = KeywordManager::getInstance();
	_TM = TextureSetManager::getInstance();

	
	megaScanId = megaScanID;
	bool idSet = generateID();
	wcout << "idSet : " << idSet << endl;
	bool pathSet = setPath(mySourcePath, myTargetPath);
	if (pathSet && idSet)
	{
		//analyse folder and collect all the asset files
		//makeObjectTargetFolder();
		generateAsset();
	}
	else
	{
		if (!idSet)
		{
			Log::log(L"<error> < ObjectSet::init> <problematic ID> : " + megaScanID);
		}
		if (!pathSet)
		{
			Log::log(L"<error> < ObjectSet::init> <wrong path> : " + pathSet);
		}
	}

	if (asset2.size() != 0)
	{
		result = true;
	}
	else if (asset3.size() != 0)
	{
		result = true;
	}
	//exportSet();

	return(result);
}

bool ObjectSet::generateID() 
{
	bool result = false;
	KeywordManager * _KM = KeywordManager::getInstance();
	short getID = _KM->getObjectID(megaScanId, objectId);
	wcout << getID << endl;
	if (getID == 1 || getID == 2)
	{
		result = true;
	}
	return(result);
}

wstring ObjectSet::getObjectID()
{
	return(objectId);
}

bool ObjectSet::setPath(wstring mySourcePath, wstring myTargetPath)
{
	bool sourceSet = false;
	bool targetSet = false;
	if(FileManager::checkPath(sourcePath) == FOLDER_EXIST)
	{
		sourcePath = mySourcePath;
		sourceSet = true;
		//wcout << sourcePath << endl;
	}
	if (FileManager::checkPath(myTargetPath) == FOLDER_EXIST && objectId!=L"")
	{
		targetPath = myTargetPath + L"/"+objectId;
		targetSet = true;
	}
	else if (_FM->createFolder(myTargetPath) == 1)
	{
		//create a new folder
		targetPath = myTargetPath + L"/" + objectId;
		targetSet = true;
	}
	return(sourceSet && targetSet);
}

void ObjectSet::generateAsset()
{
	FileManager * _FM = FileManager::getInstance();
	KeywordManager * _KM = KeywordManager::getInstance();
	vector < wstring > _files;
	vector < wstring > _folder;
	wstring _objectFolder = sourcePath + L"/" + megaScanId+L"/";
	wstring _newFolder = targetPath + L"/" + objectId;
	_FM->iterateFolder(_files, _folder, _objectFolder, true);
	short assetType = 0;
	for (vector < wstring >::iterator itr = _files.begin(); itr != _files.end(); itr++)
	{
		assetType = _KM->getFileType(*itr);
		fileKWStr myKWStr;
		wstring _fileName = _KM->makeFileName(objectId, *itr, myKWStr);
		
		if (assetType == 2)
		{
			//create 2D asset 
			if (myKWStr.extension == L".jpg")
			{
				//只处理jpg文件
				Asset2D my2DAsset(sourcePath + L"/" + megaScanId, *itr, targetPath, _fileName, myKWStr);
				asset2.push_back(my2DAsset);
			}
			
		}
		else if (assetType == 3)
		{
			//todo : create 3D asset 
			Asset3D my3DAsset(sourcePath + L"/" + megaScanId, *itr, targetPath, _fileName, myKWStr);
			asset3.push_back(my3DAsset);
			wcout << "source : " << my3DAsset .getFullSourcePath()<< endl;
			wcout << "target : " << my3DAsset .getFullTargetPath()<< endl;
			wcout << "fileName : " << _fileName << endl;

		}
	}
}

void ObjectSet::makeObjectTargetFolder() 
{
	wcout << "sourcePath : " << sourcePath <<endl;
	wcout << "targetPath : " << targetPath <<endl;
	_FM->createFolder(targetPath);
}

bool ObjectSet::setTst(wstring myTst)
{
	bool result = false;
	if (_TM->checkTstByName(myTst))
	{
		tstName = myTst;
		tst = _TM->getTstByName(tstName);
		result = true;
	}

	return(result);
}

bool ObjectSet::makeTextet()
{
	bool result = false;
	wcout << "............................." << endl;
	wcout << "megaScanId : " << megaScanId << endl;
	if (asset2.size()>0)
	{
		vector <Asset2D> assetForTextet;
		for (vector<Asset2D>::iterator itr = asset2.begin(); itr != asset2.end(); itr++)
		{
			wstring _use = (*itr).getStruct().use;
			if (_use == L"preview")
			{
				continue;
			}

			//未对应的image 换stru
			wstring textetImgName = _KM->usageNameConvert(_use);
			
			//换成tga格式
			(*itr).reformat(L".tga");

			//wcout << (*itr).getSourceName() << endl;
			if (textetImgName != L"")
			{
				//这是textureet img 文件

				//未对应的image 换name
				(*itr).renameByKW((*itr).getStruct().use, textetImgName);
				//添加对应的textet名字
				(*itr).setTextetImgName(textetImgName);
				//把这些图的地址按tst source node id 顺序打包入数组
				assetForTextet.push_back(*itr);
			}
			else
			{
			}
		}
		
		if (assetForTextet.size() > 0)
		{
			textet =_TM->makeTextset(objectId, assetForTextet, tstName);
		}
	}
	return(result);
}

void ObjectSet::exportAsset(bool my2D , bool myTextet , bool my3D)
{
	//serialize testet
	if (myTextet)
	{
		wstring textetExportDir = targetPath + L"/" + objectId + L".textet";
		Serialize::exportTextet(textetExportDir, textet);
	}

	if (my2D)
	{
		reformat2D(L".tga");
		export2D();
	}

	if (my3D)
	{

	}
	
}

void ObjectSet::reformat2D(wstring myFormat/*L".tga"*/)
{
	for (vector<Asset2D>::iterator itr = asset2.begin(); itr != asset2.end(); itr++)
	{
		(*itr).reformat(myFormat);
	}
}

void ObjectSet::export2D() 
{
	//create file test
	for (vector<Asset2D>::iterator itr = asset2.begin(); itr != asset2.end(); itr++)
	{
		//wcout << "new extension is :" << (*itr).getStruct().extension << endl;
		(*itr).createFile();
		(*itr).exportAsset();
	}
}