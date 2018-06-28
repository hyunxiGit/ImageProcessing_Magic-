#pragma once
#include <vector>
#include <string>
using namespace std;

struct TextetSource
{
	wstring FilePath;
	wstring Name;
};
struct TextetDest
{
	wstring FilePath;
	wstring ID;
	wstring Scale;
};
struct Textet
{
public:
	vector<TextetSource> sourceNodes;
	vector<TextetDest> destNodes;
	wstring textureSetType;
	wstring version;

	Textet();
	Textet(wstring myTextureSetType, vector<TextetSource> mySourceNodes, vector<TextetDest> myDestNodes);
};