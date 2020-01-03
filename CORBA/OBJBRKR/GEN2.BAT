rem Second phase of generation for ObjectBroker in the Point Of Sale example

rem Load .iml and .iml routines into repository

obbldrep central.iml  central.mml
obbldrep pos.iml      pos.mml
obbldrep pnamesvc.iml pnamesvc.mml
obbldrep store.iml    store.mml

rem Generate stubs, method skeletons, and dispatch routines

rem ...For CentralOffice
obbgen -lc -c centstb.c -B central -ps CentralOffice::Depot
obbgen -lc -t central.c	-B central       DepotImpl
obbgen -lc -d centdsp.c	-B central       DepotImpl

rem ...For PseudoNameService
obbgen -lc -c pnsstb.c   -B pnamesvc -ps PseudoNameService
obbgen -lc -t pnamesvc.c -B pnamesvc       PseudoNameServiceImpl
obbgen -lc -d pnsdsp.c   -B pnamesvc       PseudoNameServiceImpl

rem ...For POS
obbgen -lc -c posstb.c    -B pos -ps POS::POSTerminal POS::InputMedia POS::OutputMedia
obbgen -lc -t posterm.c	  -B pos     POSTerminalImpl
obbgen -lc -t im.c	  -B pos     InputMediaImpl
obbgen -lc -t om.c	  -B pos     OutputMediaImpl
obbgen -lc -d postidsp.c  -B pos     POSTerminalImpl InputMediaImpl
obbgen -lc -d omdsp.c     -B pos     OutputMediaImpl
obbgen -lc -d posall.c    -B pos     POSTerminalImpl InputMediaImpl OutputMediaImpl

rem ...For Store
obbgen -lc -c stostb.c    -B astore -ps AStore::Store AStore::StoreAccess AStore::Tax
obbgen -lc -t store.c     -B astore     StoreImpl
obbgen -lc -t store_ac.c  -B astore     StoreAccessImpl
obbgen -lc -t tax.c	  -B astore     TaxImpl
obbgen -lc -d stodsp.c	  -B astore     StoreImpl StoreAccessImpl TaxImpl

rem Done with code generation
