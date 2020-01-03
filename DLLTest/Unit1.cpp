//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma link "cgrid"
#pragma link "perfgrap"
#pragma link "TOpenGLPanel"
#pragma resource "*.dfm"

#include "Unit1.h"
TForm2 *Form2;
//---------------------------------------------------------------------------
__fastcall TForm2::TForm2(TComponent* Owner)
    : TForm(Owner)
{
}
//---------------------------------------------------------------------------

void test()
{
    TForm2 *f = new TForm2(NULL);
    f->ShowModal();
    //returnValue = f->GetReturnValue();

}
