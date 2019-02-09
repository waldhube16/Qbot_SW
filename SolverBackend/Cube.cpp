#include "Cube.h"


/*

Cube::Cube(CubeFace &UP, CubeFace &FRONT, CubeFace &LEFT, CubeFace &BACK, CubeFace &RIGHT, CubeFace &DOWN)
{

	for (int i = 0; i < 9; i++)
	{
		for (int j = 0; j < 12; j++)
		{
			face_Map_[i][j] = 0x20; 
			temp_arr_[i] = 0x20;
		}
	}

	import_all_faces(UP, LEFT, FRONT, RIGHT, BACK, DOWN);


}
*/
Cube::Cube(std::string UP, std::string FRONT, std::string LEFT, std::string BACK, std::string RIGHT, std::string DOWN)
{
	/*
	North_ = CubeSlice(UP, FRONT, RIGHT, BACK, LEFT);
	Ordinate_ = CubeSlice(-1, FRONT, RIGHT, BACK, LEFT);
	South_ = CubeSlice(DOWN, FRONT, RIGHT, BACK, LEFT);
	West_ = CubeSlice(LEFT, FRONT, DOWN, BACK, UP);
	Abscissa_ = CubeSlice(-1, FRONT, DOWN, BACK, UP);
	East_ = CubeSlice(RIGHT, FRONT, DOWN, BACK, UP);
	Near_ = CubeSlice(FRONT, DOWN, RIGHT, UP, LEFT);
	Applicate_ = CubeSlice(-1, DOWN, RIGHT, UP, LEFT);
	Far_ = CubeSlice(BACK, DOWN, RIGHT, UP, LEFT);
	*/

	WHITE_ = CubeFace::CubeFace(UP);
	GREEN_ = CubeFace::CubeFace(FRONT);
	RED_ = CubeFace::CubeFace(RIGHT);
	BLUE_ = CubeFace::CubeFace(BACK);
	ORANGE_ = CubeFace::CubeFace(LEFT);
	YELLOW_ = CubeFace::CubeFace(DOWN);

	ptr_UP_ = &WHITE_;
	ptr_FRONT_ = &GREEN_;
	ptr_RIGHT_ = &RED_;
	ptr_BACK_ = &BLUE_;
	ptr_LEFT_ = &ORANGE_;
	ptr_DOWN_ = &YELLOW_;

	import_all_faces_to_facemap(ptr_UP_, ptr_LEFT_, ptr_FRONT_, ptr_RIGHT_, ptr_BACK_, ptr_DOWN_);

	
}
void Cube::reset_cube(std::string UP, std::string FRONT, std::string LEFT, std::string BACK, std::string RIGHT, std::string DOWN)
{
	WHITE_ = CubeFace::CubeFace(UP);
	GREEN_ = CubeFace::CubeFace(FRONT);
	RED_ = CubeFace::CubeFace(RIGHT);
	BLUE_ = CubeFace::CubeFace(BACK);
	ORANGE_ = CubeFace::CubeFace(LEFT);
	YELLOW_ = CubeFace::CubeFace(DOWN);

	ptr_UP_ = &WHITE_;
	ptr_FRONT_ = &GREEN_;
	ptr_RIGHT_ = &RED_;
	ptr_BACK_ = &BLUE_;
	ptr_LEFT_ = &ORANGE_;
	ptr_DOWN_ = &YELLOW_;

	import_all_faces_to_facemap(ptr_UP_, ptr_LEFT_, ptr_FRONT_, ptr_RIGHT_, ptr_BACK_, ptr_DOWN_);
}

