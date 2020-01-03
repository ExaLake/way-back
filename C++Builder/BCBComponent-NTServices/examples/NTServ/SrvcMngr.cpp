//---------------------------------------------------------------------------
#include <vcl\vcl.h>
#pragma hdrstop
#pragma option -w-dup
//---------------------------------------------------------------------------
USEFORM("FrmMain.cpp", FrmSrvMngr);
USERES("SrvcMngr.res");
USEFORM("FrmNew.cpp", FrmNewService);
USEFORM("FrmProp.cpp", FrmProperty);
//---------------------------------------------------------------------------
WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
{
	try
	{
		Application->Initialize();
		Application->CreateForm(__classid(TFrmSrvMngr), &FrmSrvMngr);
        Application->Run();
	}
	catch (Exception &exception)
	{
		Application->ShowException(&exception);
	}
	return 0;
}
//---------------------------------------------------------------------------
