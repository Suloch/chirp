#include <stdio.h>
#include "../utils.h"

int num_passed = 0;
int num_failed = 0;

void test_numberPoetic(char *literal, double expected)
{
    double number;

    number = numberPoetic(literal);
    if (number == expected)
    {
        num_passed++;
        printf("passed: '%s' -> %lf\n", literal, number);
    }
    else
    {
        num_failed++;
        printf("failed: '%s' -> %lf, should be %lf\n", literal, number, expected);
    }
}

int main(int argc, char *argv[])
{
    /* Single word tests. */
    test_numberPoetic("x", 1.0);
    test_numberPoetic("xx", 2.0);
    test_numberPoetic("xxxxxxxxx", 9.0);
    test_numberPoetic("xxxxxxxxxx", 0.0);
    test_numberPoetic("xxxxxxxxxxx", 1.0);

    /* Multiple word tests. */
    test_numberPoetic("a b", 11.0);
    test_numberPoetic("a ab abc", 123.0);
    test_numberPoetic("a abcdefghij", 10.0);
    test_numberPoetic("a abcdefghij abcdefghij", 100.0);
    test_numberPoetic("  a ab   abc", 123.0);

    /* Decimal point tests */
    test_numberPoetic("x. xx", 1.2);
    test_numberPoetic("x. xx xxx", 1.23);

    /* Punctuation tests */
    test_numberPoetic("ain't", 4.0);
    test_numberPoetic("rock 'n roll", 414.0);
    test_numberPoetic("unfulfilled; wakin'", 15.0);
    test_numberPoetic("everybody up, taking", 926);

    /*
     * Poetic Number Literal examples from the rockstar spec.
     *
     * - Tommy was a lovestruck ladykiller initialises Tommy with the value 100
     * - Sweet Lucy was a dancer - initialises Sweet Lucy with the value 16
     * - A killer is on the loose - initialises a killer with the value 235.
     * - My dreams were ice. A life unfulfilled; wakin' everybody up, taking
     *   booze and pills - initialises my dreams with the value 3.1415926535
     * - Tommy was without initialises Tommy with the value 7
     *   because without is a Reserved Keyword, but not a Literal Word.
     */
    test_numberPoetic("a lovestruck ladykiller", 100.0);
    test_numberPoetic("a dancer", 16.0);
    test_numberPoetic("on the loose", 235.0);
    test_numberPoetic("ice. A life unfulfilled; wakin' everybody up, taking booze and pills", 3.1415926535);
    test_numberPoetic("without", 7.0);

    printf("%d tests passed\n", num_passed);
    printf("%d tests failed\n", num_failed);
    return (num_failed == 0 ? 0 : 1);
}
