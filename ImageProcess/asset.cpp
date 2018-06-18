#pragma once
#include "stdafx.h"
#include "asset.h"

Asset::Asset(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru)
{
	sourcePath = mySourcePath;
	sourceName = mySourceName;
	targetPath = myTargetPath;
	targetName = myTargetName;

	str = myStru;

	wcout << "source______________" << mySourcePath + mySourceName << endl;

	wcout << "[Asset2D] -> myTargetPath :" << targetPath << endl;
	wcout << "[Asset2D] -> myTargetName :" << targetName << endl;
}
void Asset::exportAsset()
{
	wcout << "export : " << targetPath + targetName + str.extension << endl;
}

wstring Asset::getSourcePath()
{
	return(sourcePath);
}
wstring Asset::getSourceName()
{
	return(sourceName);
}
wstring Asset::getTargetPath()
{
	return(targetPath);
}
wstring Asset::getTargetName()
{
	return(targetName);
}
fileKWStr Asset::getStruct()
{
	return(str);
}
