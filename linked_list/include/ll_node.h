/****************************************************************************
 *                                                                          *
 ****************************************************************************/

#ifndef __ANH_GS__LL_NODE_H__
#define __ANH_GS__LL_NODE_H__

#ifndef LL_NODE_TINY_BUF_SZ
#define LL_NODE_TINY_BUF_SZ 64
#endif // LL_NODE_TINY_BUF_SZ

#ifndef LL_NODE_SMALL_BUF_SZ
#define LL_NODE_SMALL_BUF_SZ ( (LL_NODE_TINY_BUF_SZ) * 4 )
#endif // LL_NODE_SMALL_BUF_SZ

#ifndef LL_NODE_LARGE_BUF_SZ
#define LL_NODE_LARGE_BUF_SZ ( (LL_NODE_SMALL_BUF_SZ) * 4 )
#endif // LL_NODE_LARGE_BUF_SZ

#ifndef LL_NODE_HUGE_BUF_SZ
#define LL_NODE_HUGE_BUF_SZ ( (LL_NODE_HUGE_BUF_SZ) * 4 )
#endif // LL_NODE_HUGE_BUF_SZ


typedef struct LLNode_t
{
    unsigned long id;
    char name[LL_NODE_TINY_BUF_SZ+1];

    struct LLNode_t* pNext;
} LLNode;

#ifdef LL_ALLOW_TEST 
extern LLNode* init_ll_node(LLNode* pNode, const char *name);  // this should not be called directly normally
#endif // LL_ALLOW_TEST

extern LLNode* ll_node_alloc(const char *name);

extern void ll_node_free(LLNode** ppNode);

extern LLNode* ll_node_copy(const LLNode* pNode);

extern void dump_node(const LLNode* pNode);

#endif  // __ANH_GS__LL_NODE_H__
