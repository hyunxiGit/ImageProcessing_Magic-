#pragma once
#include "stdafx.h"
#include "asset.h"

Asset::Asset(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru)
{
	sourcePath = mySourcePath;
	sourceName = mySourceName;
	targetPath = myTargetPath;
	targetName = myTargetName;

	sourceImageFullPath = getSourcePath() + L"/" + getSourceName();

	str = myStru;
}
void Asset::exportAsset()
{
	wcout << "export : " << targetPath + targetName + str.extension << endl;
}

wstring Asset::getUse()
{
	return(str.use);
}

void Asset::reformat(wstring myFormat)
{
	wcout << "parent reformat" << endl;
}

//todo : 这个函数最终要放在构造函数里面
void Asset::createFile(){}

void Asset::setExtension(wstring myExtension)
{
	str.extension = myExtension;
}

bool Asset::renameByKW(wstring sKW, wstring tKW)
{
	bool result = false;
	wstring::size_type pos = targetName.find(sKW);
	if (pos != wstring::npos)
	{
		wstring subStr1 = targetName.substr(0, pos);
		wstring subStr2 = targetName.substr(pos + sKW.size(), tKW.size());
		targetName = subStr1 + tKW + subStr2;
		result = true;
	}
	return(result);
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

fileKWStr & Asset::getStruct()
{
	return(str);
}

wstring Asset :: getFullSourcePath() {	return(sourceImageFullPath);}

wstring Asset::getFullTargetPath() { return(targetPath+L"/"+targetName+str.extension); }