void Cube::import_all_faces_to_facemap(CubeFace * ptr_UP_, CubeFace * ptr_LEFT_, CubeFace * ptr_FRONT_, CubeFace * ptr_RIGHT_, CubeFace * ptr_BACK_, CubeFace * ptr_DOWN_)
{
	for (int i = 0; i < 9; i++) //initialize the whole array
	{
		for (int j = 0; j < 12; j++)
		{
			face_Map_[i][j] = 0x20;
			temp_arr_[i] = 0x20;
		}
	}

	for (int i = 0; i < 3; i++) //initialize up face
	{
		for (int j = 3; j < 6; j++)
		{
			face_Map_[i][j] = ptr_UP_->face_[i][j-3];
		}
	}

	for (int i = 3; i < 6; i++) //initialize left face
	{
		for (int j = 0; j < 3; j++)
		{
			face_Map_[i][j] = ptr_LEFT_->face_[i-3][j];
		}
	}

	for (int i = 3; i < 6; i++)  //initialize front face
	{
		for (int j = 3; j < 6; j++)
		{
			face_Map_[i][j] = ptr_FRONT_->face_[i-3][j-3];
		}
	}

	for (int i = 3; i < 6; i++)  //initialize right face
	{
		for (int j = 6; j < 9; j++)
		{
			face_Map_[i][j] = ptr_RIGHT_->face_[i-3][j-6];
		}
	}

	for (int i = 3; i < 6; i++)  //initialize back face
	{
		for (int j = 9; j < 12; j++)
		{
			face_Map_[i][j] = ptr_BACK_->face_[i-3][j-9];
		}
	}

	for (int i = 6; i < 9; i++)  //initialize down face
	{
		for (int j = 3; j < 6; j++)
		{
			face_Map_[i][j] = ptr_DOWN_->face_[i-6][j-3];
		}
	}
}

void Cube::print_cube()
{
	for (int i = 0; i < 9; i++)
	{
		std::cout	<< face_Map_[i][0] << face_Map_[i][1] << face_Map_[i][2] << face_Map_[i][3] << face_Map_[i][4]  << face_Map_[i][5]
					<< face_Map_[i][6] << face_Map_[i][7] << face_Map_[i][8] << face_Map_[i][9] << face_Map_[i][10] << face_Map_[i][11] << std::endl;
	}
 }

