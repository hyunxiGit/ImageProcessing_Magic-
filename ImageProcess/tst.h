#pragma once
#include "stdafx.h"
#include <vector>
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
class Tst
{
public:
	Tst();
	vector<TstSource> sourceNodes;
	vector<TstDest> destNodes;
};