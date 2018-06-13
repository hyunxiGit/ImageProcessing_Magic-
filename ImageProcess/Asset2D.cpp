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

	wcout << "[Asset2D] -> myTargetPath :" << targetPath << endl;
	wcout << "[Asset2D] -> myTargetName :" << targetName << endl;
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