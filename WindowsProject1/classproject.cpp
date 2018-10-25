#include "classproject.h"
#include "stdafx.h"
/****************************************************/
using namespace std;
using namespace rapidxml;
using namespace Gdiplus;

void Attribute::setScale(long long x, long long y)
{
	scale.first = x;
	scale.second = y;
	return;
}

void Attribute::setScale(long long x)
{
	setScale(x, x);
	return;
}

void Attribute::setRotate(double x)
{
	rotate = x;
}