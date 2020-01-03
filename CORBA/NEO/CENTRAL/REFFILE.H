#ifndef reffile_h
#define reffile_h

#include "corba/orb.hh"

#define Object_ptr ObjectRef
#define ORB_ptr ORBRef

extern char * Primer_ORB;

char *fullPath(char *path, const char *filename);

unsigned char readRef(char *refstring, const char *filename);

void writeRef(CORBA::Object_ptr OP, CORBA::ORB_ptr orb,
              const char *filename);

#endif

