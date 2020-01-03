//=============================================================
//  Binary Tree Classes     bintree.h   v3.00
//      Template for standard binary tree types
//      Copyright 1993-1995 Scott Robert Ladd
//=============================================================

#ifndef BINTREE_H
#define BINTREE_H

#include "stddef.h"
#include "limits.h"
#include "treex.h"

//-------------------------------------------------------------
//  TreeNode
//      A node in a binary tree
//-------------------------------------------------------------

template <class D>
    struct TreeNode
        {
        // links
        TreeNode<D> * Less;
        TreeNode<D> * More;
        TreeNode<D> * Parent;

        // contents
        D Data;

        // constructor
        TreeNode
            (
            const D & item,
            TreeNode<D> * sentinel
            );

        TreeNode(); // creates a sentinel node

        // copy constructor
        TreeNode
            (
            const TreeNode<D> & node
            );

        // assignment operator
        void operator =
            (
            const TreeNode<D> & node
            );
        };

template <class D>
    TreeNode<D>::TreeNode
        (
        const D & item,
        TreeNode<D> * sentinel
        )
        : Data(item)
        {
        Parent = sentinel;
        Less   = sentinel;
        More   = sentinel;
        }

// create sentinel node
template <class D>
    TreeNode<D>::TreeNode()
        : Data()
        {
        Parent = this;
        Less   = this;
        More   = this;
        }

template <class D>
    TreeNode<D>::TreeNode
        (
        const TreeNode<D> & node
        )
        : Data(node.Data)
        {
        Parent = node.Parent;
        Less   = node.Less;
        More   = node.More;
        }

template <class D>
    void TreeNode<D>::operator =
        (
        const TreeNode<D> & node
        )
        {
        Parent = node.Parent;
        Less   = node.Less;
        More   = node.More;
        Data   = node.Data;
        }

//-------------------------------------------------------------
//  BinaryTree
//      A basic binary tree
//-------------------------------------------------------------

template <class D>
    class BinaryTree
        {
        friend
            class BinaryTreeIterator<D>;

        public:
            // constructor
            BinaryTree();

            BinaryTree
                (
                const BinaryTree<D> & tree
                );

            // destructor
            ~BinaryTree();

            // assignment opeartor
            void operator =
                (
                const BinaryTree<D> & tree
                );

            // store an item
            void Insert
                (
                const D & item
                );

            // delete an item
            Boolean Delete
                (
                const D & item
                );

            // walk entire tree, calling function for nodes
            void Walk
                (
                void (* func)(const D & item)
                );

            // erase all elements in the tree
            void Erase();

            // examine lock count
            unsigned int  GetLockCount();

            // retrieve pointer to sentinel
            const TreeNode<D> * GetSentinel();

        protected:
            TreeNode<D> * Root;     // root node
            TreeNode<D> * Sentinel; // sentinel node

            unsigned int LockCount; // number of iterator locks
            unsigned int Count;

            // function called during traverse
            void (*WalkFunc)(const D & item);

            // function to create and delete nodes
            TreeNode<D> * CreateNode
                (
                const D & item
                );

            void DeleteNode
                (
                TreeNode<D> * node
                );

            // internal insert function
            TreeNode<D> * InternalInsert
                (
                const D & item
                );

            // recursive copy function
            void RecursiveCopy
                (
                TreeNode<D> * node,
                TreeNode<D> * sent
                );

            // recursive traversal function
            void RecurseWalk
                (
                TreeNode<D> * node
                );

            // recursive deletion function
            void RecursiveDelete
                (
                TreeNode<D> * node
                );

            // find minimum node
            TreeNode<D> * Minimum
                (
                TreeNode<D> * node
                );

            // find maximum node
            TreeNode<D> * Maximum
                (
                TreeNode<D> * node
                );

            // find successor node
            TreeNode<D> * Successor
                (
                TreeNode<D> * node
                );

            // find predecessor node
            TreeNode<D> * Predecessor
                (
                TreeNode<D> * node
                );

            // find node containing specific item
            TreeNode<D> * Search
                (
                const D & item
                );
        };

// constructors
template <class D>
    BinaryTree<D>::BinaryTree()
        {
        Sentinel  = new TreeNode<D>;

        if (Sentinel == NULL)
            throw TreeEx(BTX_ALLOC);

        Root      = Sentinel;
        LockCount = 0;
        }

template <class D>
    BinaryTree<D>::BinaryTree
        (
        const BinaryTree<D> & tree
        )
        {
        Sentinel = new TreeNode<D>;

        if (Sentinel == NULL)
            throw TreeEx(BTX_ALLOC);

        Root      = Sentinel;
        LockCount = 0;
        RecursiveCopy(tree.Root, tree.Sentinel);
        }

