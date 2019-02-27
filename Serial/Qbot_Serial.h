/*
* Author: Simon Waldhuber
* Available: https://github.com/waldhube16/Qbot_SW/blob/master/Serial/Qbot_Serial.h
*/


#pragma once
#include <stdio.h>
#include <tchar.h>	
#include <string>
#include <algorithm>
#include <iostream>
#include <fstream>
#include "SerialClass.h"

int sendStringToArduino(std::string, char, std::string, Serial*);
