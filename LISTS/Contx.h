//=============================================================
// Container Exceptions     contx.h         v1.00
//      Defines an exception type for lists, etc.
//      Copyright 1995 Scott Robert Ladd
//=============================================================

#ifndef CONTX_H
#define CONTX_H

#include "diagnose.h"

enum ContainerError
    {
    CX_ALLOC,
    CX_NULL,
    CX_ARRAYALLOC,
    CX_NULLARRAY,
    CX_NOTREADY,
    CX_OVERFLOW
    };

class ContainerEx : public ExceptionBase
    {
    public:
        ContainerEx
            (
            ContainerError err
            )
            {
            Error = err;
            }

        ContainerError WhatsWrong()
            {
            return Error;
            }

        virtual void Explain
            (
            DiagOutput & diag
            );

    private:
        ContainerError Error;
    };

#endif
