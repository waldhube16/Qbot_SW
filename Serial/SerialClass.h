
/*
* Based on: 
* URL: https://github.com/manashmndl/SerialPort/blob/master/include/SerialPort.h
* Author: Manash Kumar Mandal
* LICENSE: MIT
* Modified by: Simon Waldhuber
* Available: https://github.com/waldhube16/Qbot_SW/blob/master/Serial/SerialClass.h
*/


#pragma once 
#ifndef SERIALCLASS_H
#define SERIALCLASS_H

#define ARDUINO_WAIT_TIME 2000
#define MAX_DATA_LENGTH 255

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

class Serial
{
private:
	//Serial comm handler
	HANDLE hSerial;
	//Connection status
	bool connected;
	//Get various information about the connection
	COMSTAT status;
	//Keep track of last error
	DWORD errors;

public:
	//Initialize Serial communication with the given COM port
	Serial(const char* portName);

	//Close the connection
	~Serial();

	//Read data in a buffer, if buffer_size is greater than the
	//maximum number of bytes available, it will return only the
	//bytes available. The function return -1 when nothing could
	//be read, the number of bytes actually read.
	int ReadData(char *buffer, unsigned int buffer_size);
	 	
	//Writes data from a buffer through the Serial connection
	//return true on success.
	bool WriteData(const char *buffer, unsigned int buffer_size);

	//Check if we are actually connected
	bool IsConnected();

	//Check if there is data to be read
	bool CheckAvailable();
};

#endif // SERIALCLASS_H_INCLUDED