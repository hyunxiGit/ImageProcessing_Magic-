﻿#pragma once
#include <vector>
#include <string>
using namespace std;

struct TextetSource
{
	wstring FilePath;
	wstring id;
	wstring scale;
};
struct TextetDest
{
	wstring FilePath;
	wstring name;
};
struct Textet
{
public:
	vector<TextetSource> sourceNodes;
	vector<TextetDest> destNodes;
	wstring textureSetType;
	wstring version;

	Textet();
	Textet(wstring textureSetType);
	~Textet();
private:
	bool init();
};