#pragma once
#include "CubeTriplet.h"
#include "CubeFace.h"

class CubeSlice
{
public:
	CubeSlice(std::string COLOR, std::string COLOR_T1, std::string COLOR_T2, std::string COLOR_T3, std::string COLOR_T4);
	CubeSlice();
	~CubeSlice();

private:
	CubeFace SliceFace_;
	CubeTriplet T1_;
	CubeTriplet T2_;
	CubeTriplet T3_;
	CubeTriplet T4_;

};

