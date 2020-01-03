==========================================================================

README  FEBRUARY 12, 1996  By Jon Siegel

This diskette contains complete code for the POS example in the 
book "CORBA Fundamentals and Programming" for the eight ORBs 
described in the book, plus generic code for C and C++ ORB
development environments.  The Smalltalk code is generic already, 
so we didn't repeat the smalltalk files on the diskette. 

We've described the contents of the diskette right after the 
following copyright notice:

==========================================================================

Copyright (C) 1996 by the Object Management Group, Inc.  All  
rights reserved.  

Permission to use, copy, modify, and distribute this software for
any  teaching or instructional purpose and without fee is hereby
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

==========================================================================

This diskette contains a separate directory for each ORB,
directories containing generic C and C++ code, a directory with
the standard IDL files, and a TARFILES directory.  Code is
repeated in the ORB and TARFILES directories.  You may use one or
the other, depending on what type of machine you're running on,
and what you plan to do with the code.

If you're using a PC or compatable exclusively, use the directory
with the name of your ORB.  You will be able to run the example 
from this directory if you have an ORB which runs on the Windows
or NT operating systems.  And, you will be able to view all of
the files right off the diskette, even for ORBs which provide
only a UNIX implementation. But, filenames will be in all capital
letters, 8.3 format, and will not exactly match the longer,
mixed-case filenames in the book.  Most directories include
either instructions or a script file to restore the correct
filenames.

On the other hand, if you're running on a UNIX machine, you
should copy your ORB vendor's file from the TARFILES directory.
You will need to uncompress and un-tar the file.  Doing this 
will exactly re-create the directory and file structure which
the developers used.  Follow the Make procedures in the book 
or README file to reproduce the working executables.

Each directory or tarfile includes a README file with 
instructions for getting started.

All of this code is also available on the Web, and will be 
updated as ORB versions change.  For links, start at the OMG 
home page,

  http://www.omg.org

There, you will also find links to other ORB vendors' 
implementations.  

All of us have put a lot of effort into this example, and we 
know you'll get a lot out of it.  Enjoy!

  -- The Authors

     Jon Siegel, Ph.D., Object Management Group,
     Dan Frantz, Ph.D., Digital Equipment Corporation;
     Hal Mirsky, Expersoft Corporation;
     Raghu Hudli, Ph.D., IBM Corporation;
     Peter deJong, Ph.D., Alan Klein, and Brent Wilkins, Hewlett-Packard, Inc.;
     Alex Thomas and Wilf Coles, ICL; 
     Sean Baker, Ph.D., Iona Corporation;
     Maurice Balick, SunSoft, Inc.


=======================================================================
Jon Siegel                              Phone:     508-820-4300
Director, Domain Technology             Fax:       508-820-4303
Object Management Group        
492 Old Connecticut Path                email:     siegel@omg.org
Framingham, Massachusetts 01701 USA     http://www.omg.org
========================================================================
