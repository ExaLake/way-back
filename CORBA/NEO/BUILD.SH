#!/bin/sh
# This script builds each of the servers and clients needed to
# run the Point Of Sale example. For this script to work, 
# WorkShopNEO(tm) must be properly installed. 
#
echo ========================
echo Compiling IDL interfaces
echo ========================
cd interfaces
odfimake
make

echo
echo ========================================================
echo Registering IDL interfaces with the Interface Repository
echo ========================================================
make register

echo
echo ==========================
echo Building PseudoName server
echo ==========================
cd ../PNS
odfimake
make

echo
echo =====================
echo Building Depot server
echo =====================
cd ../central
odfimake
make

echo
echo =====================
echo Building Store server
echo =====================
cd ../store
odfimake
make

echo
echo ========================
echo Building Output terminal
echo ========================
cd ../POS.out
odfimake
make

echo
echo =======================
echo Building Input terminal
echo =======================
cd ../POS.ter
odfimake
make
