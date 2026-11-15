/*
 * Problem 9: Dynamic memory
 * =========================
 * Skills: malloc, realloc, free, ownership ("who frees this?"), growable
 *         arrays, checking for allocation failure.
 *
 * Why it matters: your assembler doesn't know in advance how many labels a
 * program has, so its label table must grow. In Phase 4 you'll also allocate
 * warps and memory based on launch parameters.
 *
 * The AddressSanitizer flags in the Makefile will catch out-of-bounds
 * accesses and use-after-free bugs here, so read its reports carefully.
 *
 * Run with:  make p09_memory
 */
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include "check.h"

/* 9a. Allocate an array of n uint32_t holding 0, 1, ..., n-1 and return it.
 *     Return NULL if n <= 0 or malloc fails. The CALLER must free it. */
uint32_t *make_range(int n) {
    // TODO
    (void)n;
    return NULL;
}

/* 9b. Return a newly allocated copy of the string s (caller frees).
 *     Don't use strdup; use malloc + strlen + memcpy (remember the '\0'). */
char *copy_string(const char *s) {
    // TODO
    (void)s;
    return NULL;
}

/* ---- A growable label table: the one your assembler will need ---- */

#define MAX_LABEL_LEN 32

typedef struct {
    char name[MAX_LABEL_LEN];   /* includes the '\0' */
    int address;
} Label;

typedef struct {
    Label *items;   /* heap array with room for `capacity` labels */
    int count;      /* how many are in use */
    int capacity;
} LabelTable;

/* 9c. Start with an empty table: no allocation yet. */
void labels_init(LabelTable *t) {
    // TODO
    (void)t;
}

/* 9d. Return the address of the label called name, or -1 if not found. */
int labels_find(const LabelTable *t, const char *name) {
    // TODO
    (void)t; (void)name;
    return -1;
}

/* 9e. Add a label. Return 1 on success, or 0 if:
 *       - a label with this name already exists (duplicate labels are an
 *         assembler error),
 *       - the name is too long to fit in name[] with its '\0',
 *       - memory allocation fails.
 *     When the table is full, grow it with realloc: start with capacity 4,
 *     then double it each time.
 *     Careful: assign realloc's result to a temporary first. Why? */
int labels_add(LabelTable *t, const char *name, int address) {
    // TODO
    (void)t; (void)name; (void)address;
    return 0;
}

/* 9f. Free the table's memory and reset it to the empty state. */
void labels_free(LabelTable *t) {
    // TODO
    (void)t;
}

int main(void) {
    uint32_t *r = make_range(5);
    CHECK(r != NULL);
    if (r) {
        CHECK_EQ(r[0], 0);
        CHECK_EQ(r[4], 4);
        free(r);
    }
    CHECK(make_range(0) == NULL);

    const char *original = "loop";
    char *c = copy_string(original);
    CHECK_STR(c, "loop");
    CHECK(c != original);   /* must be a new copy, not the same pointer */
    free(c);

    LabelTable t;
    labels_init(&t);
    CHECK_EQ(t.count, 0);
    CHECK_EQ(labels_find(&t, "start"), -1);

    CHECK_EQ(labels_add(&t, "start", 0), 1);
    CHECK_EQ(labels_add(&t, "loop", 3), 1);
    CHECK_EQ(labels_add(&t, "loop", 9), 0);   /* duplicate */
    CHECK_EQ(labels_find(&t, "loop"), 3);
    CHECK_EQ(labels_find(&t, "start"), 0);
    CHECK_EQ(labels_add(&t, "this_label_name_is_way_too_long_to_fit", 1), 0);

    /* Force several rounds of growth. */
    char name[16];
    int all_added = 1;
    for (int i = 0; i < 100; i++) {
        snprintf(name, sizeof name, "L%d", i);
        if (!labels_add(&t, name, 100 + i)) all_added = 0;
    }
    CHECK(all_added);
    CHECK_EQ(t.count, 102);
    CHECK(t.capacity >= t.count);
    CHECK_EQ(labels_find(&t, "L0"), 100);
    CHECK_EQ(labels_find(&t, "L99"), 199);
    CHECK_EQ(labels_find(&t, "loop"), 3);   /* old entries survive realloc */

    labels_free(&t);
    CHECK(t.items == NULL);
    CHECK_EQ(t.count, 0);

    return report("p09_memory");
}
