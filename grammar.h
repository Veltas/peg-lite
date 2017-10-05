#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>
#include <limits.h>
#include <peg-lite.h>

struct terminal {
  unsigned char map[(1<<CHAR_BIT)/CHAR_BIT];
};

enum {
  and_prefix = 1,
  not_prefix
};

struct prefixed {
  unsigned      rule;
  unsigned char prefix;
};

struct choice {
  unsigned        n_prefixeds;
  struct prefixed *prefixeds;
};

enum {
  choice_type,
  terminal_type
};

struct rule {
  unsigned char type;
  bool          is_boring: 1,
                is_left_associative: 1;
  char          *name;
  union {
    struct {
      unsigned      n_choices;
      struct choice *choices;
    };
    struct {
      unsigned n_terminals;
      unsigned *terminals;
    };
  };
  peg_Hook parse_hook,
           reject_hook;
};

struct grammar {
  unsigned        n_rules;
  unsigned        n_terminals;
  struct rule     *rules;
  struct terminal *terminal_cache;
};

struct grammar_holder {
  void           *allocator;
  struct grammar grammar;
};

DLL_LOCAL struct grammar peg_grammar;

DLL_LOCAL void
assert_peg_grammar_loaded(void);

#endif // GRAMMAR_H_INCLUDED
