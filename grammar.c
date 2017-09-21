#include <stdbool.h>
#include <string.h>
#include "stack_alloc.h"

#include "grammar.h"

#define PEG_N_RULES 64
#define PEG_N_TERMINALS 27

static struct grammar peg_grammar;

static inline void
alloc_choices(struct rule *const rule)
{
  rule->choices = calloc(rule->n_choices, sizeof *rule->choices);
}

static inline void
alloc_prefixeds(struct choice *const choice)
{
  choice->prefixeds = choice->n_prefixeds > 0
    ? calloc(choice->n_prefixeds, sizeof *choice->prefixeds)
    : NULL;
}

static inline void
alloc_terminals(struct rule *const rule)
{
  rule->terminals = calloc(rule->n_terminals, sizeof *rule->terminals);
}

static void
assert_peg_grammar_loaded(void)
{
  static bool is_grammar_loaded = false;
  if (!is_grammar_loaded) {
    peg_grammar = (struct grammar){
      .n_rules = PEG_N_RULES,
      .n_terminals = PEG_N_TERMINALS,
      .rules = calloc(PEG_N_RULES * sizeof (struct rule)),
      .terminal_cache = calloc(PEG_N_TERMINALS * sizeof (struct terminal))
    };
    struct rule *rule = peg_grammar.rules;
    rule->type = choice_type;
    rule->name = "Grammar";
    rule->n_choices = 1;
    alloc_choices(rule);
    {
      struct choice *const choice = rule->choices;
      choice->n_prefixeds = 4;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 53;
        ++prefixed;
        prefixed->rule = 2;
        ++prefixed;
        prefixed->rule = 1;
        ++prefixed;
        prefixed->rule = 63;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 2;
        ++prefixed;
        prefixed->rule = 1;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Definition";
    rule->n_choices = 1;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 11;
        ++prefixed;
        prefixed->rule = 33;
        ++prefixed;
        prefixed->rule = 3;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Expression";
    rule->n_choices = 1;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 5;
        ++prefixed;
        prefixed->rule = 3;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 35;
        ++prefixed;
        prefixed->rule = 5;
        ++prefixed;
        prefixed->rule = 4;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Sequence";
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 4;
        ++prefixed;
        prefixed->rule = 5;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Prefix";
    rule->n_choices = 1;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 7;
        ++prefixed;
        prefixed->rule = 8;
        ++prefixed;
        prefixed->rule = 9;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 37;
      }
      ++choice;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 39;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 7;
        ++prefixed;
        prefixed->rule = 8;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Suffix";
    rule->n_choices = 4;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 10;
        ++prefixed;
        prefixed->rule = 41;
      }
      ++choice;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 10;
        ++prefixed;
        prefixed->rule = 43;
      }
      ++choice;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 10;
        ++prefixed;
        prefixed->rule = 45;
      }
      ++choice;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 10;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Primary";
    rule->n_choices = 5;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 11;
        ++prefixed;
        prefixed->prefix = not_prefix;
        prefixed->rule = 33;
      }
      ++choice;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 47;
        ++prefixed;
        prefixed->rule = 3;
        ++prefixed;
        prefixed->rule = 49;
      }
      ++choice;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 15;
      }
      ++choice;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 20;
      }
      ++choice;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 51;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "IDENTIFIER";
    rule->n_choices = 1;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 13;
        ++prefixed;
        prefixed->rule = 12;
        ++prefixed;
        prefixed->rule = 53;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 14;
        ++prefixed;
        prefixed->rule = 12;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = "IdentStart";
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 1;
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = "IdentCont";
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 2;
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "LITERAL";
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 4;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 18;
        ++prefixed;
        prefixed->rule = 16;
        ++prefixed;
        prefixed->rule = 18;
        ++prefixed;
        prefixed->rule = 53;
      }
      ++choice;
      choice->n_prefixeds = 4;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 19;
        ++prefixed;
        prefixed->rule = 17;
        ++prefixed;
        prefixed->rule = 19;
        ++prefixed;
        prefixed->rule = 53;
      }
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->prefix = not_prefix;
        prefixed->rule = 18;
        ++prefixed;
        prefixed->rule = 26;
        ++prefixed;
        prefixed->rule = 16;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->prefix = not_prefix;
        prefixed->rule = 19;
        ++prefixed;
        prefixed->rule = 26;
        ++prefixed;
        prefixed->rule = 17;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 3;
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 4;
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "CLASS";
    rule->n_choices = 1;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 4;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 21;
        ++prefixed;
        prefixed->rule = 22;
        ++prefixed;
        prefixed->rule = 23;
        ++prefixed;
        prefixed->rule = 53;
      }
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 5;
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->prefix = not_prefix;
        prefixed->rule = 23;
        ++prefixed;
        prefixed->rule = 24;
        ++prefixed;
        prefixed->rule = 22;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 6;
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Range";
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 26;
        ++prefixed;
        prefixed->rule = 25;
        ++prefixed;
        prefixed->rule = 26;
      }
      ++choice;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 26;
      }
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 7;
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "Char";
    rule->n_choices = 4;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 27;
      }
      ++choice;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 28;
      }
      ++choice;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 31;
        ++prefixed;
        prefixed->rule = 29;
      }
      ++choice;
      choice->n_prefixeds = 2;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->prefix = not_prefix;
        prefixed->rule = 32;
        ++prefixed;
        prefixed->rule = 57;
      }
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 2;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 8;
      ++terminal;
      *terminal = 9;
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 4;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 8;
      ++terminal;
      *terminal = 10;
      ++terminal;
      *terminal = 11;
      ++terminal;
      *terminal = 11;
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = NULL;
    rule->is_boring = true;
    rule->n_choices = 2;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 1;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 30;
      }
      ++choice;
      alloc_prefixeds(choice);
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 11;
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 2;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 8;
      ++terminal;
      *terminal = 11;
    }
    ++rule;
    rule->type        = terminal_type;
    rule->name        = NULL;
    rule->is_boring   = true;
    rule->n_terminals = 1;
    alloc_terminals(rule);
    {
      unsigned *terminal = rule->terminals;
      *terminal = 8;
    }
    ++rule;
    rule->type      = choice_type;
    rule->name      = "LEFTARROW";
    rule->n_choices = 1;
    alloc_choices(rule);
    {
      struct choice *choice = rule->choices;
      choice->n_prefixeds = 3;
      alloc_prefixeds(choice);
      {
        struct prefixed *prefixed = choice->prefixeds;
        prefixed->rule = 34;
        ++prefixed;
        prefixed->rule = 53;
      }
    }
  }
}

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
}

static struct grammar *
load_peg_grammar(void)
{
  static struct grammar *grammar = 
}

void *
peg_load_grammar(const char source[])
{
}

void
peg_free_grammar(void *grammar)
{
  free_stack_allocator(((struct grammar_holder *)grammar)->allocator);
}
