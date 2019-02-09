#pragma once
#include <stdio.h>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>

int sendStringToArduino(std::string, char, std::string);
