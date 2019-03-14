/*
* Author: Simon Waldhuber
* Available: https://github.com/waldhube16/Qbot_SW/blob/master/Serial/Qbot_Serial.cpp
*/

#include "Qbot_Serial.h"
#include <chrono>


using namespace cv;

// application reads from the specified serial port and reports the collected data
int sendStringToArduino(std::string tx_string, char mode, std::string port, Serial* SP)
{
	auto start = std::chrono::steady_clock::now();
	// mode = 1 ... send move string
	// mode = 2 ... send stepper command
	
	//std::ofstream logfile;
	//logfile.open("ArduinoTransmissionLog.txt");
	//logfile << "Writing this to a file.\n";
	
	//logfile << "Transmission begin!\n\n";

	//std::string port_string = "\\\\.\\COM";

	//port_string = port_string + port;
	//const char* port_string_in_char = port_string.c_str();

	//Serial* SP = new Serial(port_string_in_char);    

	if (SP->IsConnected()) {}
		//logfile << ("Connection established\n");
	else
	{
		//logfile << ("Could not connect!\n");
		return -3; 
	}
		

	char incomingData[256] = "";			//pre-allocate memory
	//printf("%s\n",incomingData);
	int dataLength = 255;
	int readResult = 0;
	char send_char[] = "CC";
	
	if(mode == 1) // send string 
	{
		//std::string scramble_string = "L2 D L' F' D R D' B' R' D2 L' D2 L F2 L' B2 R U2 F2";
		std::string scramble_string = tx_string;
		//const char*  char_scramble = scramble_string.c_str();
		
		//remove spaces from string
		auto i = 0;
		char space[] = " ";
		for (i = 0; i < strlen(space); ++i)
		{
			scramble_string.erase(std::remove(scramble_string.begin(), scramble_string.end(), space[i]), scramble_string.end());
		}


		//analyze string
		for (i = 0; i < scramble_string.length(); i++)
		{
			switch (scramble_string[i + 1])
			{
			case 0x27: //prime indicator : '
				switch (scramble_string[i])
				{
				case 'U':
					send_char[0] = 'u';
					send_char[1] = '1';
					i++;
					break;
				case 'R':
					send_char[0] = 'r';
					send_char[1] = '1';
					i++;
					break;
				case 'F':
					send_char[0] = 'f';
					send_char[1] = '1';
					i++;
					break;
				case 'D':
					send_char[0] = 'd';
					send_char[1] = '1';
					i++;
					break;
				case 'L':
					send_char[0] = 'l';
					send_char[1] = '1';
					i++;
					break;
				case 'B':
					send_char[0] = 'b';
					send_char[1] = '1';
					i++;
					break;
				default:
					SP->~Serial();
					return -1; //invalid input string 
					break;
				}
				break;

			case 0x32: //half turn indicator : 2
				switch (scramble_string[i])
				{
				case 'U':
					send_char[0] = 'U';
					send_char[1] = '2';
					i++;
					break;
				case 'R':
					send_char[0] = 'R';
					send_char[1] = '2';
					i++;
					break;
				case 'F':
					send_char[0] = 'F';
					send_char[1] = '2';
					i++;
					break;
				case 'D':
					send_char[0] = 'D';
					send_char[1] = '2';
					i++;
					break;
				case 'L':
					send_char[0] = 'L';
					send_char[1] = '2';
					i++;
					break;
				case 'B':
					send_char[0] = 'B';
					send_char[1] = '2';
					i++;
					break;
				default:
					SP->~Serial();
					return -1; //invalid input string 
					break;
				}
				break;

			default:
				switch (scramble_string[i])
				{
				case 'U':
					send_char[0] = 'U';
					send_char[1] = '1';
					break;
				case 'R':
					send_char[0] = 'R';
					send_char[1] = '1';
					break;
				case 'F':
					send_char[0] = 'F';
					send_char[1] = '1';
					break;
				case 'D':
					send_char[0] = 'D';
					send_char[1] = '1';
					break;
				case 'L':
					send_char[0] = 'L';
					send_char[1] = '1';
					break;
				case 'B':
					send_char[0] = 'B';
					send_char[1] = '1';
					break;
				default:
					SP->~Serial();
					return -1; //invalid input string
					break;
				}
				break;

			}

			SP->WriteData(send_char, 2);

			while (SP->CheckAvailable() == 0)
			{}
			


			readResult = SP->ReadData(incomingData, dataLength);
			// printf("Bytes read: (0 means no data available) %i\n",readResult);
			incomingData[readResult] = 0;

			if (incomingData[0] == 75)
			{
				//logfile << ("%s", incomingData);
			}
			else
			{
				i = scramble_string.length();
				SP->~Serial();
				return -2;
			}

			//logfile << ("%s", incomingData);
		}
		

	}
	else if (mode == 2)// send command 
	{
		send_char[0] = tx_string[0];
		send_char[1] = tx_string[1];

		SP->WriteData(send_char, 2);


		while(SP->CheckAvailable() == 0)
		{}


		readResult = SP->ReadData(incomingData, dataLength);
		// printf("Bytes read: (0 means no data available) %i\n",readResult);
		incomingData[readResult] = 0;

		if (incomingData[0] == 75)
		{
			//logfile << ("%s", incomingData);
		}
		else
		{
			//SP->~Serial();
			return -2;
		}

		//logfile << ("%s", incomingData);
	}
	//return 1; //success
	//logfile.close();

	auto duration = std::chrono::steady_clock::now() - start;
	auto dur = duration.count();
	return 0;
}


