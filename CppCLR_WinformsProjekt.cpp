/*
* Author: Simon Waldhuber
* Available:https://github.com/waldhube16/Qbot_SW/blob/master/CppCLR_WinformsProjekt.cpp
*/

// CppCLR_WinformsProjekt.cpp: Hauptprojektdatei.

#include "stdafx.h"
#include "Form1.h"

using namespace System;
using namespace System::Windows::Forms;

[STAThread]

int main() {
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	CppCLR_WinformsProjekt::Form1^ h_Form = gcnew CppCLR_WinformsProjekt::Form1();
	Application::Run(h_Form); // "CppCLR_WinformsProjekt" noch anpassen
		
	return 0;
}