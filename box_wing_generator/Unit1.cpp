//---------------------------------------------------------------------------
#include <vcl.h>
#include <string>
#include <fstream>
#include <iostream>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

#define ITS IntToStr
#define STI StrToInt
#define FTS FloatToStr
#define STF StrToFloat

TForm1 *Form1;
AnsiString FileName;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------
//Global values
//---------------------------------------------------------------------------
//Get command_line parameter
AnsiString param1 = ParamStr(1);    //-infile/-pansym
AnsiString param2 = ParamStr(2);    //Layout number 1..8
AnsiString param3 = ParamStr(3);    //Z = 0.25/0.50/0.75/0.90
AnsiString param4 = ParamStr(4);    //Wing 0/1
AnsiString param5 = ParamStr(5);    //Deflection -10..10
//Application state control struct
struct T_ASC {
   int R;
   double Z;
   int Wing;
   int dV;
   bool GUI;
   bool CMD;
};
T_ASC ASC = {1, 0.25, 1, -10, True, False};
//X position of Wing for R01 layout
double X_end_PK = 1.908;
double X_end_ZK = 3.735;
double X_start_PK = 0;
double X_start_ZK = 5.348;
//Default elevator span
double Z_otn = 0.25;
//Elevator position - front or rear wing
bool  isForward = True;
//Intermidiate section between inboard and outboard part of wing
double X_int_PK = X_end_PK/0.9*Z_otn;
double X_int_ZK = X_start_ZK-(X_start_ZK-X_end_ZK)/0.9*Z_otn;
//Vertical position of front and rear wing
double Y_ZK = 2;
double Y_PK = -0.08;
//Rear wing twist angle
double Phi_ZK = -1.530;
//Geometry of wingtip joint
double X_w[13] = {3.737, 3.674, 3.622, 3.485, 3.352, 3.117, 2.882,
                  2.647, 2.413, 2.269, 2.120, 1.978, 1.907};
double Y_w[13] = {2.000, 2.000, 1.970, 1.862, 1.711, 1.378, 1.045,
                  0.712, 0.379, 0.198, 0.060, 0.000, 0.000};
double Z_w[13] = {4.500, 4.666, 4.815, 4.930, 4.975, 4.987, 5.000,
                  5.012, 5.024, 4.981, 4.850, 4.666, 4.500};
double Phi_w[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};
//Different twist angle for R01..R08 layouts
double Phi_ZK1[8] = {-1.530, -1.4025, -1.5277, -1.6024
                     -1.249, -1.1169, -1.3868, -1.5352};
//Twist angle multiplicator for different section of wingtip joint
double Phi_mult[13] = {1,1,
                        0.87179,
                        0.74359,
                        0.60684,
                        0.30769,
                        0,0,0,0,0,0,0};

//X_f position for R01..R08 layouts
double X_f[8] = {2.899, 2.323, 3.411, 3.920,
                 2.993, 2.423, 3.477, 3.991};                        

double X_w_offset = 0;
double X_w_offset1 = 0;
bool is_w_Revers = False;

