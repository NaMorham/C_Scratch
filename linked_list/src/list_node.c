#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../include/list_node.h"

char *SLL_Node_AsStr(SLL_NODE_P pNode, char *buf, int bufSz)
{
    char buffer[65];
    memset(buffer, 0, 65 * sizeof(buffer));

    if (buf)
    {
        memset(buf, 0, bufSz*sizeof(char));
        sprintf(buf, "Node(0x%08x) [value = %s, next = 0x%08x]", pNode,
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
