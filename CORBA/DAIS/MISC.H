/*
 *****************************************************************************
 * 
 * File Name   : misc.h
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles
 * 
 * Role        : definitions for miscellaneous functions
 * 
 * DISCLAIMER: This code is intended to serve solely as a programming
 * example.  Although it emulates a point-of-sale system, it certainly is
 * not suitable for use in such a system as presented here, and it is far
 * from certain that even an extended version of this code would be
 * suitable.  Although this code compiled and ran without error on its
 * target ORB system(s) at the time it was developed, upgrades and
 * version changes may require changes.
 * 
 * COPYRIGHT 1995 by International Computers Limited
 * All rights reserved.  The copyright holders grant to the owner of the
 * book "CORBA Principles and Programming" the right to copy the code onto
 * computing hardware, manipulating and editing it as necessary, to work
 * the tutorial exercise and verify CORBA functionality for their personal
 * education.  
 * 
 *****************************************************************************
 */
#if !defined(MISC_H)
#define MISC_H

typedef void *ObjectStatePtr;

extern ObjectStatePtr 
get_state_ptr(CORBA_BOA boa,
			  CORBA_Environment *ev,
			  CORBA_Object obj);

extern void
compose_refdata(CORBA_ReferenceData *id, ObjectStatePtr ostate);

extern ObjectStatePtr
decompose_refdata(CORBA_ReferenceData *id);

extern void
ref_to_file(CORBA_Object, CORBA_Environment *ev, char *filename);

extern PseudoNameService
NameService(CORBA_Environment *ev);

extern void
application_terminate(char *message, CORBA_Environment *ev);

#endif /* MISC_H */
