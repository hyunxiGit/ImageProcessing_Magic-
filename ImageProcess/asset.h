#pragma once
#pragma once
#include "keywordManager.h"
#include <string>

using namespace std;
class Asset
{
public:
	Asset(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru);
	wstring getFullSourcePath();//full image path
	wstring getFullTargetPath();//full image path
	wstring getSourcePath();//folder
	wstring getSourceName();
	wstring getTargetPath();//folder
	wstring getTargetName();
	fileKWStr getStruct();
	wstring getUse();
	void setExtension(wstring);
	virtual void reformat(wstring myFormat);
	virtual void createFile();
	void exportAsset();
private:
	fileKWStr str;
	wstring sourcePath;//folder name
	wstring sourceName;//file name with extension
	wstring targetPath;//folder name
	wstring targetName;//file name no extension
	wstring sourceImageFullPath;
	wstring targerImageFullPath;
};