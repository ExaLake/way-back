/* rex script for the POS example */
call RxFuncAdd 'SysSleep', 'RexxUtil', 'SysSleep'

'start somdd'
call SysSleep '5'

'start  "Name Server" somdsvr -a pnssvr'
call SysSleep '5'

'start  "Central Server" somdsvr -a centralsvr'
call SysSleep '5'

'start  "Output Media 1" somdsvr -a outputsvr_1'
call SysSleep '5'

'start "Output Media 2" somdsvr -a outputsvr_2'
call SysSleep '5'

'start "Store Server 1 " somdsvr -a storesvr_1'
