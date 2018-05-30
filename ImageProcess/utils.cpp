#pragma once
#include "stdafx.h"#
extern locale loc;
wchar_t ** Utils::make2dArray(int myLength , int myCount )
{
	wchar_t ** _resultNames;
	_resultNames = (wchar_t **)(malloc(myCount * sizeof(wchar_t *)));
	for (int i = 0; i < myCount; i++)
	{
		*(_resultNames + i) = (wchar_t *)(malloc(sizeof(wchar_t) * myLength));
	}
	return(_resultNames);
}

void Utils::release2dArray (wchar_t ** my2DArray, int myCount )
{
	//释放内存
	for (int i = 0; i < myCount; i++)
	{
		free(*(my2DArray + i));
	}
	free(my2DArray);
}
