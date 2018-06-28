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