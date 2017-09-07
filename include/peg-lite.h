#ifndef VELTAS_PEG_LITE_H_INCLUDED
#define VELTAS_PEG_LITE_H_INCLUDED

void *peg_load_grammar(const char *source);

void peg_free_grammar(void *grammar);

void *peg_parse(const void *grammar, const char *source);

#endif // VELTAS_PEG_LITE_H_INCLUDED
