#pragma once
#include <string>
#include "../Qbot_GUI/SolverBackend/CubeSimulation.h"
#include "../Qbot_GUI/Qbot_Serial/Qbot_Serial.h"
#include <msclr\marshal_cppstd.h>

namespace CppCLR_WinformsProjekt {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für Form1
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		
		char colorIndex = 'X';
		//'X' ... recoloring not enabled
		//'O' ... recoloring enabled
		//'U' ... Color of Up-side
		//'R' ... Color of Right-side
		//'F' ... Color of Front-side
		//'D' ... Color of Down-side
		//'L' ... Color of Left-side
		//'B' ... Color of Back-side

		

		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

		void changeSpecificPanelColor(System::Windows::Forms::Panel^ sender)
		{
			System::Drawing::Color filling = System::Drawing::Color::White;
			switch (colorIndex)
			{
				case 'U':
					filling = System::Drawing::Color::White;
					break;
				case 'R':
					filling = System::Drawing::Color::Red;
					break;
				case 'F':
					filling = System::Drawing::Color::Lime;
					break;
				case 'D':
					filling = System::Drawing::Color::Yellow;
					break;
				case 'L':
					filling = System::Drawing::Color::Orange;
					break;
				case 'B':
					filling = System::Drawing::Color::Blue;
					break;

				default:
					filling = System::Drawing::Color::Gray;
					break;
			}

			sender->BackColor = filling;
		}

		void changePanelColor(int num, char face)
		{
			System::Drawing::Color filling = System::Drawing::Color::White;
			switch (face)
			{
				case 'U':
					filling = System::Drawing::Color::White;
					break;
				case 'R':
					filling = System::Drawing::Color::Red;
					break;
				case 'F':
					filling = System::Drawing::Color::Lime;
					break;
				case 'D':
					filling = System::Drawing::Color::Yellow;
					break;
				case 'L':
					filling = System::Drawing::Color::Orange;
					break;
				case 'B':
					filling = System::Drawing::Color::Blue;
					break;


				default:
					filling = System::Drawing::Color::Gray;
					break;
			}
			
			this->getPanel(num)->BackColor = filling; 
		}
		
		std::string  createStringFromPanels()
		{
			std::string panel_string = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";
			for (size_t i = 1; i <= 54 ; i++)
			{
				System::Drawing::Color panelColor = this->getPanel(i)->BackColor;
				if (panelColor == System::Drawing::Color::Gray)
				{
					panel_string[i - 1] = 'X'; 
				}
				else if(panelColor == System::Drawing::Color::White)
				{
					panel_string[i - 1] = 'U';
				}
				else if (panelColor == System::Drawing::Color::Red)
				{
					panel_string[i - 1] = 'R';
				}
				else if (panelColor == System::Drawing::Color::Lime)
				{
					panel_string[i - 1] = 'F';
				}
				else if (panelColor == System::Drawing::Color::Yellow)
				{
					panel_string[i - 1] = 'D';
				}
				else if (panelColor == System::Drawing::Color::Orange)
				{
					panel_string[i - 1] = 'L';
				}
				else if (panelColor == System::Drawing::Color::Blue)
				{
					panel_string[i - 1] = 'B';
				}
				else
				{
					panel_string[i - 1] = 'X';
				}
				

			}
			return panel_string; 
		}

		System::Windows::Forms::Panel^ getPanel(int num)
		{
			switch (num)
			{
			
				case 1: return U1;
				case 2: return U2;
				case 3: return U3;
				case 4: return U4;
				case 5: return U5;
				case 6: return U6;
				case 7: return U7;
				case 8: return U8;
				case 9: return U9;
				case 10: return R1;
				case 11: return R2;
				case 12: return R3;
				case 13: return R4;
				case 14: return R5;
				case 15: return R6;
				case 16: return R7;
				case 17: return R8;
				case 18: return R9;
				case 19: return F1;
				case 20: return F2;
				case 21: return F3;
				case 22: return F4;
				case 23: return F5;
				case 24: return F6;
				case 25: return F7;
				case 26: return F8;
				case 27: return F9;
				case 28: return D1;
				case 29: return D2;
				case 30: return D3;
				case 31: return D4;
				case 32: return D5;
				case 33: return D6;
				case 34: return D7;
				case 35: return D8;
				case 36: return D9;
				case 37: return L1;
				case 38: return L2;
				case 39: return L3;
				case 40: return L4;
				case 41: return L5;
				case 42: return L6;
				case 43: return L7;
				case 44: return L8;
				case 45: return L9;
				case 46: return B1;
				case 47: return B2;
				case 48: return B3;
				case 49: return B4;
				case 50: return B5;
				case 51: return B6;
				case 52: return B7;
				case 53: return B8;
				case 54: return B9;

			default:
				break;
			}
		}

		void colorPanelsFromString(std::string cubestring)
		{
			//cubestring = "DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL";

			for (size_t i = 1; i < cubestring.length()+1; i++)
			{
				changePanelColor(i, cubestring[i - 1]);
			}
		}