template <class D>
    BinaryTree<D>::~BinaryTree()
        {
        if (LockCount > 0)
            throw TreeEx(BTX_LOCKVIOLATION);

        RecursiveDelete(Root);

        delete Sentinel;
        }

template <class D>
    void BinaryTree<D>::operator =
        (
        const BinaryTree<D> & tree
        )
        {
        if (LockCount > 0)
            throw TreeEx(BTX_LOCKVIOLATION);

        RecursiveDelete(Root);
        Root = Sentinel;
        RecursiveCopy(tree.Root, tree.Sentinel);
        }

// function to create node
template <class D>
    TreeNode<D> * BinaryTree<D>::CreateNode
        (
        const D & item
        )
        {
        TreeNode<D> * z = new TreeNode<D>(item, Sentinel);

        if (z == NULL)
            throw TreeEx(BTX_ALLOC);

        return z;
        }

template <class D>
    void BinaryTree<D>::DeleteNode
        (
        TreeNode<D> * node
        )
        {
        delete node;
        }

// internal insert function
template <class D>
    TreeNode<D> * BinaryTree<D>::InternalInsert
        (
        const D & item
        )
        {
        if (LockCount > 0)
            throw TreeEx(BTX_LOCKVIOLATION);

        TreeNode<D> * y = Sentinel;
        TreeNode<D> * x = Root;

        while (x != Sentinel)
            {
            y = x;

            if (item == x->Data)
                {
                x->Data = item;
                return NULL;
                }
            else
                {
                if (item < x->Data)
                    x = x->Less;
                else
                    x = x->More;
                }
            }

        TreeNode<D> * z = CreateNode(item);
        z->Parent = y;

        if (y == Sentinel)
            Root = z;
        else
            {
            if (z->Data < y->Data)
                y->Less = z;
            else
                y->More = z;
            }

        return z;
        }

// find minimum node
template <class D>
    TreeNode<D> * BinaryTree<D>::Minimum
        (
        TreeNode<D> * node
        )
        {
        if (node != Sentinel)
            while (node->Less != Sentinel)
                node = node->Less;

        return node;
        }

// find maximum node
template <class D>
    TreeNode<D> * BinaryTree<D>::Maximum
        (
        TreeNode<D> * node
        )
        {
        if (node != Sentinel)
            while (node->More != Sentinel)
                node = node->More;

        return node;
        }

// find successor node
template <class D>
    TreeNode<D> * BinaryTree<D>::Successor
        (
        TreeNode<D> * node
        )
        {
        TreeNode<D> * x, * y;

        if (node->More != Sentinel)
            return Minimum(node->More);
        else
            {
            x = node;
            y = node->Parent;

            while ((y != Sentinel) && (x == y->More))
                {
                x = y;
                y = y->Parent;
                }
            }

        return y;
        }

// find predecessor node
template <class D>
    TreeNode<D> * BinaryTree<D>::Predecessor
        (
        TreeNode<D> * node
        )
        {
        TreeNode<D> * x, * y;

        if (node->Less != Sentinel)
            return Maximum(node->Less);
        else
            {
            x = node;
            y = node->Parent;

            while ((y != Sentinel) && (x == y->Less))
                {
                x = y;
                y = y->Parent;
                }
            }

        return y;
        }

// find node containing specific item
template <class D>
    TreeNode<D> * BinaryTree<D>::Search
        (
        const D & item
        )
        {
        TreeNode<D> * n = Root;

        while ((n != Sentinel) && (n->Data != item))
            {
            if (item < n->Data)
                n = n->Less;
            else
                n = n->More;
            }

        return n;
        }

template <class D>
    void BinaryTree<D>::Insert
        (
        const D & item
        )
        {
        InternalInsert(item);
        }

template <class D>
    Boolean BinaryTree<D>::Delete
        (
        const D & item
        )
        {
        if (LockCount > 0)
            throw TreeEx(BTX_LOCKVIOLATION);

        // find node
        TreeNode<D> * z = Search(item);

        if (z == Sentinel)
            return BOOL_FALSE;

        TreeNode<D> * y, * x;

        // find node to splice out
        if ((z->Less == Sentinel) || (z->More == Sentinel))
            y = z;
        else
            y = Successor(z);

        // find child with which to replace y
        if (y->Less != Sentinel)
            x = y->Less;
        else
            x = y->More;

        // splice child onto parent
        if (x != Sentinel)
            x->Parent = y->Parent;

        if (y->Parent == Sentinel)
            Root = x; // replace root
        else
            {
            // splice in child node
            if (y == y->Parent->Less)
                y->Parent->Less = x;
            else
                y->Parent->More = x;
            }

        // if needed, save y data
        if (y != z)
            z->Data = y->Data;

        // free memory
        DeleteNode(y);

        return BOOL_TRUE;
        }

