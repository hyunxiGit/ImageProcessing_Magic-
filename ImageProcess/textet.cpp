#pragma once
#include "stdafx.h"
#include "textet.h"
#include "textureSetManager.h"

Textet::Textet() : textureSetType(L""), version(L""){}
Textet::Textet(wstring myTextureSetType) : version(L"0")
{
	if (myTextureSetType != L"")
	{
		textureSetType = myTextureSetType;
	}
	init();
}
Textet::~Textet()
{
	vector<TextetSource>().swap(sourceNodes);
	vector<TextetDest>().swap(destNodes);
}

bool Textet::init()
{
	bool result = false;
	TextureSetManager *myTM = TextureSetManager::getInstance();
	vector<TstDest> _dest = myTM->getTstByName(textureSetType).destNodes;
	vector<TstSource> _source = myTM->getTstByName(textureSetType).sourceNodes;
	return(result);
}