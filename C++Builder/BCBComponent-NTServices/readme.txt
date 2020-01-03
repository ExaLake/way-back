NT specific components for Delphi 2.0/3.x/4.0 and C++Builder 1.0/3.0
Now has 6 components: 

TNTService:      to add, delete, control and configure WindowsNT services
TNTEventLog:     to work with event log as simple as with TStringList.
TNTUserMan:      to add, delete, get information about users and groups
TNTShare:        to manage share devices, monitor connected users, used resources 
TNTFileSecurity: to assign access rights for files on NTFS
TNTRegSecurity:  this components deals with registry's security

Delphi 4
--------
To install components into Delphi IDE open project NTSet.bpg.
Select NT.bpl in the project manager, compile and install it.
All the otjher project in the project group demonstrate the 
main fatures of components and should be opened after the
NT.bpl  is compiled and installed.
 
Delphi 3
---------
Before opening demo projects please install compile and install 
package NT.DPL using File/Open NT.DPK + compile + install
Remember to set path to the directory of NT.DPL using 
menu command Project/Options.

Delphi 2
---------
In order to install the new components into IDE do as follow:
Execute menu command Component/install
Add to the library following files:
NTReg.dcu to install the all the components of the collection
RegEdtrs.dcu to  register design time property editors


C++Builder 3.0
--------------
Full version:
In order to install the new components into IDE do as follow:
Open project group library.bpg. Compile all projects that 
included into group. Copy ntrtl.bpl into into your SYSTEM 
folder. For example d:\winnt\systen32; Use menu command
Component\install packages. Add new package ntdcl.bpl     

Shareware version:
Copy ntrtl.bpl into into your SYSTEM 
folder. For example d:\winnt\systen32; Use menu command
Component\install packages. Add new package ntdcl.bpl     


C++Builder 1.0
--------------
In order to install the new components into IDE do as follow:
Execute menu command Component/install
Add to the library files
NTReg.obj to install the all the components of the collection
RegEdtrs.obj to  register design time property editors

Note
----
Version for C++ Builder  does not have the examples 
for some components. Full help is supplied.

e-mail:   contact@risq.belcaf.minsk.by
visit us: http://www.belcaf.com
          http://members.xoom.com/sergei19/ntset.htm
