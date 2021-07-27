/**
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include <lltest_version.h>
<<<<<<< Updated upstream
#include <Utils.h>
#include <ll_node.h>

/* Util test groups */
const int test_min();
const int test_max();
const int test_limit();

/* Node tests */
const BOOL test_Node();

/* Test runners */
const int test_Utils();
const int test_Linked();
=======
#include <list_node.h>

int test_min();
int test_max();
int test_limit();
int test_itoa();

>>>>>>> Stashed changes
void showColours();
int test_Utils();
int test_SingleLinkedList();

#define LARGE_STR_BUF 256
#ifndef NULL
# define NULL ((void*)0)
#endif

<<<<<<< Updated upstream
static int g_num_tests = 4;

static const char *g_log_separator = "-----------------------------------------------------------------------------";
=======
int g_num_tests = 6;
>>>>>>> Stashed changes

/* ------------------------------------------------------------------------- */
const int main(const int argc, const char ** argv)
{
    g_log_level = LOG_TRACE;//DEBUG;

    info_log("Run %d tests: version %d.%d.%d.%d", g_num_tests, _VER_MAJOR, _VER_MINOR, _VER_PATCH, _VER_BUILD);

#ifdef USE_COLOUR
    info_log("Show colours");
    showColours();
    info_log("%s\n", g_log_separator);
#endif

    int num_passed = 0;

<<<<<<< Updated upstream
    info_log("> Util tests");
    num_passed += test_Utils();
    info_log("%s\n", g_log_separator);

    info_log("> Linked List tests");
    num_passed += test_Node();
    info_log("%s\n", g_log_separator);
=======
    num_passed += test_Utils();
    num_passed += test_SingleLinkedList();
    num_passed += test_itoa();
>>>>>>> Stashed changes

    info_log("%d/%d tests passed", num_passed, g_num_tests);
    info_log("----------------------------------------------------------------------------");

    return (num_passed == g_num_tests);
}


/* ------------------------------------------------------------------------- */
/*
 */
void showColours()
{
    info_log("----------------------------------------------------------------------------");
#ifdef USE_COLOUR
    info_log("Begin Show all normal colours");

    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s XXXX %s %s XXXX %s", "Black", C_BLK, C_BBLK, C_NRM, CB_BLK, C_NRM, CB_BBLK, C_NRM);
    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s XXXX %s %s XXXX %s", "Red", C_RED, C_BRED, C_NRM, CB_RED, C_NRM, CB_BRED, C_NRM);
    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s XXXX %s %s%s XXXX %s", "Green", C_GRN, C_BGRN, C_NRM, CB_GRN, C_NRM, C_BLK, CB_BGRN, C_NRM);
    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s XXXX %s %s%s XXXX %s", "Yellow", C_YEL, C_BYEL, C_NRM, CB_YEL, C_NRM, C_BLK, CB_BYEL, C_NRM);
    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s XXXX %s %s XXXX %s", "Blue", C_BLU, C_BBLU, C_NRM, CB_BLU, C_NRM, CB_BBLU, C_NRM);
    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s XXXX %s %s XXXX %s", "Magenta", C_MAG, C_BMAG, C_NRM, CB_MAG, C_NRM, CB_BMAG, C_NRM);
    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s XXXX %s %s%s XXXX %s", "Cyan", C_CYN, C_BCYN, C_NRM, CB_CYN, C_NRM, C_BLK, CB_BCYN, C_NRM);
    debug_log("Colour: %-8.8s: %sXXXX %sXXXX%s %s%s XXXX %s %s%s XXXX %s", "White", C_WHT, C_BWHT, C_NRM, C_BLK, CB_WHT, C_NRM, C_BLK, CB_BWHT, C_NRM);

    debug_log("----");

    debug_log("Decoration: \"Bold\"      %sxxxx XXXX iiii IIII%s", C_BLD, C_NRM);
    debug_log("Decoration: \"Italic\"    %sxxxx XXXX iiii IIII%s", C_ITL, C_NRM);
    debug_log("Decoration: \"Underline\" %sxxxx%s%s %sXXXX%s%s %siiii%s%s %sIIII%s", C_UND, C_NRM, LC_DBG, C_UND, C_NRM, LC_DBG, C_UND, C_NRM, LC_DBG, C_UND, C_NRM);

    info_log("End Show all normal colours");

#else
    info_log("Skip colour test when USE_COLOUR is not defined")

#endif
}

