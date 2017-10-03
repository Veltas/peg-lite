#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "stack_alloc.h"

#include "grammar.h"

static void
flat_size_choice_contents(size_t *const result, const struct rule *const rule)
{
  stack_acc_size(result, rule->n_choices * sizeof *rule->choices);
  for (size_t j = 0; j < rule->n_choices; ++j) {
    const struct choice *const choice = rule->choices + j;
    stack_acc_size(result, choice->n_prefixeds * sizeof *choice->prefixeds);
  }
}

static void
flat_size_terminal_contents(size_t *const result, const struct rule *const rule)
{
  stack_acc_size(result, rule->n_terminals * sizeof *rule->terminals);
}

static void
flat_size_rules(size_t *const result, const struct grammar *const grammar)
{
  stack_acc_size(result, grammar->n_rules * sizeof *grammar->rules);
  for (size_t i = 0; i < grammar->n_rules; ++i) {
    const struct rule *const rule = grammar->rules + i;
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
flatten_grammar(const struct grammar *const grammar)
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
frag_grammar_free(struct grammar *const grammar)
{
  const struct rule *const end = grammar->rules + grammar->n_rules;
  for (struct rule *rule = grammar->rules; rule != end; ++rule) {
    if (rule->type == choice_type) {
      const struct choice *const end = rule->choices + rule->n_choices;
      for (struct choice *choice = rule->choices; choice != end; ++choice)
        free(choice->prefixeds);
      free(rule->choices);
    }
    else free(rule->terminals);
  }
  free(grammar->rules);
  free(grammar->terminal_cache);
}

DLL_PUBLIC void *
peg_load_grammar(const char source[const])
{
  struct grammar grammar_store = {0};
  struct grammar *const grammar = &grammar_store;
  //TODO
  struct grammar_holder *const holder = flatten_grammar(grammar);
  frag_grammar_free(grammar);
  return holder;
}

DLL_PUBLIC void
peg_free_grammar(void *const grammar)
{
  free_stack_allocator(((struct grammar_holder *)grammar)->allocator);
}
