#ifndef ___PUNGENT_UTIL_HPP___
#define ___PUNGENT_UTIL_HPP___

#include <boost/optional.hpp>
#include <regex>
#include <type_traits>
#include <utility>
#include <tuple>

namespace pungent
{
namespace util
{
template <typename Iterator>
boost::optional<Iterator> search(
    Iterator start,
    Iterator end,
    const std::regex & r,
    std::regex_constants::match_flag_type = std::regex_constants::match_default)
{
  using maybe_it = boost::optional<Iterator>;
  std::smatch results;
  std::cout << std::string(start, end) << std::endl;
  if (std::regex_search(start, end, results, r)) {
    /* FIXME: match_continuous isn't working, so compare to start */
    auto res = results[0];
    return res.first == start ? maybe_it(results[0].second) : boost::none;
  }
  return boost::none;
}

/* http://www.cppsamples.com/common-tasks/apply-tuple-to-function.html */
template <typename F, typename Tuple, size_t... S>
decltype(auto) apply_tuple_impl(F && fn, Tuple && t, std::index_sequence<S...>)
{
  return std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))...);
}
template <typename F, typename Tuple>
decltype(auto) apply_from_tuple(Tuple && t, F && fn)
{
  constexpr size_t tSize =
      std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
  return apply_tuple_impl(std::forward<F>(fn), std::forward<Tuple>(t),
                          std::make_index_sequence<tSize>());
}

template <typename F, typename Tuple, size_t... S>
decltype(auto)
    transform_tuple_impl(F && fn, Tuple && t, std::index_sequence<S...>)
{
  return std::make_tuple(
      std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t)))...);
}

template <typename F, typename Tuple>
decltype(auto) transform_tuple(Tuple && t, F && fn)
{
  constexpr size_t tSize =
      std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
  return transform_tuple_impl(std::forward<F>(fn), std::forward<Tuple>(t),
                              std::make_index_sequence<tSize>());
}

template <typename F, typename Tuple, size_t... S>
decltype(auto)
    for_each_tuple_impl(F && fn, Tuple && t, std::index_sequence<S...>)
{
  auto l __attribute__((unused)) = {
      (std::forward<F>(fn)(std::get<S>(std::forward<Tuple>(t))), 0)...};
}

template <typename F, typename Tuple>
decltype(auto) for_each_tuple(Tuple && t, F && fn)
{
  constexpr size_t tSize =
      std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
  for_each_tuple_impl(std::forward<F>(fn), std::forward<Tuple>(t),
                      std::make_index_sequence<tSize>());
}
}
}

#endif /* ___PUNGENT_UTIL_HPP___ */
