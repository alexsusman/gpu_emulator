/*
 * Problem 5: Pointers
 * ===================
 * Skills: pointer parameters, "out" parameters, returning pointers,
 *         pointer arithmetic, NULL, const correctness.
 *
 * Why it matters: every function in your emulator takes a pointer to the
 * machine state, and your parsers will "return" several values through
 * out-parameters (e.g. "did it parse?" plus "what was the value?").
 *
 * Rule for this problem: in 5d, 5e and 5f, use pointer arithmetic
 * (p++, *p, p < end) instead of array indexing arr[i].
 *
 * Run with:  make p05_pointers
 */
#include <stdint.h>
#include <stddef.h>
#include "check.h"

/* 5a. Swap the values that a and b point to. */
void swap_u32(uint32_t *a, uint32_t *b) {
    // TODO
    (void)a; (void)b;
}

/* 5b. Find the minimum and maximum of arr[0..n-1] (n >= 1) and write them
 *     through out_min and out_max. Two results, no return value. */
void min_max(const int32_t *arr, int n, int32_t *out_min, int32_t *out_max) {
    // TODO
    (void)arr; (void)n; (void)out_min; (void)out_max;
}

/* 5c. Return a pointer to the first element equal to v, or NULL if absent.
 *     The caller can then modify the element through the pointer. */
uint32_t *find_value(uint32_t *arr, int n, uint32_t v) {
    // TODO
    (void)arr; (void)n; (void)v;
    return NULL;
}

/* 5d. Reverse arr[0..n-1] in place using two pointers that walk toward
 *     each other. Reuse swap_u32. */
void reverse(uint32_t *arr, int n) {
    // TODO
    (void)arr; (void)n;
}

/* 5e. Copy n words from src to dst (like memcpy, but for uint32_t). */
void copy_words(uint32_t *dst, const uint32_t *src, int n) {
    // TODO
    (void)dst; (void)src; (void)n;
}

/* 5f. Return the length of a C string by walking a pointer until '\0'.
 *     (Don't call strlen.) */
size_t my_strlen(const char *s) {
    // TODO
    (void)s;
    return 0;
}

int main(void) {
    uint32_t a = 1, b = 2;
    swap_u32(&a, &b);
    CHECK_EQ(a, 2);
    CHECK_EQ(b, 1);

    int32_t nums[] = {4, -7, 12, 0, 3};
    int32_t lo = 0, hi = 0;
    min_max(nums, 5, &lo, &hi);
    CHECK_EQ(lo, -7);
    CHECK_EQ(hi, 12);
    min_max(nums, 1, &lo, &hi);
    CHECK_EQ(lo, 4);
    CHECK_EQ(hi, 4);

    uint32_t mem[] = {10, 20, 30, 20};
    uint32_t *p = find_value(mem, 4, 20);
    CHECK(p == &mem[1]);
    if (p) *p = 99;              /* modify through the returned pointer */
    CHECK_EQ(mem[1], 99);
    CHECK(find_value(mem, 4, 77) == NULL);

    uint32_t r[] = {1, 2, 3, 4, 5};
    reverse(r, 5);
    CHECK_EQ(r[0], 5);
    CHECK_EQ(r[2], 3);
    CHECK_EQ(r[4], 1);
    uint32_t r2[] = {1, 2};
    reverse(r2, 2);
    CHECK_EQ(r2[0], 2);
    CHECK_EQ(r2[1], 1);

    uint32_t src[] = {7, 8, 9};
    uint32_t dst[3] = {0};
    copy_words(dst, src, 3);
    CHECK_EQ(dst[0], 7);
    CHECK_EQ(dst[2], 9);

    CHECK_EQ(my_strlen(""), 0);
    CHECK_EQ(my_strlen("ADD r1, r2, r3"), 14);

    return report("p05_pointers");
}