		void removePanelColors()
		{
			std::string cubestring = "XXXXUXXXXXXXXRXXXXXXXXFXXXXXXXXDXXXXXXXXLXXXXXXXXBXXXX";

			for (size_t i = 1; i < cubestring.length() + 1; i++)
			{
				changePanelColor(i, cubestring[i - 1]);
			}
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Panel^  U1;
	private: System::Windows::Forms::Panel^  U2;
	private: System::Windows::Forms::Panel^  U3;
	private: System::Windows::Forms::Panel^  U4;
	private: System::Windows::Forms::Panel^  U5;
	private: System::Windows::Forms::Panel^  U6;
	private: System::Windows::Forms::Panel^  U7;
	private: System::Windows::Forms::Panel^  U8;
	private: System::Windows::Forms::Panel^  U9;
	private: System::Windows::Forms::Panel^  F1;
	private: System::Windows::Forms::Panel^  F2;
	private: System::Windows::Forms::Panel^  F3;
	private: System::Windows::Forms::Panel^  F4;
	private: System::Windows::Forms::Panel^  F5;
	private: System::Windows::Forms::Panel^  F6;
	private: System::Windows::Forms::Panel^  F7;
	private: System::Windows::Forms::Panel^  F8;
	private: System::Windows::Forms::Panel^  F9;
	private: System::Windows::Forms::Panel^  R1;
	private: System::Windows::Forms::Panel^  R2;
	private: System::Windows::Forms::Panel^  R3;
	private: System::Windows::Forms::Panel^  R4;
	private: System::Windows::Forms::Panel^  R5;
	private: System::Windows::Forms::Panel^  R6;
	private: System::Windows::Forms::Panel^  R7;
	private: System::Windows::Forms::Panel^  R8;
	private: System::Windows::Forms::Panel^  R9;
	private: System::Windows::Forms::Panel^  B1;
	private: System::Windows::Forms::Panel^  B2;
	private: System::Windows::Forms::Panel^  B3;
	private: System::Windows::Forms::Panel^  B4;
	private: System::Windows::Forms::Panel^  B5;
	private: System::Windows::Forms::Panel^  B6;
	private: System::Windows::Forms::Panel^  B7;
	private: System::Windows::Forms::Panel^  B8;
	private: System::Windows::Forms::Panel^  B9;
	private: System::Windows::Forms::Panel^  D1;
	private: System::Windows::Forms::Panel^  D2;
	private: System::Windows::Forms::Panel^  D3;
	private: System::Windows::Forms::Panel^  D4;
	private: System::Windows::Forms::Panel^  D5;
	private: System::Windows::Forms::Panel^  D6;
	private: System::Windows::Forms::Panel^  D7;
	private: System::Windows::Forms::Panel^  D8;
	private: System::Windows::Forms::Panel^  D9;
	private: System::Windows::Forms::Panel^  L1;
	private: System::Windows::Forms::Panel^  L2;
	private: System::Windows::Forms::Panel^  L3;
	private: System::Windows::Forms::Panel^  L4;
	private: System::Windows::Forms::Panel^  L5;
	private: System::Windows::Forms::Panel^  L6;
	private: System::Windows::Forms::Panel^  L7;
	private: System::Windows::Forms::Panel^  L8;
	private: System::Windows::Forms::Panel^  L9;

	private: System::Windows::Forms::Button^  btn_R;
	private: System::Windows::Forms::Button^  btn_U;
	private: System::Windows::Forms::Button^  btn_F;
	private: System::Windows::Forms::Button^  btn_D;
	private: System::Windows::Forms::Button^  btn_L;
	private: System::Windows::Forms::Button^  btn_B;
	private: System::Windows::Forms::Button^  btn_Ri;
	private: System::Windows::Forms::Button^  btn_Ui;
	private: System::Windows::Forms::Button^  btn_Fi;
	private: System::Windows::Forms::Button^  btn_Di;
	private: System::Windows::Forms::Button^  btn_Li;
	private: System::Windows::Forms::Button^  btn_Bi;
	private: System::Windows::Forms::Button^  btn_Reset;
	private: System::Windows::Forms::Button^  btn_GenSolution;

	private: System::Windows::Forms::TextBox^  txt_SolutionString;
	private: System::Windows::Forms::Button^  btn_scrambleString;
	private: System::Windows::Forms::Button^  btn_SendToArduino;
private: System::Windows::Forms::Button^  btn_Recolor;
private: System::Windows::Forms::Button^  btn_EndRecolor;

private: System::Windows::Forms::Button^  btn_scrambleCubeString;

private: System::Windows::Forms::Button^  btn_CmdToArduino;
private: System::Windows::Forms::ComboBox^  box_CmdForArduino;
private: System::Windows::Forms::Label^  lbl_ComPort;
private: System::Windows::Forms::NumericUpDown^  numdd_ComPort;







	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->U1 = (gcnew System::Windows::Forms::Panel());
			this->U2 = (gcnew System::Windows::Forms::Panel());
			this->U3 = (gcnew System::Windows::Forms::Panel());
			this->U4 = (gcnew System::Windows::Forms::Panel());
			this->U5 = (gcnew System::Windows::Forms::Panel());
			this->U6 = (gcnew System::Windows::Forms::Panel());
			this->U7 = (gcnew System::Windows::Forms::Panel());
			this->U8 = (gcnew System::Windows::Forms::Panel());
			this->U9 = (gcnew System::Windows::Forms::Panel());
			this->F1 = (gcnew System::Windows::Forms::Panel());
			this->F2 = (gcnew System::Windows::Forms::Panel());
			this->F3 = (gcnew System::Windows::Forms::Panel());
			this->F4 = (gcnew System::Windows::Forms::Panel());
			this->F5 = (gcnew System::Windows::Forms::Panel());
			this->F6 = (gcnew System::Windows::Forms::Panel());
			this->F7 = (gcnew System::Windows::Forms::Panel());
			this->F8 = (gcnew System::Windows::Forms::Panel());
			this->F9 = (gcnew System::Windows::Forms::Panel());
			this->R1 = (gcnew System::Windows::Forms::Panel());
			this->R2 = (gcnew System::Windows::Forms::Panel());
			this->R3 = (gcnew System::Windows::Forms::Panel());
			this->R4 = (gcnew System::Windows::Forms::Panel());
			this->R5 = (gcnew System::Windows::Forms::Panel());
			this->R6 = (gcnew System::Windows::Forms::Panel());
			this->R7 = (gcnew System::Windows::Forms::Panel());
			this->R8 = (gcnew System::Windows::Forms::Panel());
			this->R9 = (gcnew System::Windows::Forms::Panel());
			this->B1 = (gcnew System::Windows::Forms::Panel());
			this->B2 = (gcnew System::Windows::Forms::Panel());
			this->B3 = (gcnew System::Windows::Forms::Panel());
			this->B4 = (gcnew System::Windows::Forms::Panel());
			this->B5 = (gcnew System::Windows::Forms::Panel());
			this->B6 = (gcnew System::Windows::Forms::Panel());
			this->B7 = (gcnew System::Windows::Forms::Panel());
			this->B8 = (gcnew System::Windows::Forms::Panel());
			this->B9 = (gcnew System::Windows::Forms::Panel());
			this->D1 = (gcnew System::Windows::Forms::Panel());
			this->D2 = (gcnew System::Windows::Forms::Panel());
			this->D3 = (gcnew System::Windows::Forms::Panel());
			this->D4 = (gcnew System::Windows::Forms::Panel());
			this->D5 = (gcnew System::Windows::Forms::Panel());
			this->D6 = (gcnew System::Windows::Forms::Panel());
			this->D7 = (gcnew System::Windows::Forms::Panel());
			this->D8 = (gcnew System::Windows::Forms::Panel());
			this->D9 = (gcnew System::Windows::Forms::Panel());
			this->L1 = (gcnew System::Windows::Forms::Panel());
			this->L2 = (gcnew System::Windows::Forms::Panel());
			this->L3 = (gcnew System::Windows::Forms::Panel());
			this->L4 = (gcnew System::Windows::Forms::Panel());
			this->L5 = (gcnew System::Windows::Forms::Panel());
			this->L6 = (gcnew System::Windows::Forms::Panel());
			this->L7 = (gcnew System::Windows::Forms::Panel());
			this->L8 = (gcnew System::Windows::Forms::Panel());
			this->L9 = (gcnew System::Windows::Forms::Panel());
			this->btn_R = (gcnew System::Windows::Forms::Button());
			this->btn_U = (gcnew System::Windows::Forms::Button());
			this->btn_F = (gcnew System::Windows::Forms::Button());
			this->btn_D = (gcnew System::Windows::Forms::Button());
			this->btn_L = (gcnew System::Windows::Forms::Button());
			this->btn_B = (gcnew System::Windows::Forms::Button());
			this->btn_Ri = (gcnew System::Windows::Forms::Button());
			this->btn_Ui = (gcnew System::Windows::Forms::Button());
			this->btn_Fi = (gcnew System::Windows::Forms::Button());
			this->btn_Di = (gcnew System::Windows::Forms::Button());
			this->btn_Li = (gcnew System::Windows::Forms::Button());
			this->btn_Bi = (gcnew System::Windows::Forms::Button());
			this->btn_Reset = (gcnew System::Windows::Forms::Button());
			this->btn_GenSolution = (gcnew System::Windows::Forms::Button());
			this->txt_SolutionString = (gcnew System::Windows::Forms::TextBox());
			this->btn_scrambleString = (gcnew System::Windows::Forms::Button());
			this->btn_SendToArduino = (gcnew System::Windows::Forms::Button());
			this->btn_Recolor = (gcnew System::Windows::Forms::Button());
			this->btn_EndRecolor = (gcnew System::Windows::Forms::Button());
			this->btn_scrambleCubeString = (gcnew System::Windows::Forms::Button());
			this->btn_CmdToArduino = (gcnew System::Windows::Forms::Button());
			this->box_CmdForArduino = (gcnew System::Windows::Forms::ComboBox());
			this->lbl_ComPort = (gcnew System::Windows::Forms::Label());
			this->numdd_ComPort = (gcnew System::Windows::Forms::NumericUpDown());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numdd_ComPort))->BeginInit();
			this->SuspendLayout();
			// 
			// U1
			// 
			this->U1->BackColor = System::Drawing::Color::White;
			this->U1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U1->Location = System::Drawing::Point(209, 42);
			this->U1->Name = L"U1";
			this->U1->Size = System::Drawing::Size(40, 40);
			this->U1->TabIndex = 0;
			this->U1->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// U2
			// 
			this->U2->BackColor = System::Drawing::Color::White;
			this->U2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U2->Location = System::Drawing::Point(255, 42);
			this->U2->Name = L"U2";
			this->U2->Size = System::Drawing::Size(40, 40);
			this->U2->TabIndex = 0;
			this->U2->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// U3
			// 
			this->U3->BackColor = System::Drawing::Color::White;
			this->U3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U3->Location = System::Drawing::Point(301, 42);
			this->U3->Name = L"U3";
			this->U3->Size = System::Drawing::Size(40, 40);
			this->U3->TabIndex = 0;
			this->U3->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// U4
			// 
			this->U4->BackColor = System::Drawing::Color::White;
			this->U4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U4->Location = System::Drawing::Point(209, 88);
			this->U4->Name = L"U4";
			this->U4->Size = System::Drawing::Size(40, 40);
			this->U4->TabIndex = 0;
			this->U4->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// U5
			// 
			this->U5->BackColor = System::Drawing::Color::White;
			this->U5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U5->Location = System::Drawing::Point(255, 88);
			this->U5->Name = L"U5";
			this->U5->Size = System::Drawing::Size(40, 40);
			this->U5->TabIndex = 0;
			this->U5->Click += gcnew System::EventHandler(this, &Form1::U5_Click);
			// 
			// U6
			// 
			this->U6->BackColor = System::Drawing::Color::White;
			this->U6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U6->Location = System::Drawing::Point(301, 88);
			this->U6->Name = L"U6";
			this->U6->Size = System::Drawing::Size(40, 40);
			this->U6->TabIndex = 0;
			this->U6->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// U7
			// 
			this->U7->BackColor = System::Drawing::Color::White;
			this->U7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U7->Location = System::Drawing::Point(209, 134);
			this->U7->Name = L"U7";
			this->U7->Size = System::Drawing::Size(40, 40);
			this->U7->TabIndex = 0;
			this->U7->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// U8
			// 
			this->U8->BackColor = System::Drawing::Color::White;
			this->U8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U8->Location = System::Drawing::Point(255, 134);
			this->U8->Name = L"U8";
			this->U8->Size = System::Drawing::Size(40, 40);
			this->U8->TabIndex = 0;
			this->U8->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// U9
			// 
			this->U9->BackColor = System::Drawing::Color::White;
			this->U9->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->U9->Location = System::Drawing::Point(301, 134);
			this->U9->Name = L"U9";
			this->U9->Size = System::Drawing::Size(40, 40);
			this->U9->TabIndex = 0;
			this->U9->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F1
			// 
			this->F1->BackColor = System::Drawing::Color::Lime;
			this->F1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F1->Location = System::Drawing::Point(209, 180);
			this->F1->Name = L"F1";
			this->F1->Size = System::Drawing::Size(40, 40);
			this->F1->TabIndex = 0;
			this->F1->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F2
			// 
			this->F2->BackColor = System::Drawing::Color::Lime;
			this->F2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F2->Location = System::Drawing::Point(255, 180);
			this->F2->Name = L"F2";
			this->F2->Size = System::Drawing::Size(40, 40);
			this->F2->TabIndex = 0;
			this->F2->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F3
			// 
			this->F3->BackColor = System::Drawing::Color::Lime;
			this->F3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F3->Location = System::Drawing::Point(301, 180);
			this->F3->Name = L"F3";
			this->F3->Size = System::Drawing::Size(40, 40);
			this->F3->TabIndex = 0;
			this->F3->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F4
			// 
			this->F4->BackColor = System::Drawing::Color::Lime;
			this->F4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F4->Location = System::Drawing::Point(209, 226);
			this->F4->Name = L"F4";
			this->F4->Size = System::Drawing::Size(40, 40);
			this->F4->TabIndex = 0;
			this->F4->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F5
			// 
			this->F5->BackColor = System::Drawing::Color::Lime;
			this->F5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F5->Location = System::Drawing::Point(255, 226);
			this->F5->Name = L"F5";
			this->F5->Size = System::Drawing::Size(40, 40);
			this->F5->TabIndex = 0;
			this->F5->Click += gcnew System::EventHandler(this, &Form1::F5_Click);
			// 
			// F6
			// 
			this->F6->BackColor = System::Drawing::Color::Lime;
			this->F6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F6->Location = System::Drawing::Point(301, 226);
			this->F6->Name = L"F6";
			this->F6->Size = System::Drawing::Size(40, 40);
			this->F6->TabIndex = 0;
			this->F6->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F7
			// 
			this->F7->BackColor = System::Drawing::Color::Lime;
			this->F7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F7->Location = System::Drawing::Point(209, 272);
			this->F7->Name = L"F7";
			this->F7->Size = System::Drawing::Size(40, 40);
			this->F7->TabIndex = 0;
			this->F7->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F8
			// 
			this->F8->BackColor = System::Drawing::Color::Lime;
			this->F8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F8->Location = System::Drawing::Point(255, 272);
			this->F8->Name = L"F8";
			this->F8->Size = System::Drawing::Size(40, 40);
			this->F8->TabIndex = 0;
			this->F8->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// F9
			// 
			this->F9->BackColor = System::Drawing::Color::Lime;
			this->F9->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->F9->Location = System::Drawing::Point(301, 272);
			this->F9->Name = L"F9";
			this->F9->Size = System::Drawing::Size(40, 40);
			this->F9->TabIndex = 0;
			this->F9->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R1
			// 
			this->R1->BackColor = System::Drawing::Color::Red;
			this->R1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R1->Location = System::Drawing::Point(347, 180);
			this->R1->Name = L"R1";
			this->R1->Size = System::Drawing::Size(40, 40);
			this->R1->TabIndex = 0;
			this->R1->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R2
			// 
			this->R2->BackColor = System::Drawing::Color::Red;
			this->R2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R2->Location = System::Drawing::Point(393, 180);
			this->R2->Name = L"R2";
			this->R2->Size = System::Drawing::Size(40, 40);
			this->R2->TabIndex = 0;
			this->R2->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R3
			// 
			this->R3->BackColor = System::Drawing::Color::Red;
			this->R3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R3->Location = System::Drawing::Point(439, 180);
			this->R3->Name = L"R3";
			this->R3->Size = System::Drawing::Size(40, 40);
			this->R3->TabIndex = 0;
			this->R3->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R4
			// 
			this->R4->BackColor = System::Drawing::Color::Red;
			this->R4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R4->Location = System::Drawing::Point(347, 226);
			this->R4->Name = L"R4";
			this->R4->Size = System::Drawing::Size(40, 40);
			this->R4->TabIndex = 0;
			this->R4->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R5
			// 
			this->R5->BackColor = System::Drawing::Color::Red;
			this->R5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R5->Location = System::Drawing::Point(393, 226);
			this->R5->Name = L"R5";
			this->R5->Size = System::Drawing::Size(40, 40);
			this->R5->TabIndex = 0;
			this->R5->Click += gcnew System::EventHandler(this, &Form1::R5_Click);
			// 
			// R6
			// 
			this->R6->BackColor = System::Drawing::Color::Red;
			this->R6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R6->Location = System::Drawing::Point(439, 226);
			this->R6->Name = L"R6";
			this->R6->Size = System::Drawing::Size(40, 40);
			this->R6->TabIndex = 0;
			this->R6->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R7
			// 
			this->R7->BackColor = System::Drawing::Color::Red;
			this->R7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R7->Location = System::Drawing::Point(347, 272);
			this->R7->Name = L"R7";
			this->R7->Size = System::Drawing::Size(40, 40);
			this->R7->TabIndex = 0;
			this->R7->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R8
			// 
			this->R8->BackColor = System::Drawing::Color::Red;
			this->R8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R8->Location = System::Drawing::Point(393, 272);
			this->R8->Name = L"R8";
			this->R8->Size = System::Drawing::Size(40, 40);
			this->R8->TabIndex = 0;
			this->R8->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// R9
			// 
			this->R9->BackColor = System::Drawing::Color::Red;
			this->R9->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->R9->Location = System::Drawing::Point(439, 272);
			this->R9->Name = L"R9";
			this->R9->Size = System::Drawing::Size(40, 40);
			this->R9->TabIndex = 0;
			this->R9->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B1
			// 
			this->B1->BackColor = System::Drawing::Color::Blue;
			this->B1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B1->Location = System::Drawing::Point(485, 180);
			this->B1->Name = L"B1";
			this->B1->Size = System::Drawing::Size(40, 40);
			this->B1->TabIndex = 0;
			this->B1->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B2
			// 
			this->B2->BackColor = System::Drawing::Color::Blue;
			this->B2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B2->Location = System::Drawing::Point(531, 180);
			this->B2->Name = L"B2";
			this->B2->Size = System::Drawing::Size(40, 40);
			this->B2->TabIndex = 0;
			this->B2->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B3
			// 
			this->B3->BackColor = System::Drawing::Color::Blue;
			this->B3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B3->Location = System::Drawing::Point(577, 180);
			this->B3->Name = L"B3";
			this->B3->Size = System::Drawing::Size(40, 40);
			this->B3->TabIndex = 0;
			this->B3->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B4
			// 
			this->B4->BackColor = System::Drawing::Color::Blue;
			this->B4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B4->Location = System::Drawing::Point(485, 226);
			this->B4->Name = L"B4";
			this->B4->Size = System::Drawing::Size(40, 40);
			this->B4->TabIndex = 0;
			this->B4->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B5
			// 
			this->B5->BackColor = System::Drawing::Color::Blue;
			this->B5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B5->Location = System::Drawing::Point(531, 226);
			this->B5->Name = L"B5";
			this->B5->Size = System::Drawing::Size(40, 40);
			this->B5->TabIndex = 0;
			this->B5->Click += gcnew System::EventHandler(this, &Form1::B5_Click);
			// 
			// B6
			// 
			this->B6->BackColor = System::Drawing::Color::Blue;
			this->B6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B6->Location = System::Drawing::Point(577, 226);
			this->B6->Name = L"B6";
			this->B6->Size = System::Drawing::Size(40, 40);
			this->B6->TabIndex = 0;
			this->B6->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B7
			// 
			this->B7->BackColor = System::Drawing::Color::Blue;
			this->B7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B7->Location = System::Drawing::Point(485, 272);
			this->B7->Name = L"B7";
			this->B7->Size = System::Drawing::Size(40, 40);
			this->B7->TabIndex = 0;
			this->B7->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B8
			// 
			this->B8->BackColor = System::Drawing::Color::Blue;
			this->B8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B8->Location = System::Drawing::Point(531, 272);
			this->B8->Name = L"B8";
			this->B8->Size = System::Drawing::Size(40, 40);
			this->B8->TabIndex = 0;
			this->B8->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// B9
			// 
			this->B9->BackColor = System::Drawing::Color::Blue;
			this->B9->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->B9->Location = System::Drawing::Point(577, 272);
			this->B9->Name = L"B9";
			this->B9->Size = System::Drawing::Size(40, 40);
			this->B9->TabIndex = 0;
			this->B9->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D1
			// 
			this->D1->BackColor = System::Drawing::Color::Yellow;
			this->D1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D1->Location = System::Drawing::Point(209, 318);
			this->D1->Name = L"D1";
			this->D1->Size = System::Drawing::Size(40, 40);
			this->D1->TabIndex = 0;
			this->D1->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D2
			// 
			this->D2->BackColor = System::Drawing::Color::Yellow;
			this->D2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D2->Location = System::Drawing::Point(255, 318);
			this->D2->Name = L"D2";
			this->D2->Size = System::Drawing::Size(40, 40);
			this->D2->TabIndex = 0;
			this->D2->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D3
			// 
			this->D3->BackColor = System::Drawing::Color::Yellow;
			this->D3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D3->Location = System::Drawing::Point(301, 318);
			this->D3->Name = L"D3";
			this->D3->Size = System::Drawing::Size(40, 40);
			this->D3->TabIndex = 0;
			this->D3->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D4
			// 
			this->D4->BackColor = System::Drawing::Color::Yellow;
			this->D4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D4->Location = System::Drawing::Point(209, 364);
			this->D4->Name = L"D4";
			this->D4->Size = System::Drawing::Size(40, 40);
			this->D4->TabIndex = 0;
			this->D4->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D5
			// 
			this->D5->BackColor = System::Drawing::Color::Yellow;
			this->D5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D5->Location = System::Drawing::Point(255, 364);
			this->D5->Name = L"D5";
			this->D5->Size = System::Drawing::Size(40, 40);
			this->D5->TabIndex = 0;
			this->D5->Click += gcnew System::EventHandler(this, &Form1::D5_Click);
			// 
			// D6
			// 
			this->D6->BackColor = System::Drawing::Color::Yellow;
			this->D6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D6->Location = System::Drawing::Point(301, 364);
			this->D6->Name = L"D6";
			this->D6->Size = System::Drawing::Size(40, 40);
			this->D6->TabIndex = 0;
			this->D6->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D7
			// 
			this->D7->BackColor = System::Drawing::Color::Yellow;
			this->D7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D7->Location = System::Drawing::Point(209, 410);
			this->D7->Name = L"D7";
			this->D7->Size = System::Drawing::Size(40, 40);
			this->D7->TabIndex = 0;
			this->D7->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D8
			// 
			this->D8->BackColor = System::Drawing::Color::Yellow;
			this->D8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D8->Location = System::Drawing::Point(255, 410);
			this->D8->Name = L"D8";
			this->D8->Size = System::Drawing::Size(40, 40);
			this->D8->TabIndex = 0;
			this->D8->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// D9
			// 
			this->D9->BackColor = System::Drawing::Color::Yellow;
			this->D9->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->D9->Location = System::Drawing::Point(301, 410);
			this->D9->Name = L"D9";
			this->D9->Size = System::Drawing::Size(40, 40);
			this->D9->TabIndex = 0;
			this->D9->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L1
			// 
			this->L1->BackColor = System::Drawing::Color::Orange;
			this->L1->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L1->Location = System::Drawing::Point(71, 180);
			this->L1->Name = L"L1";
			this->L1->Size = System::Drawing::Size(40, 40);
			this->L1->TabIndex = 0;
			this->L1->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L2
			// 
			this->L2->BackColor = System::Drawing::Color::Orange;
			this->L2->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L2->Location = System::Drawing::Point(117, 180);
			this->L2->Name = L"L2";
			this->L2->Size = System::Drawing::Size(40, 40);
			this->L2->TabIndex = 0;
			this->L2->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L3
			// 
			this->L3->BackColor = System::Drawing::Color::Orange;
			this->L3->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L3->Location = System::Drawing::Point(163, 180);
			this->L3->Name = L"L3";
			this->L3->Size = System::Drawing::Size(40, 40);
			this->L3->TabIndex = 0;
			this->L3->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L4
			// 
			this->L4->BackColor = System::Drawing::Color::Orange;
			this->L4->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L4->Location = System::Drawing::Point(71, 226);
			this->L4->Name = L"L4";
			this->L4->Size = System::Drawing::Size(40, 40);
			this->L4->TabIndex = 0;
			this->L4->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L5
			// 
			this->L5->BackColor = System::Drawing::Color::Orange;
			this->L5->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L5->Location = System::Drawing::Point(117, 226);
			this->L5->Name = L"L5";
			this->L5->Size = System::Drawing::Size(40, 40);
			this->L5->TabIndex = 0;
			this->L5->Click += gcnew System::EventHandler(this, &Form1::L5_Click);
			// 
			// L6
			// 
			this->L6->BackColor = System::Drawing::Color::Orange;
			this->L6->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L6->Location = System::Drawing::Point(163, 226);
			this->L6->Name = L"L6";
			this->L6->Size = System::Drawing::Size(40, 40);
			this->L6->TabIndex = 0;
			this->L6->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L7
			// 
			this->L7->BackColor = System::Drawing::Color::Orange;
			this->L7->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L7->Location = System::Drawing::Point(71, 272);
			this->L7->Name = L"L7";
			this->L7->Size = System::Drawing::Size(40, 40);
			this->L7->TabIndex = 0;
			this->L7->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L8
			// 
			this->L8->BackColor = System::Drawing::Color::Orange;
			this->L8->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L8->Location = System::Drawing::Point(117, 272);
			this->L8->Name = L"L8";
			this->L8->Size = System::Drawing::Size(40, 40);
			this->L8->TabIndex = 0;
			this->L8->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// L9
			// 
			this->L9->BackColor = System::Drawing::Color::Orange;
			this->L9->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->L9->Location = System::Drawing::Point(163, 272);
			this->L9->Name = L"L9";
			this->L9->Size = System::Drawing::Size(40, 40);
			this->L9->TabIndex = 0;
			this->L9->Click += gcnew System::EventHandler(this, &Form1::ColorablePanel_Click);
			// 
			// btn_R
			// 
			this->btn_R->Location = System::Drawing::Point(399, 42);
			this->btn_R->Name = L"btn_R";
			this->btn_R->Size = System::Drawing::Size(40, 25);
			this->btn_R->TabIndex = 2;
			this->btn_R->Text = L"R";
			this->btn_R->UseVisualStyleBackColor = true;
			this->btn_R->Click += gcnew System::EventHandler(this, &Form1::btn_R_Click);
			// 
			// btn_U
			// 
			this->btn_U->Location = System::Drawing::Point(353, 42);
			this->btn_U->Name = L"btn_U";
			this->btn_U->Size = System::Drawing::Size(40, 25);
			this->btn_U->TabIndex = 3;
			this->btn_U->Text = L"U";
			this->btn_U->UseVisualStyleBackColor = true;
			this->btn_U->Click += gcnew System::EventHandler(this, &Form1::btn_U_Click);
			// 
			// btn_F
			// 
			this->btn_F->Location = System::Drawing::Point(445, 42);
			this->btn_F->Name = L"btn_F";
			this->btn_F->Size = System::Drawing::Size(40, 25);
			this->btn_F->TabIndex = 4;
			this->btn_F->Text = L"F";
			this->btn_F->UseVisualStyleBackColor = true;
			this->btn_F->Click += gcnew System::EventHandler(this, &Form1::btn_F_Click);
			// 
			// btn_D
			// 
			this->btn_D->Location = System::Drawing::Point(491, 42);
			this->btn_D->Name = L"btn_D";
			this->btn_D->Size = System::Drawing::Size(40, 25);
			this->btn_D->TabIndex = 5;
			this->btn_D->Text = L"D";
			this->btn_D->UseVisualStyleBackColor = true;
			this->btn_D->Click += gcnew System::EventHandler(this, &Form1::btn_D_Click);
			// 
			// btn_L
			// 
			this->btn_L->Location = System::Drawing::Point(537, 42);
			this->btn_L->Name = L"btn_L";
			this->btn_L->Size = System::Drawing::Size(40, 25);
			this->btn_L->TabIndex = 6;
			this->btn_L->Text = L"L";
			this->btn_L->UseVisualStyleBackColor = true;
			this->btn_L->Click += gcnew System::EventHandler(this, &Form1::btn_L_Click);
			// 
			// btn_B
			// 
			this->btn_B->Location = System::Drawing::Point(583, 42);
			this->btn_B->Name = L"btn_B";
			this->btn_B->Size = System::Drawing::Size(40, 25);
			this->btn_B->TabIndex = 7;
			this->btn_B->Text = L"B";
			this->btn_B->UseVisualStyleBackColor = true;
			this->btn_B->Click += gcnew System::EventHandler(this, &Form1::btn_B_Click);
			// 
			// btn_Ri
			// 
			this->btn_Ri->Location = System::Drawing::Point(399, 73);
			this->btn_Ri->Name = L"btn_Ri";
			this->btn_Ri->Size = System::Drawing::Size(40, 25);
			this->btn_Ri->TabIndex = 2;
			this->btn_Ri->Text = L"R\'";
			this->btn_Ri->UseVisualStyleBackColor = true;
			this->btn_Ri->Click += gcnew System::EventHandler(this, &Form1::btn_Ri_Click);
			// 
			// btn_Ui
			// 
			this->btn_Ui->Location = System::Drawing::Point(353, 73);
			this->btn_Ui->Name = L"btn_Ui";
			this->btn_Ui->Size = System::Drawing::Size(40, 25);
			this->btn_Ui->TabIndex = 3;
			this->btn_Ui->Text = L"U\'";
			this->btn_Ui->UseVisualStyleBackColor = true;
			this->btn_Ui->Click += gcnew System::EventHandler(this, &Form1::btn_Ui_Click);
			// 
			// btn_Fi
			// 
			this->btn_Fi->Location = System::Drawing::Point(445, 73);
			this->btn_Fi->Name = L"btn_Fi";
			this->btn_Fi->Size = System::Drawing::Size(40, 25);
			this->btn_Fi->TabIndex = 4;
			this->btn_Fi->Text = L"F\'";
			this->btn_Fi->UseVisualStyleBackColor = true;
			this->btn_Fi->Click += gcnew System::EventHandler(this, &Form1::btn_Fi_Click);
			// 
			// btn_Di
			// 
			this->btn_Di->Location = System::Drawing::Point(491, 73);
			this->btn_Di->Name = L"btn_Di";
			this->btn_Di->Size = System::Drawing::Size(40, 25);
			this->btn_Di->TabIndex = 5;
			this->btn_Di->Text = L"D\'";
			this->btn_Di->UseVisualStyleBackColor = true;
			this->btn_Di->Click += gcnew System::EventHandler(this, &Form1::btn_Di_Click);
			// 
			// btn_Li
			// 
			this->btn_Li->Location = System::Drawing::Point(537, 73);
			this->btn_Li->Name = L"btn_Li";
			this->btn_Li->Size = System::Drawing::Size(40, 25);
			this->btn_Li->TabIndex = 6;
			this->btn_Li->Text = L"L\'";
			this->btn_Li->UseVisualStyleBackColor = true;
			this->btn_Li->Click += gcnew System::EventHandler(this, &Form1::btn_Li_Click);
			// 
			// btn_Bi
			// 
			this->btn_Bi->Location = System::Drawing::Point(583, 73);
			this->btn_Bi->Name = L"btn_Bi";
			this->btn_Bi->Size = System::Drawing::Size(40, 25);
			this->btn_Bi->TabIndex = 7;
			this->btn_Bi->Text = L"B\'";
			this->btn_Bi->UseVisualStyleBackColor = true;
			this->btn_Bi->Click += gcnew System::EventHandler(this, &Form1::btn_Bi_Click);
			// 
			// btn_Reset
			// 
			this->btn_Reset->Location = System::Drawing::Point(26, 13);
			this->btn_Reset->Name = L"btn_Reset";
			this->btn_Reset->Size = System::Drawing::Size(99, 25);
			this->btn_Reset->TabIndex = 8;
			this->btn_Reset->Text = L"Reset Cube";
			this->btn_Reset->UseVisualStyleBackColor = true;
			this->btn_Reset->Click += gcnew System::EventHandler(this, &Form1::btn_Reset_Click);
			// 
			// btn_GenSolution
			// 
			this->btn_GenSolution->Location = System::Drawing::Point(26, 45);
			this->btn_GenSolution->Name = L"btn_GenSolution";
			this->btn_GenSolution->Size = System::Drawing::Size(120, 23);
			this->btn_GenSolution->TabIndex = 9;
			this->btn_GenSolution->Text = L"Generate Solution";
			this->btn_GenSolution->UseVisualStyleBackColor = true;
			this->btn_GenSolution->Click += gcnew System::EventHandler(this, &Form1::btn_GenSolution_Click);
			// 
			// txt_SolutionString
			// 
			this->txt_SolutionString->Location = System::Drawing::Point(10, 463);
			this->txt_SolutionString->Name = L"txt_SolutionString";
			this->txt_SolutionString->Size = System::Drawing::Size(646, 20);
			this->txt_SolutionString->TabIndex = 10;
			this->txt_SolutionString->Text = L"Solution goes here";
			// 
			// btn_scrambleString
			// 
			this->btn_scrambleString->Location = System::Drawing::Point(26, 74);
			this->btn_scrambleString->Name = L"btn_scrambleString";
			this->btn_scrambleString->Size = System::Drawing::Size(153, 23);
			this->btn_scrambleString->TabIndex = 11;
			this->btn_scrambleString->Text = L"Scramble from Moveset";
			this->btn_scrambleString->UseVisualStyleBackColor = true;
			this->btn_scrambleString->Click += gcnew System::EventHandler(this, &Form1::btn_scrambleString_Click);
			// 
			// btn_SendToArduino
			// 
			this->btn_SendToArduino->Location = System::Drawing::Point(704, 463);
			this->btn_SendToArduino->Name = L"btn_SendToArduino";
			this->btn_SendToArduino->Size = System::Drawing::Size(131, 23);
			this->btn_SendToArduino->TabIndex = 12;
			this->btn_SendToArduino->Text = L"Send To Arduino";
			this->btn_SendToArduino->UseVisualStyleBackColor = true;
			this->btn_SendToArduino->Click += gcnew System::EventHandler(this, &Form1::btn_SendToArduino_Click);
			// 
			// btn_Recolor
			// 
			this->btn_Recolor->Location = System::Drawing::Point(209, 13);
			this->btn_Recolor->Name = L"btn_Recolor";
			this->btn_Recolor->Size = System::Drawing::Size(132, 23);
			this->btn_Recolor->TabIndex = 13;
			this->btn_Recolor->Text = L"Start Recolor";
			this->btn_Recolor->UseVisualStyleBackColor = true;
			this->btn_Recolor->Click += gcnew System::EventHandler(this, &Form1::btn_Recolor_Click);
			// 
			// btn_EndRecolor
			// 
			this->btn_EndRecolor->Location = System::Drawing::Point(348, 13);
			this->btn_EndRecolor->Name = L"btn_EndRecolor";
			this->btn_EndRecolor->Size = System::Drawing::Size(131, 23);
			this->btn_EndRecolor->TabIndex = 14;
			this->btn_EndRecolor->Text = L"End Recolor";
			this->btn_EndRecolor->UseVisualStyleBackColor = true;
			this->btn_EndRecolor->Click += gcnew System::EventHandler(this, &Form1::btn_EndRecolor_Click);
			// 
			// btn_scrambleCubeString
			// 
			this->btn_scrambleCubeString->Location = System::Drawing::Point(26, 104);
			this->btn_scrambleCubeString->Name = L"btn_scrambleCubeString";
			this->btn_scrambleCubeString->Size = System::Drawing::Size(153, 23);
			this->btn_scrambleCubeString->TabIndex = 16;
			this->btn_scrambleCubeString->Text = L"Scramble from Cubestring";
			this->btn_scrambleCubeString->UseVisualStyleBackColor = true;
			this->btn_scrambleCubeString->Click += gcnew System::EventHandler(this, &Form1::btn_scrambleCubeString_Click);
			// 
			// btn_CmdToArduino
			// 
			this->btn_CmdToArduino->Location = System::Drawing::Point(714, 73);
			this->btn_CmdToArduino->Name = L"btn_CmdToArduino";
			this->btn_CmdToArduino->Size = System::Drawing::Size(121, 23);
			this->btn_CmdToArduino->TabIndex = 18;
			this->btn_CmdToArduino->Text = L"Send Command";
			this->btn_CmdToArduino->UseVisualStyleBackColor = true;
			this->btn_CmdToArduino->Click += gcnew System::EventHandler(this, &Form1::btn_CmdToArduino_Click);
			// 
			// box_CmdForArduino
			// 
			this->box_CmdForArduino->FormattingEnabled = true;
			this->box_CmdForArduino->Items->AddRange(gcnew cli::array< System::Object^  >(18) {
				L"Y0", L"y0", L"X0", L"x0", L"A1", L"a1",
					L"A2", L"a2", L"A3", L"a3", L"A4", L"a4", L"A5", L"a5", L"A6", L"a6", L"E1", L"E2"
			});
			this->box_CmdForArduino->Location = System::Drawing::Point(714, 46);
			this->box_CmdForArduino->Name = L"box_CmdForArduino";
			this->box_CmdForArduino->Size = System::Drawing::Size(121, 21);
			this->box_CmdForArduino->TabIndex = 19;
			this->box_CmdForArduino->Text = L"Y0";
			// 
			// lbl_ComPort
			// 
			this->lbl_ComPort->AutoSize = true;
			this->lbl_ComPort->Location = System::Drawing::Point(714, 104);
			this->lbl_ComPort->Name = L"lbl_ComPort";
			this->lbl_ComPort->Size = System::Drawing::Size(56, 13);
			this->lbl_ComPort->TabIndex = 20;
			this->lbl_ComPort->Text = L"COM-Port:";
			// 
			// numdd_ComPort
			// 
			this->numdd_ComPort->Location = System::Drawing::Point(776, 102);
			this->numdd_ComPort->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 255, 0, 0, 0 });
			this->numdd_ComPort->Name = L"numdd_ComPort";
			this->numdd_ComPort->Size = System::Drawing::Size(58, 20);
			this->numdd_ComPort->TabIndex = 21;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(882, 491);
			this->Controls->Add(this->numdd_ComPort);
			this->Controls->Add(this->lbl_ComPort);
			this->Controls->Add(this->box_CmdForArduino);
			this->Controls->Add(this->btn_CmdToArduino);
			this->Controls->Add(this->btn_scrambleCubeString);
			this->Controls->Add(this->btn_EndRecolor);
			this->Controls->Add(this->btn_Recolor);
			this->Controls->Add(this->btn_SendToArduino);
			this->Controls->Add(this->btn_scrambleString);
			this->Controls->Add(this->txt_SolutionString);
			this->Controls->Add(this->btn_GenSolution);
			this->Controls->Add(this->btn_Reset);
			this->Controls->Add(this->btn_Bi);
			this->Controls->Add(this->btn_B);
			this->Controls->Add(this->btn_Li);
			this->Controls->Add(this->btn_L);
			this->Controls->Add(this->btn_Di);
			this->Controls->Add(this->btn_D);
			this->Controls->Add(this->btn_Fi);
			this->Controls->Add(this->btn_F);
			this->Controls->Add(this->btn_Ui);
			this->Controls->Add(this->btn_Ri);
			this->Controls->Add(this->btn_U);
			this->Controls->Add(this->btn_R);
			this->Controls->Add(this->D9);
			this->Controls->Add(this->B9);
			this->Controls->Add(this->R9);
			this->Controls->Add(this->F9);
			this->Controls->Add(this->L9);
			this->Controls->Add(this->U9);
			this->Controls->Add(this->D8);
			this->Controls->Add(this->B8);
			this->Controls->Add(this->R8);
			this->Controls->Add(this->F8);
			this->Controls->Add(this->L8);
			this->Controls->Add(this->U8);
			this->Controls->Add(this->D7);
			this->Controls->Add(this->B7);
			this->Controls->Add(this->R7);
			this->Controls->Add(this->F7);
			this->Controls->Add(this->L7);
			this->Controls->Add(this->U7);
			this->Controls->Add(this->D6);
			this->Controls->Add(this->B6);
			this->Controls->Add(this->R6);
			this->Controls->Add(this->F6);
			this->Controls->Add(this->D5);
			this->Controls->Add(this->B5);
			this->Controls->Add(this->R5);
			this->Controls->Add(this->F5);
			this->Controls->Add(this->L6);
			this->Controls->Add(this->U6);
			this->Controls->Add(this->D4);
			this->Controls->Add(this->B4);
			this->Controls->Add(this->R4);
			this->Controls->Add(this->F4);
			this->Controls->Add(this->L5);
			this->Controls->Add(this->U5);
			this->Controls->Add(this->D3);
			this->Controls->Add(this->B3);
			this->Controls->Add(this->R3);
			this->Controls->Add(this->F3);
			this->Controls->Add(this->L4);
			this->Controls->Add(this->U4);
			this->Controls->Add(this->D2);
			this->Controls->Add(this->B2);
			this->Controls->Add(this->R2);
			this->Controls->Add(this->F2);
			this->Controls->Add(this->L3);
			this->Controls->Add(this->U3);
			this->Controls->Add(this->D1);
			this->Controls->Add(this->B1);
			this->Controls->Add(this->R1);
			this->Controls->Add(this->L2);
			this->Controls->Add(this->F1);
			this->Controls->Add(this->L1);
			this->Controls->Add(this->U2);
			this->Controls->Add(this->U1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedToolWindow;
			this->Name = L"Form1";
			this->Text = L"Qbot";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->numdd_ComPort))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion




