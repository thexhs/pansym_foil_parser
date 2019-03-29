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
double X_end_PK = 1.908;
double X_end_ZK = 3.735;
double Z_otn = 0.25;
double X_start_PK = 0;
double X_start_ZK = 5.348;
double X_int_PK = X_end_PK/0.9*Z_otn;
double X_int_ZK = X_start_ZK-(X_start_ZK-X_end_ZK)/0.9*Z_otn;
double Y_ZK = 2;
double Phi_ZK = -1.530;
bool  isForward = True;

double X_w[13] = {3.737, 3.674, 3.622, 3.485, 3.352, 3.117, 2.882,
                  2.647, 2.413, 2.269, 2.120, 1.978, 1.907};
double Y_w[13] = {2.000, 2.000, 1.970, 1.862, 1.711, 1.378, 1.045,
                  0.712, 0.379, 0.198, 0.060, 0.000, 0.000};
double Z_w[13] = {4.500, 4.666, 4.815, 4.930, 4.975, 4.987, 5.000,
                  5.012, 5.024, 4.981, 4.850, 4.666, 4.500};
double Phi_w[13] = {0,0,0,0,0,0,0,0,0,0,0,0,0};

double Phi_ZK1[8] = {-1.530, -1.4025, -1.5277, -1.6024
                     -1.249, -1.1169, -1.3868, -1.5352};
                     
double Phi_mult[13] = {1,1,
                        0.87179,
                        0.74359,
                        0.60684,
                        0.30769,
                        0,0,0,0,0,0,0};