std::string Cube::generate_cubestring()
{
	//Cube defintion string is the state of the cube in form of a string based on a specific order (U1-U9 -> R1-R9 -> F1-F9 -> D1-D9 -> L1-L9 -> B1-B9 , defined by H. Kociemba):
	/*   
    The names of the facelet positions of the cube
                  |************|
                  |*U1**U2**U3*|
                  |************|
                  |*U4**U5**U6*|
                  |************|
                  |*U7**U8**U9*|
                  |************|
     |************|************|************|************|
     |*L1**L2**L3*|*F1**F2**F3*|*R1**R2**R3*|*B1**B2**B3*|
     |************|************|************|************|
     |*L4**L5**L6*|*F4**F5**F6*|*R4**R5**R6*|*B4**B5**B6*|
     |************|************|************|************|
     |*L7**L8**L9*|*F7**F8**F9*|*R7**R8**R9*|*B7**B8**B9*|
     |************|************|************|************|
                  |************|
                  |*D1**D2**D3*|
                  |************|
                  |*D4**D5**D6*|
                  |************|
                  |*D7**D8**D9*|
                  |************|

    A cube definition string "UBL..." means for example: In position U1 we have the U-color, in position U2 we have the
    B-color, in position U3 we have the L color etc. according to the order U1, U2, U3, U4, U5, U6, U7, U8, U9, R1, R2,
    R3, R4, R5, R6, R7, R8, R9, F1, F2, F3, F4, F5, F6, F7, F8, F9, D1, D2, D3, D4, D5, D6, D7, D8, D9, L1, L2, L3, L4,
    L5, L6, L7, L8, L9, B1, B2, B3, B4, B5, B6, B7, B8, B9 of the enum constants.
    */
	
	
	
	std::string Up_string =			face_Map_[0][3] + face_Map_[0][4] + face_Map_[0][5]\
								+	face_Map_[1][3] + face_Map_[1][4] + face_Map_[1][5]\
								+	face_Map_[2][3] + face_Map_[2][4] + face_Map_[2][5];

	std::string Right_string =		face_Map_[3][6] + face_Map_[3][7] + face_Map_[3][8]\
								+	face_Map_[4][6] + face_Map_[4][7] + face_Map_[4][8]\
								+	face_Map_[5][6] + face_Map_[5][7] + face_Map_[5][8];

	std::string Front_string =		face_Map_[3][3] + face_Map_[3][4] + face_Map_[3][5]\
								+	face_Map_[4][3] + face_Map_[4][4] + face_Map_[4][5]\
								+	face_Map_[5][3] + face_Map_[5][4] + face_Map_[5][5];

	std::string Down_string =		face_Map_[6][3] + face_Map_[6][4] + face_Map_[6][5]\
								+	face_Map_[7][3] + face_Map_[7][4] + face_Map_[7][5]\
								+	face_Map_[8][3] + face_Map_[8][4] + face_Map_[8][5];

	std::string Left_string =		face_Map_[3][0] + face_Map_[3][1] + face_Map_[3][2]\
								+	face_Map_[4][0] + face_Map_[4][1] + face_Map_[4][2]\
								+	face_Map_[5][0] + face_Map_[5][1] + face_Map_[5][2];

	std::string Back_string =		face_Map_[3][9] + face_Map_[3][10] + face_Map_[3][11]\
								+	face_Map_[4][9] + face_Map_[4][10] + face_Map_[4][11]\
								+	face_Map_[5][9] + face_Map_[5][10] + face_Map_[5][11];

	std::string Cube_string = Up_string + Right_string + Front_string + Down_string + Left_string + Back_string;
	return Cube_string; 
}
bool Cube::scramble_from_cubestring(std::string cube_string, CubeFace * ptr_UP_, CubeFace * ptr_LEFT_, CubeFace * ptr_FRONT_, CubeFace * ptr_RIGHT_, CubeFace * ptr_BACK_, CubeFace * ptr_DOWN_)
{
	//cube_string = "DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL"; 
	auto i = 0;
	auto sub_i = 0; 
	//order important
	CubeFace* Faces[] = { ptr_UP_, ptr_RIGHT_, ptr_FRONT_, ptr_DOWN_, ptr_LEFT_, ptr_BACK_ };

	for (i = 0; i < 54; i = i+9)
	{
		if(i > 0)
		{
			sub_i = i / 9;
		}
		else if (i == 0)
		{
			sub_i = 0; 
		}

		Faces[sub_i]->face_[0][0] = cube_string[i];
		Faces[sub_i]->face_[0][1] = cube_string[i+1];
		Faces[sub_i]->face_[0][2] = cube_string[i+2];
		Faces[sub_i]->face_[1][0] = cube_string[i+3];
		Faces[sub_i]->face_[1][1] = cube_string[i+4];
		Faces[sub_i]->face_[1][2] = cube_string[i+5];
		Faces[sub_i]->face_[2][0] = cube_string[i+6];
		Faces[sub_i]->face_[2][1] = cube_string[i+7];
		Faces[sub_i]->face_[2][2] = cube_string[i+8];
	}
	import_all_faces_to_facemap(ptr_UP_, ptr_LEFT_, ptr_FRONT_, ptr_RIGHT_, ptr_BACK_, ptr_DOWN_);
	
	if (generate_cubestring() == cube_string)
		return 1; //success
	else
		return 0; //failure
}
bool Cube::scramble_from_string(std::string scramble_string)
{
	//reset the cube
	//this->reset_cube("U", "F", "L", "B", "R", "D");

	//remove spaces from string
	auto i = 0;
	char space[] = " "; 
	for (i = 0; i < strlen(space); ++i)
	{
		scramble_string.erase(std::remove(scramble_string.begin(), scramble_string.end(), space[i]), scramble_string.end());
	}

	//remove 2s from string 
	for (i = 0; i < scramble_string.length(); i++)
	{
		if (scramble_string[i] == '2')
		{
			scramble_string[i] = scramble_string[i - 1];
		}
	}


	//analyze string
	for (i = 0; i < scramble_string.length(); i++)
	{
		switch (scramble_string[i+1])
			{
				case 0x27: //prime indicator : '
					switch (scramble_string[i])
					{
						case 'U':
							this->U_prime();
							i++;
							break;
						case 'R':
							this->R_prime();
							i++;
							break;
						case 'F':
							this->F_prime();
							i++;
							break;
						case 'D':
							this->D_prime();
							i++;
							break;
						case 'L':
							this->L_prime();
							i++;
							break;
						case 'B':
							this->B_prime();
							i++;
							break;
						default:
							return 0; //invalid input string 
							break;
					}
					break;
				
				default:
					switch (scramble_string[i])
					{
						case 'U':
							this->U();
							break;
						case 'R':
							this->R();
							break;
						case 'F':
							this->F();
							break;
						case 'D':
							this->D();
							break;
						case 'L':
							this->L();
							break;
						case 'B':
							this->B();
							break;
						default:
							return 0; //invalid input string
							break;
					}
					break;
		
		}
		
		
	}
	return 1; //success

}

