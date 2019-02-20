/*
* Author: Simon Waldhuber
* Available: https://github.com/waldhube16/Qbot_SW/blob/master/SolverBackend/CubeFace.cpp
*/



#include <iostream>
#include "CubeFace.h"


CubeFace::CubeFace(std::string COLOR)
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; ++i)
		{
			face_[j][i] = COLOR;
			faceCache_[j][i] = -1;
		}
	}

}

CubeFace::CubeFace()
{
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; ++i)
		{
			face_[j][i] = -1;
			faceCache_[j][i] = -1;
		}
	}
}

void CubeFace::rotate_Face()
{
	//cache current state
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; ++i)
			faceCache_[j][i] = face_[j][i];
	}

	//rotate corners
	face_[0][0] = faceCache_[2][0];
	face_[2][0] = faceCache_[2][2];
	face_[2][2] = faceCache_[0][2];
	face_[0][2] = faceCache_[0][0];

	//rotate edges
	face_[0][1] = faceCache_[1][0];
	face_[1][0] = faceCache_[2][1];
	face_[2][1] = faceCache_[1][2];
	face_[1][2] = faceCache_[0][1];


	//reset cache
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; ++i)
			faceCache_[j][i] = -1;
	}

}

void CubeFace::prime_Face()
{
	//cache current state
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; ++i)
			faceCache_[j][i] = face_[j][i];
	}

	//rotate corners

	face_[0][0] = faceCache_[0][2];
	face_[2][0] = faceCache_[0][0];
	face_[2][2] = faceCache_[2][0];
	face_[0][2] = faceCache_[2][2];

	//rotate edges
	face_[0][1] = faceCache_[1][2];
	face_[1][0] = faceCache_[0][1];
	face_[2][1] = faceCache_[1][0];
	face_[1][2] = faceCache_[2][1];


	//reset cache
	for (int j = 0; j < 3; j++)
	{
		for (int i = 0; i < 3; ++i)
			faceCache_[j][i] = -1;
	}
}

void CubeFace::print_Face()
{
	std::cout	<<  face_[0][0] << "   " <<  face_[0][1] << "   " <<  face_[0][2] << "\n"
				<<  face_[1][0] << "   " <<  face_[1][1] << "   " <<  face_[1][2] << "\n"
				<<  face_[2][0] << "   " <<  face_[2][1] << "   " <<  face_[2][2] << "\n" << std::endl;

}

std::string CubeFace::get_Faceval(int i, int j)
{
	return face_[i][j];

	

}

void CubeFace::set_Faceval(int i, int j, std::string COLOR)
{
	face_[i][j] = COLOR;
}


CubeFace::~CubeFace()
{
}



