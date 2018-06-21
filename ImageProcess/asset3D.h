#pragma once
#include <string>
#include "asset.h"

using namespace std;
class Asset3D : public Asset
{
public:
	Asset3D(wstring, wstring, wstring, wstring, fileKWStr);
};