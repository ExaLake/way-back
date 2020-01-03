#!/bin/sh
# This script launches the various servers in separate X Terminals.
# It waits a few seconds ($delay) after launching each server to
# make sure that the previous server has properly started and 
# registered it self with the pseudo naming service.
#
delay=5
(cd PNS ; xterm -sb -title "PseudoName server (pname)" -e pname &) 
sleep $delay
(cd central ; xterm -sb -title "Depot" -e depot &)
sleep $delay
(cd store ; xterm -sb -title "Store (store 101 1.05)" -e store 101 1.05 &)
sleep $delay
(cd POS.out ; xterm -sb -title "POS Output (outsrv 25)" -e outsrv 25 &)
sleep $delay
(cd POS.ter ; xterm -sb -title "POS Input (posclt 101 25)" -e posclt 101 25 &)