int scanCube(std::string port, Serial* SP)
{
	Mat U;
	Mat	R;
	Mat	F;
	Mat	D;
	Mat	L;
	Mat	B;
	Mat test;

	VideoCapture cap(0); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;

	int flag;
	int i; 
	flag = sendStringToArduino("X0", 2, port, SP);
	flag += sendStringToArduino("Y1", 2, port, SP);

	//test = snap(cap);
	Sleep(1000);
	for (i = 0; i < 4; i++)
	{
		cap >> L;
	}
	cap >> L;// = snap(cap);
	imwrite("Left.jpeg", L);

	flag += sendStringToArduino("Y2", 2, port, SP);

	Sleep(1000);
	for (i = 0; i < 4; i++)
	{
		cap >> R;
	}
	imwrite("Right.jpeg", R);

	flag += sendStringToArduino("x0", 2, port, SP);
	flag += sendStringToArduino("Y0", 2, port, SP);
	flag += sendStringToArduino("Y1", 2, port, SP);
	flag += sendStringToArduino("y0", 2, port, SP);
	flag += sendStringToArduino("X0", 2, port, SP);
	flag += sendStringToArduino("y1", 2, port, SP);

	Sleep(1000);
	for (i = 0; i < 4; i++)
	{
		cap >> D;
	}
	imwrite("Down.jpeg", D);

	flag += sendStringToArduino("Y2", 2, port, SP);

	Sleep(1000);
	for (i = 0; i < 4; i++)
	{
		cap >> U;
	}
	imwrite("Up.jpeg", U);

	flag += sendStringToArduino("x0", 2, port, SP);
	flag += sendStringToArduino("Y0", 2, port, SP);
	flag += sendStringToArduino("Y1", 2, port, SP);
	flag += sendStringToArduino("X1", 2, port, SP);

	Sleep(1000);
	for (i = 0; i < 4; i++)
	{
		cap >> F;
	}
	imwrite("Front.jpeg", F);

	flag += sendStringToArduino("x2", 2, port, SP);

	Sleep(1000);
	for (i = 0; i < 4; i++)
	{
		cap >> B;
	}
	imwrite("Back.jpeg", B);

	flag += sendStringToArduino("X1", 2, port, SP);
	flag += sendStringToArduino("y0", 2, port, SP);
	// the camera will be deinitialized automatically in VideoCapture destructor
	return flag; 
}

Mat snap(VideoCapture cap)
{
		Mat frame;
		cap >> frame; // get a new frame from camera
		return frame; 
}
	

