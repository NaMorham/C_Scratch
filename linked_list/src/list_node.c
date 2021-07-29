#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <Utils.h>
#include "../include/list_node.h"

#ifndef LARGE_STR_BUF
# define LARGE_STR_BUF 1024
#endif

const char *SLL_Node_AsStr(SLL_NODE_P pNode, char *buf, int bufSz)
{
    char buffer[LARGE_STR_BUF+1];
    memset(buffer, 0, sizeof(char)*(LARGE_STR_BUF+1));

    if (buf)
    {
        memset(buf, 0, bufSz*sizeof(char));
        sprintf_s(buf, bufSz-1, "Node(0x%08x) [value = %s, next = 0x%08x]", pNode,
            (pNode ? myitoa(pNode->value, buffer, 10) : "NAN"),
            (pNode ? pNode->next : 0));
    }
    return buf;
}

SLL_Node* Create_SLL_Node(int val)
{
    SLL_Node* pNew = (SLL_Node*)malloc(sizeof(SLL_Node));
    if (pNew)
    {
        pNew->next = 0;
        pNew->value = val;
    }
    return pNew;
}

SLL_Node* Prepend_SLL_Node(int val, SLL_Node *pListHead)
{
    SLL_Node* pNew = (SLL_Node*)malloc(sizeof(SLL_Node));
    if (pNew)
    {
        pNew->next = pListHead;
        pNew->value = val;
    }
    return pNew;
}

SLL_Node* Append_SLL_Node(int val, SLL_Node *pListHead)
{
    SLL_Node* pNew = Create_SLL_Node(val);
    SLL_Node* pNode = pListHead;
    while (pNode)
    {
        pNode = pNode->next;
    }
    if (pNode)
    {
        pNode->next = pNew;
    }
    return pNew;
}
