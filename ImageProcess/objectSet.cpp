#pragma once
#include "stdafx.h"
#include "objectSet.h"
//#include "asset3D.h"

using namespace std;

ObjectSet::ObjectSet():megaScanId(L""), objectId(L""), sourcePath(L""), targetPath(L"")
{}

bool ObjectSet::init(wstring megaScanID, wstring mySourcePath, wstring myTargetPath)
{
	sourcePath = mySourcePath;
	targetPath = myTargetPath;

	_FM = FileManager::getInstance();
	_KM = KeywordManager::getInstance();

	
	megaScanId = megaScanID;
	bool idSet = generateID();
	bool pathSet = setPath(mySourcePath, myTargetPath);
	if (pathSet && idSet)
	{
		//analyse folder and collect all the asset files
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

}

bool ObjectSet::generateID() 
{
	bool result = false;
	KeywordManager * _KM = KeywordManager::getInstance();
	short getID = _KM->getObjectID(megaScanId, objectId);
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
		//wcout << targetPath << endl;
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
		wstring _fileName = _KM->getFileName(objectId, *itr, myKWStr);
		
		if (assetType == 2)
		{
			//create 2D asset 
			Asset2D my2DAsset(sourcePath + L"/" + megaScanId, *itr, targetPath , _fileName, myKWStr);
			asset2.push_back(my2DAsset);
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

void ObjectSet::generateTextureSet() {}
void ObjectSet::exportSet() 
{
	//create file test
	//for (vector<Asset2D>::iterator itr = asset2.begin(); itr != asset2.end(); itr++)
	//{

	//	(*itr).reformat(L".tga");
	//	wcout << "new extension is :" << (*itr).getStruct().extension << endl;
	//	(*itr).createFile();
	//	(*itr).exportAsset();
	//}
}