void Cube::R()
{
	rotate_z_prime();
	U();
	rotate_z();
}

void Cube::R_prime()
{
	rotate_z_prime();
	U_prime();
	rotate_z();
}

void Cube::F()
{
	rotate_x();
	U();
	rotate_x_prime();
}

void Cube::F_prime()
{
	rotate_x();
	U_prime();
	rotate_x_prime();
}

void Cube::L()
{
	rotate_z();
	U();
	rotate_z_prime();
}

void Cube::L_prime()
{
	rotate_z();
	U_prime();
	rotate_z_prime();
}

void Cube::B()
{
	rotate_x_prime();
	U();
	rotate_x();
}

void Cube::B_prime()
{
	rotate_x_prime();
	U_prime();
	rotate_x();
}

void Cube::D()
{
	rotate_x_prime();
	rotate_x_prime();
	U();
	rotate_x();
	rotate_x();
}

void Cube::D_prime()
{
	rotate_x_prime();
	rotate_x_prime();
	U_prime();
	rotate_x();
	rotate_x();
}

void Cube::U()
{
	std::string temp_arr_left[3];
	std::string temp_arr_front[3];
	std::string temp_arr_right[3];
	std::string temp_arr_back[3];

	//rotate tiles on vertical faces - direction : <---
	for (int i = 0; i < 3; i++)
	{
		temp_arr_left[i] = ptr_LEFT_->face_[0][i];
		temp_arr_front[i] = ptr_FRONT_->face_[0][i];
		temp_arr_right[i] = ptr_RIGHT_->face_[0][i];
		temp_arr_back[i] = ptr_BACK_->face_[0][i];
	}

	for (int i = 0; i < 3; i++)
	{
		ptr_LEFT_->face_[0][i] = temp_arr_front[i];
		ptr_FRONT_->face_[0][i] = temp_arr_right[i];
		ptr_RIGHT_->face_[0][i] = temp_arr_back[i];
		ptr_BACK_->face_[0][i] = temp_arr_left[i];
	}
	
	ptr_UP_->rotate_Face(); 

}

void Cube::U_prime()
{
	std::string temp_arr_left[3];
	std::string temp_arr_front[3];
	std::string temp_arr_right[3];
	std::string temp_arr_back[3];

	//rotate tiles on vertical faces - direction : --->
	for (int i = 0; i < 3; i++)
	{
		temp_arr_left[i] = ptr_LEFT_->face_[0][i];
		temp_arr_front[i] = ptr_FRONT_->face_[0][i];
		temp_arr_right[i] = ptr_RIGHT_->face_[0][i];
		temp_arr_back[i] = ptr_BACK_->face_[0][i];
	}

	for (int i = 0; i < 3; i++)
	{
		ptr_LEFT_->face_[0][i] = temp_arr_back[i];
		ptr_FRONT_->face_[0][i] = temp_arr_left[i];
		ptr_RIGHT_->face_[0][i] = temp_arr_front[i];
		ptr_BACK_->face_[0][i] = temp_arr_right[i];
	}

	ptr_UP_->prime_Face();



}

void Cube::rotate_y()
{
	CubeFace* temp_ptr_left = ptr_LEFT_;
	CubeFace* temp_ptr_front = ptr_FRONT_;
	CubeFace* temp_ptr_right = ptr_RIGHT_;
	CubeFace* temp_ptr_back = ptr_BACK_;


	ptr_UP_->rotate_Face();
	ptr_DOWN_->prime_Face();

	ptr_LEFT_ = temp_ptr_front;
	ptr_FRONT_ = temp_ptr_right;
	ptr_RIGHT_ = temp_ptr_back;
	ptr_BACK_ = temp_ptr_left;
}

