#pragma once
#include "CubeFace.h"
#include "CubeSlice.h"
#include <iostream>
#include <string>
#include <algorithm>

class Cube
{
public:
	Cube(std::string UP, std::string FRONT, std::string RIGHT, std::string BACK, std::string LEFT, std::string DOWN);
	void reset_cube(std::string UP, std::string FRONT, std::string LEFT, std::string BACK, std::string RIGHT, std::string DOWN);

	void import_all_faces_to_facemap(CubeFace * ptr_UP_, CubeFace * ptr_LEFT_, CubeFace * ptr_FRONT_, CubeFace * ptr_RIGHT_, CubeFace * ptr_BACK_, CubeFace * ptr_DOWN_);
	
	void print_cube();
	std::string generate_cubestring();
	bool scramble_from_cubestring(std::string cubes_tring, CubeFace * ptr_UP_, CubeFace * ptr_LEFT_, CubeFace * ptr_FRONT_, CubeFace * ptr_RIGHT_, CubeFace * ptr_BACK_, CubeFace * ptr_DOWN_);
	bool scramble_from_string(std::string);
	void R();
	void R_prime();
	void F();
	void F_prime();
	void L();
	void L_prime();
	void B();
	void B_prime();
	void D();
	void D_prime();
	void U();
	void U_prime();

	void rotate_y();
	void rotate_y_prime();
	void rotate_x();
	void rotate_x_prime();
	void rotate_z();
	void rotate_z_prime();


	~Cube();


	
	CubeFace WHITE_;
	CubeFace GREEN_;
	CubeFace RED_ ;
	CubeFace BLUE_ ;
	CubeFace ORANGE_ ;
	CubeFace YELLOW_ ;
	

	CubeFace* ptr_UP_;
	CubeFace* ptr_FRONT_;
	CubeFace* ptr_RIGHT_;
	CubeFace* ptr_BACK_;
	CubeFace* ptr_LEFT_;
	CubeFace* ptr_DOWN_;
	

	std::string face_Map_[9][12];
	std::string temp_arr_[12];
};

