#pragma once
#include <string>
#include <Magick++.h>
using namespace Magick;

using namespace std;
class Image_W
//image++ unicode wrapper
{
public:
	Image data;
	Image_W();
	Image_W(string);
	Image_W(wstring);
	short write(string);
	short write(wstring);
};