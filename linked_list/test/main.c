#include <stdlib.h>
#include <stdio.h>
#include <limits.h>

#include <Utils.h>
#include <lltest_version.h>

int test_min();
int test_max();
int test_limit();

int test_Utils();
void showColours();

int g_num_tests = 3;

/* ------------------------------------------------------------------------- */
int main(int argc, char ** argv)
{
    g_log_level = LOG_DEBUG;

#ifdef USE_COLOUR
    info_log("Show colours");
    showColours();
#endif

    info_log("Run tests: version %d.%d.%d.%d", _VER_MAJOR, _VER_MINOR, _VER_PATCH, _VER_BUILD);

    int num_passed = 0;

    num_passed+=test_Utils();

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
int test_Utils()
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
int test_MinVal_Int(int a, int b, char *name, int expected)
{
    int result = MinVal(a, b);

    if (result == expected)
    {
        debug_log("TEST: %-32.32s: %sPASS%s", name, C_BGRN, C_NRM);
        return TRUE;
    }
    else
    {
        debug_log("TEST: %-32.32s: %sFAIL%s : MinVal(%d, %d) -> expected %d, got %d", name, C_BRED, LC_DBG, a, b, expected, result);
        return FALSE;
    }
}

int test_min()
{
    trace_log("Begin Utils::MinVal tests");

    /* Test the MinVal macro */
    test_MinVal_Int(0, 0, "zero, zero min test", 0);
    test_MinVal_Int(0, 1, "zero, one min test", 0);
    test_MinVal_Int(1, 0, "one, zero min test", 0);

    test_MinVal_Int(-1, 1, "-one, one min test", -1);
    test_MinVal_Int(1, -1, "one, -one min test", -1);

    test_MinVal_Int(1, 42, "one, forty-two min test", 1);
    test_MinVal_Int(42, 1, "forty-two, one min test", 1);

    test_MinVal_Int(-1, -42, "-one, -forty-two min test", -42);
    test_MinVal_Int(-42, -1, "-forty-two, -one min test", -42);

    test_MinVal_Int(0, INT_MAX, "0, INT_MAX min test", 0);
    test_MinVal_Int(0, INT_MIN, "0, INT_MIN min test", INT_MIN);
    test_MinVal_Int(INT_MAX, INT_MIN, "INT_MIN, INT_MAX min test", INT_MIN);

    test_MinVal_Int(3765, 3765, "Same positive value min test", 3765);
    test_MinVal_Int(-3765, -3765, "Same negative value min test", -3765);

    trace_log("Begin Utils::MinVal tests");

    return FALSE;
}

/* ------------------------------------------------------------------------- */
int test_MaxVal_Int(int a, int b, char *name, int expected)
{
    int result = MaxVal(a, b);

    if (result == expected)
    {
        debug_log("TEST: %-32.32s: %sPASS%s", name, C_BGRN, C_NRM);
        return TRUE;
    }
    else
    {
        debug_log("TEST: %-32.32s: %sFAIL%s : MaxVal(%d, %d) -> expected %d, got %d", name, C_BRED, LC_DBG, a, b, expected, result);
        return FALSE;
    }
}

int test_max()
{
    trace_log("Begin Utils::MaxVal tests");

    /* Test the MaxVal macro */
    test_MaxVal_Int (0, 0, "zero, zero max test", 0);
    test_MaxVal_Int (0, 1, "zero, one max test", 1);
    test_MaxVal_Int (1, 0, "one, zero max test", 1);

    test_MaxVal_Int (-1, 1, "-one, one max test", 1);
    test_MaxVal_Int (1, -1, "one, -one max test", 1);

    test_MaxVal_Int (1, 42, "one, forty-two max test", 42);
    test_MaxVal_Int (42, 1, "forty-two, one max test", 42);

    test_MaxVal_Int (-1, -42, "-one, -forty-two max test", -1);
    test_MaxVal_Int (-42, -1, "-forty-two, -one max test", -1);

    test_MaxVal_Int (0, INT_MAX, "0, INT_MAX max test", INT_MAX);
    test_MaxVal_Int (0, INT_MIN, "0, INT_MIN max test", 0);
    test_MaxVal_Int (INT_MAX, INT_MIN, "INT_MIN, INT_MAX max test", INT_MAX);

    test_MaxVal_Int (3765, 3765, "Same positive value max test", 3765);
    test_MaxVal_Int (-3765, -3765, "Same negative value max test", -3765);

    trace_log("Begin Utils::MaxVal tests");

    return FALSE;
}

int test_limit()
{
    trace_log("Begin Utils::LimitVal tests");

    /* Test the LimitVal macro */

    trace_log("Begin Utils::LimitVal tests");

    return FALSE;
}
