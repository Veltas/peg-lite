Packrat-normalized PEG form
===========================

An explanation of the 'normalized form' which is used internally in the library.

Transformations are applied to the full PEG grammar to reduce it to a form that
can be stored/processed easier.

PEG: the input
--------------

In brief, a PEG is a set of named non-terminals, each of which is given a single
definition which is a combination of:

* String literals of length 0+.
* A non-terminal.
* Bracketed rules.
* A concatenated sequence.
* An ordered choice (`/`).
* A consume-if-given (`?`).
* A consume-as-many-as-possible (`*`).
* A consume-at-least-one (`+`).
* A non-consuming assumption (`&`).
* A non-consuming forbidden (`!`).

Normalized form: the result
---------------------------

The normalised form is a set of named non-terminals, each of which is either:

* A concatenated sequence of terminal sets.
* An ordered choice of a concatenated sequence of non-terminals, `&` of
  non-terminals, `!` of non-terminals.

Reduction algorithm
-------------------

Operator removal:

* `a?` becomes `(a /)`.
* `a*` becomes new NT, with rule `(a newNTname /)`.
* `a+` creates new NT, becoming `(a newNTName)`, with rule `(a newNTname /)`.

Simplify:

* Repeated direct applications of `&` and `!` become `&` or `!` (to calculate:
  `&` is worth 2, `!` is worth 1, total odd then `!`, total even then `&`).
* Bracketed ordered choices of `'terminal'`, `NT`, `(&NT)`, `(!NT)` are
  expanded, e.g. `a/(b/c)/d` becomes `a/b/c/d`.
* Top-level brackets and immediate nested brackets are removed.

Bracket removal:

* Brackets that weren't expanded are now replaced with a new NT containing the
  bracketed part.

Terminal removal:

* Terminals that are part of an ordered choice or a concatentated sequence with
  non-terminals or `&`/`!` prefixed non-terminals are removed.
