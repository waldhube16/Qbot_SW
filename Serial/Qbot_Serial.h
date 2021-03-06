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
#include "opencv2/opencv.hpp"

int sendStringToArduino(std::string tx_string, char mode, std::string port, Serial* SP);

int scanCube(std::string port, Serial* SP);
cv::Mat snap(cv::VideoCapture cap); 
