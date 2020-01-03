

#ifdef DLL_DIALOG_EXPORT
	#define DLLDIALOG __declspec(dllexport)
#else 
	#define DLLDIALOG __declspec(dllimport)
#endif

void DLLDIALOG ShowDialog();