//Move Buttons
private: System::Void btn_U_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.U();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
	}

private: System::Void btn_Ui_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.U_prime();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_R_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.R();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);	
}

private: System::Void btn_Ri_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.R_prime();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_F_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.F();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_Fi_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.F_prime();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_D_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.D();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_Di_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.D_prime();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_L_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.L();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_Li_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.L_prime();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_B_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.B();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}

private: System::Void btn_Bi_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.B_prime();
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}


private: System::Void btn_Reset_Click(System::Object^  sender, System::EventArgs^  e) {
	Erno.reset_cube(UP, FRONT, LEFT, BACK, RIGHT, DOWN);
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
	txt_SolutionString->Clear();
	
}

private: System::Void btn_GenSolution_Click(System::Object^  sender, System::EventArgs^  e) {
	std::string cubestring = Erno.generate_cubestring();
	//convert from string to char*
	const char* const_cubestring = cubestring.c_str();

	int max_moves = 20;
	long timeout = 3;
	bool final_solve = 0, first_solve = 1; 
	std::string solution;
	if (::solution(const_cubestring, max_moves, timeout, 0, "cache") == NULL)
	{
		solution = "Cube not solvable!";
	}
	else
	{
		solution = ::solution(const_cubestring, max_moves, timeout, 0, "cache");
	}
	System::String^ solutionstring = gcnew String(solution.c_str());
	txt_SolutionString->Clear();
	txt_SolutionString->AppendText(solutionstring);
}
private: System::Void btn_scrambleString_Click(System::Object^  sender, System::EventArgs^  e) {
	//std::string testscramble = "L2 D L' F' D R D' B' R' D2 L' D2 L F2 L' B2 R U2 F2";
	
	//convert C++/CLI string to std::string 
	System::String^ text_input = txt_SolutionString->Text;
	msclr::interop::marshal_context context;
	std::string textbox_scramble = context.marshal_as<std::string>(text_input);

	//bool success = Erno.scramble_from_string(testscramble);
	bool success = Erno.scramble_from_string(textbox_scramble);
	Erno.import_all_faces_to_facemap(Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	std::string cubestring = Erno.generate_cubestring();
	colorPanelsFromString(cubestring);
}



private: System::Void btn_SendToArduino_Click(System::Object^  sender, System::EventArgs^  e) 
{
	System::String^ text_input;
	msclr::interop::marshal_context context;

	text_input = txt_SolutionString->Text;
	std::string textbox_scramble = context.marshal_as<std::string>(text_input);
	
	text_input = numdd_ComPort->Text;
	std::string tx_com_port = context.marshal_as<std::string>(text_input);

	int flag = sendStringToArduino(textbox_scramble, 1, tx_com_port);

	if (flag == 0)
	{
		MessageBox::Show("Transmission successful!");
	}
	else if (flag == -1)
	{
		MessageBox::Show("Transmission error");
	}
	else if (flag == -2)
	{
		MessageBox::Show("Acknowledge error");
	}
	else if (flag == -3)
	{
		MessageBox::Show("Connection error");
	}
}

private: System::Void U1_Click(System::Object^  sender, System::EventArgs^  e) {
	MessageBox::Show("Click Event");
}


private: System::Void btn_Recolor_Click(System::Object^  sender, System::EventArgs^  e) {
	removePanelColors();
	colorIndex = 'O'; 
}


private: System::Void U5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (colorIndex != 'X')
	{
		colorIndex = 'U';
	}
}

