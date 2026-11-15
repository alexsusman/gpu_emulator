# C practice problems

Ten short problem sets covering the C you need for Phases 2 and 3 of the GPU emulator: building the CPU emulator and the assembler. Each problem is a single `.c` file with function stubs marked `// TODO` and a `main()` full of tests. You replace the stubs until every test passes.

## How to work

1. Open the problem's `.c` file and read the comment at the top.
2. Implement the `TODO` functions. You can delete the `(void)x;` lines; they only silence "unused parameter" warnings in the stubs.
3. From inside this folder, run `make <problem name>`, for example `make p03_encoding`. You'll see a line for every failed check and a summary like `p03_encoding: 20/20 checks passed -- all good!`
4. Repeat until it passes, then commit.

Run `make all` to run every problem at once, and `make clean` to delete build output.

A few ground rules that will make this worth the time:

- **Predict before you run.** For each test, guess the result first. Being wrong is where the learning happens.
- **Fix warnings as well as failures.** The Makefile builds with `-Wall -Wextra` and the sanitizers, so treat any warning or sanitizer report as a bug.
- **Use the manual, not full solutions.** `man 3 strtol` (or any other function name) in Terminal shows the official documentation. Looking up how a function works is good practice; looking up a solution to the problem isn't.
- **Don't edit the tests.** If you think a test is wrong, re-read the spec in the comment first.

## The problems

| # | File | Skills | Used later in |
| --- | --- | --- | --- |
| 1 | `p01_integers.c` | `<stdint.h>` types, wraparound, signed vs unsigned, `printf` formats | Everywhere |
| 2 | `p02_bits.c` | Bitwise operators, masks, bit fields, counting bits | Decoding, active masks (Phase 5) |
| 3 | `p03_encoding.c` | Packing and unpacking instructions, sign extension | Assembler and emulator |
| 4 | `p04_structs.c` | Structs, arrays of structs, passing by pointer, `const` | Warps and threads (Phase 4) |
| 5 | `p05_pointers.c` | Pointer parameters, out-parameters, pointer arithmetic, `NULL` | Everywhere |
| 6 | `p06_stack_machine.c` | `enum`, `switch`, a fetch-execute loop, error handling | Emulator core (Phase 2) |
| 7 | `p07_strings.c` | `strtok`, `strtol`, `strchr`, trimming, validating input | Assembler (Phase 3) |
| 8 | `p08_files.c` | `fopen`, `fgets`, `fprintf`, error messages with line numbers | Assembler (Phase 3) |
| 9 | `p09_memory.c` | `malloc`, `realloc`, `free`, a growable array | Label table (Phase 3) |
| 10 | `p10_mini_assembler/` | Splitting code into `.c`/`.h` files, everything combined | Phase 3 directly |

Do them in order: later problems reuse code from earlier ones (problem 8 reuses your problem 7 functions, and problem 10 reuses problems 3 and 7).

## When you're done

If problems 1 to 9 pass and you finished the capstone, you know enough C to move on to Phase 1 (theory) and Phase 2 (the emulator). You don't need to memorize anything here; you'll come back to these files as a reference.
