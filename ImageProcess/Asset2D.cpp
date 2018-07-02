#pragma once
#include "stdafx.h"
#include "asset2D.h"

Asset2D::Asset2D(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru) : Asset(mySourcePath, mySourceName, myTargetPath, myTargetName, myStru)
{
	textetImgName = L"";
}

void Asset2D::exportAsset()
{
	wstring _path = getFullTargetPath();
	image.write(_path);
}

wstring Asset2D::getTextetImgName()
{
	return(textetImgName);
}

void Asset2D::setTextetImgName(wstring myName)
{
	if (myName != L"")
	{
		textetImgName = myName;
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