private: System::Void R5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (colorIndex != 'X')
	{
		colorIndex = 'R';
	}
}

private: System::Void F5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (colorIndex != 'X')
	{
		colorIndex = 'F';
	}
}

private: System::Void D5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (colorIndex != 'X')
	{
		colorIndex = 'D';
	}
}

private: System::Void L5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (colorIndex != 'X')
	{
		colorIndex = 'L';
	}
}

private: System::Void B5_Click(System::Object^  sender, System::EventArgs^  e) {
	if (colorIndex != 'X')
	{
		colorIndex = 'B';
	}
}

private: System::Void ColorablePanel_Click(System::Object^  sender, System::EventArgs^  e) {
	System::Windows::Forms::Panel^ panel_sender = safe_cast<System::Windows::Forms::Panel^>(sender);
	changeSpecificPanelColor(panel_sender); 
}

private: System::Void btn_EndRecolor_Click(System::Object^  sender, System::EventArgs^  e) {
	//end recoloring mode
	colorIndex = 'X'; 

	//generate string
	std::string cubestring = createStringFromPanels();

	//display generated string 
	System::String^ cubestring_converted = gcnew String(cubestring.c_str());
	txt_SolutionString->Clear();
	txt_SolutionString->AppendText(cubestring_converted);

	//scramble cube model
	Erno.scramble_from_cubestring(cubestring, Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_);
	
}

