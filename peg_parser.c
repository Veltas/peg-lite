#include <stddef.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>

#include "grammar.h"

#define PEG_N_TERMINALS 27

#define ARR_INIT(basename, compound_literal) \
  .basename = compound_literal, \
  .n_##basename = sizeof (compound_literal) / sizeof (compound_literal)[0]

#define INIT_RULES(...) ARR_INIT(rules, ((struct rule []){__VA_ARGS__}))

#define INIT_CHOICES(...) \
  .type = choice_type, \
  ARR_INIT(choices, ((struct choice []){__VA_ARGS__}))

#define INIT_TERMINALS(...) \
  .type = terminal_type, \
  ARR_INIT(terminals, ((unsigned []){__VA_ARGS__}))

#define INIT_PREFIXEDS(...) \
  ARR_INIT(prefixeds, ((struct prefixed []){__VA_ARGS__}))

// Based on peg-parser-codified.txt, and in turn peg-peg-reduced.peg
DLL_LOCAL struct grammar peg_grammar = {
  .terminal_cache = (struct terminal [PEG_N_TERMINALS]){{{0}}},
  .n_terminals = PEG_N_TERMINALS,
  INIT_RULES(
    {
      .name = "Grammar",
      INIT_CHOICES(
        {INIT_PREFIXEDS({53}, {2}, {1}, {63})}
      )
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({2}, {1})},
        {0}
      )
    },
    {
      .name = "Definition",
      INIT_CHOICES(
        {INIT_PREFIXEDS({11}, {33}, {3})}
      )
    },
    {
      .name = "Expression",
      INIT_CHOICES(
        {INIT_PREFIXEDS({5}, {3})}
      )
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({35}, {5}, {4})},
        {0}
      )
    },
    {
      .name = "Sequence",
      INIT_CHOICES(
        {INIT_PREFIXEDS({4}, {5})},
        {0}
      )
    },
    {
      .name = "Prefix",
      INIT_CHOICES(
        {INIT_PREFIXEDS({7}, {8}, {9})}
      )
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({37})},
        {INIT_PREFIXEDS({39})}
      )
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({7}, {8})},
        {0}
      )
    },
    {
      .name = "Suffix",
      INIT_CHOICES(
        {INIT_PREFIXEDS({10}, {41})},
        {INIT_PREFIXEDS({10}, {43})},
        {INIT_PREFIXEDS({10}, {45})},
        {INIT_PREFIXEDS({10})}
      )
    },
    {
      .name = "Primary",
      INIT_CHOICES(
        {INIT_PREFIXEDS({11}, {33, not_prefix})},
        {INIT_PREFIXEDS({47}, {3}, {49})},
        {INIT_PREFIXEDS({15})},
        {INIT_PREFIXEDS({20})},
        {INIT_PREFIXEDS({51})}
      )
    },
    {
      .name = "IDENTIFIER",
      INIT_CHOICES(
        {INIT_PREFIXEDS({13}, {12}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({14}, {12})},
        {0}
      )
    },
    {
      .name = "IdentStart",
      INIT_TERMINALS(0)
    },
    {
      .name = "IdentCont",
      INIT_TERMINALS(1)
    },
    {
      .name = "LITERAL",
      INIT_CHOICES(
        {INIT_PREFIXEDS({18}, {16}, {18}, {53})},
        {INIT_PREFIXEDS({19}, {17}, {19}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({18, not_prefix}, {26}, {16})},
        {0}
      )
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({19, not_prefix}, {26}, {17})},
        {0}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(2)
    },
    {
      .is_boring = true,
      INIT_TERMINALS(3)
    },
    {
      .name = "CLASS",
      INIT_CHOICES(
        {INIT_PREFIXEDS({21}, {22}, {23}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(4)
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({23, not_prefix}, {24}, {22})},
        {0}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(5)
    },
    {
      .name = "Range",
      INIT_CHOICES(
        {INIT_PREFIXEDS({26}, {25}, {26})},
        {INIT_PREFIXEDS({26})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(6)
    },
    {
      .name = "Char",
      INIT_CHOICES(
        {INIT_PREFIXEDS({27})},
        {INIT_PREFIXEDS({28})},
        {INIT_PREFIXEDS({31}, {29})},
        {INIT_PREFIXEDS({32, not_prefix}, {57})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(7, 8)
    },
    {
      .is_boring = true,
      INIT_TERMINALS(7, 9, 10, 10)
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({30})},
        {0}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(10)
    },
    {
      .is_boring = true,
      INIT_TERMINALS(7, 10)
    },
    {
      .is_boring = true,
      INIT_TERMINALS(7)
    },
    {
      .name = "LEFTARROW",
      INIT_CHOICES(
        {INIT_PREFIXEDS({34}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(11, 6)
    },
    {
      .name = "SLASH",
      INIT_CHOICES(
        {INIT_PREFIXEDS({36}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(12)
    },
    {
      .name = "AND",
      INIT_CHOICES(
        {INIT_PREFIXEDS({38}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(13)
    },
    {
      .name = "NOT",
      INIT_CHOICES(
        {INIT_PREFIXEDS({40}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(14)
    },
    {
      .name = "QUESTION",
      INIT_CHOICES(
        {INIT_PREFIXEDS({42}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(15)
    },
    {
      .name = "STAR",
      INIT_CHOICES(
        {INIT_PREFIXEDS({44}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(16)
    },
    {
      .name = "PLUS",
      INIT_CHOICES(
        {INIT_PREFIXEDS({46}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(17)
    },
    {
      .name = "OPEN",
      INIT_CHOICES(
        {INIT_PREFIXEDS({48}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(18)
    },
    {
      .name = "CLOSE",
      INIT_CHOICES(
        {INIT_PREFIXEDS({50}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(19)
    },
    {
      .name = "DOT",
      INIT_CHOICES(
        {INIT_PREFIXEDS({52}, {53})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(20)
    },
    {
      .name = "Spacing",
      INIT_CHOICES(
        {INIT_PREFIXEDS({58}, {53})},
        {INIT_PREFIXEDS({54}, {53})},
        {0}
      )
    },
    {
      .name = "Comment",
      INIT_CHOICES(
        {INIT_PREFIXEDS({55}, {56}, {60})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(21)
    },
    {
      .is_boring = true,
      INIT_CHOICES(
        {INIT_PREFIXEDS({60, not_prefix}, {57}, {56})},
        {0}
      )
    },
    {
      .name = "Any",
      INIT_TERMINALS(22)
    },
    {
      .name = "Space",
      INIT_CHOICES(
        {INIT_PREFIXEDS({61})},
        {INIT_PREFIXEDS({59})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(23)
    },
    {
      .name = "EndOfLine",
      INIT_CHOICES(
        {INIT_PREFIXEDS({61})},
        {INIT_PREFIXEDS({62})}
      )
    },
    {
      .is_boring = true,
      INIT_TERMINALS(24, 25)
    },
    {
      .is_boring = true,
      INIT_TERMINALS(26)
    },
    {
      .name = "EndOfFile",
      INIT_CHOICES(
        {INIT_PREFIXEDS({57, not_prefix})}
      )
    }
  )
};

static inline void
terminal_insert(struct terminal *const terminal, const unsigned char c)
{
  const size_t i = c/CHAR_BIT;
  terminal->map[i] |= (1 << c%CHAR_BIT);
}

static void
terminal_all(struct terminal *const terminal)
{
  memset(terminal->map, UCHAR_MAX, sizeof terminal->map);
}

static inline bool
terminal_has(struct terminal *const terminal, const unsigned char c)
{
  const size_t i = c/CHAR_BIT;
  return terminal->map[i] & (1 << c%CHAR_BIT);
}

DLL_LOCAL void
assert_peg_grammar_loaded(void)
{
  static bool is_grammar_loaded = false;
  if (!is_grammar_loaded) {
    is_grammar_loaded = true;
    // We only need to assign terminal sets, everything else was done statically
    for (unsigned char c = 'a'; c <= 'z'; ++c) {
      terminal_insert(peg_grammar.terminal_cache    , c);
      terminal_insert(peg_grammar.terminal_cache + 1, c);
    }
    for (unsigned char c = 'A'; c <= 'Z'; ++c) {
      terminal_insert(peg_grammar.terminal_cache    , c);
      terminal_insert(peg_grammar.terminal_cache + 1, c);
    }
    for (unsigned char c = '0'; c <= '9'; ++c)
      terminal_insert(peg_grammar.terminal_cache + 1, c);
    for (unsigned char c = '0'; c <= '2'; ++c)
      terminal_insert(peg_grammar.terminal_cache + 9, c);
    for (unsigned char c = '0'; c <= '7'; ++c)
      terminal_insert(peg_grammar.terminal_cache + 10, c);
    const unsigned singles[][2] = {
      {0, '_'},
      {1, '_'},
      {2, '\''},
      {3, '\"'},
      {4, '['},
      {5, ']'},
      {6, '-'},
      {7, '\\'},
      {8, 'n'},
      {8, 'r'},
      {8, 't'},
      {8, '\''},
      {8, '\"'},
      {8, '['},
      {8, ']'},
      {8, '\\'},
      {11, '<'},
      {12, '/'},
      {13, '&'},
      {14, '!'},
      {15, '?'},
      {16, '*'},
      {17, '+'},
      {18, '('},
      {19, ')'},
      {20, '.'},
      {21, '#'},
      {23, ' '},
      {23, '\t'},
      {23, '\n'},
      {23, '\r'},
      {24, '\r'},
      {25, '\n'},
      {26, '\r'},
      {27, '\n'}
    };
    for (size_t i = 0; i < sizeof singles / 2; ++i)
      terminal_insert(
        peg_grammar.terminal_cache + singles[i][0],
        singles[i][1]
      );
    terminal_all(peg_grammar.terminal_cache + 22);
  }
}
