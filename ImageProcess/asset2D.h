#pragma once
#include <string>
#include "image_w.h"
#include "asset.h"

using namespace std;
class Asset2D : public Asset
{
public:
	Asset2D(wstring , wstring , wstring , wstring , fileKWStr );
	virtual void reformat( wstring myFormat);
	virtual void createFile();
	void exportAsset();
private:
	Image_W image;
};