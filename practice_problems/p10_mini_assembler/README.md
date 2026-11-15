# Problem 10 (capstone): a mini assembler in multiple files

This problem combines everything from problems 1 to 9, and practices splitting a program across `.c` and `.h` files. It's a small preview of Phase 3.

## Your task

Create `asm.h` and `asm.c` in this folder. `asm.h` must declare these two functions, and `asm.c` must implement them:

```c
int assemble_line(const char *line, uint32_t *out_instr);
int assemble_file(const char *path, uint32_t *out, int max);
```

`main.c` already contains the tests. Don't edit it. Build and run with `make p10` from the `practice_problems` folder. Until `asm.h` exists, the build fails with "asm.h: No such file or directory"; that's expected.

Remember everything from the C refresher: an include guard in every header, `#include <stdint.h>` in the header since it uses `uint32_t`, and `static` on helper functions that only `asm.c` uses.

**Recommended:** go further and split it into three modules, reusing your code from earlier problems. For example `encoding.h/.c` (problem 3), `parse.h/.c` (problem 7) and `asm.h/.c` (which uses both). The Makefile compiles every `.c` file in this folder automatically.

## The instruction set

Use the 32-bit layout from problem 3 (opcode in bits 31–24, rd 23–20, rs1 19–16, rs2 15–12, signed 12-bit immediate in 11–0).

| Instruction | Opcode | Operands | Encoded as |
| --- | --- | --- | --- |
| `CONST rd, imm` | `0x01` | a register and a number (decimal or hex, -2048..2047) | rd and imm set, rs1 = rs2 = 0 |
| `ADD rd, rs1, rs2` | `0x02` | three registers | rd, rs1, rs2 set, imm = 0 |
| `SUB rd, rs1, rs2` | `0x03` | three registers | same as ADD |
| `MUL rd, rs1, rs2` | `0x04` | three registers | same as ADD |
| `HALT` | `0xFF` | none | everything else 0 |

Instruction names are case-insensitive. Registers are `r0` to `r15`. Operands are separated by commas and/or spaces. A `;` starts a comment that runs to the end of the line.

## assemble_line

- Returns `1` and writes the encoded instruction to `*out_instr` if the line contains a valid instruction.
- Returns `0` if the line is empty, only whitespace, or only a comment.
- Returns `-1` for any error: unknown instruction, wrong number of operands, a bad register, a bad number, or an immediate that doesn't fit in 12 bits.

**Watch out:** `line` is `const char *`, and the tests pass string literals, which live in read-only memory. `strtok` modifies the string it splits, so calling it directly on `line` will crash. Copy the line into a local buffer first (`snprintf(buf, sizeof buf, "%s", line)` is a safe way to copy).

## assemble_file

- Assembles each line of the file at `path` and stores the instructions in `out`, in order.
- Returns the number of instructions stored.
- Returns `-1` if the file can't be opened, if any line has an error, or if the file contains more than `max` instructions.
- On a line error, prints a message to `stderr` that includes the file name and line number, for example `data/mini_bad.asm:3: wrong number of operands`.

The tests use `data/mini.asm` and `data/mini_bad.asm`; have a look at them.