/* ------------------------------------------------------------------------- */
<<<<<<< Updated upstream
const int test_Utils()
=======
/*
 */
int test_Utils()
>>>>>>> Stashed changes
{
    /* Run tests on the Utils include/files */
    trace_log("============================================================================");
    trace_log("Begin Utils tests");

    int result = 0;

    result += test_min();
    result += test_max();
    result += test_limit();

    trace_log("End Utils tests");

    return result;
}

/* ------------------------------------------------------------------------- */
<<<<<<< Updated upstream
const int test_MinVal_Int(const int a, const int b, const char *name, const int expected)
=======
/*
 */
int test_MinVal_Int(int a, int b, char *name, int expected)
>>>>>>> Stashed changes
{
    int result = MinVal(a, b);

    if (result == expected)
    {
        debug_log("TEST: %-64.64s: %sPASS%s", name, C_BGRN, C_NRM);
        return TRUE;
    }
    else
    {
        debug_log("TEST: %-64.64s: %sFAIL%s : MinVal(%d, %d) -> expected %d, got %d", name, C_BRED, LC_DBG, a, b, expected, result);
        return FALSE;
    }
}

<<<<<<< Updated upstream
const int test_min()
=======
/*
 */
int test_min()
>>>>>>> Stashed changes
{
    int pass = TRUE;

    trace_log("----------------------------------------------------------------------------");
    trace_log("Begin Utils::MinVal tests");

    /* Test the MinVal macro */
    pass &= test_MinVal_Int(0, 0, "0, 0 min test", 0);
    pass &= test_MinVal_Int(0, 1, "0, 1 min test", 0);
    pass &= test_MinVal_Int(1, 0, "1, 0 min test", 0);

    pass &= test_MinVal_Int(-1, 1, "-1, 1 min test", -1);
    pass &= test_MinVal_Int(1, -1, "1, -1 min test", -1);

    pass &= test_MinVal_Int(1, 42, "1, 42 min test", 1);
    pass &= test_MinVal_Int(42, 1, "42, 1 min test", 1);

    pass &= test_MinVal_Int(-1, -42, "-1, -42 min test", -42);
    pass &= test_MinVal_Int(-42, -1, "-42, -1 min test", -42);

    pass &= test_MinVal_Int(0, INT_MAX, "0, INT_MAX min test", 0);
    pass &= test_MinVal_Int(0, INT_MIN, "0, INT_MIN min test", INT_MIN);
    pass &= test_MinVal_Int(INT_MAX, INT_MIN, "INT_MIN, INT_MAX min test", INT_MIN);

    pass &= test_MinVal_Int(3765, 3765, "Same positive value min test", 3765);
    pass &= test_MinVal_Int(-3765, -3765, "Same negative value min test", -3765);

    trace_log("End Utils::MinVal tests");

    return pass;
}

/* ------------------------------------------------------------------------- */
<<<<<<< Updated upstream
const int test_MaxVal_Int(const int a, const int b, const char *name, const int expected)
=======
/*
 */
int test_MaxVal_Int(int a, int b, char *name, int expected)
>>>>>>> Stashed changes
{
    int result = MaxVal(a, b);

    if (result == expected)
    {
        debug_log("TEST: %-64.64s: %sPASS%s", name, C_BGRN, C_NRM);
        return TRUE;
    }
    else
    {
        debug_log("TEST: %-64.64s: %sFAIL%s : MaxVal(%d, %d) -> expected %d, got %d", name, C_BRED, LC_DBG, a, b, expected, result);
        return FALSE;
    }
}

