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
struct LLNode_t* init_ll_node(struct LLNode_t* pNode, const char *name)
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

struct LLNode_t* ll_node_alloc(const char *name)
{
	return NULL;
}

void ll_node_free(struct LLNode_t** ppNode)
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

struct LLNode_t* ll_node_copy(const struct LLNode_t* pNode)
{
	return NULL;
}

void dump_node(const struct LLNode_t* pNode)
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
