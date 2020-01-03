rem First phase of generation for ObjectBroker in the Point Of Sale example

rem Create and load local context object
obbldctx -c -U primer.col

rem Assigning unique UUIDs to IDL files
obbgen -u -f Central.idl
obbgen -u -f PNS.idl
obbgen -u -f POS.idl
obbgen -u -f Store.idl

rem Create new repository and load it with IDLs
obbldrep -c POS.idl Store.idl Central.idl PNS.idl

rem Generate default .IML and .MML files

rem ...For CentralOffice (depot)
obbgen -i central.iml CentralOffice::Depot
obbgen -m central.mml CentralOffice::Depot

rem ...For PseudoNameService
obbgen -i pnamesvc.iml PseudoNameService
obbgen -m pnamesvc.mml PseudoNameService

rem ...For POS
obbgen -i pos.iml POS::POSTerminal POS::InputMedia POS::OutputMedia
obbgen -m pos.mml POS::POSTerminal POS::InputMedia POS::OutputMedia

rem ...For Store
obbgen -i store.iml AStore::Store AStore::StoreAccess AStore::Tax
obbgen -m store.mml AStore::Store AStore::StoreAccess AStore::Tax

rem Now stop and edit the pos.iml file as in the README.TXT file
rem    or in the book.