<<<<<<< Updated upstream
const int test_max()
=======
/*
 */
int test_max()
>>>>>>> Stashed changes
{
    int pass = TRUE;

    trace_log("----------------------------------------------------------------------------");
    trace_log("Begin Utils::MaxVal tests");

    /* Test the MaxVal macro */
    pass &= test_MaxVal_Int (0, 0, "0, 0 max test", 0);
    pass &= test_MaxVal_Int (0, 1, "0, 1 max test", 1);
    pass &= test_MaxVal_Int (1, 0, "1, 0 max test", 1);

    pass &= test_MaxVal_Int (-1, 1, "-1, 1 max test", 1);
    pass &= test_MaxVal_Int (1, -1, "1, -1 max test", 1);

    pass &= test_MaxVal_Int (1, 42, "1, 42 max test", 42);
    pass &= test_MaxVal_Int (42, 1, "42, 1 max test", 42);

    pass &= test_MaxVal_Int (-1, -42, "-1, -42 max test", -1);
    pass &= test_MaxVal_Int (-42, -1, "-42, -1 max test", -1);

    pass &= test_MaxVal_Int (0, INT_MAX, "0, INT_MAX max test", INT_MAX);
    pass &= test_MaxVal_Int (0, INT_MIN, "0, INT_MIN max test", 0);
    pass &= test_MaxVal_Int (INT_MAX, INT_MIN, "INT_MIN, INT_MAX max test", INT_MAX);

    pass &= test_MaxVal_Int (3765, 3765, "Same positive value max test", 3765);
    pass &= test_MaxVal_Int (-3765, -3765, "Same negative value max test", -3765);

    trace_log("End Utils::MaxVal tests");

    return pass;
}

/* ------------------------------------------------------------------------- */
<<<<<<< Updated upstream
const int test_LimitVal_Int(const int mn, const int mx, const int val, const char *name, const int expected)
=======
/*
 */
int test_LimitVal_Int(int mn, int mx, int val, char *name, int expected)
>>>>>>> Stashed changes
{
    int result = LimitVal(mn, mx, val);

    if (result == expected)
    {
        debug_log("TEST: %-64.64s: %sPASS%s", name, C_BGRN, C_NRM);
        return TRUE;
    }
    else
    {
        warn_log("TEST: %-64.64s: %sFAIL%s", name, C_BRED, C_NRM);
        warn_log("> LimitVal(%d, %d, %d) -> expected %d, got %d", mn, mx, val, expected, result);
        return FALSE;
    }
}

<<<<<<< Updated upstream
const int test_limit()
=======
/*
 */
