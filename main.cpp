#include <iostream>
#include "pungent.hpp"

#include <string>

int main()
{
  using namespace pungent;
  Token plus("\\+");
  Token minus("\\-");
  Token times("\\*");
  Token div("/");
  Token num("[0-9]+");
  Token open_paren("\\(");
  Token close_paren("\\)");

  std::string s(")a");
  std::string a(*close_paren.try_parse(s.cbegin(), s.cend()), s.cend());
  std::cout << a << std::endl;

  util::apply_from_tuple(std::make_tuple(1, 2), [](auto a, auto b) {
    std::cout << a << "," << b << std::endl;
  });

  auto res = util::transform_tuple(std::make_tuple(1, 2),
                                   [](auto a) { return a + 1; });
  util::apply_from_tuple(
      res, [](auto a, auto b) { std::cout << a << ',' << b << std::endl; });

  std::cout << make_fun<int>([](auto a, auto b) { return a + b; }, 1, 2)
            << std::endl;

  run_tup(std::make_tuple(34, 45));

  /* Nonterminal<int> E; */
  /* E = make_rule({num}, [](auto num) { return std::stoi(num); }) | */
  /*     make_rule({open_paren, E, close_paren}, */
  /*               [](auto, auto e, auto) { return e; }) | */
  /*     make_rule({E, times, E}, [](auto a, auto, auto b) { return a * b; }) |
   */
  /*     make_rule({E, div, E}, [](auto a, auto, auto b) { return a / b; }) | */
  /*     make_rule({E, plus, E}, [](auto a, auto, auto b) { return a + b; }) |
   */
  /*     make_rule({E, minus, E}, [](auto a, auto, auto b) { return a - b; });
   */
  /* std::cout << E.parse("2 + 3") << std::endl; */
}
