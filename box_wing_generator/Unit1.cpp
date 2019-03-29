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

void __fastcall TForm1::RadioGroup1Click(TObject *Sender)
{
AnsiString exeFile=Application->ExeName;
AnsiString exePath=ExtractFilePath(exeFile);
if (RadioGroup1->ItemIndex == 0)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-10.txt");
if (RadioGroup1->ItemIndex == 1)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-8.txt");
if (RadioGroup1->ItemIndex == 2)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-6.txt");
if (RadioGroup1->ItemIndex == 3)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-4.txt");
if (RadioGroup1->ItemIndex == 4)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_-2.txt");
if (RadioGroup1->ItemIndex == 5)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_0.txt");
if (RadioGroup1->ItemIndex == 6)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_2.txt");
if (RadioGroup1->ItemIndex == 7)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_4.txt");
if (RadioGroup1->ItemIndex == 8)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_6.txt");
if (RadioGroup1->ItemIndex == 9)
   Memo1->Lines->LoadFromFile(exePath+"\\airfoil\\P-273-FLAP_8.txt");
if (RadioGroup1->ItemIndex == 10)
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

void __fastcall TForm1::Button3Click(TObject *Sender)
{
        FileName = "R02-new.in";
        Memo3->Lines->SaveToFile(FileName);
        ShellExecute(0, "open", "Pansym98.exe", FileName, "", SW_SHOWNORMAL);
}
//---------------------------------------------------------------------------


