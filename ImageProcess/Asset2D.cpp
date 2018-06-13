#pragma once
#include "stdafx.h"
#include "asset2D.h"

Asset2D::Asset2D(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru)
{
	sourcePath = mySourcePath;
	sourceName = mySourceName;
	targetPath = myTargetPath;
	targetName = myTargetName;

	str = myStru;

	wcout << "source______________" << mySourcePath + mySourceName << endl;
	image = Image_W(mySourcePath + mySourceName);

	//wcout << "[Asset2D] -> sourcePath :" << sourcePath << endl;
	//wcout << "[Asset2D] -> mySourceName :" << sourceName << endl;
	wcout << "[Asset2D] -> myTargetPath :" << targetPath << endl;
	wcout << "[Asset2D] -> myTargetName :" << targetName << endl;

	//wcout << "[Asset2D] -> myStru " << str.extension << endl;
	//wcout << "[Asset2D] -> myStru " << str.use << endl;
	//wcout << "[Asset2D] -> myStru " << str.size << endl;
	//wcout << "[Asset2D] -> myStru " << str.lod << endl;
	//wcout << "[Asset2D] -> myStru " << str.variation << endl;
}
void Asset2D::exportAsset()
{
	wcout << "export : " << targetPath + targetName + str.extension << endl;
	if (str.use == L"preview")
	{
		//preview image
		//copy image
	}
	else
	{
		//other images
		wstring _path = targetPath + targetName + str.extension;
		image.write(_path);
	}
}


void Asset2D::reformat(wstring myFormat)
{
	//todo : if myFormat 合法
	str.extension = myFormat;
}