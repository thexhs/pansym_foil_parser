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
   TButton *btnFoil;
        TRadioGroup *rgdV;
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
   TMemo *mAirfoil;
   TMemo *mWinglet;
   TButton *btnWing;
   TMemo *mWing;
   TMemo *mInFile;
   TButton *btnWinglet;
   TButton *btnAuto;
   TButton *btnMakeIn;
   TButton *btnPANSYM;
   TButton *btnVisual;
   TButton *btnOU2GEO;
   TButton *Button10;
        void __fastcall btnFoilClick(TObject *Sender);
        void __fastcall btnPANSYMClick(TObject *Sender);
        void __fastcall rgZClick(TObject *Sender);
   void __fastcall rgRClick(TObject *Sender);
   void __fastcall btnWingClick(TObject *Sender);
   void __fastcall rgWingClick(TObject *Sender);
   void __fastcall btnWingletClick(TObject *Sender);
   void __fastcall btnAutoClick(TObject *Sender);
   void __fastcall btnMakeInClick(TObject *Sender);
   void __fastcall btnOU2GEOClick(TObject *Sender);
   void __fastcall btnVisualClick(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        AnsiString FmtStr72(AnsiString InputStr);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
