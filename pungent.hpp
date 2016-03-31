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
};

template <typename... Args>
void run_tup(std::tuple<Args...> t)
{
  util::for_each_tuple(t, [](auto el) { std::cout << el << std::endl; });
}

struct parse_error : public std::runtime_error {
  parse_error(const std::string & s = "") : std::runtime_error(s)
  {
  }
};

template <typename Func, typename... Args>
struct Rule {
  std::tuple<Args...> sentential;
  Func f;
  using out_type = typename std::result_of<Func>::type;

  Rule(std::tuple<Args...> tup, Func fun) : sentential(tup), f(fun)
  {
  }

  template <typename _Func, typename... _Args>
  static Rule<_Func, _Args...> make_rule(std::tuple<_Args...> tup, _Func fun)
  {
    return Rule<_Func, _Args...>(tup, fun);
  }

  template <typename Iterator>
  struct return_type {
    Iterator end;
    out_type result;
  };
  template <typename Iterator>
  using maybe = boost::optional<return_type<Iterator>>;

  template <typename Iterator>
  maybe<Iterator> invoke(Iterator start, Iterator end)
  {
    try {
      auto results = util::transform_tuple(sentential, [&](auto el) {
        auto res = el.try_parse(start, end);
        if (!res) {
          throw parse_error();
        }
        auto st  = res->end;
        auto out = res->result;
        start    = st;
        return out;
      });
      return return_type<Iterator>{start, util::apply_from_tuple(results, f)};
    } catch (parse_error &) {
      return boost::none;
    }
  }
};

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
