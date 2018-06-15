#pragma once
#include "stdafx.h"

using namespace std;

ObjectSet::ObjectSet():megaScanId(L""), objectId(L""), sourcePath(L""), targetPath(L"")
{}

bool ObjectSet::init(wstring megaScanID, wstring mySourcePath, wstring myTargetPath)
{
	sourcePath = mySourcePath;
	targetPath = myTargetPath;

	FileManager * _FM = FileManager::getInstance();

	megaScanId = megaScanID;
	generateID();
	bool pathSet = setPath(mySourcePath, myTargetPath);
	if (pathSet)
	{
		//analyse folder and collect all the asset files
	}
}

bool ObjectSet::generateID() 
{
	bool result = false;
	KeywordManager * _KM = KeywordManager::getInstance();
	_KM->getObjectID(megaScanId, objectId);
	return(result);
}

wstring ObjectSet::getObjectID()
{
	return(objectId);
}

bool ObjectSet::setPath(wstring mySourcePath, wstring myTargetPath)
{
	bool result = false;
	if(FileManager::checkPath(sourcePath) == FOLDER_EXIST)
	{
		sourcePath = mySourcePath;
	}
	if (FileManager::checkPath(myTargetPath) == FOLDER_EXIST && objectId!=L"")
	{
		targetPath = myTargetPath + L"/"+objectId;
		wcout << targetPath << endl;
	}
}

void ObjectSet::generateTextureSet() {}
void ObjectSet::exportSet() {}