int test_limit()
>>>>>>> Stashed changes
{
    int pass = TRUE;

    trace_log("----------------------------------------------------------------------------");
    trace_log("Begin Utils::LimitVal tests");

    /* Test the LimitVal macro */
    trace_log(">>> 0 value tests");
    pass &= test_LimitVal_Int(0, 0, 0, "Limit test: All 0", 0);

    /* In range tests */
    trace_log(">>> Small in range tests");
    pass &= test_LimitVal_Int(0, 1, 0, "Limit test: 0 to 1, 0", 0);
    pass &= test_LimitVal_Int(0, 1, 1, "Limit test: 0 to 1, 1", 1);

    /* handle bad max min vals as well (Max < min) */
    pass &= test_LimitVal_Int(1, 0, 0, "Limit test: 1 to 0, 0", 0);
    pass &= test_LimitVal_Int(1, 0, 1, "Limit test: 1 to 0, 1", 1);

    pass &= test_LimitVal_Int(-1, 0, 0, "Limit test: 1 to 0, 0", 0);
    pass &= test_LimitVal_Int(-1, 0, -1, "Limit test: 1 to 0, 1", -1);

    pass &= test_LimitVal_Int(0, -1, 0, "Limit test: 0 to -1, 0", 0);
    pass &= test_LimitVal_Int(0, -1, -1, "Limit test: 0 to -1, -1", -1);

    pass &= test_LimitVal_Int(-1, 1, 0, "Limit test: -1 to 1, 0", 0);
    pass &= test_LimitVal_Int(1, -1, 0, "Limit test: 1 to -1, 0", 0);

    pass &= test_LimitVal_Int(-1, 1, -1, "Limit test: -1 to 1, -1", -1);
    pass &= test_LimitVal_Int(1, -1, -1, "Limit test: 1 to -1, -1", -1);

    pass &= test_LimitVal_Int(-1, 1, 1, "Limit test: -1 to 1, 1", 1);
    pass &= test_LimitVal_Int(1, -1, 1, "Limit test: 1 to -1, 1", 1);

    pass &= test_LimitVal_Int(10, 20, 15, "Limit test: 10 to 20, 15 (in range)", 15);
    pass &= test_LimitVal_Int(20, 10, 15, "Limit test: 20 to 10, 15 (in range, bad order)", 15);

    trace_log(">>> Small out of range tests");
    pass &= test_LimitVal_Int(0, 1, 2, "Limit test: 0 to 1, value = 2 (above range)", 1);
    pass &= test_LimitVal_Int(0, 1, -1, "Limit test: 0 to 1, value = -1 (below range)", 0);

    pass &= test_LimitVal_Int(1, 0, 2, "Limit test: 1 to 0, value = 2 (above range, bad order)", 1);
    pass &= test_LimitVal_Int(1, 0, -1, "Limit test: 1 to 0, value = -1 (below range, bad order)", 0);

    pass &= test_LimitVal_Int(-1, 0, 1, "Limit test: 1 to 0, value = 1 (above -ve range)", 0);
    pass &= test_LimitVal_Int(-1, 0, -2, "Limit test: 1 to 0, value = -2 (below -ve range)", -1);

    pass &= test_LimitVal_Int(10, 20, 25, "Limit test: 10 to 20, value = 25 (above range)", 20);
    pass &= test_LimitVal_Int(10, 20, 5, "Limit test: 10 to 20, value = 5 (below range)", 10);

    pass &= test_LimitVal_Int(-20, -10, -5, "Limit test: -20 to -10, value = -5 (above range)", -10);
    pass &= test_LimitVal_Int(-20, -10, -25, "Limit test: -20 to -10, value = -25 (below range)", -20);

    pass &= test_LimitVal_Int(-1230, 1230, 2345, "Limit test: -1230 to 1230, value = 2345 (above range)", 1230);
    pass &= test_LimitVal_Int(-1230, 1230, -2345, "Limit test: -1230 to 1230, value = -2345 (below range)", -1230);

    pass &= test_LimitVal_Int(10, 20, -5, "Limit test: 10 to 20, value = -5 (-ve value below +ve range)", 10);
    pass &= test_LimitVal_Int(-20, -10, 5, "Limit test: -20 to -10, value = 5 (+ve value above -ve range)", -10);

    trace_log("End Utils::LimitVal tests");

    return pass;
}

/* ------------------------------------------------------------------------- */
<<<<<<< Updated upstream
extern const unsigned long __ll_node_get_global_id();

