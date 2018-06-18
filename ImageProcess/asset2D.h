#pragma once
#include <string>
#include "keywordManager.h"
#include "image_w.h"
#include "asset.h"

using namespace std;
class Asset2D : public Asset
{
public:
	Asset2D(wstring , wstring , wstring , wstring , fileKWStr );
	void reformat( wstring myFormat);
	void exportAsset();
private:
	Image_W image;
};