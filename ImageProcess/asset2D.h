#pragma once
#include <string>
#include "keywordManager.h"
#include "image_w.h"

using namespace std;
class Asset2D
{
public:
	Asset2D(wstring, wstring, wstring, wstring, fileKWStr);
	//void export();
	void reformat( wstring myFormat);
	void exportAsset();
private:
	Image_W image;
	fileKWStr str;
	wstring sourcePath;
	wstring sourceName;
	wstring targetPath;
	wstring targetName;
};