/* test with defined name */
const BOOL _test_Node1()
{
    trace_log(">> Begin:test node 1");

    BOOL pass = TRUE;

    unsigned long pre_id;
    LLNode dummyNode;

    const char *expected_name = "test name 1";

    LLNode *pDummyNode = NULL;

    pre_id = __ll_node_get_global_id();

    trace_log("> Linked::Node Static test 1: pre test id [%lu]", pre_id);

    pDummyNode = init_ll_node(&dummyNode, expected_name);

    /* dummy test node */
    if (pDummyNode)
    {
        dump_node(pDummyNode);
        pass = ((pDummyNode == &dummyNode) && (pDummyNode->id = (pre_id+1)) && (strcmp(pDummyNode->name, expected_name) == 0));

        if (pass)
        {
            debug_log("Dummy Node 1 test: %sPASS%s", C_BGRN, C_NRM);
            debug_log("> Node data: id [%lu], name [%s]", pDummyNode->id, pDummyNode->name);
        }
        else
        {
            warn_log("Dummy Node 1 test: %sFAIL%s", C_BRED, C_NRM);
            if (pDummyNode != &dummyNode)
            {
                warn_log("> Returned node pointer [%p] does not match source addresss [%p]", pDummyNode, &dummyNode);
            }
            if (pDummyNode->id != (pre_id+1))
            {
                warn_log("> Node global id [%lu] did not match expected value [%lu]", pDummyNode->id, (pre_id+1));
            }
            if (strcmp(pDummyNode->name, expected_name) != 0)
            {
                warn_log("> Node name [%s] did not match expected value [%s]", pDummyNode->name, expected_name);
            }
        }
    }
    else
    {
        error_log("GOt null pointer from static node init");
        pass = FALSE;
    }

    trace_log("<< End:test node 1");

    return pass;
}

/* test with empty name */
const BOOL _test_Node2()
{
    trace_log(">> Begin:test node 2");

    BOOL pass = TRUE;

    unsigned long pre_id;
    LLNode dummyNode;

    char expected_name[LL_NODE_TINY_BUF_SZ+1];

    pre_id = __ll_node_get_global_id();
    memset(expected_name, '\0', sizeof(char)*(LL_NODE_TINY_BUF_SZ+1));
    /* sprintf is safe since max ulong is 18446744073709551615 == 20 characters
       as long as the buffer is larger than 20+12 charcaters */
    sprintf(expected_name, "Unnamed_node_%lu", (pre_id+1));
    /*snprintf(expected_name, LL_NODE_TINY_BUF_SZ, 0, "Unnamed_node_%lu", (pre_id+1));*/

    LLNode *pDummyNode = NULL;

    trace_log("> Linked::Node Static test 2 (empty name): pre test id [%lu]", pre_id);

    pDummyNode = init_ll_node(&dummyNode, "");

    /* dummy test node */
    if (pDummyNode)
    {
        dump_node(pDummyNode);
        pass = ((pDummyNode == &dummyNode) && (pDummyNode->id = (pre_id+1)) && (strcmp(pDummyNode->name, expected_name) == 0));

        if (pass)
        {
            debug_log("Dummy Node 1 test: %sPASS%s", C_BGRN, C_NRM);
            debug_log("> Node data: id [%lu], name [%s]", pDummyNode->id, pDummyNode->name);
        }
        else
        {
            warn_log("Dummy Node 1 test: %sFAIL%s", C_BRED, C_NRM);
            if (pDummyNode != &dummyNode)
            {
                warn_log("> Returned node pointer [%p] does not match source addresss [%p]", pDummyNode, &dummyNode);
            }
            if (pDummyNode->id != (pre_id+1))
            {
                warn_log("> Node global id [%lu] did not match expected value [%lu]", pDummyNode->id, (pre_id+1));
            }
            if (strcmp(pDummyNode->name, expected_name) != 0)
            {
                warn_log("> Node name [%s] did not match expected value [%s]", pDummyNode->name, expected_name);
            }
        }
    }
    else
    {
        error_log("Got null pointer from static node init");
        pass = FALSE;
    }

    trace_log("<< End: test node 2");
    return pass;
}

