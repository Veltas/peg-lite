#ifndef VELTAS_PEG_LITE_H_INCLUDED
#define VELTAS_PEG_LITE_H_INCLUDED

#include <stddef.h>

#if defined _WIN32 || defined __CYGWIN__
  #ifdef BUILDING_DLL
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllexport))
    #else
      #define DLL_PUBLIC __declspec(dllexport)
    #endif
  #else
    #ifdef __GNUC__
      #define DLL_PUBLIC __attribute__ ((dllimport))
    #else
      #define DLL_PUBLIC __declspec(dllimport)
    #endif
  #endif
  #define DLL_LOCAL
#else
  #if __GNUC__ >= 4
    #define DLL_PUBLIC __attribute__ ((visibility ("default")))
    #define DLL_LOCAL  __attribute__ ((visibility ("hidden")))
  #else
    #define DLL_PUBLIC
    #define DLL_LOCAL
  #endif
#endif

struct peg_AST {
  struct peg_AST *peg_AST;
};

typedef void
(*peg_Hook)(
  void *,        // parse_state
  const char [], // rule_name
  size_t,        // rule_parse_start
  size_t         // rule_parse_end, this is SIZE_MAX in reject hooks
);

// Load grammar object, given PEG source definition.
DLL_PUBLIC void *
peg_load_grammar(const char source[]);

// Clean up resources used by a grammar object.
DLL_PUBLIC void
peg_free_grammar(void *grammar);

// For rule_name with 1+2*n child nodes, structure as a left-associative rule.
DLL_PUBLIC void
peg_left_associative(const void *grammar, const char rule_name[]);

// Do not include rule_name in AST (but allow children of this node).
// The root rule may not be boring.
DLL_PUBLIC void
peg_boring(void *grammar, const char rule_name[]);

// Add callback hook to successful parsing of rule_name (not just accept, but
// wherever rule_name is accepted as part of a successful parse).
DLL_PUBLIC void
peg_hook_parse(
  void       *grammar,
  const char rule_name[],
  peg_Hook   hook,
  void       *callback_data
);

// Add callback hook to every time a rule is rejected by the parser.
DLL_PUBLIC void
peg_hook_reject(
  void       *grammar,
  const char rule_name[],
  peg_Hook   hook,
  void       *callback_data
);

// Parses source text, invoking hooks (if any), returns parse success state.
DLL_PUBLIC _Bool
peg_parse(const void *grammar, const char source[]);

// Parses source text and builds an AST from its structure, invoking hooks (if
// any). Returns the built AST.
DLL_PUBLIC struct peg_AST *
peg_load_ast(const void *grammar, const char source[]);

// Frees the resources of the AST after it's been used.
DLL_PUBLIC void
peg_free_ast(struct peg_AST *ast);

// Get the callback_data that was given to the hook registering function within
// the hook.
DLL_PUBLIC void *
peg_callback_data(void *parse_state);

// Get the first non-boring parent rule's name, or NULL if root rule.
DLL_PUBLIC const char *
peg_parent_rule(void *parse_state);

#endif // VELTAS_PEG_LITE_H_INCLUDED
