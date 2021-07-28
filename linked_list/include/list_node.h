/*****************************************************************************
 *  Basic node struct for a linked list                                      *
 ****************************************************************************/

#ifndef __NaM_CScratch_LIST_NODE_H__
#define __NaM_CScratch_LIST_NODE_H__

#include <stdlib.h>

struct _SLL_NODE {
    int value;
    void* next;
};

typedef struct _SLL_NODE SLL_Node;
typedef struct _SLL_NODE* SLL_NODE_P;

extern const char *SLL_Node_AsStr(SLL_NODE_P pNode, char *buf, int bufSz);

extern SLL_Node* Create_SLL_Node(int val);

extern SLL_Node* Prepend_SLL_Node(int val, SLL_Node *pListHead);

extern SLL_Node* Append_SLL_Node(int val, SLL_Node *pListHead);

#endif // __NaM_CScratch_LIST_NODE_H__
