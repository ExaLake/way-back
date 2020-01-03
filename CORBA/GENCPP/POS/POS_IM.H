/*

Copyright (C) 1996 by the Object Management Group, Inc.  All  
rights reserved.  

Permission to use, copy, modify, and distribute this software for
any teaching or instructional purpose and without fee is hereby
granted, provided that the above copyright notice appear in all
copies and that both that copyright notice and this permission
notice appear in supporting documentation, and that the names of
Object Management Group, Inc. (OMG) and John Wiley and Sons, Inc.
(Wiley) not be used in advertising or publicity pertaining to
distribution of the software without specific, written prior
permission.

THIS SOFTWARE IS SOLD AS IS WITHOUT WARRANTY OF ANY KIND, EITHER
EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE IMPLIED
WARRANTY OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE.  Neither OMG, Wiley, nor their dealers or distributors
assume any liability of any alleged or actual damages arising
from the use of or the inability to use this software.  (Some
states do not allow the exclusion of implied warranties, so the
exclusion may not apply to you.)

*/
#ifndef POS_IM_H
#define POS_IM_H

#include <### interface header file>

class InputMedia_i : <### ORB specific base class>
{
private:
	POS::POSTerminal_var m_POSTerminalRef;
public:
	InputMedia_i(POS::POSTerminal_ptr pTer);
	virtual void BarcodeInput (const char * Item);
	virtual void KeypadInput (const char *Cmd);
};

#endif
