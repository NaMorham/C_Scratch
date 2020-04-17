#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include <lltest_version.h>
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
void showColours();

static int g_num_tests = 4;

static const char *g_log_separator = "-----------------------------------------------------------------------------";

/* ------------------------------------------------------------------------- */
const int main(const int argc, const char ** argv)
{
    g_log_level = LOG_DEBUG;

    info_log("Run %d tests: version %d.%d.%d.%d", g_num_tests, _VER_MAJOR, _VER_MINOR, _VER_PATCH, _VER_BUILD);

#ifdef USE_COLOUR
    info_log("Show colours");
    showColours();
    info_log("%s\n", g_log_separator);
#endif

    int num_passed = 0;

    info_log("> Util tests");
    num_passed += test_Utils();
    info_log("%s\n", g_log_separator);

    info_log("> Linked List tests");
    num_passed += test_Node();
    info_log("%s\n", g_log_separator);

    info_log("%d/%d tests passed", num_passed, g_num_tests);

    return (num_passed = g_num_tests);
}


/* ------------------------------------------------------------------------- */
void showColours()
{
#ifdef USE_COLOUR
    trace_log("Begin Show all normal colours");

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

    trace_log("End Show all normal colours");
#endif
}

/* ------------------------------------------------------------------------- */
const int test_Utils()
{
    /* Run tests on the Utils include/files */
    trace_log("Begin Utils tests");

    int result = 0;

    result += test_min();
    result += test_max();
    result += test_limit();

    trace_log("End Utils tests");

    return result;
}

/* ------------------------------------------------------------------------- */
const int test_MinVal_Int(const int a, const int b, const char *name, const int expected)
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

const int test_min()
{
    int pass = TRUE;

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
const int test_MaxVal_Int(const int a, const int b, const char *name, const int expected)
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

const int test_max()
{
    int pass = TRUE;

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
const int test_LimitVal_Int(const int mn, const int mx, const int val, const char *name, const int expected)
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

const int test_limit()
{
    int pass = TRUE;

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
extern const unsigned long __ll_node_get_global_id();

/* test with defined name */
const BOOL _test_Node1()
{
    trace_log(">> Begin:test node 1");

    BOOL pass = TRUE;

    unsigned long pre_id;
    struct LLNode_t dummyNode;

    const char *expected_name = "test name 1";

    struct LLNode_t *pDummyNode = NULL;

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
    struct LLNode_t dummyNode;

    char expected_name[LL_NODE_TINY_BUF_SZ+1];

    pre_id = __ll_node_get_global_id();
    memset(expected_name, '\0', sizeof(char)*(LL_NODE_TINY_BUF_SZ+1));
    /* sprintf is safe since max ulong is 18446744073709551615 == 20 characters
       as long as the buffer is larger than 20+12 charcaters */
    sprintf(expected_name, "Unnamed_node_%lu", (pre_id+1));
    /*snprintf(expected_name, LL_NODE_TINY_BUF_SZ, 0, "Unnamed_node_%lu", (pre_id+1));*/

    struct LLNode_t *pDummyNode = NULL;

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
    struct LLNode_t dummyNode;

    char expected_name[LL_NODE_TINY_BUF_SZ+1];

    pre_id = __ll_node_get_global_id();
    memset(expected_name, '\0', sizeof(char)*(LL_NODE_TINY_BUF_SZ+1));
    /* sprintf is safe since max ulong is 18446744073709551615 == 20 characters
       as long as the buffer is larger than 20+12 charcaters */
    sprintf(expected_name, "Unnamed_node_%lu", (pre_id+1));
    /*snprintf(expected_name, LL_NODE_TINY_BUF_SZ, 0, "Unnamed_node_%lu", (pre_id+1));*/

    struct LLNode_t *pDummyNode = NULL;

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

    trace_log("--- Static allocation ---");
    pass &= _test_Node1();
    pass &= _test_Node2();
    pass &= _test_Node3();

    trace_log("--- Memory allocation ---");

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