/* test with NULL name */
const BOOL _test_Node3()
{
    trace_log(">> Begin:test node 3");

    BOOL pass = TRUE;

    unsigned long pre_id;
    LLNode dummyNode;

    char expected_name[LL_NODE_TINY_BUF_SZ+1];

    pre_id = __ll_node_get_global_id();
    memset(expected_name, '\0', sizeof(char)*(LL_NODE_TINY_BUF_SZ+1));
    /* sprintf is safe since max ulong is 18446744073709551615 == 20 characters
       as long as the buffer is larger than 20+12 charcaters */
    sprintf(expected_name, "Unnamed_node_%lu", (pre_id+1));
    /*snprintf(expected_name, LL_NODE_TINY_BUF_SZ, 0, "Unnamed_node_%lu", (pre_id+1));*/

    LLNode *pDummyNode = NULL;

    trace_log("> Linked::Node Static test 3 (NULL name): pre test id [%lu]", pre_id);

    pDummyNode = init_ll_node(&dummyNode, NULL);

    /* dummy test node */
    if (pDummyNode)
    {
        dump_node(pDummyNode);
        pass = ((pDummyNode == &dummyNode) && (pDummyNode->id = (pre_id+1)) && (strcmp(pDummyNode->name, expected_name) == 0));

        if (pass)
        {
            debug_log("Dummy Node 1 test: %sPASS%s", C_BGRN, C_NRM);
            debug_log("> Node data: id [%lu], name [%s]", pDummyNode->id, pDummyNode->name);
        }
        else
        {
            warn_log("Dummy Node 1 test: %sFAIL%s", C_BRED, C_NRM);
            if (pDummyNode != &dummyNode)
            {
                warn_log("> Returned node pointer [%p] does not match source addresss [%p]", pDummyNode, &dummyNode);
            }
            if (pDummyNode->id != (pre_id+1))
            {
                warn_log("> Node global id [%lu] did not match expected value [%lu]", pDummyNode->id, (pre_id+1));
            }
            if (strcmp(pDummyNode->name, expected_name) != 0)
            {
                warn_log("> Node name [%s] did not match expected value [%s]", pDummyNode->name, expected_name);
            }
        }
    }
    else
    {
        error_log("Got null pointer from static node init");
        pass = FALSE;
    }

    trace_log("<< End:test node 3");

    return pass;
}

const BOOL test_Node()
{
    BOOL pass = TRUE;

    trace_log("Begin Linked::Node tests");

    debug_log("--- Static allocation ---");
    pass &= _test_Node1();
    pass &= _test_Node2();
    pass &= _test_Node3();

    debug_log("--- Memory allocation ---");
    trace_log("> C stdlib calloc with ll_node_free");
    // IMPORTANT: Use calloc so we zero out the new node - we are not calling init!!!
    LLNode *pNode = (LLNode *)calloc(1,sizeof(LLNode));
    if (pNode)
    {
        debug_log("New LLNode at [%p]", pNode);
        dump_node(pNode);
        ll_node_free(&pNode);
        pass &= (pNode == NULL);
        debug_log("After free, pNode [%p]", pNode);
    }
    else
    {
        error_log("Could not allocate memory for a LLNode_t");
        pass = FALSE;
    }

    trace_log("> ll_node_alloc with C stdlib free");
    pNode = ll_node_alloc("Test alloc 1");
    if (pNode)
    {
        debug_log("Got new node at [%p]", pNode);
        dump_node(pNode);
        free(pNode);
        pNode = NULL;
    }
    else
    {
        error_log("Could not allocate new LLNode");
        pass = FALSE;
    }
   
    trace_log("> ll_node_alloc with ll_node_free");
    pNode = ll_node_alloc("Test alloc 1");
    if (pNode)
    {
        debug_log("Got new node at [%p]", pNode);
        dump_node(pNode);
        ll_node_free(&pNode);
        pass &= (pNode == NULL);
        dump_node(pNode);
        debug_log("After free, pNode [%p]", pNode);
    }
    else
    {
        error_log("Could not allocate new LLNode");
        pass = FALSE;
    }

	LLNode *pCopyNode = NULL;
    trace_log("> ll_node_alloc, ll_node_copy with ll_node_free");
    pNode = ll_node_alloc("Test alloc 2");
    if (pNode)
    {
        debug_log("Got new node at [%p]", pNode);
        dump_node(pNode);
        pCopyNode = ll_node_copy(pNode);
    }
    else
    {
        error_log("Could not allocate new LLNode");
        pass = FALSE;
    }

    if (!pNode)
    {
    	// do nothing
    }
    else if (pCopyNode)
    {
        debug_log("Got copied node at [%p]", pCopyNode);
        dump_node(pCopyNode);
    }
    else
    {
        error_log("Could not allocate copied LLNode");
        pass = FALSE;
    }

    if (pNode)
    {
        ll_node_free(&pNode);
        dump_node(pNode);
        pass &= (pNode == NULL);
    }
    if (pCopyNode)
    {
        ll_node_free(&pCopyNode);
        dump_node(pCopyNode);
        pass &= (pCopyNode == NULL);
    }

    trace_log("End Linked::Node tests");

    return pass;
}

