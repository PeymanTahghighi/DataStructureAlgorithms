#pragma once

//===========================================================================
//===========================================================================
#include<string>
#include<cstdint>
#include<cassert>
#include<vector>
//===========================================================================
//===========================================================================

//---------------------------------------------------------------------------
#define EPSILON 0.0001
#define MAX_FRACTION 4
#define ENABLE_DRAWING_FUNCTIONS 1
#define DRAW_Y_OFFSET 50
#define SCREEN_WIDTH 1800
#define SCREEN_HEIGHT 600
#define AVG_FRAME 50
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
inline void intToString(int number, std::string &ret)
{
	int tempNumber = abs(number);

	int reminder = tempNumber % 10;
	tempNumber = tempNumber / 10;

	ret = (char)(reminder + 48);

	while (tempNumber != 0)
	{
		reminder = tempNumber % 10;
		tempNumber = tempNumber / 10;
		ret = (char)(reminder + 48) + ret;
	}

	if (number < 0)
		ret = "-" + ret;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
inline void floatToString(float number, std::string &ret)
{
	float fractionPart = abs(number) - floorf(number);
	int integralPart = (int)number;

	//integral part
	int reminder = integralPart % 10;
	integralPart = integralPart / 10;

	ret = (char)(reminder + 48);

	while (integralPart != 0)
	{
		reminder = integralPart % 10;
		integralPart = integralPart / 10;
		ret = (char)(reminder + 48) + ret;
	}
	//----------------------------------------------------

	//fraction part
	if (fractionPart >= EPSILON)
	{
		ret += ".";
		int fractionCount = 0;
		while (fractionPart >= EPSILON && fractionCount < MAX_FRACTION)
		{
			fractionPart *= 10;
			ret += (char)((int)fractionPart + 48);
			fractionPart -= floorf(fractionPart);
			fractionCount++;
		}
	}
	//----------------------------------------------------

	if (number < 0)
		ret = "-" + ret;

}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
template<typename T>
T Max(const T &first, const T &second)
{
	if (first > second)
		return first;
	return second;
}
//---------------------------------------------------------------------------

//---------------------------------------------------------------------------
template<typename T>
T Min(const T &first, const T &second)
{
	if (first < second)
		return first;
	return second;
}
//---------------------------------------------------------------------------
