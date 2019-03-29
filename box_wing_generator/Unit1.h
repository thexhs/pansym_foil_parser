//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <ExtCtrls.hpp>
#include <Dialogs.hpp>
#include <ComCtrls.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TButton *Button2;
        TRadioGroup *rgdV;
        TButton *Button3;
        TButton *Button4;
        TOpenDialog *OpenDialog1;
        TRadioGroup *rgR;
        TRadioGroup *rgZ;
        TRadioGroup *rgWing;
        TPageControl *PageControl1;
        TTabSheet *TabSheet1;
        TTabSheet *TabSheet2;
        TTabSheet *TabSheet3;
        TTabSheet *TabSheet4;
        TMemo *Memo1;
        TMemo *Memo3;
   TButton *Button5;
   TMemo *Memo4;
   TMemo *Memo2;
   TButton *Button6;
        void __fastcall rgdVClick(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall rgZClick(TObject *Sender);
   void __fastcall rgRClick(TObject *Sender);
   void __fastcall Button5Click(TObject *Sender);
   void __fastcall rgWingClick(TObject *Sender);
   void __fastcall Button6Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        AnsiString FmtStr72(AnsiString InputStr);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
