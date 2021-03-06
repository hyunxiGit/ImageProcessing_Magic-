﻿#pragma once
#include "stdafx.h"


struct TstSource
{
	wstring name;
	wstring format;
	wstring colorSpace;
	wstring destID;
	wstring destChannerl;
	
};
struct TstDest
{
	wstring ID;
	wstring NameSuffix;
	wstring Format;
	wstring FileType;
	wstring ColorSpace;
	wstring Filter;
	wstring GenarateMipmap;
	wstring MipmapFilter;
	wstring Scale;
};
struct Tst
{
	wstring tstName;
	vector<TstSource> sourceNodes;
	vector<TstDest> destNodes;
	wstring version;

	Tst();
	Tst(vector<TstSource> sourceNodes, vector<TstDest> destNodes);
	~Tst();
};