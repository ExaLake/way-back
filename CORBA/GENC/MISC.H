/*
 *****************************************************************************
 * 
 * File Name   : misc.h
 * 
 * Date        : 23nov95
 * 
 * Author      : Wilf Coles, ICL
 * 
 * Role        : definitions for miscellaneous functions for generic C ORB
 * 
 * Copyright (C) 1996 by the Object Management Group, Inc.  All  
 * rights reserved.  
 * 
 * Permission to use, copy, modify, and distribute this software for
 * any  teaching or instructional purpose and without fee is hereby
 * granted, provided that the above copyright notice appear in all
 * copies and that both that copyright notice and this permission
 * notice appear in supporting documentation, and that the names of
 * Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
 * (Wiley) not be used in advertising or publicity pertaining to
 * distribution of the software without specific, written prior
 * permission.
 * 
 * THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
 * EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
 * WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
 * assume any liability of any alleged or actual damages arising
 * from the use of or the inability to use this software.  (Some
 * states do not allow the exclusion of implied warranties, so the
 * exclusion may not apply to you.)
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
