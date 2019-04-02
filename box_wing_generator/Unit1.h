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
        TButton *btnGetOu;
   TButton *btnHead;
   TTabSheet *TabSheet5;
   TMemo *mHead;
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
        void __fastcall FormShow(TObject *Sender);
        void __fastcall rgdVClick(TObject *Sender);
   void __fastcall btnHeadClick(TObject *Sender);
        void __fastcall btnGetOuClick(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        AnsiString FmtStr72(AnsiString InputStr);
        void ConvertASC(void);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
