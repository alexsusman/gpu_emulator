/*
 * check.h - a tiny test framework used by every problem.
 *
 * You don't need to edit this file, but read it once: it's a good example
 * of macros, static variables and printf formatting.
 */
#ifndef CHECK_H
#define CHECK_H

#include <stdio.h>
#include <string.h>

static int checks_run = 0;
static int checks_failed = 0;

/* CHECK(condition): passes if the condition is true. */
#define CHECK(cond)                                                     \
    do {                                                                \
        checks_run++;                                                   \
        if (!(cond)) {                                                  \
            checks_failed++;                                            \
            printf("  FAIL %s:%d: %s\n", __FILE__, __LINE__, #cond);    \
        }                                                               \
    } while (0)

/* CHECK_EQ(actual, expected): compares two integers, prints both on failure. */
#define CHECK_EQ(actual, expected)                                      \
    do {                                                                \
        long long a_ = (long long)(actual);                             \
        long long e_ = (long long)(expected);                           \
        checks_run++;                                                   \
        if (a_ != e_) {                                                 \
            checks_failed++;                                            \
            printf("  FAIL %s:%d: %s gave %lld, expected %lld\n",       \
                   __FILE__, __LINE__, #actual, a_, e_);                \
        }                                                               \
    } while (0)

/* CHECK_HEX(actual, expected): like CHECK_EQ but prints in hex (for bits). */
#define CHECK_HEX(actual, expected)                                     \
    do {                                                                \
        unsigned long long a_ = (unsigned long long)(actual);           \
        unsigned long long e_ = (unsigned long long)(expected);         \
        checks_run++;                                                   \
        if (a_ != e_) {                                                 \
            checks_failed++;                                            \
            printf("  FAIL %s:%d: %s gave 0x%llX, expected 0x%llX\n",   \
                   __FILE__, __LINE__, #actual, a_, e_);                \
        }                                                               \
    } while (0)

/* CHECK_STR(actual, expected): compares two strings (NULL-safe). */
#define CHECK_STR(actual, expected)                                     \
    do {                                                                \
        const char *a_ = (actual);                                      \
        const char *e_ = (expected);                                    \
        checks_run++;                                                   \
        if (a_ == NULL || e_ == NULL ? a_ != e_ : strcmp(a_, e_) != 0) {\
            checks_failed++;                                            \
            printf("  FAIL %s:%d: %s gave \"%s\", expected \"%s\"\n",   \
                   __FILE__, __LINE__, #actual,                         \
                   a_ ? a_ : "(NULL)", e_ ? e_ : "(NULL)");             \
        }                                                               \
    } while (0)

/* Print a summary. Returns 0 if everything passed (use as main's return). */
static int report(const char *name) {
    int passed = checks_run - checks_failed;
    printf("%s: %d/%d checks passed%s\n", name, passed, checks_run,
           checks_failed == 0 ? "  -- all good!" : "");
    return checks_failed == 0 ? 0 : 1;
}

#endif
