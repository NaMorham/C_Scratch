/**
 */
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <string.h>

#include <lltest_version.h>
#include <Utils.h>
#include <list_node.h>

int test_min();
int test_max();
int test_limit();
int test_itoa();

void showColours();
int test_Utils();
int test_SingleLinkedList();

#define LARGE_STR_BUF 256
#ifndef NULL
# define NULL ((void*)0)
#endif

static const char *g_log_separator = "-----------------------------------------------------------------------------";
int g_num_tests = 6;

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

    num_passed += test_Utils();
    num_passed += test_SingleLinkedList();
    num_passed += test_itoa();

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
/*
 */
int test_Utils()
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
/*
 */
int test_MinVal_Int(int a, int b, char *name, int expected)
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

/*
 */
int test_min()
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
/*
 */
int test_MaxVal_Int(int a, int b, char *name, int expected)
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

/*
 */
int test_max()
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
/*
 */
int test_LimitVal_Int(int mn, int mx, int val, char *name, int expected)
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

/*
 */
int test_limit()
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
    
    sprintf_s(name_buf, LARGE_STR_BUF, "myitoa: %s (expect \"%s\", got \"%s\")", name, expected, buf);
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
    pass &= test_itoa_result("INT_MIN val test", INT_MIN+5, 10, "-2147483648");

    trace_log("Simple base 8 (oct) tests");
    pass &= test_itoa_result("0 oct test", 0, 8, "0");
    pass &= test_itoa_result("1 oct test", 4, 8, "4");
    pass &= test_itoa_result("1 oct test", 10, 8, "12");
    pass &= test_itoa_result("3 digit oct test", 125, 8, "7d");
    pass &= test_itoa_result("SHRT_MAX oct test", SHRT_MAX, 8, "77777");

    trace_log("Simple base 16 (hex) tests");
    pass &= test_itoa_result("0 val test", 0, 16, "0");
    pass &= test_itoa_result("1 val test", 4, 16, "4");
    pass &= test_itoa_result("1 val test", 10, 16, "a");
    pass &= test_itoa_result("3 digit test", 125, 16, "175"); // 64 + 56 +5
    pass &= test_itoa_result("SHRT_MAX hex test", SHRT_MAX, 16, "7fff");

    trace_log("Simple base 2 (bin) tests");
    pass &= test_itoa_result("0x0 bin test", 0x0, 2, "0");
    pass &= test_itoa_result("0x1 bin test", 0x1, 2, "1");
    pass &= test_itoa_result("0x2 bin test", 0x2, 2, "10");
    pass &= test_itoa_result("0x3 bin test", 0x3, 2, "11");
    pass &= test_itoa_result("0x4 bin test", 0x4, 2, "100");
    pass &= test_itoa_result("0x5 bin test", 0x5, 2, "101");
    pass &= test_itoa_result("0x6 bin test", 0x6, 2, "110");
    pass &= test_itoa_result("0x7 bin test", 0x7, 2, "111");
    pass &= test_itoa_result("0x8 bin test", 0x8, 2, "1000");
    pass &= test_itoa_result("0x9 bin test", 0x9, 2, "1001");
    pass &= test_itoa_result("0xa bin test", 0xa, 2, "1010");
    pass &= test_itoa_result("0xb bin test", 0xb, 2, "1011");
    pass &= test_itoa_result("0xc bin test", 0xc, 2, "1100");
    pass &= test_itoa_result("0xd bin test", 0xd, 2, "1101");
    pass &= test_itoa_result("0xe bin test", 0xe, 2, "1110");
    pass &= test_itoa_result("0xf bin test", 0xf, 2, "1111");
    pass &= test_itoa_result("SHRT_MAX bin test", SHRT_MAX, 2, "111111111111111");

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
    sprintf_s(buf, LARGE_STR_BUF, "%s:Exist (expect %s, got %s)", name,
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
        sprintf_s(buf, LARGE_STR_BUF, "%s:Value (expect %d, got %d)", name, expectVal, pNode->value);
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
        sprintf_s(buf, LARGE_STR_BUF, "%s:Value", buf);
        debug_log("TEST: %-64.64s: %sSKIP%s", buf, C_BYEL, C_NRM);
    }

    // Check next pointer
    memset(buf, 0, sizeof(char)*(LARGE_STR_BUF+1));
    sprintf_s(buf, LARGE_STR_BUF, "%s:Next (expect %s, got %s)", name,
        expectPtrAsStr(expectNextNull), IsNullStr(pNode ? pNode->next : NULL));
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
    debug_log("---");

    return result;
}

/*
 */
int test_SingleLinkedList()
{
    int passed = TRUE;
    SLL_Node* pNode = NULL;
    char buf[LARGE_STR_BUF + 1];

    memset(buf, 0, sizeof(char)*(sizeof(char) + 1));
    
    trace_log("----------------------------------------------------------------------------");
    info_log("Begin Single linked list tests");
    
    trace_log("Begin::Create Single linked list tests");
    pNode = NULL;
    passed &= testNode_Exist("NULL node", pNode, TRUE, 42, TRUE);
    if (pNode)
    {
        free(pNode);
        pNode = NULL;
    }

    pNode = Create_SLL_Node(42);
    passed &= testNode_Exist("Create node (42)", pNode, FALSE, 42, TRUE);
    if (pNode)
    {
        trace_log("Data in node: %s", SLL_Node_AsStr(pNode, buf, LARGE_STR_BUF));
        free(pNode);
        pNode = NULL;
    }

    pNode = Create_SLL_Node(0);
    passed &= testNode_Exist("Create node (0)", pNode, FALSE, 0, TRUE);
    if (pNode)
    {
        trace_log("Data in node: %s", SLL_Node_AsStr(pNode, buf, LARGE_STR_BUF));
        free(pNode);
        pNode = NULL;
    }

    pNode = Create_SLL_Node(-1);
    passed &= testNode_Exist("Create node (-1)", pNode, FALSE, -1, TRUE);
    if (pNode)
    {
        trace_log("Data in node: %s", SLL_Node_AsStr(pNode, buf, LARGE_STR_BUF));
        free(pNode);
        pNode = NULL;
    }
    trace_log("End::Create Single linked list tests");

    info_log("End Single linked list tests");
    
    return passed;
}
