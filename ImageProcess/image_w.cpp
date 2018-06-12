#pragma once
#include "stdafx.h"
#include"image_w.h"
#include <Magick++.h>
#include "serialize.h"

using namespace Magick;
Image_W::Image_W()
{

}

Image_W::Image_W(string myPath)
{
	Image myImage(myPath);
	this->data = myImage;
}

Image_W::Image_W(wstring myPath)
{
	string _path = Serialize::wStringToUTF8(myPath);
	Image myImage(_path);
	this->data = myImage;
}


short Image_W::write(string myTargetPath)
{
	short result = -1;
	this->data.write(myTargetPath);
	return (result);
}

short Image_W::write(wstring myTargetPath)
{
	short result = -1;
	string _path = Serialize::wStringToUTF8(myTargetPath);
	this->data.write(_path);
	return (result);
}