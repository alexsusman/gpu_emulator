# Practice problems Makefile
#
#   make p03_encoding    build and run one problem
#   make p10             build and run the capstone
#   make all             build and run everything
#   make clean           delete build output
#
# Run these from inside the practice_problems folder.

CC = clang
CFLAGS = -std=c11 -Wall -Wextra -g -fsanitize=address,undefined

PROBLEMS = p01_integers p02_bits p03_encoding p04_structs p05_pointers \
           p06_stack_machine p07_strings p08_files p09_memory

P10_SRC = $(wildcard p10_mini_assembler/*.c)
P10_HDR = $(wildcard p10_mini_assembler/*.h)

.PHONY: all clean p10 $(PROBLEMS)

all:
	@for p in $(PROBLEMS) p10; do $(MAKE) --no-print-directory $$p; echo; done

# "make p03_encoding" builds bin/p03_encoding, then runs it.
$(PROBLEMS): %: bin/%
	@./bin/$@

bin/%: %.c check.h | bin
	$(CC) $(CFLAGS) $< -o $@

p10: bin/p10
	@./bin/p10

bin/p10: $(P10_SRC) $(P10_HDR) check.h | bin
	$(CC) $(CFLAGS) -I. $(P10_SRC) -o $@

bin:
	mkdir -p bin

clean:
	rm -rf bin p08_output.txt
