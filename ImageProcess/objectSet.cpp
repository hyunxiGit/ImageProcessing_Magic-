#pragma once
#include "stdafx.h"

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
		analyseObjectSet();
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

short ObjectSet::analyseObjectSet()
// -1: wrong asset , 1: 2D, 2:3D
{
	FileManager * _FM = FileManager::getInstance();
	KeywordManager * _KM = KeywordManager::getInstance();
	vector < wstring > _files;
	vector < wstring > _folder;
	wstring _objectFolder = sourcePath + L"/" + megaScanId+L"/";
	_FM->iterateFolder(_files, _folder, _objectFolder, true);
	short assetType = 0;
	for (vector < wstring >::iterator itr = _files.begin(); itr != _files.end(); itr++)
	{
		assetType = _KM->getFileType(*itr);
		wcout << *itr << endl;
		wcout << assetType << endl;
	}
}

void ObjectSet::generateTextureSet() {}
void ObjectSet::exportSet() {}