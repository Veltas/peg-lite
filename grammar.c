#include "stack_alloc.h"

#include "grammar.h"

static struct grammar *
load_peg_grammar(void)
{
}

void *
peg_load_grammar(const char source[])
{
}

void
peg_free_grammar(void *grammar)
{
  free_stack_allocator(((struct grammar_holder *)grammar)->stack_allocator);
}