const int test_Linked()
{
    int pass = 0;

    trace_log("Begin Linked tests");

    pass += test_Node();

    trace_log("End Linked tests");

    return pass;
}

=======
/*
 */
int test_itoa_result(char* name, int val, int base, char* expected)
{
    char buf[LARGE_STR_BUF+1], name_buf[LARGE_STR_BUF+1];
    int pass = TRUE;
    
    memset(buf, 0, sizeof(char)*(LARGE_STR_BUF+1));
    memset(name_buf, 0, sizeof(char)*(LARGE_STR_BUF+1));
    
    (void)myitoa(val, buf, base);
    //trace_log("myitoa(%d, buf, %d) -> \"%s\"", val, base, buf);
    
    sprintf(name_buf, "myitoa: %s (expect \"%s\", got \"%s\")", name, expected, buf);
    if (strcmp(expected, buf) == 0)
    {
        debug_log("TEST: %-64.64s: %sPASS%s", name_buf, C_BGRN, C_NRM);
    }
    else
    {
        warn_log("TEST: %-64.64s: %sFAIL%s", name_buf, C_BRED, C_NRM);
        pass = FALSE;
    }
    return pass;
}

/*
 */
int test_itoa()
{
    char testbuf[LARGE_STR_BUF+1];
    int pass = TRUE;
    
    memset(testbuf, 0, sizeof(char)*(LARGE_STR_BUF+1));
    
    info_log("----------------------------------------------------------------------------");
    info_log("Begin Utils::itoa tests");

    /* Test the itoa func */
    trace_log("Simple base 10 tests");
    pass &= test_itoa_result("0 val test", 0, 10, "0");
    pass &= test_itoa_result("1 val test", 4, 10, "4");
    pass &= test_itoa_result("3 digit test", 125, 10, "125");
    pass &= test_itoa_result("negative val test", -13, 10, "-13");
    pass &= test_itoa_result("SHRT_MAX val test", SHRT_MAX, 10, "32767");
    pass &= test_itoa_result("SHRT_MIN val test", SHRT_MIN, 10, "-32768");
    pass &= test_itoa_result("INT_MAX val test", INT_MAX, 10, "2147483647");
    pass &= test_itoa_result("INT_MIN val test", INT_MIN, 10, "-2147483648");

    trace_log("Simple base 16 (hex) tests");
    pass &= test_itoa_result("0 val test", 0, 16, "0");
    pass &= test_itoa_result("1 val test", 4, 16, "4");
    pass &= test_itoa_result("1 val test", 10, 16, "A");
    pass &= test_itoa_result("3 digit test", 125, 16, "125");

    info_log("End Utils::itoa tests");

    return pass;
}

/* ------------------------------------------------------------------------- */
char* expectPtrAsStr(int val) { return (val == TRUE ? "not null" : "null"); }

