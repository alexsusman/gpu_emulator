/*
 * Problem 7: Parsing strings
 * ==========================
 * Skills: '\0'-terminated strings, strchr, strcspn, strtok, strtol, strcmp,
 *         isspace, validating input.
 *
 * Why it matters: these are the building blocks of your Phase 3 assembler.
 * Each function here handles one piece of a line like
 *         loop:   ADD r3, r1, -12   ; a comment
 *
 * Look functions up in the manual from Terminal, e.g.  man 3 strtol
 *
 * Run with:  make p07_strings
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>
#include "check.h"

/* 7a. Remove a trailing newline ('\n', and also '\r' if present) in place.
 *     Hint: strcspn. */
void strip_newline(char *line) {
    // TODO
    (void)line;
}

/* 7b. Cut the line at the first ';' (start of a comment), in place.
 *     Hint: strchr. */
void strip_comment(char *line) {
    // TODO
    (void)line;
}

/* 7c. Trim whitespace from both ends. Trailing whitespace is removed in
 *     place; return a pointer to the first non-whitespace character.
 *     Example: "  ADD r1  " -> returns pointer to "ADD r1".
 *     Hint: isspace() from <ctype.h>; cast the char to unsigned char. */
char *trim(char *s) {
    // TODO
    return s;
}

/* 7d. Split `line` into tokens separated by spaces, tabs and commas.
 *     Store a pointer to each token in tokens[] (at most max_tokens of them)
 *     and return how many were found. Modifies line (that's how strtok works).
 *     Example: "ADD r3, r1,r2" -> 4 tokens: "ADD" "r3" "r1" "r2" */
int tokenize(char *line, char *tokens[], int max_tokens) {
    // TODO
    (void)line; (void)tokens; (void)max_tokens;
    return 0;
}

/* 7e. Parse a register name "r0" .. "r15".
 *     On success write the number to *out and return 1. On failure return 0
 *     and leave *out unchanged.
 *     Must reject: "r16", "r", "x3", "r3a", "r-1", "" and NULL.
 *     Hint: check tok[0], then strtol(tok + 1, &end, 10) and inspect end. */
int parse_register(const char *tok, int *out) {
    // TODO
    (void)tok; (void)out;
    return 0;
}

/* 7f. Parse an integer in decimal ("42", "-7") or hex ("0x2A").
 *     On success write it to *out and return 1; on failure return 0.
 *     Must reject: "", "abc", "12abc", and values outside int32_t's range.
 *     Hint: strtol with base 0, then check `end` and the range. */
int parse_int(const char *tok, int32_t *out) {
    // TODO
    (void)tok; (void)out;
    return 0;
}

/* 7g. Return 1 if tok is a label definition: at least one character
 *     followed by a ':' at the very end, e.g. "loop:". Otherwise 0. */
int is_label(const char *tok) {
    // TODO
    (void)tok;
    return 0;
}

/* 7h. Look up an instruction name and return its opcode, or -1 if unknown.
 *     The match should be case-insensitive ("add" == "ADD").
 *     Hint: loop over the table and use strcasecmp from <strings.h>, or
 *     write your own comparison with toupper(). */
typedef struct {
    const char *name;
    int opcode;
} OpInfo;

static const OpInfo OPS[] = {
    {"CONST", 0x01}, {"ADD", 0x02}, {"SUB", 0x03}, {"MUL", 0x04}, {"HALT", 0xFF},
};
static const int NUM_OPS = sizeof OPS / sizeof OPS[0];

int lookup_opcode(const char *name) {
    // TODO
    (void)name; (void)OPS; (void)NUM_OPS;
    return -1;
}

int main(void) {
    char buf[128];

    strcpy(buf, "ADD r1\n");
    strip_newline(buf);
    CHECK_STR(buf, "ADD r1");
    strcpy(buf, "ADD r1\r\n");
    strip_newline(buf);
    CHECK_STR(buf, "ADD r1");
    strcpy(buf, "no newline");
    strip_newline(buf);
    CHECK_STR(buf, "no newline");

    strcpy(buf, "ADD r1 ; add things");
    strip_comment(buf);
    CHECK_STR(buf, "ADD r1 ");
    strcpy(buf, "; only a comment");
    strip_comment(buf);
    CHECK_STR(buf, "");

    strcpy(buf, "   ADD r1  \t");
    CHECK_STR(trim(buf), "ADD r1");
    strcpy(buf, "    ");
    CHECK_STR(trim(buf), "");

    char *toks[8];
    strcpy(buf, "ADD r3, r1,r2");
    int n = tokenize(buf, toks, 8);
    CHECK_EQ(n, 4);
    if (n == 4) {
        CHECK_STR(toks[0], "ADD");
        CHECK_STR(toks[1], "r3");
        CHECK_STR(toks[3], "r2");
    }
    strcpy(buf, "  ,  ");
    CHECK_EQ(tokenize(buf, toks, 8), 0);
    strcpy(buf, "a b c d e");
    CHECK_EQ(tokenize(buf, toks, 3), 3);   /* respects max_tokens */

    int reg = -1;
    CHECK_EQ(parse_register("r0", &reg), 1);
    CHECK_EQ(reg, 0);
    CHECK_EQ(parse_register("r15", &reg), 1);
    CHECK_EQ(reg, 15);
    reg = 7;
    CHECK_EQ(parse_register("r16", &reg), 0);
    CHECK_EQ(parse_register("r", &reg), 0);
    CHECK_EQ(parse_register("x3", &reg), 0);
    CHECK_EQ(parse_register("r3a", &reg), 0);
    CHECK_EQ(parse_register("r-1", &reg), 0);
    CHECK_EQ(parse_register("", &reg), 0);
    CHECK_EQ(parse_register(NULL, &reg), 0);
    CHECK_EQ(reg, 7);   /* failures must not change *out */

    int32_t v = 0;
    CHECK_EQ(parse_int("42", &v), 1);
    CHECK_EQ(v, 42);
    CHECK_EQ(parse_int("-7", &v), 1);
    CHECK_EQ(v, -7);
    CHECK_EQ(parse_int("0x2A", &v), 1);
    CHECK_EQ(v, 42);
    CHECK_EQ(parse_int("", &v), 0);
    CHECK_EQ(parse_int("abc", &v), 0);
    CHECK_EQ(parse_int("12abc", &v), 0);
    CHECK_EQ(parse_int("99999999999", &v), 0);

    CHECK_EQ(is_label("loop:"), 1);
    CHECK_EQ(is_label("x:"), 1);
    CHECK_EQ(is_label(":"), 0);
    CHECK_EQ(is_label("loop"), 0);

    CHECK_EQ(lookup_opcode("ADD"), 0x02);
    CHECK_EQ(lookup_opcode("add"), 0x02);
    CHECK_EQ(lookup_opcode("Halt"), 0xFF);
    CHECK_EQ(lookup_opcode("ADDD"), -1);
    CHECK_EQ(lookup_opcode("AD"), -1);

    return report("p07_strings");
}
