//---------------------------------------------------------------------------
//   this short program single use tool for composition of 704 text file 
//   in one csv file for later analysis via Pandas
//   These data stored in separated folder, such as
//
//   R01
//      forward
//        file1.txt
//        file2.txt
//      aft
//        file1.txt
//        file2.txt
// 
//    Some info stored in files, some coded into folders and subfolsers name
//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
#include <fstream>
#include <iostream>
#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
   : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
   //Start values, counters for loops
   int R = 1; int W = 0; int Z = 0; int dV = -10;
   //Values for CSV
   float AoA, Cx, Cy, Mz;
   //Some strings for compose filename
   AnsiString Filename = Edit1->Text;  //User input, folder path
   AnsiString f = Filename;
   AnsiString f1 = f;
   AnsiString f2 = f1;
   AnsiString d;
   AnsiString z;
   std::string s;
   do {
      W = 0;
      do {
         f = Filename;
         f += "\\R0"+IntToStr(R)+"\\";
         if (W == 0) f+= "forward\\"; else f+="aft\\";
         f += "R0"+IntToStr(R);
         if (W == 0) f+= "00"; else f+="01";
         Z = 0;
         do {
			//Compose filename and assign values
            if (Z == 0) {z = "0.25";  f1 = f; f1 += "025";}
            if (Z == 1) {z = "0.50";  f1 = f;  f1 += "050";}
            if (Z == 2) {z = "0.75";  f1 = f;  f1 += "075";}
            if (Z == 3) {z = "0.90";  f1 = f;  f1 += "090";}
            for (dV = -10; dV <= 10; dV += 2)
            {
                //Compose filename
				if (dV == -10) {f2 = f1; f2 += "m10";}
                if (dV == -8)  {f2 = f1; f2 += "m08";}
                if (dV == -6)  {f2 = f1; f2 += "m06";}
                if (dV == -4)  {f2 = f1; f2 += "m04";}
                if (dV == -2)  {f2 = f1; f2 += "m02";}
                if (dV ==  0)  {f2 = f1; f2 += "p00";}
                if (dV ==  2)  {f2 = f1; f2 += "p02";}
                if (dV ==  4)  {f2 = f1; f2 += "p04";}
                if (dV ==  6)  {f2 = f1; f2 += "p06";}
                if (dV ==  8)  {f2 = f1; f2 += "p08";}
                if (dV == 10)  {f2 = f1; f2 += "p10";}
                f2 += ".txt";
                //Open file, skip first line;
                std::ifstream i_file(f2.c_str());
                std::getline(i_file,s);
                  for(int i=1; i<=22; i++)
                  {
                     //Read line and add delimiters for CSV file
					 std::getline(i_file,s);
                     s.insert(6,",");
                     s.insert(22,",");
                     s.insert(36,",");
                     Memo1->Lines->Add(IntToStr(R)+", "+IntToStr(W)+", "+z+", "+
                                       IntToStr(dV)+", "+AnsiString(s.c_str()));
                  }
                i_file.close();
                Memo2->Lines->Add(f2);
            }
            Z++;
         } while (Z<=3);
         W++;
      } while (W <= 1);
      R++;
   } while (R <= 8);
   //dump data to CSV
   Memo1->Lines->SaveToFile(Filename+"\\result.csv");
}
//---------------------------------------------------------------------------
