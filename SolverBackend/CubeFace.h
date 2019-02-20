/*
* Author: Simon Waldhuber
* Available: https://github.com/waldhube16/Qbot_SW/blob/master/SolverBackend/CubeFace.h
*/

#pragma once
#include <string>

class CubeFace
{
public:
	CubeFace(std::string COLOR);
	CubeFace();
	void rotate_Face();
	void prime_Face();
	void print_Face();
	std::string get_Faceval(int, int);
	void set_Faceval(int i, int j, std::string value);
	~CubeFace();


	std::string face_[3][3];
	std::string faceCache_[3][3];
};

