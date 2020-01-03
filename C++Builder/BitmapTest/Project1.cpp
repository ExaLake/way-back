//---------------------------------------------------------------------------
#include <vcl.h>
#pragma hdrstop
USERES("Project1.res");
USEFORM("Unit1.cpp", Form1);
USEUNIT("..\..\Projects\textureBitmapLib\Bitmap.c");
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE hinst, HINSTANCE, LPSTR, int)
{

    try
    {
        Application->Initialize();
        Application->CreateForm(__classid(TForm1), &Form1);
        Application->Run();
    }
    catch (Exception &exception)
    {
        Application->ShowException(&exception);
    }
    return 0;
}
//---------------------------------------------------------------------------