template <class D>
    void BinaryTree<D>::Walk
        (
        void (* func)(const D & item)
        )
        {
        WalkFunc = func;
        RecurseWalk(Root);
        }

template <class D>
    void BinaryTree<D>::Erase()
        {
        if (LockCount > 0)
            throw TreeEx(BTX_LOCKVIOLATION);

        RecursiveDelete(Root);

        Root = Sentinel;
        }

template <class D>
    void BinaryTree<D>::RecursiveCopy
        (
        TreeNode<D> * node,
        TreeNode<D> * sent
        )
        {
        if (node != sent)
            {
            Insert(node->Data);
            RecursiveCopy(node->Less,sent);
            RecursiveCopy(node->More,sent);
            }
        }

template <class D>
    void BinaryTree<D>::RecurseWalk
        (
        TreeNode<D> * node
        )
        {
        if (node != Sentinel)
            {
            RecurseWalk(node->Less);
            WalkFunc(node->Data);
            RecurseWalk(node->More);
            }
        }

template <class D>
    void BinaryTree<D>::RecursiveDelete
        (
        TreeNode<D> * node
        )
        {
        if (node != Sentinel)
            {
            RecursiveDelete(node->Less);
            RecursiveDelete(node->More);
            DeleteNode(node);
            }
        }

// manipulate lock count
template <class D>
    inline size_t BinaryTree<D>::GetLockCount()
        {
        return LockCount;
        }

template <class D>
    inline const TreeNode<D> * BinaryTree<D>::GetSentinel()
        {
        return Sentinel;
        }

//---------------------------
// binary tree iterator class
//---------------------------

template <class D>
    class BinaryTreeIterator
        {
        public:
            BinaryTreeIterator
                (
                BinaryTree<D> & bt
                );

            BinaryTreeIterator
                (
                BinaryTreeIterator<D> & iter
                );

            ~BinaryTreeIterator();

            void operator =
                (
                BinaryTreeIterator<D> & iter
                );

            void Smallest();
            void Largest();

            void operator ++ ();
            void operator -- ();

            D operator * ();

        protected:
            BinaryTree<D> & Tree;
            TreeNode<D>   * Node;
        };

template <class D>
    BinaryTreeIterator<D>::BinaryTreeIterator
        (
        BinaryTree<D> & bt
        )
        : Tree(bt)
        {
        if (Tree.LockCount == UINT_MAX)
            throw TreeEx(BTX_LOCKMAX);

        ++Tree.LockCount;

        Smallest();
        }

template <class D>
    BinaryTreeIterator<D>::BinaryTreeIterator
        (
        BinaryTreeIterator<D> & iter
        )
        : Tree(iter.Tree)
        {
        if (Tree.LockCount == UINT_MAX)
            throw TreeEx(BTX_LOCKMAX);

        ++Tree.LockCount;

        Node = iter.Node;
        }

template <class D>
    BinaryTreeIterator<D>::~BinaryTreeIterator()
        {
        if (Tree.LockCount == 0)
            throw TreeEx(BTX_LOCKZERO);

        --Tree.LockCount;
        }

template <class D>
    void BinaryTreeIterator<D>::operator =
        (
        BinaryTreeIterator<D> & iter
        )
        {
        Tree = iter.Tree;

        if (Tree.LockCount == 0)
            throw TreeEx(BTX_LOCKZERO);

        --Tree.LockCount;

        if (Tree.LockCount == UINT_MAX)
            throw TreeEx(BTX_LOCKMAX);

        ++Tree.LockCount;

        Node = iter.Node;
        }

template <class D>
    void BinaryTreeIterator<D>::Smallest()
        {
        Node = Tree.Minimum(Tree.Root);
        }

template <class D>
    void BinaryTreeIterator<D>::Largest()
        {
        Node = Tree.Maximum(Tree.Root);
        }

template <class D>
    void BinaryTreeIterator<D>::operator ++ ()
        {
        Node = Tree.Successor(Node);
        }

template <class D>
    void BinaryTreeIterator<D>::operator -- ()
        {
        Node = Tree.Predecessor(Node);
        }

template <class D>
    D BinaryTreeIterator<D>::operator * ()
        {
        if (Node == Tree.GetSentinel())
            throw TreeEx(BTX_NOTFOUND);
        else
            return Node->Data;
        }

#endif
