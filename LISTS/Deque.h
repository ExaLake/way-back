//=============================================================
// Deques                deque.h         v1.00
//      Defines templates for classes of deques
//      Copyright 1995 Scott Robert Ladd
//=============================================================

#ifndef DEQUE_H
#define DEQUE_H

#include "simple.h"
#include "limits.h"
#include "contx.h"

//---------------------------
// Deque (Double-ended queue)
//---------------------------

template <class T>
    class DequeDynamic
        {
        public:
            DequeDynamic();

            DequeDynamic
                (
                const DequeDynamic<T> & deq
                );

            ~DequeDynamic();

            void operator =
                (
                const DequeDynamic<T> & deq
                );

            void PushTop
                (
                const T & item
                );

            void PushBtm
                (
                const T & item
                );

            T PopTop();
            T PopBtm();

            void Erase();

            size_t GetCount();

        protected:
            struct Node
                {
                T Data;
                Node * Prev;
                Node * Next;
                };

            Node * Head;
            Node * Tail;
            size_t Count;

            // utility functions
            void DeepCopy
                (
                const DequeDynamic<T> & deq
                );
        };

template <class T>
    void DequeDynamic<T>::DeepCopy
        (
        const DequeDynamic<T> & deq
        )
        {
        if (deq.Count == 0)
            {
            Head = NULL;
            Tail = NULL;
            Count = 0;
            return;
            }

        Node * n = deq.Head;

        do  {
            PushBtm(n->Data);
            n = n->Next;
            }
        while (n != NULL);
        }

template <class T>
    inline DequeDynamic<T>::DequeDynamic()
        {
        Count = 0;
        Head  = NULL;
        Tail  = NULL;
        }

template <class T>
    inline DequeDynamic<T>::DequeDynamic
        (
        const DequeDynamic<T> & deq
        )
        {
        Count = 0;
        DeepCopy(deq);
        }

template <class T>
    inline DequeDynamic<T>::~DequeDynamic()
        {
        Erase();
        }

template <class T>
    void DequeDynamic<T>::operator =
        (
        const DequeDynamic<T> & deq
        )
        {
        Erase();
        DeepCopy(deq);
        }

template <class T>
    void DequeDynamic<T>::PushTop(const T & item)
        {
        Node * newhead = new Node;

        if (newhead == NULL)
            throw ContainerEx(CX_ALLOC);

        newhead->Prev = NULL;
        newhead->Next = Head;
        newhead->Data = item;

        Head = newhead;

        ++Count;
        }

template <class T>
    void DequeDynamic<T>::PushBtm(const T & item)
        {
        Node * newtail = new Node;

        if (newtail == NULL)
            throw ContainerEx(CX_ALLOC);

        newtail->Prev = Tail;
        newtail->Next = NULL;
        newtail->Data = item;

        if (Tail != NULL)
            Tail->Next = newtail;
        else
            Head = newtail;

        Tail = newtail;

        ++Count;
        }

template <class T>
    T DequeDynamic<T>::PopTop()
        {
        if (Head == NULL)
            throw ContainerEx(CX_NULL);

        T result = Head->Data;

        Node * newhead = Head->Next;

        delete Head;

        Head = newhead;

        --Count;

        if (Head != NULL)
            Head->Prev = NULL;

        return result;
        }

template <class T>
    T DequeDynamic<T>::PopBtm()
        {
        if (Head == NULL)
            throw ContainerEx(CX_NULL);

        T result = Tail->Data;

        Node * newtail = Tail->Prev;

        delete Head;

        Tail = newtail;
        Tail->Next = NULL;

        --Count;

        return result;
        }

template <class T>
    void DequeDynamic<T>::Erase()
        {
        while (Count)
            PopTop();
        }

template <class T>
    inline size_t DequeDynamic<T>::GetCount()
        {
        return Count;
        }

//---------------------------
// Deque (Double-ended queue)
//---------------------------

template <class T, size_t Limit>
    class Deque
        {
        public:
            Deque();

            Deque
                (
                const Deque<T,Limit> & deq
                );

            ~Deque();

            void operator =
                (
                const Deque<T,Limit> & deq
                );

            void PushTop
                (
                const T & item
                );

            void PushBtm
                (
                const T & item
                );

            T PopTop();
            T PopBtm();

            void Erase();

            size_t GetCount();

        protected:
            T Data[Limit];
            size_t Head;
            size_t Tail;
            size_t Count;

            // utility functions
            void DeepCopy
                (
                const Deque<T,Limit> & deq
                );
        };

template <class T, size_t Limit>
    void Deque<T,Limit>::DeepCopy
        (
        const Deque<T,Limit> & deq
        )
        {
        Count = deq.Count;
        Head  = deq.Head;
        Tail  = deq.Tail;

        for (size_t n = 0; n < Limit; ++n)
            Data[n] = deq.Data[n];
        }

template <class T, size_t Limit>
    inline Deque<T,Limit>::Deque()
        {
        Count = 0;
        Head  = 0;
        Tail  = 0;
        }

template <class T, size_t Limit>
    inline Deque<T,Limit>::Deque
        (
        const Deque<T,Limit> & deq
        )
        {
        Count = 0;
        DeepCopy(deq);
        }

template <class T, size_t Limit>
    inline Deque<T,Limit>::~Deque()
        {
        Erase();
        }

template <class T, size_t Limit>
    void Deque<T,Limit>::operator =
        (
        const Deque<T,Limit> & deq
        )
        {
        Erase();
        DeepCopy(deq);
        }

template <class T, size_t Limit>
    void Deque<T,Limit>::PushTop(const T & item)
        {
        if (Count == Limit)
            throw ContainerEx(CX_OVERFLOW);

        if (Count == 0)
            {
            Tail = 0;
            Head = 0;
            Data[0] = item;
            }
        else
            {
            if (Head == 0)
                Head = Limit - 1;
            else
                --Head;

            Data[Head] = item;
            }

        ++Count;
        }

template <class T, size_t Limit>
    void Deque<T,Limit>::PushBtm(const T & item)
        {
        if (Count == Limit)
            throw ContainerEx(CX_OVERFLOW);

        if (Count == 0)
            {
            Tail = 0;
            Head = 0;
            Data[0] = item;
            }
        else
            {
            ++Tail;

            if (Tail == Limit)
                Tail = 0;

            Data[Tail] = item;
            }

        ++Count;
        }

template <class T, size_t Limit>
    T Deque<T,Limit>::PopTop()
        {
        if (Count == 0)
            throw ContainerEx(CX_NULL);

        T result = Data[Head];

        --Count;

        if (Count != 0)
            {
            ++Head;

            if (Head == Limit)
                Head = 0;
            }

        return result;
        }

template <class T, size_t Limit>
    T Deque<T,Limit>::PopBtm()
        {
        if (Count == 0)
            throw ContainerEx(CX_NULL);

        T result = Data[Tail];

        --Count;

        if (Count != 0)
            {
            if (Tail == 0)
                Tail = Limit - 1;
            else
                --Tail;
            }

        return result;
        }

template <class T, size_t Limit>
    inline void Deque<T,Limit>::Erase()
        {
        Count = 0;
        }

template <class T, size_t Limit>
    inline size_t Deque<T,Limit>::GetCount()
        {
        return Count;
        }

#endif