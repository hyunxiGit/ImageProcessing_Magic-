#pragma once
#include "stdafx.h"
#include "asset2D.h"

Asset2D::Asset2D(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru) : Asset(mySourcePath, mySourceName, myTargetPath, myTargetName, myStru)
{
	image = Image_W(getSourcePath() + getSourceName());

	wcout << "[Asset2D] -> myTargetPath :" << getTargetPath() << endl;
	wcout << "[Asset2D] -> myTargetName :" << getTargetName() << endl;
}
void Asset2D::exportAsset()
{
	if (getStruct().use == L"preview")
	{
		//preview image
		//copy image
	}
	else
	{
		//other images
		wstring _path = getTargetPath() + getTargetName() + getStruct().extension;
		//image.write(_path);
	}
}


void Asset2D::reformat(wstring myFormat)
{
	//todo : if myFormat 合法
	getStruct().extension = myFormat;
}