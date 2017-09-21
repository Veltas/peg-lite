#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include <stddef.h>
#include <stdint.h>
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
  unsigned char prefix;
  unsigned      rule;
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
  bool          is_boring;
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

#endif // GRAMMAR_H_INCLUDED
