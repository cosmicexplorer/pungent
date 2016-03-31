pungent
=======

A parser generator, because the world really needs another one of these.

# Goals, and what current tools don't accomplish them
- integrate with c++ and allow re-entrance
    - flex/bison doesn't care at all about this (super hard to get parser into its own namespace)
    - use native c++ regexps, lambdas, and operator overloading, for example
- create parsers without having to know obscure incantations
    - `boost::spirit` requires skinning >= 3 goats
    - same with bison, although at least their docs are alright
- parse directly into objects
    - boost::spirit does this pretty well, although you have to call things like `BOOST_FUSION_ADAPT_STRUCT` and it feels very hacky and you have to do this for every struct you want to use in your parser
- support EBNF-like grammar
    - everyone does this but it's important

# Things that aren't goals
- speed
- language formalisms

# TODO
- add ebnf syntax
    - can use c++'s `operator*`, `operator+`, etc and overload for `Token` and `Nonterminal` classes
    - for all numerical quantifiers, return vector of `Out` instead of just out
    - add `*`, `+`, `{,}`, `?` somehow

[Jison](https://github.com/zaach/jison) actually does this extremely well, but I want to use C++ for my compiler so I'm kinda out of luck.