private: System::Void btn_scrambleCubeString_Click(System::Object^  sender, System::EventArgs^  e) {
	//Test String: 
	//std::string test_string = "DUUBULDBFRBFRRULLLBRDFFFBLURDBFDFDRFRULBLUFDURRBLBDUDL";
	System::String^ text_input = txt_SolutionString->Text;
	msclr::interop::marshal_context context;
	std::string textbox_scramble = context.marshal_as<std::string>(text_input);
	
	if(textbox_scramble.length() == 54)
	{
		colorPanelsFromString(textbox_scramble);
		if(Erno.scramble_from_cubestring(textbox_scramble, Erno.ptr_UP_, Erno.ptr_LEFT_, Erno.ptr_FRONT_, Erno.ptr_RIGHT_, Erno.ptr_BACK_, Erno.ptr_DOWN_) == 1)
		{}
		else
		{
			txt_SolutionString->Clear();
			txt_SolutionString->AppendText("Could not scramble Cube!");
		}
	}
	else
	{
		txt_SolutionString->Clear();
		txt_SolutionString->AppendText("Invalid Cubestring!");
	}
	
}


private: System::Void btn_CmdToArduino_Click(System::Object^  sender, System::EventArgs^  e) {
	System::String^ text_input; 
	msclr::interop::marshal_context context;

	text_input = box_CmdForArduino->Text;
	std::string tx_cmd = context.marshal_as<std::string>(text_input);

	text_input = numdd_ComPort->Text;
	std::string tx_com_port = context.marshal_as<std::string>(text_input);

	int flag = sendStringToArduino(tx_cmd, 2, tx_com_port);

	if (flag == 0)
	{
		MessageBox::Show("Transmission successful!");
	}
	else if (flag == -1)
	{
		MessageBox::Show("Transmission error");
	}
	else if (flag == -2)
	{
		MessageBox::Show("Acknowledge error");
	}
	else if (flag == -3)
	{
		MessageBox::Show("Connection error");
	}
}


};

	
}
