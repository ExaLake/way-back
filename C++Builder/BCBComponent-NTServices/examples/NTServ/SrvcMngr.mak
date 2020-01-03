# ---------------------------------------------------------------------------
VERSION = BCB.03
# ---------------------------------------------------------------------------
!ifndef BCB
BCB = $(MAKEDIR)\..
!endif
# ---------------------------------------------------------------------------
PROJECT = SrvcMngr.exe
OBJFILES = SrvcMngr.obj FrmMain.obj FrmNew.obj FrmProp.obj
RESFILES = SrvcMngr.res
RESDEPEN = $(RESFILES) FrmMain.dfm FrmNew.dfm FrmProp.dfm
LIBFILES = 
LIBRARIES = ntrtl.lib vcldbx35.lib vcldb35.lib vclx35.lib vcl35.lib
SPARELIBS = vcl35.lib vclx35.lib vcldb35.lib vcldbx35.lib ntrtl.lib
PACKAGES = vclx35.bpi VCL35.bpi vcldb35.bpi vcldbx35.bpi bcbsmp35.bpi dclocx35.bpi \
  Qrpt35.bpi teeui35.bpi teedb35.bpi tee35.bpi ibsmp35.bpi dss35.bpi NMFast35.bpi \
  inetdb35.bpi inet35.bpi VclMid35.bpi
PATHASM = .;
PATHCPP = .;
PATHPAS = .;
PATHRC = .;
DEBUGLIBPATH = $(BCB)\lib\debug
RELEASELIBPATH = $(BCB)\lib\release
DEFFILE =
# ---------------------------------------------------------------------------
CFLAG1 = -Od -Hc -w -Ve -r- -k -y -v -vi- -c -b- -w-par -w-inl -Vx
CFLAG2 = -I..\..\;$(BCB)\include;$(BCB)\include\vcl -H=$(BCB)\lib\vcld.csm
CFLAG3 =
PFLAGS = -AWinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE \
  -U..\..\..\builder3;..\..\;$(BCB)\lib\obj;$(BCB)\lib;$(DEBUGLIBPATH) \
  -I..\..\;$(BCB)\include;$(BCB)\include\vcl -$Y -$W -$O- -v -JPHNV -M
RFLAGS = -i..\..\;$(BCB)\include;$(BCB)\include\vcl
AFLAGS = /i..\..\ /i$(BCB)\include /i$(BCB)\include\vcl /mx /w2 /zd /dUSEPACKAGES
LFLAGS = -L..\..\..\builder3;..\..\;$(BCB)\lib\obj;$(BCB)\lib;$(DEBUGLIBPATH) -aa -Tpe \
  -x -v
IFLAGS =
LINKER = ilink32
# ---------------------------------------------------------------------------
ALLOBJ = c0w32.obj sysinit.obj $(OBJFILES)
ALLRES = $(RESFILES)
ALLLIB = $(LIBFILES) $(LIBRARIES) import32.lib cp32mt.lib
# ---------------------------------------------------------------------------
.autodepend

!ifdef IDEOPTIONS

[Version Info]
IncludeVerInfo=0
AutoIncBuild=0
MajorVer=1
MinorVer=0
Release=0
Build=0
Debug=0
PreRelease=0
Special=0
Private=0
DLL=0
Locale=1033
CodePage=1252

[Version Info Keys]
FileVersion=1.0.0.0

[HistoryLists\hlIncludePath]
Count=2
Item0=..\..\;$(BCB)\include;$(BCB)\include\vcl
Item1=$(BCB)\include;$(BCB)\include\vcl

[HistoryLists\hlLibraryPath]
Count=3
Item0=..\..\..\builder3;..\..\;$(BCB)\lib\obj;$(BCB)\lib
Item1=..\..\;$(BCB)\lib\obj;$(BCB)\lib
Item2=$(BCB)\lib\obj;$(BCB)\lib

[HistoryLists\hlConditionals]
Count=1
Item0=USEPACKAGES

[HistoryLists\hlUnitAliases]
Count=1
Item0=WinTypes=Windows;WinProcs=Windows;DbiTypes=BDE;DbiProcs=BDE;DbiErrs=BDE

[Debugging]
DebugSourceDirs=

[Parameters]
RunParams=
HostApplication=

!endif

$(PROJECT): $(OBJFILES) $(RESDEPEN) $(DEFFILE)
    $(BCB)\BIN\$(LINKER) @&&!
    $(LFLAGS) +
    $(ALLOBJ), +
    $(PROJECT),, +
    $(ALLLIB), +
    $(DEFFILE), +
    $(ALLRES) 
!

.pas.hpp:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.pas.obj:
    $(BCB)\BIN\dcc32 $(PFLAGS) { $** }

.cpp.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $* 

.c.obj:
    $(BCB)\BIN\bcc32 $(CFLAG1) $(CFLAG2) -o$* $**

.rc.res:
    $(BCB)\BIN\brcc32 $(RFLAGS) $<
#-----------------------------------------------------------------------------
