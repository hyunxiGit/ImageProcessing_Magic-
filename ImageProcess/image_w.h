#pragma once
//#include <Magick++.h>
//using namespace Magick;

class Image_W
//image++ unicode wrapper
{
public:
	//Image data;
	Image_W();
	Image_W(string);
	Image_W(wstring);
	short write(string);
	short write(wstring);
};