#ifndef ___PUNGENT_PUNGENT_HPP___
#define ___PUNGENT_PUNGENT_HPP___

#include "utils.hpp"

#include <stdexcept>

namespace pungent
{
struct Token {
  std::regex reg;
  const std::regex ws;
  Token(const std::string & s)
      : reg(std::regex(std::string("^") + s)), ws("\\s*")
  {
  }

  template <typename Iterator>
  boost::optional<Iterator>
      try_parse(Iterator start, Iterator end, bool respect_ws = false)
  {
    Iterator after_ws =
        respect_ws ? start : util::search(start, end, ws).value_or(start);
    return util::search(after_ws, end, reg);
  }
};

template <typename Out>
struct Nonterminal {
  /* template <typename Iterator> */
  /*     std::function < Out() */
};

/* template <typename Out, typename... Args> */
/* struct Rule : public Nonterminal<Out> { */
/*   std::tuple<Args...> sentential; */
/*   std::function<Out(Args...)> f; */

/*   template <typename Iterator> */
/*   struct result_type { */
/*     Iterator end; */
/*     Out result; */
/*   }; */
/*   template <typename Iterator> */
/*   using maybe = boost::optional<result_type<Iterator>>; */

/*   struct parse_error : public std::runtime_error { */
/*     parse_error(const std::string & s = "") : std::runtime_error(s) */
/*     { */
/*     } */
/*   }; */

/*   template <typename Iterator> */
/*   maybe<Iterator> invoke(Iterator start, Iterator end) */
/*   { */
/*     try { */
/*       auto results = hana::transform(sentential, [&](auto el) { */
/*         auto res = el.try_parse(start, end); */
/*         if (!res) { */
/*           throw parse_error(); */
/*         } */
/*         auto st  = res->end; */
/*         auto out = res->result; */
/*         start    = st; */
/*         return out; */
/*       }); */
/*     } catch (parse_error &) { */
/*       return boost::none; */
/*     } */
/*     return return_type<Iterator>{start, util::apply_from_tuple()}; */
/*   } */

/*   template <typename... OtherArgs> */
/*   Nonterminal<Out> operator|(const Rule<Out, OtherArgs...> & rhs) */
/*   { */
/*   } */
/* }; */

template <typename Out, typename Func, typename... Args>
Out make_fun(Func f, Args... args)
{
  return f(args...);
}

/* template <typename Out, typename Args...> */
/* class Nonterminal { */
/*   std::vector<Rule<Func>> productions; */

/* public: */
/*   Nonterminal(); */

/*   Out parse(const std::string &) const; */
/* }; */
}

#endif /* ___PUNGENT_PUNGENT_HPP___ */
