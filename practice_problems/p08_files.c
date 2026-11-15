/*
 * Problem 8: Reading and writing files
 * ====================================
 * Skills: fopen / fgets / fprintf / fclose, checking for errors, line
 *         numbers in error messages, combining your string helpers.
 *
 * Why it matters: your assembler reads .asm files line by line, and later
 * you'll want to save results and statistics to files.
 *
 * Copy your strip_newline, strip_comment, trim and parse_int from
 * p07_strings.c into this file (below the includes) and reuse them.
 * Take a look at the files in data/ before you start.
 *
 * Run with:  make p08_files   (from the practice_problems folder, so the
 *                              relative paths like "data/numbers.txt" work)
 */
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <inttypes.h>
#include <limits.h>
#include "check.h"

/* ---- paste your helpers from p07 here ---- */

/* 8a. Count the lines in the file that contain code: skip lines that are
 *     empty, only whitespace, or only a comment.
 *     Return -1 if the file can't be opened. */
int count_code_lines(const char *path) {
    // TODO
    (void)path;
    return 0;
}

/* 8b. Read a file with one number per line (decimal or hex; blank lines and
 *     comments allowed) into out[], storing at most max numbers.
 *     Return how many numbers were read.
 *     If a line isn't a valid number, print an error to stderr like
 *         data/bad_numbers.txt:3: not a number: 'oops'
 *     close the file, and return -1. Also return -1 if the file can't be
 *     opened. */
int load_numbers(const char *path, int32_t *out, int max) {
    // TODO
    (void)path; (void)out; (void)max;
    return 0;
}

/* 8c. Write the n values to a file, one per line, in the format 0x%08X
 *     (use PRIX32), e.g. "0x000000FF". Overwrite the file if it exists.
 *     Return 1 on success, 0 if the file can't be opened. */
int save_hex(const char *path, const uint32_t *values, int n) {
    // TODO
    (void)path; (void)values; (void)n;
    return 0;
}

int main(void) {
    CHECK_EQ(count_code_lines("data/program.asm"), 6);
    CHECK_EQ(count_code_lines("data/does_not_exist.asm"), -1);

    int32_t nums[10] = {0};
    int n = load_numbers("data/numbers.txt", nums, 10);
    CHECK_EQ(n, 4);
    CHECK_EQ(nums[0], 42);
    CHECK_EQ(nums[1], 16);
    CHECK_EQ(nums[2], -5);
    CHECK_EQ(nums[3], 7);
    CHECK_EQ(load_numbers("data/numbers.txt", nums, 2), 2);   /* respects max */

    printf("(the next line should be an error message about line 3)\n");
    CHECK_EQ(load_numbers("data/bad_numbers.txt", nums, 10), -1);
    CHECK_EQ(load_numbers("data/does_not_exist.txt", nums, 10), -1);

    /* Write a file, then read it back with your own loader. */
    uint32_t vals[] = {1, 255, 0x7FFFFFFF};
    CHECK_EQ(save_hex("p08_output.txt", vals, 3), 1);
    int32_t back[3] = {0};
    CHECK_EQ(load_numbers("p08_output.txt", back, 3), 3);
    CHECK_EQ(back[0], 1);
    CHECK_EQ(back[1], 255);
    CHECK_EQ(back[2], 0x7FFFFFFF);

    return report("p08_files");
}
