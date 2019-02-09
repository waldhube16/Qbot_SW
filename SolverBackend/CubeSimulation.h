#pragma once
// Including SDKDDKVer.h defines the highest available Windows platform.

// If you wish to build your application for a previous Windows platform, include WinSDKVer.h and
// set the _WIN32_WINNT macro to the platform you wish to support before including SDKDDKVer.h.

#pragma once
#include <SDKDDKVer.h>

#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>
#include <string>
#include <sstream>
#include "CubeFace.h"
#include "Cube.h"


extern "C"
{
#include "AlgorithmEmbeddedC/search.h"
}

void clear_screen(char fill);
void print_cube_to_cmd();
void print_cubestring_to_cmd();
void print_help_to_cmd();
void determine_user_input(std::string, char&);
int runCMDversion();


std::string UP = "U", FRONT = "F", LEFT = "L", BACK = "B", RIGHT = "R", DOWN = "D";
Cube Erno = Cube::Cube(UP, FRONT, LEFT, BACK, RIGHT, DOWN);
