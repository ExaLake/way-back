
COMObjectps.dll: dlldata.obj COMObject_p.obj COMObject_i.obj
	link /dll /out:COMObjectps.dll /def:COMObjectps.def /entry:DllMain dlldata.obj COMObject_p.obj COMObject_i.obj \
		kernel32.lib rpcndr.lib rpcns4.lib rpcrt4.lib oleaut32.lib uuid.lib \

.c.obj:
	cl /c /Ox /DWIN32 /D_WIN32_WINNT=0x0400 /DREGISTER_PROXY_DLL \
		$<

clean:
	@del COMObjectps.dll
	@del COMObjectps.lib
	@del COMObjectps.exp
	@del dlldata.obj
	@del COMObject_p.obj
	@del COMObject_i.obj
