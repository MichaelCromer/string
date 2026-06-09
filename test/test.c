#include <stdio.h>
#include <stdlib.h>

#include "../string.h"

#define RUN(fn) test_run(#fn, fn)

#define PASS()                                                      \
    do {                                                            \
        state.passed++;                                             \
        return;                                                     \
    } while (0)         


#define ASSERT(expr)                                                \
    do {                                                            \
        if (!(expr)) {                                              \
            fprintf(stderr, "%s:%d: %s: assertion failed: %s\n",    \
                    __FILE__, __LINE__, state.current, #expr);      \
            return;                                                 \
        }                                                           \
    } while (0)


typedef void (*test_fn)(void);

static struct
{
    const char *current;
    int passed;
    int total;
}
state;


const char *TEST_STR = "Hello World";



void test_run(const char *name, test_fn fn)
{
    int before = state.passed;

    state.current = name;
    state.total++;

    fn();

    if (state.passed == before) {
        fprintf(stderr, "FAIL : %s\n", name);
        return;
    }

    printf("PASS : %s\n", name);
}


void test_strcpy(void)
{
    struct String *string = string_create(64);
    string_strcpy(string, TEST_STR);
    int res = string_strcmp(string, TEST_STR);
    string_destroy(string);

    ASSERT(0 == res);
    PASS();
}


void test_strcpy_short(void)
{
    size_t N = 3;
    struct String *string = string_create(N);
    string_strcpy(string, TEST_STR);
    int res1 = string_strncmp(string, TEST_STR, N);
    int res2 = string_strcmp(string, TEST_STR);
    string_destroy(string);

    ASSERT(0 == res1);
    ASSERT(0 != res2);
    PASS();
}


void test_strdup(void)
{
    struct String *string = string_strdup(TEST_STR);
    int res = string_strcmp(string, TEST_STR);
    string_destroy(string);
    
    ASSERT(0 == res);
    PASS();
}


void test_strndup(void)
{
    size_t N = 3;
    struct String *string = string_strndup(TEST_STR, N);
    int res1 = string_strcmp(string, TEST_STR);
    int res2 = string_strncmp(string, TEST_STR, N);
    string_destroy(string);

    ASSERT(0 != res1);
    ASSERT(0 == res2);
    PASS();
}


void test_true(void)
{
    ASSERT(1);
    PASS();
}


void test_false(void)
{
    ASSERT(0);
    PASS();
}


int main(void)
{
    RUN(test_strcpy);
    RUN(test_strcpy_short);
    RUN(test_strdup);
    RUN(test_strndup);

    printf("\n%d/%d tests passed!\n", state.passed, state.total);

    return (state.passed == state.total) ? 0 : 1;
}