void Cube::rotate_y_prime()
{
	CubeFace* temp_ptr_left = ptr_LEFT_;
	CubeFace* temp_ptr_front = ptr_FRONT_;
	CubeFace* temp_ptr_right = ptr_RIGHT_;
	CubeFace* temp_ptr_back = ptr_BACK_;


	ptr_UP_->prime_Face();
	ptr_DOWN_->rotate_Face();

	ptr_LEFT_ = temp_ptr_back;
	ptr_FRONT_ = temp_ptr_left;
	ptr_RIGHT_ = temp_ptr_front;
	ptr_BACK_ = temp_ptr_right;
}

void Cube::rotate_x()
{
	CubeFace* temp_ptr_up = ptr_UP_;
	CubeFace* temp_ptr_front = ptr_FRONT_;
	CubeFace* temp_ptr_back = ptr_BACK_;
	CubeFace* temp_ptr_down = ptr_DOWN_;

	ptr_RIGHT_->rotate_Face();
	ptr_LEFT_->prime_Face();
	ptr_UP_->rotate_Face();
	ptr_UP_->rotate_Face();
	ptr_BACK_->rotate_Face();
	ptr_BACK_->rotate_Face();
	
	ptr_BACK_ = temp_ptr_up;
	ptr_UP_ = temp_ptr_front;
	ptr_FRONT_ = temp_ptr_down;
	ptr_DOWN_ = temp_ptr_back;


}

void Cube::rotate_x_prime()
{
	CubeFace* temp_ptr_up = ptr_UP_;
	CubeFace* temp_ptr_front = ptr_FRONT_;
	CubeFace* temp_ptr_back = ptr_BACK_;
	CubeFace* temp_ptr_down = ptr_DOWN_;

	ptr_RIGHT_->prime_Face();
	ptr_LEFT_->rotate_Face();
	ptr_DOWN_->prime_Face();
	ptr_DOWN_->prime_Face();
	ptr_BACK_->prime_Face();
	ptr_BACK_->prime_Face();

	ptr_BACK_ = temp_ptr_down;
	ptr_UP_ = temp_ptr_back;
	ptr_FRONT_ = temp_ptr_up;
	ptr_DOWN_ = temp_ptr_front;


}

void Cube::rotate_z()
{
	CubeFace* temp_ptr_up = ptr_UP_;
	CubeFace* temp_ptr_right = ptr_RIGHT_;
	CubeFace* temp_ptr_down = ptr_DOWN_;
	CubeFace* temp_ptr_left = ptr_LEFT_;

	ptr_UP_->rotate_Face();
	ptr_FRONT_->rotate_Face();
	ptr_RIGHT_->rotate_Face();
	ptr_DOWN_->rotate_Face();
	ptr_LEFT_->rotate_Face();
	ptr_BACK_->prime_Face();



	ptr_RIGHT_ = temp_ptr_up;
	ptr_DOWN_ = temp_ptr_right;
	ptr_LEFT_ = temp_ptr_down;
	ptr_UP_ = temp_ptr_left;
	

}

void Cube::rotate_z_prime()
{
	CubeFace* temp_ptr_up = ptr_UP_;
	CubeFace* temp_ptr_right = ptr_RIGHT_;
	CubeFace* temp_ptr_down = ptr_DOWN_;
	CubeFace* temp_ptr_left = ptr_LEFT_;

	ptr_UP_->prime_Face();
	ptr_FRONT_->prime_Face();
	ptr_RIGHT_->prime_Face();
	ptr_DOWN_->prime_Face();
	ptr_LEFT_->prime_Face();
	ptr_BACK_->rotate_Face();



	ptr_RIGHT_ = temp_ptr_down;
	ptr_DOWN_ = temp_ptr_left;
	ptr_LEFT_ = temp_ptr_up;
	ptr_UP_ = temp_ptr_right;


}

Cube::~Cube()
{
}
