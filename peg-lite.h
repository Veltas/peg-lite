#ifndef VELTAS_PEG_LITE_H_INCLUDED
#define VELTAS_PEG_LITE_H_INCLUDED

#include <stddef.h>

struct peg_AST {
  struct peg_AST *peg_AST;
};

void *
peg_load_grammar(const char *source);

void
peg_free_grammar(void *grammar);

void
peg_left_recursive(const void *grammar, 

size_t
peg_parse(const void *grammar, const char *source);

struct peg_AST *
peg_load_ast(const void *grammar, const char *source);

void
peg_free_ast(peg_AST *ast);

#endif // VELTAS_PEG_LITE_H_INCLUDED
