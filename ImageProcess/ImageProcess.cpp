// ImageProcess.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<Magick++.h>

int main()
{
	Magick::Image image("100x100", "white");
	image.pixelColor(49, 49, "red");
	image.write("red_pixel.png");
    return 0;
}

