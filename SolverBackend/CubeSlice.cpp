#include "CubeSlice.h"


CubeSlice::CubeSlice(std::string COLOR, std::string COLOR_T1, std::string COLOR_T2, std::string COLOR_T3, std::string COLOR_T4)
{
	SliceFace_ = CubeFace(COLOR);
	T1_ = CubeTriplet(COLOR_T1);
	T2_ = CubeTriplet(COLOR_T2);
	T3_ = CubeTriplet(COLOR_T3);
	T4_ = CubeTriplet(COLOR_T4);
}

CubeSlice::CubeSlice()
{
	SliceFace_ = CubeFace();
	T1_ = CubeTriplet();
	T2_ = CubeTriplet();
	T3_ = CubeTriplet();
	T4_ = CubeTriplet();
}


CubeSlice::~CubeSlice()
{
}
