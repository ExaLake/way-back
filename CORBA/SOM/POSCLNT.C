/*
 *   (C) COPYRIGHT International Business Machines Corp. 1995, 1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *
 *   DISCLAIMER OF WARRANTIES.
 *   The following [enclosed] code is sample code created by IBM
 *   Corporation. This sample code is not part of any standard or IBM
 *   product and is provided to you solely for the purpose of assisting
 *   you in the development of your applications.  The code is provided
 *   "AS IS". IBM MAKES NO WARRANTIES, EXPRESS OR IMPLIED, INCLUDING BUT
 *   NOT LIMITED TO THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 *   FOR A PARTICULAR PURPOSE, REGARDING THE FUNCTION OR PERFORMANCE OF
 *   THIS CODE.  IBM shall not be liable for any damages arising out of
 *   your use of the sample code, even if they have been advised of the
 *   possibility of such damages.
 *
 *   DISTRIBUTION.
 *   This sample code can be freely distributed, copied, altered, and
 *   incorporated into other software, provided that it bears the above
 *   Copyright notice and DISCLAIMER intact.
 */

/*
 *    this is the main driver client program that takes input from
 *    the keyboard and simulates input from the keypad and barcode
 *    reader to the InputMedia object
 */

#include <stdio.h>
#include <ctype.h>

#include <corba12.h>
#include <pos.ih>

#define MAX_STR 100

extern char *storeid;
extern char *posid;

void print_help ();

main (int argc, char **argv)
{
    CORBA_char instring[MAX_STR];
    CORBA_Environment ev;
    POS_InputMedia  inputmedia;
    char loggedin = 0;

    SOM_InitEnvironment(&ev);
    SOMD_Init(&ev);

/** validate the command line arguments **/

    if (argc != 5)
    {
	printf("Usage: %s -posid [n] -storeid [m]\n\t n and m are integers \n",
			argv[0]);
	exit(1);
    }

    if ( !(strcmp (argv[1], "-posid")))
    {
	posid = argv[2];
    }
    else if ( ! (strcmp (argv[1],"-storeid")))
    {
	storeid = argv[2];
    }
    else
    {
	printf("incorrect input parameter: %s\n", argv[1]);
	exit(1);
    }
       
    if ( !(strcmp(argv[3],"-posid")))
    {
	posid = argv[4];
    }
    else if ( !(strcmp(argv[3],"-storeid")))
    {
	storeid = argv[4];
    }
    else
    {
	printf("incorrect input parameter: %s\n", argv[3]);
	exit(1);
    }

    /** create the inputmedia object **/

    inputmedia = POS_InputMediaNew();

    /**  do not process any transactions until the user logs on **/
    printf("Please log in:  ");
    fflush (stdout);
	

    /**	fall into a loop, reading from the keyboard and calling **/
    /** barcode_input or keypad_input as appropriate on the     **/
    /** InputMedia object until the user shuts down the system  **/
    /** by entering X                                           **/

    while (1)
    {    
	scanf("%s",instring);
        if (!loggedin && instring[0] != 'l' && instring[0] != 'L') {
           printf("Please log in first (l/L):  ");
	   fflush (stdout);
           continue;
        }
	else 
	   loggedin = 1;
	
	if (isdigit(instring[0])) 
	    POS_InputMedia_BarcodeInput(inputmedia,&ev,instring);

	else if ((toupper(instring[0]) == 'X'))
	{
	    SOMD_Uninit(&ev);
	    SOM_UninitEnvironment(&ev);
	    application_terminate ("exit selected", &ev);
	}
	else  if ((toupper (instring[0]) == 'H'))
	 	print_help();
	else
	    POS_InputMedia_KeypadInput(inputmedia,&ev,instring);
        if (ev._major != CORBA_NO_EXCEPTION)
	       handle_exception (&ev);
        CORBA_exception_free (&ev);
        printf ("Enter Barcode or command (h for help) \n [Ready]   ");
	fflush (stdout);

    }
}

void print_help()
{
	 printf ("Valid commands are \n"
		 " \t1. barcode \n"
	         " \t2. p|P -- for print POS Sales summary\n"
	         " \t3. s|S -- for print store Sales summary\n"
		 " \t4. t|T -- for end of sale (Terminate)\n"
	         " \t5. q|Q -- item quantity (preceeding barcode input)\n"
	         " \t6. x|X -- exit application \n\n");



}
