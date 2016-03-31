#include <iostream>
#include <boost/hana/assert.hpp>
#include <boost/hana/equal.hpp>
#include <boost/hana/for_each.hpp>
#include <boost/hana/integral_constant.hpp>
#include <boost/hana/transform.hpp>
#include <boost/hana/tuple.hpp>
#include <string>
namespace hana = boost::hana;
using namespace hana::literals;
struct Fish {
  std::string name;
};
struct Cat {
  std::string name;
};
struct Dog {
  std::string name;
};
int main()
{
  hana::tuple<Fish, Cat, Dog> animals{{"Nemo"}, {"Garfield"}, {"Snoopy"}};
  animals[0_c].name =
      "Moby Dick"; // can modify elements in place, like std::tuple
  auto names = hana::transform(animals, [](auto a) { return a.name; });
  BOOST_HANA_RUNTIME_CHECK(names ==
                           hana::make_tuple("Moby Dick", "Garfield", "Snoopy"));
  hana::for_each(names, [&](auto a) { std::cout << a << std::endl; });
}
