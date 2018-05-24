#pragma once
#include "stdafx.h"

Asset2D::Asset2D()
{

}
bool Asset2D::reFormat()
{
	Image myImg("d:\\oebei_4K_Albedo.jpg");
	myImg.write("d:/oebei_4K_Albedo.tga");
}