#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "stack_alloc.h"
#include "xarray.h"
#include "set.h"

#include "grammar.h"

#define UNUSED(x) ((void)(sizeof (x)))

static void
flat_size_choice_contents(size_t *const result, struct rule *const rule)
{
  rule->n_choices = xarray_size(rule->choices);
  stack_acc_size(result, rule->n_choices * sizeof *rule->choices);
  for (size_t j = 0; j < rule->n_choices; ++j) {
    struct choice *const choice = rule->choices + j;
    choice->n_prefixeds = xarray_size(choice->prefixeds);
    stack_acc_size(result, choice->n_prefixeds * sizeof *choice->prefixeds);
  }
}

static void
flat_size_terminal_contents(size_t *const result, struct rule *const rule)
{
  rule->n_terminals = xarray_size(rule->terminals);
  stack_acc_size(result, rule->n_terminals * sizeof *rule->terminals);
}

static void
flat_size_rules(size_t *const result, struct grammar *const grammar)
{
  grammar->n_rules = xarray_size(grammar->rules);
  stack_acc_size(result, grammar->n_rules * sizeof *grammar->rules);
  for (size_t i = 0; i < grammar->n_rules; ++i) {
    struct rule *const rule = grammar->rules + i;
    stack_acc_size(result, strlen(rule->name) + 1);
    if (rule->type == choice_type)
      flat_size_choice_contents(result, rule);
    else
      flat_size_terminal_contents(result, rule);
  }
}

static void
flat_size_cache(size_t *const result, struct grammar *const grammar)
{
  grammar->n_terminals = xarray_size(grammar->terminal_cache);
  stack_acc_size(
    result, grammar->n_terminals * sizeof *grammar->terminal_cache
  );
}

static size_t
flat_size(struct grammar *const grammar)
{
  size_t result = 0;
  stack_acc_size(&result, sizeof (struct grammar_holder));
  flat_size_rules(&result, grammar);
  flat_size_cache(&result, grammar);
  return result;
}

static void
flatten_grammar_prefixed_contents(
  struct choice *const choice,
  void *const          allocator)
{
  struct prefixed *const prefixeds =
    stack_alloc(allocator, choice->n_prefixeds * sizeof *prefixeds);
  memcpy(prefixeds, choice->prefixeds, choice->n_prefixeds * sizeof *prefixeds);
  choice->prefixeds = prefixeds;
}

static void
flatten_grammar_choice_contents(
  struct rule *const rule,
  void *const        allocator)
{
  struct choice *const choices =
    stack_alloc(allocator, rule->n_choices * sizeof *choices);
  memcpy(choices, rule->choices, rule->n_choices * sizeof *choices);
  for (size_t i = 0; i < rule->n_choices; ++i)
    flatten_grammar_prefixed_contents(choices + i, allocator);
  rule->choices = choices;
}

static void
flatten_grammar_terminal_contents(
  struct rule *const rule,
  void *const        allocator)
{
  unsigned *const terminals =
    stack_alloc(allocator, rule->n_terminals * sizeof *terminals);
  memcpy(terminals, rule->terminals, rule->n_terminals * sizeof *terminals);
  rule->terminals = terminals;
}

static void
flatten_grammar_rules(
  struct grammar *const grammar,
  void *const           allocator)
{
  struct rule *const rules =
    stack_alloc(allocator, grammar->n_rules * sizeof *rules);
  memcpy(rules, grammar->rules, grammar->n_rules * sizeof *rules);
  const struct rule *const end = rules + grammar->n_rules;
  for (struct rule *rule = rules; rule != end; ++rule) {
    if (!rule->type) flatten_grammar_choice_contents(rule, allocator);
    else flatten_grammar_terminal_contents(rule, allocator);
  }
  grammar->rules = rules;
}

static void
flatten_grammar_cache(
  struct grammar *const grammar,
  void *const           allocator)
{
  struct terminal *const terminals =
    stack_alloc(allocator, grammar->n_terminals * sizeof *terminals);
  memcpy(
    terminals, grammar->terminal_cache, grammar->n_terminals * sizeof *terminals
  );
  grammar->terminal_cache = terminals;
}

static struct grammar_holder *
flatten_grammar(struct grammar *const grammar)
{
  void *const allocator = load_stack_allocator(flat_size(grammar));
  struct grammar_holder *const holder = stack_alloc(allocator, sizeof *holder);
  holder->allocator = allocator;
  holder->grammar = *grammar;
  flatten_grammar_rules(&holder->grammar, allocator);
  flatten_grammar_cache(&holder->grammar, allocator);
  return holder;
}

static void
free_frag_grammar(struct grammar *const grammar)
{
  const struct rule *const end = grammar->rules + grammar->n_rules;
  for (struct rule *rule = grammar->rules; rule != end; ++rule) {
    if (rule->type == choice_type) {
      const struct choice *const end = rule->choices + rule->n_choices;
      for (struct choice *choice = rule->choices; choice != end; ++choice)
        free_xarray(choice->prefixeds);
      free_xarray(rule->choices);
    }
    else free_xarray(rule->terminals);
  }
  free_xarray(grammar->rules);
  free_xarray(grammar->terminal_cache);
}

DLL_PUBLIC void *
peg_load_grammar(const char source[const])
{
  struct grammar *const grammar = &(struct grammar){0};
  UNUSED(source[0]); // FIXME
  //TODO
  struct grammar_holder *const holder = flatten_grammar(grammar);
  free_frag_grammar(grammar);
  return holder;
}

DLL_PUBLIC void
peg_free_grammar(void *const grammar)
{
  struct grammar_holder *const holder = grammar;
  free_set(holder->grammar.rule_numbers);
  free_stack_allocator(holder->allocator);
}
