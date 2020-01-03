#include "reffile.h"
#include <stream.h>
#include <string.h>
#include <stdlib.h>

char* Primer_ORB = "OMG_PRIMER_ORB";

char *fullPath(char *path, const char *filename) {
  char *homepath = getenv("OMGHOME");
  if (!homepath) {
    cerr << "Environment parameter OMGHOME not found" << endl;
    return 0;
  }
  else {
    strcpy(path,homepath);
    strcat(path,filename);
    return path;
  }
}

unsigned char readRef(char *refstring, const char *filename) {
  char path[256];
  ifstream is(fullPath(path,filename));
  if (is) {
    is >> refstring;
    return 1;
  }
  else {
    cerr << "Error opening file " << filename << endl;
    return 0;
  }
}

void writeRef(CORBA::Object_ptr OP, CORBA::ORB_ptr orb,
              const char *filename) {
  char path[256];
  ofstream os(fullPath(path,filename));
  if (os) {
    char *refstring = orb->object_to_string(OP);
    os << refstring;
    CORBA::string_free(refstring);
  }
  else {
    cerr << "Error opening file " << filename << endl;
  }
}

