#ifndef ___PUNGENT_PUNGENT_HPP___
#define ___PUNGENT_PUNGENT_HPP___

#include "util.hpp"

#include <boost/variant.hpp>
#include <stdexcept>

namespace pungent
{
struct Token {
  std::regex reg;
  const std::regex ws;
  Token(const std::string & s) : reg(std::regex(s)), ws("\\s*")
  {
  }

  template <typename Iterator>
  boost::optional<Iterator>
      try_parse(Iterator start, Iterator end, bool respect_ws = false)
  {
    Iterator after_ws = respect_ws ? start : *util::search(start, end, ws);
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

template <typename Func, typename... Args, typename Func2, typename... Args2>
struct Rule;

template <typename Iterator, typename Out>
struct posn_and_result {
  Iterator posn;
  Out result;
};
template <typename Iterator, typename Func, typename... Args>
using result_or_next = boost::variant<
    posn_and_result<Iterator, typename std::result_of<Func>::type>,
    boost::optional<Rule<Func, Args...>>>;

template <typename Func, typename... Args, typename Func2, typename... Args2>
struct Rule {
  std::tuple<Args...> sentential;
  using Out = typename std::result_of<Func>::type;
  Func f;

  using maybe_next_rule = boost::optional<Rule<Func2, Args2...>>;
  maybe_next_rule backup;

  Rule(std::tuple<Args...> tup, Func fun, maybe_next_rule r)
      : sentential(tup), f(fun), backup(r)
  {
  }

  template <typename _Func,
            typename... _Args,
            typename _Func2,
            typename... _Args2>
  static Rule<_Func, _Args...> make_rule(
      std::tuple<_Args...> tup,
      _Func fun,
      typename Rule<_Func2, Args2...>::maybe_next_rule r = boost::none)
  {
    return Rule<_Func, _Args...>(tup, fun, r);
  }

  template <typename Iterator>
  using return_type = result_or_next<Iterator, Func2, Args2...>;

  template <typename Iterator>
  return_type<Iterator> invoke(Iterator start, Iterator end)
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
      return return_type<Iterator>(posn_and_result<Iterator, Out>{
          start, util::apply_from_tuple(results, f)});
    } catch (parse_error &) {
      return backup;
    }
  }
};

template <typename Func1, typename Func2, typename... Args1, typename... Args2>
decltype(auto) operator|(const Rule<Func1, Args1...> & lhs,
                         const Rule<Func2, Args2...> & rhs)
{
  using maybe_next_rule = typename Rule<Func1, Args1...>::maybe_next_rule;
  return make_rule(lhs.sentential, lhs.f, maybe_next_rule(rhs));
}

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
