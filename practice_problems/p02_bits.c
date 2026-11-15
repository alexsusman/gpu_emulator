/*
 * Problem 2: Bit manipulation
 * ===========================
 * Skills: &, |, ^, ~, <<, >>, masks.
 *
 * Why it matters: decoding instructions means pulling bit fields out of a
 * 32-bit number, and in Phase 5 each warp tracks which threads are active
 * with a 32-bit "active mask" (bit i = thread i is active).
 *
 * Bits are numbered from 0 (least significant, rightmost) to 31.
 *
 * Run with:  make p02_bits
 */
#include <stdint.h>
#include "check.h"

/* 2a. Return bit i of x (0 or 1). */
int get_bit(uint32_t x, int i) {
    // TODO
    (void)x; (void)i;
    return 0;
}

/* 2b. Return x with bit i set to 1. */
uint32_t set_bit(uint32_t x, int i) {
    // TODO
    (void)x; (void)i;
    return 0;
}

/* 2c. Return x with bit i cleared to 0. */
uint32_t clear_bit(uint32_t x, int i) {
    // TODO
    (void)x; (void)i;
    return 0;
}

/* 2d. Return x with bit i flipped. */
uint32_t toggle_bit(uint32_t x, int i) {
    // TODO
    (void)x; (void)i;
    return 0;
}

/* 2e. Return a mask with the lowest n bits set (0 <= n <= 32).
 *     Example: low_mask(4) == 0xF, low_mask(0) == 0.
 *     In Phase 5: a warp with n threads starts with active mask low_mask(n).
 *     Hint: n == 32 needs special care (see problem 1b). */
uint32_t low_mask(int n) {
    // TODO
    (void)n;
    return 0;
}

/* 2f. Extract `width` bits of x starting at bit `lo`, shifted down to bit 0.
 *     Example: get_field(0xABCD, 4, 8) == 0xBC.
 *     This is the core operation of your instruction decoder.
 *     Hint: shift, then mask. Reuse low_mask. */
uint32_t get_field(uint32_t x, int lo, int width) {
    // TODO
    (void)x; (void)lo; (void)width;
    return 0;
}

/* 2g. Return x with the `width`-bit field at `lo` replaced by `value`.
 *     Only the low `width` bits of value are used; other bits of x are kept.
 *     Example: set_field(0xABCD, 4, 8, 0x12) == 0xA12D.
 *     This is the core operation of your assembler's encoder. */
uint32_t set_field(uint32_t x, int lo, int width, uint32_t value) {
    // TODO
    (void)x; (void)lo; (void)width; (void)value;
    return 0;
}

/* 2h. Count how many bits of x are 1.
 *     In Phase 5: "how many threads in this warp are active?"
 *     Write it with a loop (don't use compiler builtins). */
int count_ones(uint32_t x) {
    // TODO
    (void)x;
    return 0;
}

/* 2i. Return the index of the lowest set bit, or -1 if x == 0.
 *     Example: lowest_set_bit(0x8) == 3, lowest_set_bit(0x6) == 1. */
int lowest_set_bit(uint32_t x) {
    // TODO
    (void)x;
    return 0;
}

int main(void) {
    CHECK_EQ(get_bit(0x5, 0), 1);
    CHECK_EQ(get_bit(0x5, 1), 0);
    CHECK_EQ(get_bit(0x5, 2), 1);
    CHECK_EQ(get_bit(0x80000000, 31), 1);

    CHECK_HEX(set_bit(0x0, 3), 0x8);
    CHECK_HEX(set_bit(0x8, 3), 0x8);
    CHECK_HEX(set_bit(0x0, 31), 0x80000000);
    CHECK_HEX(clear_bit(0xF, 1), 0xD);
    CHECK_HEX(clear_bit(0xD, 1), 0xD);
    CHECK_HEX(toggle_bit(0xF, 0), 0xE);
    CHECK_HEX(toggle_bit(0xE, 0), 0xF);

    CHECK_HEX(low_mask(0), 0x0);
    CHECK_HEX(low_mask(4), 0xF);
    CHECK_HEX(low_mask(12), 0xFFF);
    CHECK_HEX(low_mask(32), 0xFFFFFFFF);

    CHECK_HEX(get_field(0xABCD, 4, 8), 0xBC);
    CHECK_HEX(get_field(0xABCD, 0, 4), 0xD);
    CHECK_HEX(get_field(0x12345678, 24, 8), 0x12);
    CHECK_HEX(get_field(0x12345678, 0, 32), 0x12345678);

    CHECK_HEX(set_field(0xABCD, 4, 8, 0x12), 0xA12D);
    CHECK_HEX(set_field(0x0, 24, 8, 0xFF), 0xFF000000);
    CHECK_HEX(set_field(0xFFFFFFFF, 0, 4, 0x0), 0xFFFFFFF0);
    CHECK_HEX(set_field(0x0, 0, 4, 0x1F), 0xF); /* extra bits must be dropped */

    CHECK_EQ(count_ones(0x0), 0);
    CHECK_EQ(count_ones(0xF), 4);
    CHECK_EQ(count_ones(0xA5), 4);
    CHECK_EQ(count_ones(0xFFFFFFFF), 32);

    CHECK_EQ(lowest_set_bit(0x0), -1);
    CHECK_EQ(lowest_set_bit(0x1), 0);
    CHECK_EQ(lowest_set_bit(0x8), 3);
    CHECK_EQ(lowest_set_bit(0x6), 1);
    CHECK_EQ(lowest_set_bit(0x80000000), 31);

    return report("p02_bits");
}
