# This file is a bourne shell script that will build all 
# the executables for the primer POS application. You
# may need to modify the values of PRIMER_IDL and DAIS_ROOT
# to suit your own environment.

set -a									# export all variables

PRIMER_IDL=./idl						# location of IDL
DAIS_ROOT=/dais							# DAIS installation point 

# Compile all the IDL
# ===================

stubgen  -lc -I$PRIMER_IDL Store.idl 
stubgen  -lc -I$PRIMER_IDL POS.idl 
stubgen  -lc -I$PRIMER_IDL Central.idl 
stubgen  -lc -I$PRIMER_IDL PNS.idl

# Compile all the stubs and all the application code
# ==================================================

cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include c_Central.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include c_PNS.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include c_POS.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include c_Store.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include central.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include depot_main.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include im.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include linear.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include m_Central.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include m_PNS.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include m_POS.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include m_Store.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include misc.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include om.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include om_main.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include pname_main.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include pnamesvc.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include pos_main.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include posterminal.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include s_Central.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include s_PNS.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include s_POS.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include s_Store.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include store.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include store_access.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include store_main.c
cc -gXc -c ${DEFINES} -I. -I$DAIS_ROOT/include tax.c

# make a library of the stub code
# ===============================
ar ru libprimer.a  c_Central.o m_Central.o s_Central.o \
                c_PNS.o m_PNS.o s_PNS.o \
                c_Store.o m_Store.o s_Store.o \
                c_POS.o m_POS.o s_POS.o

# final build for the store, central, pos and om executables
# ==========================================================
cc -o store  store_main.o tax.o store.o misc.o store_access.o \
			-L. -lprimer \
			-L$DAIS_ROOT/lib -ldais -lxti -lnsl

cc -o central depot_main.o pnamesvc.o central.o misc.o linear.o \
			-L. -lprimer \
			-L$DAIS_ROOT/lib -ldais -lxti -lnsl

cc -o pos  pos_main.o posterminal.o im.o  misc.o om.o \
			-L. -lprimer \
			-L$DAIS_ROOT/lib -ldais -lxti -lnsl

cc -o om  om_main.o om.o misc.o posterminal.o im.o \
			-L. -lprimer \
			-L$DAIS_ROOT/lib -ldais -lxti -lnsl




