/*
 * Problem 6: A switch-based stack machine
 * =======================================
 * Skills: enum, switch, a fetch-execute loop, structs + arrays + pointers
 *         together, error handling.
 *
 * Why it matters: this is a warm-up for Phase 2. A real emulator is a loop
 * around one big switch statement. This machine is deliberately different
 * from your GPU (it uses a stack instead of registers), so you practice the
 * pattern without spoiling the design work of Phase 2.
 *
 * The machine:
 *   - A stack of up to STACK_SIZE int32_t values. sp is the number of values
 *     on it, so the top value is stack[sp - 1]. Empty stack: sp == 0.
 *   - pc is the index of the next instruction in the program array.
 *
 * Instructions:
 *   PUSH n   push n
 *   POP      discard the top value
 *   ADD      pop b, pop a, push a + b
 *   SUB      pop b, pop a, push a - b      (order matters!)
 *   MUL      pop b, pop a, push a * b
 *   DUP      push a copy of the top value
 *   SWAP     swap the top two values
 *   JNZ t    pop a value; if it is nonzero, jump to instruction index t,
 *            otherwise continue with the next instruction
 *   HALT     stop
 *
 * Run with:  make p06_stack_machine
 */
#include <stdint.h>
#include "check.h"

#define STACK_SIZE 16

typedef enum { OP_PUSH, OP_POP, OP_ADD, OP_SUB, OP_MUL, OP_DUP, OP_SWAP, OP_JNZ, OP_HALT } Opcode;

typedef struct {
    Opcode op;
    int32_t arg;   /* used by PUSH and JNZ only */
} Instr;

typedef struct {
    int32_t stack[STACK_SIZE];
    int sp;
    int pc;
    int halted;
    int error;     /* 1 if the program did something illegal */
} VM;

/* 6a. Reset the VM: empty stack, pc 0, not halted, no error. */
void vm_init(VM *vm) {
    // TODO
    (void)vm;
}

/* 6b. Run `prog` (an array of `len` instructions) until one of these:
 *       - HALT executes                    -> halted = 1
 *       - pc leaves the range 0..len-1     -> halted = 1
 *       - an error happens                 -> error = 1 and halted = 1
 *     Errors: popping from an empty stack (underflow), pushing onto a full
 *     stack (overflow), or an unknown opcode (use the switch's default case).
 *
 *     Return the number of instructions executed (HALT counts as one).
 *
 *     Suggested structure:
 *         while (!vm->halted) {
 *             if (pc out of range) { halt; break; }
 *             Instr in = prog[vm->pc];
 *             vm->pc++;              // jumps overwrite this
 *             switch (in.op) { ... }
 *         }
 *     Tip: small static helper functions push() and pop() that check for
 *     errors will keep the switch short and readable. */

int vm_run(VM *vm, const Instr *prog, int len) {
    // TODO
    (void)vm; (void)prog; (void)len;
    return 0;
}

/* Helper for the tests: the value on top of the stack (or -999 if empty). */
static int32_t top(const VM *vm) {
    return vm->sp > 0 ? vm->stack[vm->sp - 1] : -999;
}

int main(void) {
    VM vm;

    Instr add[] = { {OP_PUSH, 2}, {OP_PUSH, 3}, {OP_ADD, 0}, {OP_HALT, 0} };
    vm_init(&vm);
    CHECK_EQ(vm_run(&vm, add, 4), 4);
    CHECK_EQ(top(&vm), 5);
    CHECK_EQ(vm.sp, 1);
    CHECK_EQ(vm.error, 0);

    /* No HALT: the machine stops when pc runs off the end. */
    Instr sub[] = { {OP_PUSH, 10}, {OP_PUSH, 4}, {OP_SUB, 0} };
    vm_init(&vm);
    CHECK_EQ(vm_run(&vm, sub, 3), 3);
    CHECK_EQ(top(&vm), 6);
    CHECK_EQ(vm.halted, 1);

    Instr square[] = { {OP_PUSH, 7}, {OP_DUP, 0}, {OP_MUL, 0}, {OP_HALT, 0} };
    vm_init(&vm);
    vm_run(&vm, square, 4);
    CHECK_EQ(top(&vm), 49);

    Instr swap[] = { {OP_PUSH, 1}, {OP_PUSH, 2}, {OP_SWAP, 0}, {OP_HALT, 0} };
    vm_init(&vm);
    vm_run(&vm, swap, 4);
    CHECK_EQ(vm.stack[0], 2);
    CHECK_EQ(vm.stack[1], 1);

    Instr popper[] = { {OP_PUSH, 1}, {OP_PUSH, 2}, {OP_POP, 0}, {OP_HALT, 0} };
    vm_init(&vm);
    vm_run(&vm, popper, 4);
    CHECK_EQ(top(&vm), 1);
    CHECK_EQ(vm.sp, 1);

    /* A loop: count down from 3 to 0.
     *   0: PUSH 3
     *   1: PUSH -1     <- loop start
     *   2: ADD
     *   3: DUP
     *   4: JNZ 1
     *   5: HALT                                                     */
    Instr loop[] = { {OP_PUSH, 3}, {OP_PUSH, -1}, {OP_ADD, 0},
                     {OP_DUP, 0}, {OP_JNZ, 1}, {OP_HALT, 0} };
    vm_init(&vm);
    CHECK_EQ(vm_run(&vm, loop, 6), 1 + 4 * 3 + 1);
    CHECK_EQ(top(&vm), 0);
    CHECK_EQ(vm.sp, 1);

    /* Errors */
    Instr underflow[] = { {OP_ADD, 0}, {OP_HALT, 0} };
    vm_init(&vm);
    vm_run(&vm, underflow, 2);
    CHECK_EQ(vm.error, 1);
    CHECK_EQ(vm.halted, 1);

    Instr overflow[STACK_SIZE + 1];
    for (int i = 0; i < STACK_SIZE + 1; i++) {
        overflow[i].op = OP_PUSH;
        overflow[i].arg = i;
    }
    vm_init(&vm);
    vm_run(&vm, overflow, STACK_SIZE + 1);
    CHECK_EQ(vm.error, 1);

    Instr bad[] = { {(Opcode)99, 0} };
    vm_init(&vm);
    vm_run(&vm, bad, 1);
    CHECK_EQ(vm.error, 1);

    return report("p06_stack_machine");
}