double X_w_offset = 0;
double X_w_offset1 = 0;
bool is_w_Revers = False;
//---------------------------------------------------------------------------
//    Load selected airfoil in Memo1
//---------------------------------------------------------------------------
void __fastcall TForm1::rgdVClick(TObject *Sender)
{
   AnsiString exeFile=Application->ExeName;
   AnsiString exePath=ExtractFilePath(exeFile);
   if (rgdV->ItemIndex == 0)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-10.txt");
   if (rgdV->ItemIndex == 1)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-8.txt");
   if (rgdV->ItemIndex == 2)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-6.txt");
   if (rgdV->ItemIndex == 3)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-4.txt");
   if (rgdV->ItemIndex == 4)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-2.txt");
   if (rgdV->ItemIndex == 5)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_0.txt");
   if (rgdV->ItemIndex == 6)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_2.txt");
   if (rgdV->ItemIndex == 7)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_4.txt");
   if (rgdV->ItemIndex == 8)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_6.txt");
   if (rgdV->ItemIndex == 9)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_8.txt");
   if (rgdV->ItemIndex == 10)
      Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_10.txt");
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
if(OpenDialog1->Execute())
   {
      FileName = OpenDialog1->FileName;
      Memo2->Lines->LoadFromFile(FileName);
   }
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
Memo3->Clear();
    std::ifstream is(FileName.c_str()); if(!is.is_open()) return;
    std::string s;
    for(int i = 1; i < 27; i++)
    {
       std::getline(is,s);
       AnsiString S = s.c_str();
       Memo3->Lines->Add(S);
    }
    Memo3->Lines->Add(Memo1->Text);
    for(int i = 27; i < 48; i++)
    {
       std::getline(is,s);
    }
    for(int i = 48; !is.eof(); i++)
    {
       std::getline(is,s);
       AnsiString S = s.c_str();
       Memo3->Lines->Add(S);
    }
}
//---------------------------------------------------------------------------
//    Execute PANSYM solver
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
        FileName = "R02-new.in";
        Memo3->Lines->SaveToFile(FileName);
        ShellExecute(0, "open", "Pansym98.exe", FileName.c_str(), "", SW_SHOWNORMAL);
}
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
//    Select elevator span
//---------------------------------------------------------------------------
void __fastcall TForm1::rgZClick(TObject *Sender)
{
if (rgZ->ItemIndex == 0)
   Z_otn = 0.25;
if (rgZ->ItemIndex == 1)
   Z_otn = 0.50;
if (rgZ->ItemIndex == 2)
   Z_otn = 0.75;
if (rgZ->ItemIndex == 3)
   Z_otn = 0.90;
}
//---------------------------------------------------------------------------
//    Select layout between R01..08
//---------------------------------------------------------------------------
void __fastcall TForm1::rgRClick(TObject *Sender)
{
   if ((rgR->ItemIndex == 0)||(rgR->ItemIndex == 4)){   //R01 ||  R05
      X_end_PK = 1.908;
      X_end_ZK = 3.735;
      X_w_offset = 0;
      X_w_offset1 = 0;
   }
   if ((rgR->ItemIndex == 1)||(rgR->ItemIndex == 5)){   //R02 ||  R06
      X_end_PK = 0.957;
      X_end_ZK = 2.784;
      X_w_offset = -0.95;
      X_w_offset1 = 0;
   }
   if ((rgR->ItemIndex == 2)||(rgR->ItemIndex == 6)){   //R03 ||  R07
      X_end_PK = 2.695;
      X_end_ZK = 4.522;
      X_w_offset = 0.785;
      X_w_offset1 = 0.003;
   }
   if ((rgR->ItemIndex == 3)||(rgR->ItemIndex == 7)){   //R04 ||  R08
      X_end_PK = 3.482;
      X_end_ZK = 5.348;
      X_w_offset = 1.611;
      X_w_offset1 = -0.036;
   }
   X_int_PK = X_end_PK/0.9*Z_otn;
   X_int_ZK = X_start_ZK-(X_start_ZK-X_end_ZK)/0.9*Z_otn;
   if(rgR->ItemIndex >= 4) {
      Y_ZK = 2;
      is_w_Revers = True;
   }
   else {
      Y_ZK = 0;
      is_w_Revers = False;
   }
   Phi_ZK = Phi_ZK1[rgR->ItemIndex];
}
//---------------------------------------------------------------------------
//    Select wing with elevator
//---------------------------------------------------------------------------
void __fastcall TForm1::rgWingClick(TObject *Sender)
{
   if (rgWing->ItemIndex == 0)
      isForward = True;
   else
      isForward = False;
}
//---------------------------------------------------------------------------
//    Write in Memo4 code for Wing
//---------------------------------------------------------------------------
void __fastcall TForm1::Button5Click(TObject *Sender)
{
   #define M4LA Memo4->Lines->Add
   #define ITS IntToStr
   #define FTS FloatToStr
   //Small hack, special case, Z = 0.9 mimic with Z = 0.75 and elevator on two part
   bool isZ09 = False;
   if (Z_otn == 0.9)
   {
      Z_otn = 0.75;
      isZ09 = True;
   }
   Memo4->Clear();
   //First SECTION
   AnsiString S = "";
   M4LA("#FRONT WING - INBOARD PART");
   M4LA("  1  2  0 2 -20  1 12                    0  0");
   M4LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   M4LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
      if(isForward) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(ITS(0));
      S += FmtStr72(FTS(-0.08));
      S += FmtStr72(ITS(0));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA(S);
      if(isForward) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_end_PK/0.9*Z_otn));
      S += FmtStr72(FTS(-0.08));
      S += FmtStr72(FTS(Z_otn*5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA("< z%  ><     ><     ><     ><     ><     ><     ><     ><     ><     >");
   M4LA("  0.0    .05    .1     .2      .3    .4     .5     .6     .7     .8  ");
   M4LA("   .9   1.0");
   //SECOND SECTION
   M4LA("#FRONT WING - OUTBOARD PART");
   M4LA("  2  2  0 2 -20  1 12                    0  0");
   M4LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   M4LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
      if((isZ09)&&(isForward)) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_end_PK/0.9*Z_otn));
      S += FmtStr72(FTS(-0.08));
      S += FmtStr72(FTS(Z_otn*5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA(S);
      if((isZ09)&&(isForward)) S+=FmtStr72(ITS(-2)); else S+=FmtStr72(ITS(-1));
      S += FmtStr72(FTS(X_end_PK));
      S += FmtStr72(FTS(-0.08));
      S += FmtStr72(FTS(4.5));
      S += FmtStr72(ITS(1));
      S += FmtStr72(ITS(0));
   M4LA(S); S= "";
   M4LA("< z%  ><     ><     ><     ><     ><     ><     ><     ><     ><     >");
   M4LA("  0.0    .05    .1     .2      .3    .4     .5     .6     .7     .8  ");
   M4LA("   .9   1.0");
   //THIRD SECTION
   M4LA("#REAR WING - INBOARD PART");
   M4LA("  3  2  0 2 -20  1 12                    0  0");
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
   M4LA("  4  2  0 2 -20  1 12                    0  0");
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
   M4LA(S); S= "";
   M4LA("< z%  ><     ><     ><     ><     ><     ><     ><     ><     ><     >");
   M4LA("  0.0    .05    .1     .2      .3    .4     .5     .6     .7     .8  ");
   M4LA("   .9   1.0");
   if (isZ09) Z_otn = 0.9;
}
//---------------------------------------------------------------------------
//    Write in Memo4 code for Winglet
//---------------------------------------------------------------------------
void __fastcall TForm1::Button6Click(TObject *Sender)
{
   #define M4LA Memo4->Lines->Add
   #define ITS IntToStr
   #define FTS FloatToStr
   Memo4->Clear();
   //First SECTION
   AnsiString S = "";
   M4LA("#winglet R0"+ITS(rgR->ItemIndex+1));
   M4LA(" -5  2  0 13-20  0  0                     0");
   M4LA(" NE IT IB NS NU II NI UI NL IC IM IP IM ICO   ICOE");
   M4LA("< NP  >< Xm  >< Ym  >< Zm  ><Ch m >< Fi  >");
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
      if(is_w_Revers) S+=FmtStr72(FTS(Phi_w[12-i]));
      else S+=FmtStr72(FTS(Phi_w[i]));

      M4LA(S); S= "";
      if(i!=12)M4LA(" NPROF X_PR.K Y_PR.K Z_PR.K CHORD  FI_KRUT");
   }
}
//---------------------------------------------------------------------------

