/*
 * Problem 3: Encoding and decoding instructions
 * =============================================
 * Skills: combining bit fields, structs as return values, sign extension.
 *
 * Why it matters: this is the exact code your assembler (encode) and
 * emulator (decode) need. Use the same layout in your real project, or
 * adapt it to your own ISA.md.
 *
 * Instruction layout (32 bits):
 *
 *    31      24 23  20 19  16 15  12 11          0
 *   +----------+------+------+------+-------------+
 *   |  opcode  |  rd  | rs1  | rs2  |  immediate  |
 *   +----------+------+------+------+-------------+
 *      8 bits   4 bits 4 bits 4 bits    12 bits
 *
 * The immediate is a SIGNED 12-bit number (-2048 .. 2047), stored in two's
 * complement in the low 12 bits.
 *
 * You may copy your functions from p02_bits.c into this file.
 *
 * Run with:  make p03_encoding
 */
#include <stdint.h>
#include "check.h"

typedef struct {
    uint8_t opcode;
    uint8_t rd;
    uint8_t rs1;
    uint8_t rs2;
    int32_t imm;    /* already sign-extended */
} Decoded;

/* 3a. Interpret the low `bits` bits of `value` as a two's complement
 *     signed number and return it as an int32_t.
 *     Examples (bits = 12): 0x005 -> 5, 0x7FF -> 2047, 0x800 -> -2048,
 *                           0xFFF -> -1
 *     Hint: if the top bit of the field (bit bits-1) is set, the number is
 *     negative: subtract 2^bits. */
int32_t sign_extend(uint32_t value, int bits) {
    // TODO
    (void)value; (void)bits;
    return 0;
}

/* 3b. Pack the fields into one 32-bit instruction using the layout above.
 *     Assume the inputs are already in range (we check ranges elsewhere).
 *     Careful: a negative imm must only occupy the low 12 bits. */
uint32_t encode(uint8_t opcode, uint8_t rd, uint8_t rs1, uint8_t rs2, int32_t imm) {
    // TODO
    (void)opcode; (void)rd; (void)rs1; (void)rs2; (void)imm;
    return 0;
}

/* 3c. Unpack an instruction into a Decoded struct.
 *     The immediate must come out sign-extended. */
Decoded decode(uint32_t instr) {
    // TODO
    Decoded d = {0};
    (void)instr;
    return d;
}

int main(void) {
    CHECK_EQ(sign_extend(0x005, 12), 5);
    CHECK_EQ(sign_extend(0x7FF, 12), 2047);
    CHECK_EQ(sign_extend(0x800, 12), -2048);
    CHECK_EQ(sign_extend(0xFFF, 12), -1);
    CHECK_EQ(sign_extend(0xF, 4), -1);
    CHECK_EQ(sign_extend(0x7, 4), 7);

    CHECK_HEX(encode(0x02, 3, 1, 2, 0), 0x02312000);
    CHECK_HEX(encode(0xFF, 0, 0, 0, 0), 0xFF000000);
    CHECK_HEX(encode(0x01, 5, 0, 0, 42), 0x0150002A);
    CHECK_HEX(encode(0x01, 5, 0, 0, -1), 0x01500FFF);
    CHECK_HEX(encode(0x01, 15, 15, 15, -2048), 0x01FFF800);

    Decoded d = decode(0x02312000);
    CHECK_EQ(d.opcode, 0x02);
    CHECK_EQ(d.rd, 3);
    CHECK_EQ(d.rs1, 1);
    CHECK_EQ(d.rs2, 2);
    CHECK_EQ(d.imm, 0);

    d = decode(0x01500FFF);
    CHECK_EQ(d.opcode, 0x01);
    CHECK_EQ(d.rd, 5);
    CHECK_EQ(d.imm, -1);

    /* Round trip: every legal immediate must survive encode -> decode. */
    int roundtrip_ok = 1;
    for (int32_t imm = -2048; imm <= 2047; imm++) {
        Decoded r = decode(encode(0x07, 9, 4, 11, imm));
        if (r.opcode != 0x07 || r.rd != 9 || r.rs1 != 4 || r.rs2 != 11 || r.imm != imm) {
            roundtrip_ok = 0;
            break;
        }
    }
    CHECK(roundtrip_ok);

    return report("p03_encoding");
}
