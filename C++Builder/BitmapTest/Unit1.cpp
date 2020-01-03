//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
 bitmaps =
        CreateCompatibleBitmap(this->Canvas->Handle, 64, 64);

 memDC = CreateCompatibleDC( this->Canvas->Handle ) ;

}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button1Click(TObject *Sender)
{
    Timer1->Enabled = true;
    SelectObject(memDC, bitmaps );
    for ( int i = 0 ; i < 64 ; i+=4)
       for ( int j = 0 ; j < 64 ; j+=4 )
       {
        SetPixel(memDC, i, j , random(256)*256*256);
        SetPixel(memDC, i+1, j+1 , random(256)*256*256);
        SetPixel(memDC, i+3, j+3 , random(256)*256*256);
        SetPixel(memDC, i+4, j+4 , random(256)*256*256);

       }

    /* Test le deplacement d<un pixel ...
     *
     * SetPixel(memDC, xpos , 10 , 8799786 random( 256*256) );
     *  xpos++;
     */
    StretchBlt(
    this->Canvas->Handle,
    0,0,
    this->Width,
    this->Height,
    memDC,
    0,0,
    64,64,
    SRCCOPY
   );

    // BitBlt(this->Canvas->Handle, 0,0,  this->Width, this->Height,   memDC, 0,0 , SRCCOPY	);


}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormResize(TObject *Sender)
{
      StretchBlt(
    this->Canvas->Handle,
    0,0,
    this->Width,
    this->Height,
    memDC,
    0,0,
    64,64,
    SRCCOPY
   );
    
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
     SelectObject(memDC, bitmaps );


    for ( int i = 0 ; i < 64 ; i+=2)
       for ( int j = 0 ; j < 64 ; j+=2 )
       {
        SetPixel(memDC, i, j , random(256)*256*256);
        SetPixel(memDC, i+1, j+1 , random(256)*256*256);
       }

    /* Test le deplacement d<un pixel ...
     *
     * SetPixel(memDC, xpos , 10 , 8799786 random( 256*256) );
     *  xpos++;
     */
    StretchBlt(
    this->Canvas->Handle,
    0,0,
    this->Width,
    this->Height,
    memDC,
    0,0,
    64,64,
    SRCCOPY
   );
    
}
//---------------------------------------------------------------------------

