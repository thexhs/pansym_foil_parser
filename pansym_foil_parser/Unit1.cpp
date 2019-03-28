//---------------------------------------------------------------------------

#include <vcl.h>
#include <string>
#include <fstream>
#include <iostream>
using namespace std;
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
// An Airfoil definition section
//---------------------------------------------------------------------------
struct A_ITBE_0
{
double X;
double Y_Up;
double Y_Down;
};

struct A_ITBE_1
{
double X;
double Y_mean;
double Y_thicness;
};

struct A_ITBE_2
{
double X;
double Y;
};

struct TAirfoil
{
        AnsiString Name;
        int Type;
        int Number;
        int PointCount;
        bool ISYM;
        bool IMASH;
        bool IROT;
        float CMASH;
        float HROT;
        float FIROT;
        A_ITBE_0 Coords0[500];
        A_ITBE_1 Coords1[500];
        A_ITBE_2 Coords2[500];
};

typedef TAirfoil* PTAirfoil;
TList *AList = new TList;
int ACount=0;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
  if(!OpenDialog1->Execute()) return;
    String Name=OpenDialog1->FileName;

    std::ifstream is(Name.c_str()); if(!is.is_open()) return;
    std::string s;

    while(!is.eof())
        {
        std::getline(is,s);

        String S=s.c_str(); // convert back to Borland AnsiString

        Memo1->Lines->Add(S);
        }
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button2Click(TObject *Sender)
{
Memo1->Clear();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button3Click(TObject *Sender)
{
//Current Line
int LOffset = 0;
//Initial Position
LOffset = 4;
//Read first airfoil in memo



//Airfoil description parameters
AnsiString sBlock_Number = "";
AnsiString sBlock_Type = "";
AnsiString sAF_Number = "";
AnsiString sAF_PointCount = "";
AnsiString sAF_Type = "";
AnsiString sAF_IMASH = "";
AnsiString sAF_IPREOB = "";
//Airfoil description parameters
int iBlock_Number = 0;
int iBlock_Type = 0;
int iAF_Number = 0;
int iAF_PointCount = 0;
int iAF_Type = 0;
int iAF_IMASH = 0;
int iAF_IPREOB = 0;

bool isFoil = true;

while(isFoil){
   //Skip first line - block Name
   LOffset+=2;
   //Read second Line - Sequence of control Number
   //Check Block Type, parse wirst two number
   sBlock_Number = (Memo1->Lines->Strings[LOffset][1]);
   sBlock_Number += (Memo1->Lines->Strings[LOffset][2]);
   sBlock_Number += (Memo1->Lines->Strings[LOffset][3]);

   sBlock_Type = (Memo1->Lines->Strings[LOffset][4]);
   sBlock_Type += (Memo1->Lines->Strings[LOffset][5]);
   sBlock_Type += (Memo1->Lines->Strings[LOffset][6]);

   iBlock_Number = StrToInt(sBlock_Number);
   iBlock_Type = StrToInt(sBlock_Type);

   if((iBlock_Number==0)&&(iBlock_Type == 0)){
      //Print block name and control string
      Memo2->Lines->Add(Memo1->Lines->Strings[LOffset-1]);
      //Add Airfoil name to list
      lstAirfoils->Items->Add(Memo1->Lines->Strings[LOffset-1]);
      //Create an airfoil object
      TAirfoil * AirfoilItem;
      AirfoilItem = new TAirfoil;
      AirfoilItem->Name = Memo1->Lines->Strings[LOffset-1];
      //Print control line
      Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);

      sAF_Number = (Memo1->Lines->Strings[LOffset][7]);
      sAF_Number += (Memo1->Lines->Strings[LOffset][8]);
      sAF_Number += (Memo1->Lines->Strings[LOffset][9]);

      sAF_PointCount = (Memo1->Lines->Strings[LOffset][16]);
      sAF_PointCount += (Memo1->Lines->Strings[LOffset][17]);
      sAF_PointCount += (Memo1->Lines->Strings[LOffset][18]);

      sAF_Type = (Memo1->Lines->Strings[LOffset][10]);
      sAF_Type += (Memo1->Lines->Strings[LOffset][11]);
      sAF_Type += (Memo1->Lines->Strings[LOffset][12]);

      sAF_IMASH = (Memo1->Lines->Strings[LOffset][22]);
      sAF_IMASH += (Memo1->Lines->Strings[LOffset][23]);
      sAF_IMASH += (Memo1->Lines->Strings[LOffset][24]);

      sAF_IPREOB = (Memo1->Lines->Strings[LOffset][25]);
      sAF_IPREOB += (Memo1->Lines->Strings[LOffset][26]);
      sAF_IPREOB += (Memo1->Lines->Strings[LOffset][27]);

      lbeNumber->Text = sAF_Number;
      lbePointCount->Text = sAF_PointCount;
      lbeType->Text = sAF_Type;

      iAF_Number = StrToInt(StrWSRem(sAF_Number));
      iAF_PointCount = StrToInt(StrWSRem(sAF_PointCount));
      iAF_Type = StrToInt(StrWSRem(sAF_Type));
      iAF_IMASH = StrToInt(StrWSRem(sAF_IMASH));
      iAF_IPREOB = StrToInt(StrWSRem(sAF_IPREOB));
      //
      AirfoilItem->Number = iAF_Number;
      AirfoilItem->PointCount = iAF_PointCount;
      AirfoilItem->Type = iAF_Type;
      AirfoilItem->IMASH = iAF_IMASH;
      AirfoilItem->IROT = iAF_IPREOB;

      //
      //if AF_Type = 0
      if(iAF_Type == 0){
      //Two commentaries
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          //Compute Line Count with Points Coordinates
          int LineCount = iAF_PointCount/10;
          if (iAF_PointCount%10)LineCount++;
          stgAcoords->RowCount = iAF_PointCount+1;
          stgAcoords->ColCount = 3;
          //Read first block of Points
          int NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[0][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          //One Commentaries
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          //Read second block of Points
          NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[1][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          //One Commentaries
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          //Read third block of Points
          NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[2][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          if((iAF_IMASH!=0)||(iAF_IPREOB!=0))
          {
              LOffset++;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              LOffset++;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          }
      }
      //if AF_Type = 1
      if(iAF_Type == 1){
      //Two commentaries
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          //Compute Line Count with Points Coordinates
          int LineCount = iAF_PointCount/10;
          if (iAF_PointCount%10)LineCount++;
          stgAcoords->RowCount = iAF_PointCount+1;
          stgAcoords->ColCount = 3;
          //Read first block of Points
          int NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[0][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          //One Commentaries
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          //Read second block of Points
          NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[1][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          //One Commentaries
          LOffset++;
          //Read third block of Points
          NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[2][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          if(iAF_IMASH!=0)
          {
              LOffset++;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              LOffset++;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          }
      }
      //if AF_Type = 2
      if(iAF_Type == 2){
          //Two commentaries
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          //Compute Line Count with Points Coordinates
          int LineCount = iAF_PointCount/10;
          if (iAF_PointCount%10)LineCount++;
          stgAcoords->RowCount = iAF_PointCount+1;
          stgAcoords->ColCount = 2;
          //Read first block of Points
          int NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[0][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          //One Commentaries
          LOffset++;
          Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          //Read second block of Points
          NumberInLine = 0;
          for(int i = 0; i < LineCount; i++)
          {
              LOffset++;
              if (i < LineCount-1) NumberInLine = 10;
                 else NumberInLine = iAF_PointCount-(LineCount-1)*10;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              for(int j = 0; j < NumberInLine; j++)
              {
              stgAcoords->Cells[1][1+i*10+j] = Memo1->Lines->Strings[LOffset].SubString(j*7+1,7);
              }
          }
          if(iAF_IMASH!=0)
          {
              LOffset++;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
              LOffset++;
              Memo2->Lines->Add(Memo1->Lines->Strings[LOffset]);
          }
       }
       //Add Airfoil_Item to list
       //Add Coords from StringGrid to memory
       for(int i = 1; i<=AirfoilItem->PointCount; i++)
        {
           if (iAF_Type == 0) {
                AirfoilItem->Coords0[i].X = StrToFloat(stgAcoords->Cells[0][i]);
                AirfoilItem->Coords0[i].Y_Up = StrToFloat(stgAcoords->Cells[1][i]);
                AirfoilItem->Coords0[i].Y_Down = StrToFloat(stgAcoords->Cells[2][i]);
           }
           else
           {
                AirfoilItem->Coords0[i].X = 0;
                AirfoilItem->Coords0[i].Y_Up = 0;
                AirfoilItem->Coords0[i].Y_Down = 0;
           }
           if (iAF_Type == 1) {
                AirfoilItem->Coords1[i].X = StrToFloat(stgAcoords->Cells[0][i]);
                if(stgAcoords->Cells[1][i]!="")
                AirfoilItem->Coords1[i].Y_mean = StrToFloat(stgAcoords->Cells[1][i]);
                else AirfoilItem->Coords1[i].Y_mean = 0;
                AirfoilItem->Coords1[i].Y_thicness = StrToFloat(stgAcoords->Cells[2][i]);
           }
           else
           {
                AirfoilItem->Coords1[i].X = 0;
                AirfoilItem->Coords1[i].Y_mean = 0;
                AirfoilItem->Coords1[i].Y_thicness = 0;
           }
           if (iAF_Type == 2) {
                AirfoilItem->Coords2[i].X = StrToFloat(stgAcoords->Cells[0][i]);
                AirfoilItem->Coords2[i].Y = StrToFloat(stgAcoords->Cells[1][i]);
           }
           else
           {
                AirfoilItem->Coords2[i].X = 0;
                AirfoilItem->Coords2[i].Y = 0;
           }
        }
       //
       AList->Add(AirfoilItem);
   }
   else isFoil = false;
}
}
//---------------------------------------------------------------------------
void __fastcall TForm1::lstAirfoilsClick(TObject *Sender)
{
        DrawAirfoil(lstAirfoils->ItemIndex);
        TAirfoil * AirfoilItem;
        AirfoilItem = (PTAirfoil) AList->Items[lstAirfoils->ItemIndex];
        lbeType->Text = AirfoilItem->Type;
        lbeNumber->Text = IntToStr(AirfoilItem->Number);
        lbePointCount->Text = IntToStr(AirfoilItem->PointCount);
        //Show Coord in STG for selected foil
        if(AirfoilItem->Type == 2){
                stgAcoords->RowCount = AirfoilItem->PointCount+1;
                stgAcoords->ColCount = 2;
                for (int i=1; i<=AirfoilItem->PointCount; i++){
                      stgAcoords->Cells[0][i] = FloatToStr(AirfoilItem->Coords2[i].X);
                      stgAcoords->Cells[1][i] = FloatToStr(AirfoilItem->Coords2[i].Y);
                }
        }
        if(AirfoilItem->Type == 1){
                stgAcoords->RowCount = AirfoilItem->PointCount+1;
                stgAcoords->ColCount = 3;
                for (int i=1; i<=AirfoilItem->PointCount; i++){
                      stgAcoords->Cells[0][i] = FloatToStr(AirfoilItem->Coords1[i].X);
                      stgAcoords->Cells[1][i] = FloatToStr(AirfoilItem->Coords1[i].Y_mean);
                      stgAcoords->Cells[2][i] = FloatToStr(AirfoilItem->Coords1[i].Y_thicness);

                }
        }
        if(AirfoilItem->Type == 0){
                stgAcoords->RowCount = AirfoilItem->PointCount+1;
                stgAcoords->ColCount = 3;
                for (int i=1; i<=AirfoilItem->PointCount; i++){
                      stgAcoords->Cells[0][i] = FloatToStr(AirfoilItem->Coords0[i].X);
                      stgAcoords->Cells[1][i] = FloatToStr(AirfoilItem->Coords0[i].Y_Up);
                      stgAcoords->Cells[2][i] = FloatToStr(AirfoilItem->Coords0[i].Y_Down);

                }
        }
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//    Draw selected airfoil contour on canvas on plot some data
//---------------------------------------------------------------------------
void TForm1::DrawAirfoil(int Index)
{
        //Clear SCR
        Image1->Canvas->Rectangle(-10,-10,1000,1000);
        int X_LE = 16, Y_LE = 65;
        //Load an airfoil by Index
        TAirfoil * AirfoilItem;
        AirfoilItem = (PTAirfoil) AList->Items[Index];
        //LoadCoordsToSTG
        //Calculate airfoil parameters
        float MinX=0, MaxX=0;
        for(int i=1; i<= AirfoilItem->PointCount; i++){
           if (AirfoilItem->Type == 0){
               if(AirfoilItem->Coords0[i].X > MaxX)
                  MaxX = AirfoilItem->Coords0[i].X;
           }
           if (AirfoilItem->Type == 1){
               if(AirfoilItem->Coords1[i].X > MaxX)
                  MaxX = AirfoilItem->Coords1[i].X;
           }
           if (AirfoilItem->Type == 2){
               if(AirfoilItem->Coords2[i].X > MaxX)
                  MaxX = AirfoilItem->Coords2[i].X;
           }
        }
        //Scale
        float Scale = (520.0-16.0*2)/(MaxX - MinX);
        //Draw
        int Dx=X_LE,Dy=Y_LE;
        if (AirfoilItem->Type == 2) {
        Image1->Canvas->MoveTo(AirfoilItem->Coords2[1].X*Scale+X_LE, -1*AirfoilItem->Coords2[1].Y*Scale+Y_LE);
        for(int i=1; i<= AirfoilItem->PointCount; i++){
                Dx = AirfoilItem->Coords2[i].X*Scale+X_LE;
                Dy = -1*AirfoilItem->Coords2[i].Y*Scale+Y_LE;
                Image1->Canvas->LineTo(Dx, Dy);
                Image1->Canvas->MoveTo(Dx, Dy);
        }
        }
        if (AirfoilItem->Type == 0) {
        Image1->Canvas->MoveTo(X_LE,Y_LE);
        for(int i=1; i<= AirfoilItem->PointCount; i++){
                Dx = AirfoilItem->Coords0[i].X*Scale+X_LE;
                Dy = -1*AirfoilItem->Coords0[i].Y_Up*Scale+Y_LE;
                Image1->Canvas->LineTo(Dx, Dy);
                Image1->Canvas->MoveTo(Dx, Dy);
        }
        Image1->Canvas->MoveTo(X_LE,Y_LE);
        for(int i=1; i<= AirfoilItem->PointCount; i++){
                Dx = AirfoilItem->Coords0[i].X*Scale+X_LE;
                Dy = -1*AirfoilItem->Coords0[i].Y_Down*Scale+Y_LE;
                Image1->Canvas->LineTo(Dx, Dy);
                Image1->Canvas->MoveTo(Dx, Dy);
        }
        }
        if (AirfoilItem->Type == 1) {
        Image1->Canvas->MoveTo(X_LE,Y_LE);
        for(int i=1; i<= AirfoilItem->PointCount; i++){
                Dx = AirfoilItem->Coords1[i].X*Scale+X_LE;
                Dy = -1*(AirfoilItem->Coords1[i].Y_mean+AirfoilItem->Coords1[i].Y_thicness)*Scale+Y_LE;
                Image1->Canvas->LineTo(Dx, Dy);
                Image1->Canvas->MoveTo(Dx, Dy);
        }
        Image1->Canvas->MoveTo(X_LE,Y_LE);
        for(int i=1; i<= AirfoilItem->PointCount; i++){
                Dx = AirfoilItem->Coords1[i].X*Scale+X_LE;
                Dy = -1*(AirfoilItem->Coords1[i].Y_mean-AirfoilItem->Coords1[i].Y_thicness)*Scale+Y_LE;
                Image1->Canvas->LineTo(Dx, Dy);
                Image1->Canvas->MoveTo(Dx, Dy);
        }
        }
}
//---------------------------------------------------------------------------
//     Function for whitespace remove
//---------------------------------------------------------------------------
AnsiString TForm1::StrWSRem(AnsiString Input){
        AnsiString Output="";
        bool StartIsDone = false;
        bool FirstNumberDone = false;
        int i=1,j=1;
        //Skip first whitespace sequence
        for (; i <= strlen(Input.c_str()); i++){
                if(Input[i]!=(char)32) { StartIsDone = true; break; }
        }
        //Copy first number;
        for (; i<= strlen(Input.c_str()); i++){
                if((Input[i]!=(char)32)) Output += Input[i];
                else
                {
                     FirstNumberDone = true; break;
                }
        }
        return Output;
}
//---------------------------------------------------------------------------
void __fastcall TForm1::SaveClick(TObject *Sender)
{
        TAirfoil * AirfoilItem;
        AirfoilItem = (PTAirfoil) AList->Items[lstAirfoils->ItemIndex];

        if(!SaveDialog1->Execute()) return;
        String Name=SaveDialog1->FileName;

        std::ofstream out(Name.c_str()); if(!out.is_open()) return;
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out
        std::cout<<AirfoilItem->Name.c_str()<<endl;
        //Get foil chord
        //Calculate airfoil parameters
        float Normalizator = 1;
        if(cbeNormalize){
        float MinX=0, MaxX=0;
        for(int i=1; i<= AirfoilItem->PointCount; i++){
           if (AirfoilItem->Type == 0){
               if(AirfoilItem->Coords0[i].X > MaxX)
                  MaxX = AirfoilItem->Coords0[i].X;
           }
           if (AirfoilItem->Type == 1){
               if(AirfoilItem->Coords1[i].X > MaxX)
                  MaxX = AirfoilItem->Coords1[i].X;
           }
           if (AirfoilItem->Type == 2){
               if(AirfoilItem->Coords2[i].X > MaxX)
                  MaxX = AirfoilItem->Coords2[i].X;
           }
        }
        Normalizator = MaxX-MinX;
        }
        if (AirfoilItem->Type == 0)
        {
           std::cout<<IntToStr(AirfoilItem->PointCount*2-1).c_str()<<std::endl;
           for(int i=AirfoilItem->PointCount; i>0; i--)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].Y_Up)/Normalizator).c_str()<<std::endl;
           }
           for(int i=2; i<=AirfoilItem->PointCount; i++)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].Y_Down)/Normalizator).c_str()<<std::endl;
           }
        }
        if (AirfoilItem->Type == 1)
        {
           std::cout<<IntToStr(AirfoilItem->PointCount*2-1).c_str()<<std::endl;
           for(int i=AirfoilItem->PointCount; i>0; i--)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].Y_mean+AirfoilItem->Coords1[i].Y_thicness)/Normalizator).c_str()<<std::endl;
           }
           for(int i=2; i<=AirfoilItem->PointCount; i++)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].Y_mean-AirfoilItem->Coords1[i].Y_thicness)/Normalizator).c_str()<<std::endl;
           }
        }
        if (AirfoilItem->Type == 2)
        {
           std::cout<<IntToStr(AirfoilItem->PointCount).c_str()<<std::endl;
           for(int i=AirfoilItem->PointCount; i>0; i--)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords2[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords2[i].Y)/Normalizator).c_str()<<std::endl;
           }
        }
        std::cout.rdbuf(coutbuf); //reset to standard output again
        out.close();
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button4Click(TObject *Sender)
{
        //Create an Airfoil instance and load by index
        TAirfoil * AirfoilItem;
        AirfoilItem = (PTAirfoil) AList->Items[lstAirfoils->ItemIndex];
        //Get file name
        if(!SaveDialog1->Execute()) return;
        String Name=SaveDialog1->FileName;
        //Create output stream
        std::ofstream out(Name.c_str()); if(!out.is_open()) return;
        std::streambuf *coutbuf = std::cout.rdbuf(); //save old buf
        std::cout.rdbuf(out.rdbuf()); //redirect std::cout to out
        //Write foil name
        std::cout<<AirfoilItem->Name.c_str()<<endl;
        //Get foil chord
        //Calculate airfoil parameters
        float Normalizator = 1;
        if(cbeNormalize){
        float MinX=0, MaxX=0;
        for(int i=1; i<= AirfoilItem->PointCount; i++){
           if (AirfoilItem->Type == 0){
               if(AirfoilItem->Coords0[i].X > MaxX)
                  MaxX = AirfoilItem->Coords0[i].X;
           }
           if (AirfoilItem->Type == 1){
               if(AirfoilItem->Coords1[i].X > MaxX)
                  MaxX = AirfoilItem->Coords1[i].X;
           }
           if (AirfoilItem->Type == 2){
               if(AirfoilItem->Coords2[i].X > MaxX)
                  MaxX = AirfoilItem->Coords2[i].X;
           }
        }
        Normalizator = MaxX-MinX;
        }
        if (AirfoilItem->Type == 0)
        {
           for(int i=AirfoilItem->PointCount; i>0; i--)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].Y_Up)/Normalizator).c_str()<<std::endl;
           }
           for(int i=2; i<=AirfoilItem->PointCount; i++)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords0[i].Y_Down)/Normalizator).c_str()<<std::endl;
           }
        }
        if (AirfoilItem->Type == 1)
        {
           for(int i=AirfoilItem->PointCount; i>0; i--)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].Y_mean+AirfoilItem->Coords1[i].Y_thicness)/Normalizator).c_str()<<std::endl;
           }
           for(int i=2; i<=AirfoilItem->PointCount; i++)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords1[i].Y_mean-AirfoilItem->Coords1[i].Y_thicness)/Normalizator).c_str()<<std::endl;
           }
        }
        if (AirfoilItem->Type == 2)
        {
           for(int i=AirfoilItem->PointCount; i>0; i--)
           {
              std::cout<<FloatToStr((AirfoilItem->Coords2[i].X)/Normalizator).c_str()<<" ";
              std::cout<<FloatToStr((AirfoilItem->Coords2[i].Y)/Normalizator).c_str()<<std::endl;
           }
        }
        std::cout.rdbuf(coutbuf); //reset to standard output again
        out.close();
}
//---------------------------------------------------------------------------
