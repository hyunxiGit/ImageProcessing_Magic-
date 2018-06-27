#pragma once
#include "stdafx.h"
#include "textet.h"
#include "textureSetManager.h"

Textet::Textet() : textureSetType(L""), version(L"0"){}
Textet::Textet(wstring myTextureSetType , vector<TextetSource> mySourceNodes , vector<TextetDest> myDestNodes)
{
	version = L"0";
	if (myTextureSetType != L"")
	{
		textureSetType = myTextureSetType;
	}
	sourceNodes = mySourceNodes;
	destNodes = myDestNodes;
}
Textet::~Textet()
{
}

bool Textet::init()
{
	bool result = false;
	TextureSetManager *myTM = TextureSetManager::getInstance();
	vector<TstDest> _dest = myTM->getTstByName(textureSetType).destNodes;
	vector<TstSource> _source = myTM->getTstByName(textureSetType).sourceNodes;
	return(result);
}