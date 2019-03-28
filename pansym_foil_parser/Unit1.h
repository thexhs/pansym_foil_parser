//---------------------------------------------------------------------------

#ifndef Unit1H
#define Unit1H
//---------------------------------------------------------------------------
#include <Classes.hpp>
#include <Controls.hpp>
#include <StdCtrls.hpp>
#include <Forms.hpp>
#include <Dialogs.hpp>
#include <ExtCtrls.hpp>
#include <Grids.hpp>
//---------------------------------------------------------------------------
class TForm1 : public TForm
{
__published:	// IDE-managed Components
        TButton *Button1;
        TMemo *Memo1;
        TOpenDialog *OpenDialog1;
        TMemo *Memo2;
        TButton *Button3;
        TLabeledEdit *lbePointCount;
        TLabeledEdit *lbeNumber;
        TLabeledEdit *lbeType;
        TListBox *lstAirfoils;
        TStringGrid *stgAcoords;
        TButton *Save;
        TButton *Button2;
        TImage *Image1;
        TSaveDialog *SaveDialog1;
        TButton *Button4;
        TButton *Button5;
        TCheckBox *cbeNormalize;
        void __fastcall Button1Click(TObject *Sender);
        void __fastcall Button2Click(TObject *Sender);
        void __fastcall Button3Click(TObject *Sender);
        void __fastcall lstAirfoilsClick(TObject *Sender);
        void __fastcall SaveClick(TObject *Sender);
        void __fastcall Button4Click(TObject *Sender);
private:	// User declarations
public:		// User declarations
        __fastcall TForm1(TComponent* Owner);
        void DrawAirfoil(int Index);
        AnsiString StrWSRem(AnsiString Input);
};
//---------------------------------------------------------------------------
extern PACKAGE TForm1 *Form1;
//---------------------------------------------------------------------------
#endif
