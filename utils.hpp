#ifndef ___PUNGENT_UTILS_HPP___
#define ___PUNGENT_UTILS_HPP___

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
boost::optional<Iterator>
    search(Iterator start, Iterator end, const std::regex & r)
{
  using maybe_it = boost::optional<Iterator>;
  std::smatch results;
  return std::regex_search(start, end, results, r) ? maybe_it(results[0].second)
                                                   : boost::none;
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
  std::size_t constexpr tSize =
      std::tuple_size<typename std::remove_reference<Tuple>::type>::value;
  return apply_tuple_impl(std::forward<F>(fn), std::forward<Tuple>(t),
                          std::make_index_sequence<tSize>());
}

template <typename F, typename Tuple>
decltype(auto) transform_tuple(Tuple && t, F && fn)
{
  
}
}
}

#endif /* ___PUNGENT_UTILS_HPP___ */
