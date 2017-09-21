#include <stdbool.h>
#include <string.h>
#include "stack_alloc.h"

#include "grammar.h"

static void
flat_size_choice_contents(size_t *const result, const struct rule *const rule)
{
  stack_acc_size(result, rule->n_choices * sizeof *rule->choices);
  for (unsigned j = 0; j < rule->n_choices; ++j) {
    struct choice *const choice = rule->choices[j];
    stack_acc_size(result, choice->n_prefixeds * sizeof *choice->prefixed);
  }
}

static void
flat_size_terminal_contents(size_t *const result, const struct rule *const rule)
{
  stack_acc_size(result, rule->n_terminals * sizeof *rule->terminals)
}

static void
flat_size_rules(size_t *const result, const struct grammar *const grammar)
{
  stack_acc_size(result, grammar->n_rules * sizeof *rules);
  for (unsigned i = 0; i < grammar->n_rules; ++i) {
    struct rule *const rule = grammar->rules + i;
    stack_acc_size(result, strlen(rule->name) + 1);
    if (rule->type == choice_type)
      flat_size_choice_contents(result, rule);
    else
      flat_size_terminal_contents(result, rule);
  }
}

static void
flat_size_cache(size_t *const result, const struct grammar *const grammar)
{
  stack_acc_size(
    result, grammar->n_terminals * sizeof *grammar->terminal_cache
  );
}

static size_t
flat_size(const struct grammar *const grammar)
{
  size_t result = 0;
  stack_acc_size(&result, sizeof (struct grammar_holder));
  flat_size_rules(&result, grammar);
  flat_size_cache(&result, grammar);
  return result;
}

static struct grammar_holder *
flatten_grammar(struct grammar *grammar)
{
  void *const allocator = load_stack_allocator(flat_size(grammar));
  struct grammar_holder *const holder = stack_alloc(allocator, sizeof *holder);
  holder->allocator = allocator;
  holder->grammar = grammar;
  //TODO
}

void *
peg_load_grammar(const char source[])
{
  //TODO
}

void
peg_free_grammar(void *grammar)
{
  free_stack_allocator(((struct grammar_holder *)grammar)->allocator);
}
