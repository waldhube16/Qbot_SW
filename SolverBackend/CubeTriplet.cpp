#include "CubeTriplet.h"


CubeTriplet::CubeTriplet()
{
	for (int i = 0; i < 3; i++)
	{
		trip_arr_[i] = -1;
	}
}

CubeTriplet::CubeTriplet(std::string COLOR)
{
	for (int i = 0; i < 3; i++)
	{
		trip_arr_[i] = COLOR;
	}
}


CubeTriplet::~CubeTriplet()
{
}