//Get application folder
AnsiString exeFile=Application->ExeName;
AnsiString exePath=ExtractFilePath(exeFile);
//---------------------------------------------------------------------------
//  To PANSYM 7 char format conversion routine  - TRIM and adding WHITESPACE
//---------------------------------------------------------------------------
AnsiString TForm1::FmtStr72(AnsiString InputStr)
{
        AnsiString InternalStr = "       ";
        for(int j=1; j<=7;j++)
        {
           if (j <= strlen(InputStr.c_str()))
           if (InputStr[j] == ',')
              InternalStr[j] = '.';
              else
              InternalStr[j] = InputStr[j];
           else
           InternalStr[j] = ' ';
        }
        return InternalStr;
}
//---------------------------------------------------------------------------
//    Input from different group of Radio Button
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//    Select layout between R01..08
//---------------------------------------------------------------------------
void __fastcall TForm1::rgRClick(TObject *Sender)
{
   ASC.R = rgR->ItemIndex+1;
}
//---------------------------------------------------------------------------
//    Select elevator span
//---------------------------------------------------------------------------
void __fastcall TForm1::rgZClick(TObject *Sender)
{
if (rgZ->ItemIndex == 0)
   ASC.Z = 0.25;
if (rgZ->ItemIndex == 1)
   ASC.Z = 0.50;
if (rgZ->ItemIndex == 2)
   ASC.Z = 0.75;
if (rgZ->ItemIndex == 3)
   ASC.Z = 0.90;
}
//---------------------------------------------------------------------------
//    Select wing with elevator
//---------------------------------------------------------------------------
void __fastcall TForm1::rgWingClick(TObject *Sender)
{
   ASC.Wing = rgWing->ItemIndex;
}
//---------------------------------------------------------------------------
//    FILE WRITE SECTION
//---------------------------------------------------------------------------
//    Load selected airfoil in mAirfoil and write into files folder
//---------------------------------------------------------------------------
void __fastcall TForm1::btnFoilClick(TObject *Sender)
{
   #define MALL mAirfoil->Lines->LoadFromFile
   MALL(exePath+"\\airfoil\\P-273-FLAP_"+ITS(ASC.dV)+".txt");
   mAirfoil->Lines->SaveToFile(exePath+"\\files\\airfoil_w_elevator.txt");
}
//---------------------------------------------------------------------------
//    Write in Memo4 code for Wing
//---------------------------------------------------------------------------
void __fastcall TForm1::btnWingClick(TObject *Sender)
{
   Form1->ConvertASC();
   #define M4LA mWing->Lines->Add
   //Small hack, special case, Z = 0.9 mimic with Z = 0.75 and elevator on two part
   bool isZ09 = False;
   if (Z_otn == 0.9)
   {
      Z_otn = 0.75;
      isZ09 = True;
   }
   mWing->Clear();
   //First SECTION
   AnsiString S = "";
   //mWing->SetTextBuf("#FRONT WING - INBOARD PART");
   M4LA("#FRONT WING - INBOARD PART");
   M4LA("  1  2  0 2 -18  1 12                    0  0");
   M4LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   M4LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
      if(isForward) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(ITS(0));
      S += FmtStr72(FTS(Y_PK));
      S += FmtStr72(ITS(0));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA(S);
      if(isForward) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_end_PK/0.9*Z_otn));
      S += FmtStr72(FTS(Y_PK));
      S += FmtStr72(FTS(Z_otn*5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA("< z%  ><     ><     ><     ><     ><     ><     ><     ><     ><     >");
   M4LA("  0.0    .05    .1     .2      .3    .4     .5     .6     .7     .8  ");
   M4LA("   .9   1.0");
   //SECOND SECTION
   M4LA("#FRONT WING - OUTBOARD PART");
   M4LA("  2  2  0 2 -18  1 12                    0  0");
   M4LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   M4LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
      if((isZ09)&&(isForward)) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_end_PK/0.9*Z_otn));
      S += FmtStr72(FTS(Y_PK));
      S += FmtStr72(FTS(Z_otn*5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA(S);
      if((isZ09)&&(isForward)) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_end_PK));
      S += FmtStr72(FTS(Y_PK));
      S += FmtStr72(FTS(4.5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA("< z%  ><     ><     ><     ><     ><     ><     ><     ><     ><     >");
   M4LA("  0.0    .05    .1     .2      .3    .4     .5     .6     .7     .8  ");
   M4LA("   .9   1.0");
   //THIRD SECTION
   M4LA("#REAR WING - INBOARD PART");
   M4LA("  3  2  0 2 -18  1 12                    0  0");
   M4LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   M4LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
      if(isForward) S+=FmtStr72(ITS(-1)); else S+=FmtStr72(ITS(-2));
      S += FmtStr72(FTS(X_start_ZK));
      S += FmtStr72(FTS(Y_ZK));
      S += FmtStr72(FTS(0));
      S += FmtStr72(ITS(1));
      S += FmtStr72(FTS(Phi_ZK));
   M4LA(S); S= "";
   M4LA(S);
      if(isForward) S+=FmtStr72(ITS(-1)); else S+=FmtStr72(ITS(-2));
      S += FmtStr72(FTS(X_start_ZK-(X_start_ZK-X_end_ZK)/0.9*Z_otn));
      S += FmtStr72(FTS(Y_ZK));
      S += FmtStr72(FTS(Z_otn*5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(FTS(Phi_ZK));
   M4LA(S); S= "";
   M4LA("< z%  ><     ><     ><     ><     ><     ><     ><     ><     ><     >");
   M4LA("  0.0    .05    .1     .2      .3    .4     .5     .6     .7     .8  ");
   M4LA("   .9   1.0");
   //FOURTH SECTION
   M4LA("#REAR WING - OUTBOARD PART");
   M4LA("  4  2  0 2 -18  1 12                    0  0");
   M4LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   M4LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
      if((isZ09)&&(!isForward)) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_start_ZK-(X_start_ZK-X_end_ZK)/0.9*Z_otn));
      S += FmtStr72(FTS(Y_ZK));
      S += FmtStr72(FTS(Z_otn*5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(FTS(Phi_ZK));
   M4LA(S); S= "";
   M4LA(S);
      if((isZ09)&&(!isForward)) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_end_ZK));
      S += FmtStr72(FTS(Y_ZK));
      S += FmtStr72(FTS(4.5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(FTS(Phi_ZK));
   M4LA(S);
   M4LA("< z%  ><     ><     ><     ><     ><     ><     ><     ><     ><     >");
   M4LA("  0.0    .05    .1     .2      .3    .4     .5     .6     .7     .8  ");
   M4LA("   .9   1.0");
   //Strange triks for remowing last line
   //mWing->SelStart = mWing->GetTextLen();
   //mWing->SelLength = 0;
   //mWing->SelText = "   .9   1.0";
   if (isZ09) Z_otn = 0.9;
   mWing->Lines->SaveToFile(exePath+"\\files\\wing.txt");
}
//---------------------------------------------------------------------------
//    Write in Memo4 code for Winglet
//---------------------------------------------------------------------------
void __fastcall TForm1::btnWingletClick(TObject *Sender)
{
   Form1->ConvertASC();
   #define MW2LA mWinglet->Lines->Add
   mWinglet->Clear();
   //First SECTION
   AnsiString S = "";
   MW2LA("#winglet R0"+ITS(ASC.R));
   MW2LA(" -5  2  0 13-18  0  0                     0");
   MW2LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   MW2LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
   //Prepare array with winglet twist andle for compile text in next cycle
   for(int i = 0; i<=12; i++)
   {
      Phi_w[i] = Phi_mult[i]*Phi_ZK;
   }
   for(int i = 0; i<=12; i++)
   {
      S = "";
      if (i<2)
         S+=FmtStr72(ITS(1));
      else
         if (i!=12)
            S+=FmtStr72(ITS(i+1));
         else
            S+=FmtStr72(ITS(i));

      if(is_w_Revers){
         if(i==12) S+=FmtStr72(FTS(X_w[12-i]+X_w_offset));
         else S+=FmtStr72(FTS(X_w[12-i]+X_w_offset+X_w_offset1));
      }
      else{
         if(i==0) S+=FmtStr72(FTS(X_w[i]+X_w_offset));
         else S+=FmtStr72(FTS(X_w[i]+X_w_offset+X_w_offset1));
      }
      S+=FmtStr72(FTS(Y_w[i]));
      S+=FmtStr72(FTS(Z_w[i]));
      S+=FmtStr72(ITS(1));
      if(is_w_Revers) S+=FmtStr72(FTS(Phi_w[12-i]*-1));
      else S+=FmtStr72(FTS(Phi_w[i]));

      MW2LA(S); S= "";
      if(i!=12)MW2LA(" NPROF X_PR.K Y_PR.K Z_PR.K CHORD  FI_KRUT");
   }
   mWinglet->Lines->SaveToFile(exePath+"\\files\\winglet.txt");
}
//---------------------------------------------------------------------------
//    Write first 5 lines of output file - HEAD
//---------------------------------------------------------------------------
void __fastcall TForm1::btnHeadClick(TObject *Sender)
{
   Form1->ConvertASC();
   #define MHLA mHead->Lines->Add
   mHead->Clear();
   //First SECTION
   AnsiString S = "";
   MHLA("BOX WING R0"+ITS(ASC.R));
   MHLA("suMekRprNchRreGplVreAitRdsGgrFneLlnTprHviS");
   MHLA("  1  0  1 -1 22  0  1  0  0  1  0  0  0  0");
   MHLA(" Sk     Bk     Lk     Xc     Yc     Zc     rvr    dp     xend   Smid   dAlfkr Cx0");
   S = " 20     1      10     ";
   S += FmtStr72(FTS(X_f[ASC.R-1]-0.3));
   S += " 0.0   0.      0.05    0.1    20.    .62   0.     .0123";
   MHLA(S);
   mHead->Lines->SaveToFile(exePath+"\\files\\config.txt");
}

//---------------------------------------------------------------------------
//    Btn Click Simulation
//---------------------------------------------------------------------------
void __fastcall TForm1::btnAutoClick(TObject *Sender)
{
   Form1->btnHead->Click();
   Form1->btnFoil->Click();
   Form1->btnWing->Click();
   Form1->btnWinglet->Click();
}
//---------------------------------------------------------------------------
//    Make IN file for PANSYM
//---------------------------------------------------------------------------
void __fastcall TForm1::btnMakeInClick(TObject *Sender)
{
   Form1->btnAutoClick(NULL);

   #define SIBB std::ios_base::binary
   #define SIFS std::ifstream
   #define SOFS std::ofstream

   SIFS if_config((exePath+"\\files\\config.txt").c_str(), SIBB);
   SIFS if_head((exePath+"\\files\\head.txt").c_str(), SIBB);
   SIFS if_airfoil_w_elevator((exePath+"\\files\\airfoil_w_elevator.txt").c_str(),
                              SIBB);
   SIFS if_remain_foil((exePath+"\\files\\remain_foil.txt").c_str(), SIBB);
   SIFS if_wing((exePath+"\\files\\wing.txt").c_str(), SIBB);
   SIFS if_winglet((exePath+"\\files\\winglet.txt").c_str(), SIBB);
   SIFS if_trail((exePath+"\\files\\trail.txt").c_str(), SIBB);

   SOFS of_output((exePath+"\\output.in").c_str(), SIBB);

   of_output << if_config.rdbuf() << if_head.rdbuf() <<
                if_airfoil_w_elevator.rdbuf() <<
                if_remain_foil.rdbuf() << if_wing.rdbuf() <<
                if_winglet.rdbuf() << if_trail.rdbuf();

   of_output.close();
   mInFile->Lines->LoadFromFile(exePath+"\output.in");
}
//---------------------------------------------------------------------------
//    Execute PANSYM solver
//---------------------------------------------------------------------------
void __fastcall TForm1::btnPANSYMClick(TObject *Sender)
{
   ShellExecute(0, "open", "Pansym98.exe", "output.in", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnOU2GEOClick(TObject *Sender)
{
   ShellExecute(0, "open", "OU2GEO.EXE", "output.ou", "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------
void __fastcall TForm1::btnVisualClick(TObject *Sender)
{
   ShellExecute(0, "open", "Visual.exe", "output.geo", "", SW_SHOWNORMAL);
}

void __fastcall TForm1::FormShow(TObject *Sender)
{
   //Parse comandline arguments and create Application Control Struct
   if (param1!="") {
      ASC.CMD = True;
      ASC.GUI = False;
   }
   if (ASC.CMD) {
      ASC.R = STI(param2);
      if (param3 == "0.25") ASC.Z = 0.25;
      if (param3 == "0.50") ASC.Z = 0.50;
      if (param3 == "0.75") ASC.Z = 0.75;
      if (param3 == "0.90") ASC.Z = 0.90;
      ASC.Wing = STI(param4);
      ASC.dV = STI(param5);
      mInFile->Lines->Add(ITS(ASC.R)+" "+FTS(ASC.Z)+" "+ITS(ASC.Wing)+" "+ITS(ASC.dV));
   }
   if (param1 == "-infile") {
      Form1->btnMakeInClick(NULL);
      Form1->Close();
   }
   if (param1 == "-pansym") {
      Form1->btnMakeInClick(NULL);
      ShellExecute(0, "open", "Pansym98.exe", "output.in", "", SW_SHOWNORMAL);
      Form1->Close();

   }
   if (param1 == "-visual") {
      Form1->btnMakeInClick(NULL);
      int PansymHandle = 0;
      //
      STARTUPINFO cif;
      ZeroMemory(&cif,sizeof(STARTUPINFO));
      PROCESS_INFORMATION pi;
      //Run PANSYM in while loop
      do {
        CreateProcess("Pansym98.exe"," output.in",
	   NULL,NULL,FALSE,NULL,NULL,exePath.c_str(),&cif,&pi);
      } while (WaitForSingleObject(pi.hProcess,INFINITE));
      //Run OU2GEO converter in while loop
      do {
        CreateProcess("OU2GEO.exe"," output.ou",
	   NULL,NULL,FALSE,NULL,NULL,exePath.c_str(),&cif,&pi);
      } while (WaitForSingleObject(pi.hProcess,INFINITE));
      //After all run Visual viewer
      ShellExecute(0, "open", "VISUAL.exe", "output.geo", "", SW_SHOWNORMAL);
      Form1->Close();
   }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::rgdVClick(TObject *Sender)
{
   int Start = -10;
   int Step = 2;
   ASC.dV = Start+rgdV->ItemIndex*Step;
}
//---------------------------------------------------------------------------
//      Get Data from App. Control Struct into set of global variables
//---------------------------------------------------------------------------
void TForm1::ConvertASC(void)
{
   //Convert ASC variable in old
   Z_otn = ASC.Z;
   if (ASC.Wing==0) isForward = True;
   if (ASC.Wing==1) isForward = False;

   if ((ASC.R == 1)||(ASC.R == 5)){   //R01 ||  R05
      X_end_PK = 1.908;
      X_end_ZK = 3.735;
      X_w_offset = 0;
      X_w_offset1 = 0;
   }
   if ((ASC.R == 2)||(ASC.R == 6)){   //R02 ||  R06
      X_end_PK = 0.957;
      X_end_ZK = 2.784;
      X_w_offset = -0.95;
      X_w_offset1 = 0;
   }
   if ((ASC.R == 3)||(ASC.R == 7)){   //R03 ||  R07
      X_end_PK = 2.695;
      X_end_ZK = 4.522;
      X_w_offset = 0.785;
      X_w_offset1 = 0.003;
   }
   if ((ASC.R == 4)||(ASC.R == 8)){   //R04 ||  R08
      X_end_PK = 3.482;
      X_end_ZK = 5.348;
      X_w_offset = 1.611;
      X_w_offset1 = -0.036;
   }
   X_int_PK = X_end_PK/0.9*Z_otn;
   X_int_ZK = X_start_ZK-(X_start_ZK-X_end_ZK)/0.9*Z_otn;
   if(ASC.R >= 5) {
      Y_ZK = -0.08;
      Y_PK = 2;
      is_w_Revers = True;
   }
   else {
      Y_ZK = 2;
      Y_PK = -0.08;
      is_w_Revers = False;
   }
   Phi_ZK = Phi_ZK1[ASC.R-1];
}

