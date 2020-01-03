//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
//---------------------------------------------------------------------------
USEFORM("FrmMan.cpp", FrmManager);
USERES("UManager.res");
USEFORM("FrNew.cpp", FrmNew);
USEFORM("FrGroup.cpp", FrmGroups);
USEFORM("FrProper.cpp", FrmProperty);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TFrmManager), &FrmManager);
		Application->CreateForm(__classid(TFrmProperty), &FrmProperty);
		Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
