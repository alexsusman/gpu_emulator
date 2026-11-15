/*
 * Problem 4: Structs and arrays of structs
 * ========================================
 * Skills: typedef struct, nested structs, arrays inside structs, arrays of
 *         structs, passing structs by pointer, const pointers.
 *
 * Why it matters: this IS the shape of your Phase 4 GPU. A warp has one
 * program counter shared by all its threads, but every thread has its own
 * registers. Operations run only on ACTIVE threads (see the active mask).
 *
 * Run with:  make p04_structs
 */
#include <stdint.h>
#include "check.h"

#define WARP_SIZE 4
#define NUM_REGS  8

typedef struct {
    uint32_t id;               /* global thread id */
    uint32_t regs[NUM_REGS];
} Thread;

typedef struct {
    uint32_t pc;
    uint32_t active_mask;      /* bit i set = threads[i] is active */
    Thread threads[WARP_SIZE];
} Warp;

/* 4a. Initialize a warp: pc = 0, all WARP_SIZE threads active, every
 *     register 0, and thread ids first_id, first_id + 1, ... */
void warp_init(Warp *w, uint32_t first_id) {
    // TODO
    (void)w; (void)first_id;
}

/* 4b. Initialize an array of warps so thread ids continue across warps:
 *     warps[0] gets ids 0..3, warps[1] gets 4..7, and so on. */
void block_init(Warp warps[], int num_warps) {
    // TODO
    (void)warps; (void)num_warps;
}

/* 4c. For every ACTIVE thread: regs[rd] = that thread's id.
 *     (This is how a kernel learns "which element am I?") */
void warp_read_tid(Warp *w, int rd) {
    // TODO
    (void)w; (void)rd;
}

/* 4d. For every ACTIVE thread: regs[rd] = regs[rs] + imm. */
void warp_add_imm(Warp *w, int rd, int rs, int32_t imm) {
    // TODO
    (void)w; (void)rd; (void)rs; (void)imm;
}

/* 4e. For every ACTIVE thread: regs[rd] = regs[rs1] * regs[rs2]. */
void warp_mul(Warp *w, int rd, int rs1, int rs2) {
    // TODO
    (void)w; (void)rd; (void)rs1; (void)rs2;
}

/* 4f. Return the sum of register r over ALL threads (active or not).
 *     Note the `const`: this function promises not to modify the warp. */
uint32_t warp_sum_reg(const Warp *w, int r) {
    // TODO
    (void)w; (void)r;
    return 0;
}

/* Already written. QUESTION: the test in main() shows this function does
 * NOT change the caller's warp. Explain why in one sentence, then compare
 * it to warp_init. (Write your answer in your notes.) */
void reset_pc_by_value(Warp w) {
    w.pc = 0;
    printf("  (inside reset_pc_by_value, pc is %u)\n", w.pc);
}

int main(void) {
    Warp w;
    warp_init(&w, 100);
    CHECK_EQ(w.pc, 0);
    CHECK_HEX(w.active_mask, 0xF);
    CHECK_EQ(w.threads[0].id, 100);
    CHECK_EQ(w.threads[3].id, 103);
    CHECK_EQ(w.threads[2].regs[5], 0);

    Warp block[3];
    block_init(block, 3);
    CHECK_EQ(block[0].threads[0].id, 0);
    CHECK_EQ(block[1].threads[0].id, 4);
    CHECK_EQ(block[2].threads[3].id, 11);

    /* A tiny "kernel": r1 = tid; r2 = r1 + 1; r3 = r1 * r2 */
    warp_init(&w, 0);
    warp_read_tid(&w, 1);
    warp_add_imm(&w, 2, 1, 1);
    warp_mul(&w, 3, 1, 2);
    CHECK_EQ(w.threads[2].regs[1], 2);
    CHECK_EQ(w.threads[2].regs[2], 3);
    CHECK_EQ(w.threads[2].regs[3], 6);
    CHECK_EQ(warp_sum_reg(&w, 3), 0 * 1 + 1 * 2 + 2 * 3 + 3 * 4);

    /* Inactive threads must not change. Only threads 0 and 2 active: */
    warp_init(&w, 0);
    w.active_mask = 0x5;
    warp_add_imm(&w, 4, 4, 10);
    CHECK_EQ(w.threads[0].regs[4], 10);
    CHECK_EQ(w.threads[1].regs[4], 0);
    CHECK_EQ(w.threads[2].regs[4], 10);
    CHECK_EQ(w.threads[3].regs[4], 0);

    w.pc = 42;
    reset_pc_by_value(w);
    CHECK_EQ(w.pc, 42); /* why? see the QUESTION above */

    return report("p04_structs");
}
