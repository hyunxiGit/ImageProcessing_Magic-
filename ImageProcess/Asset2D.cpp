#pragma once
#include "stdafx.h"
#include "asset2D.h"

Asset2D::Asset2D(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru) : Asset(mySourcePath, mySourceName, myTargetPath, myTargetName, myStru)
{}

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
		wstring _path = getFullTargetPath()+ getStruct().extension;
		image.write(_path);
	}
}

void Asset2D::createFile()
{
	wstring sourceImagePath = getFullSourcePath();
	image = Image_W(sourceImagePath);
}

void Asset2D::reformat(wstring myFormat)
{
	//todo : if myFormat 合法
	if (getUse() == L"preview")
	{
		setExtension(L".png");
	}
	else
	{
		setExtension(myFormat);
	}
}