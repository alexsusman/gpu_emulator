/*
 * Problem 1: Fixed-width integers
 * ================================
 * Skills: <stdint.h> types, unsigned wraparound, signed vs unsigned,
 *         casting, printing exact-width types with <inttypes.h>.
 *
 * Why it matters: your GPU's registers are exactly 32 bits, opcodes are
 * exactly 8 bits, and immediates are exactly 12 bits. You need to know what
 * happens at the edges of those ranges.
 *
 * Before you code: for each test in main(), PREDICT the answer first, then
 * check whether you were right. The surprises are the lesson.
 *
 * Run with:  make p01_integers
 */
#include <stdint.h>
#include <inttypes.h>
#include <stdio.h>
#include "check.h"

/* 1a. Return a + b as an 8-bit unsigned number.
 *     Example: 250 + 10 does NOT give 260. What does it give, and why? */
uint8_t wrap_add_u8(uint8_t a, uint8_t b) {
    // TODO
    (void)a; (void)b;
    return 0;
}

/* 1b. Return 1 if `value` fits in an unsigned field of `bits` bits
 *     (1 <= bits <= 32), otherwise 0.
 *     Example: 255 fits in 8 bits, 256 does not.
 *     Hint: be careful with bits == 32. Shifting a 32-bit value by 32 is
 *     undefined behavior in C (the sanitizer will catch it). */
int fits_unsigned(uint32_t value, int bits) {
    // TODO
    (void)value; (void)bits;
    return 0;
}

/* 1c. Return 1 if `value` fits in a SIGNED two's complement field of `bits`
 *     bits (1 <= bits <= 32), otherwise 0.
 *     Example: a 12-bit signed field holds -2048 .. 2047.
 *     You'll need exactly this check for your assembler's immediates. */
int fits_signed(int32_t value, int bits) {
    // TODO
    (void)value; (void)bits;
    return 0;
}

/* 1d. Return the same 32 bits, reinterpreted as unsigned.
 *     What does -1 look like as an unsigned 32-bit number? */
uint32_t as_unsigned(int32_t x) {
    // TODO
    (void)x;
    return 0;
}

/* 1e. The reverse: the same 32 bits, reinterpreted as signed. */
int32_t as_signed(uint32_t x) {
    // TODO
    (void)x;
    return 0;
}

/* 1f. Write `x` into `out` (a buffer of size `n`) in the format
 *         "<decimal> 0x<hex, 8 digits, uppercase>"
 *     Example: 255 -> "255 0x000000FF"
 *     Use snprintf with the PRIu32 / PRIX32 macros from <inttypes.h>.
 *     Look them up: they're how you print uint32_t portably. */
void format_u32(uint32_t x, char *out, size_t n) {
    // TODO
    (void)x;
    if (n > 0) out[0] = '\0';
}

int main(void) {
    CHECK_EQ(wrap_add_u8(1, 2), 3);
    CHECK_EQ(wrap_add_u8(250, 10), 4);
    CHECK_EQ(wrap_add_u8(255, 1), 0);

    CHECK_EQ(fits_unsigned(255, 8), 1);
    CHECK_EQ(fits_unsigned(256, 8), 0);
    CHECK_EQ(fits_unsigned(15, 4), 1);
    CHECK_EQ(fits_unsigned(16, 4), 0);
    CHECK_EQ(fits_unsigned(0xFFFFFFFF, 32), 1);

    CHECK_EQ(fits_signed(2047, 12), 1);
    CHECK_EQ(fits_signed(2048, 12), 0);
    CHECK_EQ(fits_signed(-2048, 12), 1);
    CHECK_EQ(fits_signed(-2049, 12), 0);
    CHECK_EQ(fits_signed(-1, 1), 1);
    CHECK_EQ(fits_signed(1, 1), 0);
    CHECK_EQ(fits_signed(INT32_MIN, 32), 1);

    CHECK_HEX(as_unsigned(-1), 0xFFFFFFFF);
    CHECK_HEX(as_unsigned(-2), 0xFFFFFFFE);
    CHECK_EQ(as_signed(0xFFFFFFFF), -1);
    CHECK_EQ(as_signed(0x80000000), INT32_MIN);

    char buf[32];
    format_u32(255, buf, sizeof buf);
    CHECK_STR(buf, "255 0x000000FF");
    format_u32(0xDEADBEEF, buf, sizeof buf);
    CHECK_STR(buf, "3735928559 0xDEADBEEF");

    return report("p01_integers");
}
