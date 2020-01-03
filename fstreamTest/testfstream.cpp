// testfstream.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream.h>
#include <fstream.h>


struct toto
{
	int x;
	int y;
};

int main(int argc, char* argv[])
{
	ofstream f;
	
	toto t;
	t.x = 100;
	t.y = 200;

	f.open("test.bin", ios::in , ios::binary);

	for ( int i = 0 ; i < 10000 ; i++)
		f.write( (unsigned char*)&t, sizeof(toto) );

	return 0;
}

