#pragma once
#pragma once
#include "keywordManager.h"
#include <string>

using namespace std;
class Asset
{
public:
	Asset(wstring, wstring, wstring, wstring, fileKWStr);
	void exportAsset();
	wstring getSourcePath();//folder
	wstring getSourceName();
	wstring getTargetPath();//folder
	wstring getTargetName();
	fileKWStr getStruct();
private:
	fileKWStr str;
	wstring sourcePath;
	wstring sourceName;
	wstring targetPath;
	wstring targetName;
};