#pragma once
#include <string>
#include "image_w.h"
#include "asset.h"

using namespace std;
class Asset2D : public Asset
{
public:
	Asset2D(wstring mySourcePath, wstring mySourceName, wstring myTargetPath, wstring myTargetName, fileKWStr myStru);
	virtual void reformat( wstring myFormat);
	wstring getTextetImgName();
	void setTextetImgName(wstring);
	virtual void createFile();
	void exportAsset();
private:
	wstring textetImgName; //textet source node name
	Image_W image;
};