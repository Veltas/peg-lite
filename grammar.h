#ifndef GRAMMAR_H_INCLUDED
#define GRAMMAR_H_INCLUDED

#include <stddef.h>
#include <peg-lite.h>

enum {
  no_prefix,
  and_prefix,
  not_prefix
};

struct choice {
  unsigned n_sequents;
  struct {
    unsigned char prefix;
    unsigned rule;
  } sequents[];
};

enum {
  choice_type,
  terminal_type
};

struct rule {
  unsigned char type;

  struct {
    unsigned n_choices;
    struct choice choices[];
  };

  struct {
    unsigned n_terminals;
    struct terminal terminals[];
  };
};

struct grammar {
  unsigned n_rules;
  union rule rules[];
};

#endif // GRAMMAR_H_INCLUDED