/*
 */
int testNode_Exist(char* name, SLL_NODE_P pNode, int expectNull, int expectVal, int expectNextNull)
{
    char buf[LARGE_STR_BUF+1];
    int result = TRUE;

    // Check node pointer
    memset(buf, 0, sizeof(char)*(LARGE_STR_BUF+1));
    sprintf(buf, "%s:Exist (expect %s, got %s)", name,
        expectPtrAsStr(expectNull), IsNullStr(pNode));
    if (pNode && !expectNull)
    {
        debug_log("TEST: %-64.64s: %sPASS%s", buf, C_BGRN, C_NRM);
    }
    else if (!pNode && expectNull)
    {
        debug_log("TEST: %-64.64s: %sPASS%s", buf, C_BGRN, C_NRM);
    }
    else
    {
        warn_log("TEST: %-64.64s: %sFAIL%s", buf, C_BRED, C_NRM);
        result = FALSE;
    }

    // Check value
    if (pNode)
    {
        memset(buf, 0, sizeof(char)*(LARGE_STR_BUF+1));
        sprintf(buf, "%s:Value (expect %d, got %d)", name, expectVal, pNode->value);
        if (pNode->value == expectVal)
        {
            debug_log("TEST: %-64.64s: %sPASS%s", buf, C_BGRN, C_NRM);
        }
        else
        {
            warn_log("TEST: %-64.64s: %sFAIL%s", buf, C_BRED, C_NRM);
            result = FALSE;
        }
    }
    else
    {
        memset(buf, 0, sizeof(char)*(LARGE_STR_BUF+1));
        sprintf(buf, "%s:Value", buf);
        debug_log("TEST: %-64.64s: %sSKIP%s", buf, C_BYEL, C_NRM);
    }

    // Check next pointer
    memset(buf, 0, sizeof(char)*(LARGE_STR_BUF+1));
    sprintf(buf, "%s:Next (expect %s, got %s)", name,
        expectPtrAsStr(expectNextNull), IsNullStr(pNode->next));
    if (pNode)
    {
        if (pNode->next && !expectNextNull)
        {
            debug_log("TEST: %-64.64s: %sPASS%s", buf, C_BGRN, C_NRM);
        }
        else if (!pNode->next && expectNextNull)
        {
            debug_log("TEST: %-64.64s: %sPASS%s", buf, C_BGRN, C_NRM);
        }
        else
        {
            warn_log("TEST: %-64.64s: %sFAIL%s", buf, C_BRED, C_NRM);
            result = FALSE;
        }
    }
    else
    {
        debug_log("TEST: %-64.64s: %sSKIP%s", buf, C_BYEL, C_NRM);
    }
    
    return result;
}

/*
 */
int test_SingleLinkedList()
{
    int passed = TRUE;
    SLL_Node* pNode = NULL;
    
    trace_log("----------------------------------------------------------------------------");
    trace_log("Begin Single linked list tests");
    
    trace_log("Begin::Create Single linked list tests");
    pNode = Create_SLL_Node(42);
    passed &= testNode_Exist("NULL node", pNode, FALSE, 42, TRUE);
    free(pNode);
    pNode = NULL;

    pNode = Create_SLL_Node(42);
    passed &= testNode_Exist("Create node (42)", pNode, FALSE, 42, TRUE);
    free(pNode);
    pNode = NULL;

    pNode = Create_SLL_Node(0);
    passed &= testNode_Exist("Create node (0)", pNode, FALSE, 0, TRUE);
    free(pNode);
    pNode = NULL;

    pNode = Create_SLL_Node(-1);
    passed &= testNode_Exist("Create node (-1)", pNode, FALSE, -1, TRUE);
    free(pNode);
    pNode = NULL;
    trace_log("End::Create Single linked list tests");

    trace_log("End Single linked list tests");
    
    return passed;
}
>>>>>>> Stashed changes
