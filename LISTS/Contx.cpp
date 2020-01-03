//=============================================================
// Container Exceptions     contx.h         v1.00
//      Defines an exception type for lists, etc.
//      Copyright 1995 Scott Robert Ladd
//=============================================================

#include "contx.h"

void ContainerEx::Explain
    (
    DiagOutput & diag
    )
    {
    switch (Error)
        {
        case CX_ALLOC:
            diag.DisplayMsg("List: Memory allocation failed",
                            DIAG_ERROR);
            break;
        case CX_NULL:
            diag.DisplayMsg("List: Attempt to use empty list",
                            DIAG_WARNING);
            break;
        case CX_ARRAYALLOC:
            diag.DisplayMsg("List: Failed to allocate array",
                            DIAG_WARNING);
            break;
        case CX_NULLARRAY:
            diag.DisplayMsg("List: Can't copy from NULL array",
                            DIAG_WARNING);
            break;
        case CX_NOTREADY:
            diag.DisplayMsg("List: Work pointer not initialized",
                            DIAG_WARNING);
            break;
        case CX_OVERFLOW:
            diag.DisplayMsg("List: Overflowed capacity",
                            DIAG_ERROR);
        }
    }

