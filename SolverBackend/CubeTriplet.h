#pragma once
#include <string>

class CubeTriplet
{
public:
	CubeTriplet();
	CubeTriplet(std::string COLOR);
	~CubeTriplet();

private:
	std::string trip_arr_[3];
};

