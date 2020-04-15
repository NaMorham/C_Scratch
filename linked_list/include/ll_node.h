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


struct LLNode_t
{
	unsigned long id;
	char name[LL_NODE_TINY_BUF_SZ+1];

	struct LLNode_t* pNext;
};

extern struct LLNode_t* init_ll_node(struct LLNode_t* pNode, char *name);

extern void dump_node(struct LLNode_t* pNode);

#endif. // __ANH_GS__LL_NODE_H__
