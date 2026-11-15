/*
 * Problem 10 (capstone): A mini assembler split across files
 * ==========================================================
 * Read p10_mini_assembler/README.md first. This file contains only the
 * tests: your job is to create asm.h and asm.c (and any other .c/.h files
 * you like) in this folder so that it compiles and the tests pass.
 *
 * Don't edit this file.
 *
 * Run with:  make p10
 */
#include <stdint.h>
#include "check.h"
#include "asm.h"

int main(void) {
    uint32_t instr = 0;

    /* Valid lines. The string literals here are READ-ONLY memory:
     * assemble_line must not modify `line` (strtok would!). */
    CHECK_EQ(assemble_line("ADD r3, r1, r2", &instr), 1);
    CHECK_HEX(instr, 0x02312000);
    CHECK_EQ(assemble_line("SUB r0, r15, r7", &instr), 1);
    CHECK_HEX(instr, 0x030F7000);
    CHECK_EQ(assemble_line("  const r5, -1   ; comments and lowercase are fine", &instr), 1);
    CHECK_HEX(instr, 0x01500FFF);
    CHECK_EQ(assemble_line("CONST r2, 0x10", &instr), 1);
    CHECK_HEX(instr, 0x01200010);
    CHECK_EQ(assemble_line("HALT", &instr), 1);
    CHECK_HEX(instr, 0xFF000000);

    /* Lines with no instruction. */
    CHECK_EQ(assemble_line("", &instr), 0);
    CHECK_EQ(assemble_line("     ", &instr), 0);
    CHECK_EQ(assemble_line("   ; just a comment", &instr), 0);

    /* Errors. */
    CHECK_EQ(assemble_line("ADD r1, r2", &instr), -1);          /* too few operands */
    CHECK_EQ(assemble_line("ADD r1, r2, r3, r4", &instr), -1);  /* too many */
    CHECK_EQ(assemble_line("JUMP r1", &instr), -1);             /* unknown instruction */
    CHECK_EQ(assemble_line("ADD r1, r2, r99", &instr), -1);     /* bad register */
    CHECK_EQ(assemble_line("CONST r1, 5000", &instr), -1);      /* doesn't fit in 12 bits */
    CHECK_EQ(assemble_line("CONST r1, r2", &instr), -1);        /* not a number */
    CHECK_EQ(assemble_line("HALT r1", &instr), -1);             /* HALT takes no operands */

    /* Whole files. */
    uint32_t prog[16] = {0};
    int n = assemble_file("data/mini.asm", prog, 16);
    CHECK_EQ(n, 6);
    CHECK_HEX(prog[0], 0x01100006);
    CHECK_HEX(prog[1], 0x01200007);
    CHECK_HEX(prog[2], 0x02312000);
    CHECK_HEX(prog[3], 0x01500002);
    CHECK_HEX(prog[4], 0x04435000);
    CHECK_HEX(prog[5], 0xFF000000);

    printf("(the next line should be an error message about line 3)\n");
    CHECK_EQ(assemble_file("data/mini_bad.asm", prog, 16), -1);
    CHECK_EQ(assemble_file("data/does_not_exist.asm", prog, 16), -1);
    CHECK_EQ(assemble_file("data/mini.asm", prog, 3), -1);       /* program too big */

    return report("p10_mini_assembler");
}
