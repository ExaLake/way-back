// testException2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <iostream.h>

void MyFunc( void );

class CException
{
public:
    CException(){};
    ~CException(){};
    const char *ShowReason() const { return "Exception in CException class."; }

};

class CDtorDemo
{
public:
    CDtorDemo();
    ~CDtorDemo();
};

CDtorDemo::CDtorDemo()
{
    cout << "Constructing CDtorDemo." << endl;
}

CDtorDemo::~CDtorDemo()
{
    cout << "Destructing CDtorDemo." << endl;
}

void MyFunc(int type)
{
	if ( type == 1 )
	{
		CDtorDemo D;
		cout<< "In MyFunc(). Throwing CException exception." << endl;
		throw CException();
	}
	if ( type == 2 )
	{
		throw 23;
	}
}



int main(int argc, char* argv[])
{
	    cout << "In main." << endl;
    try
    {
        cout << "In try block, calling MyFunc()." << endl;
        MyFunc(2);
    }
    catch( CException E )
    {
        cout << "In catch handler." << endl;
        cout << "Caught CException exception type: ";
        cout << E.ShowReason() << endl;
    }
    catch( char *str )
    {
        cout << "Caught some other exception: " << str << endl;
    }
	catch(int i)
	{
		cout << "Caught some other exception: " << i << endl;
	}

    cout << "Back in main. Execution resumes here." << endl;
    return 0;
}
