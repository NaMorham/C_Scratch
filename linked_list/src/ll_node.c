#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include <Utils.h>
#include <ll_node.h>

#ifndef NULL
#define NULL (void*)0
#endif

unsigned long g_node_id_counter = 0;

const unsigned long __ll_node_get_global_id()
{
    return g_node_id_counter;
}

#ifndef LL_ALLOW_TEST
static
#endif  // LL_ALLOW_TEST
LLNode* init_ll_node(LLNode* pNode, const char *name)
{
    size_t name_len = 0;

    trace_log("Begin: init LL Node");

    if (pNode)
    {
        pNode->id = ++g_node_id_counter;
        debug_log("Set id: %ld", pNode->id);

        memset(pNode->name, '\0', sizeof(char)*(LL_NODE_TINY_BUF_SZ+1));
        if (name && (strlen(name) > 0))
        {
            name_len = strlen(name);
            strncpy(pNode->name, name, (name_len < LL_NODE_TINY_BUF_SZ ? name_len : LL_NODE_TINY_BUF_SZ));
            debug_log("Set name: %s", pNode->name);
        }
        else
        {
            /* sprintf is safe since max ulong is 18446744073709551615 == 20 characters
               as long as the buffer is larger than 20+12 charcaters */
            sprintf(pNode->name, "Unnamed_node_%lu", pNode->id);
            debug_log("Set default name: %s", pNode->name);
        }

        pNode->pNext = NULL;
    }

    trace_log("End: init LL Node");

    return pNode;
}

LLNode* ll_node_alloc(const char *name)
{
    trace_log("Allocate and initialise new LLNode");

    // allocation is initialisation
    LLNode *pNewNode = (LLNode *)malloc(sizeof(LLNode));
    if (pNewNode)
    {
        init_ll_node(pNewNode, name);
    }

    return pNewNode;
}

void ll_node_free(LLNode** ppNode)
{
    if (ppNode == NULL)
    {
        error_log("NULL pointer pointer passed to free");
    }
    else if (*ppNode == NULL)
    {
        error_log("NULL pointer passed to free");
    }
    else
    {
        trace_log("Free node pointer [%p]", *ppNode);
        free(*ppNode);
        *ppNode = NULL;
    }
}

LLNode* ll_node_copy(const LLNode* pNode)
{
    trace_log("Allocate, initialise and duplicate an existing LLNode");
    LLNode *pNewNode = NULL;
    if (pNode)
    {
        // we have something to copy
        pNewNode = ll_node_alloc(pNode->name);
    }
    else
    {
        error_log("NULL pointer pointer passed to copy");
    }
    return pNewNode;
}

void dump_node(const LLNode* pNode)
{
    if (pNode)
    {
        debug_log("NODE [%p]: { id: %lu, name.: \"%s\", pNext: %p }", pNode, pNode->id, pNode->name, pNode->pNext);
    }
    else
    {
        warn_log("Got NULL node pointer for dump operation");
    }
}
