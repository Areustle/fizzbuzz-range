/******************************************************************************
 * Fizzbuzz with range-v3
 *
 * Author: Alexander Reustle
 * Date: 2020-12-14
 *
 * This is my crack at a flexible fizzbuzz like application with range-v3.
 *
 * My fizzbuzz extends other range-based fizzbuzz implimentations while adding
 * support for multiple inputs beyond just "fizz" and "buzz" as well as
 * variable spacing on word trigger, just in case the requirements change ;)
 *
 * In writing this I found a peculiar lack of support between ranges and
 * pack expansion, hence the need for the helper function.
 ******************************************************************************/

#include <functional>
#include <iostream>
#include <numeric>
#include <string>
#include <utility>
#include <vector>

#include "range/v3/action/join.hpp"
#include "range/v3/view/cycle.hpp"
#include "range/v3/view/intersperse.hpp"
#include "range/v3/view/iota.hpp"
#include "range/v3/view/take.hpp"
#include "range/v3/view/transform.hpp"
#include "range/v3/view/zip_with.hpp"

using namespace ranges;

using std::pair;
using std::string;
using std::vector;


// fizzbuzz helper function. Given a count (n) and a pack of base vectors
// formatted prior, construct the output range and transform it as a string,
// which is returned.
template <typename... base_vecs>
auto helper(unsigned n, base_vecs&&... bvs) -> string {

  // Expand the pack of all base vectors as infinite ranges with views::cycle.
  // Then zip together with a fold.
  auto rng_fb = views::zip_with([](auto&&... x) { return (x + ...); },
                                (bvs | views::cycle)...);

  // Infinite string of ints starting at 1, as strings!
  auto rng_is = views::iota(1) |
                views::transform([](auto&& x) { return std::to_string(x); });

  // zip the two together. Thus used to return std::max(a, b), but what if a
  // user inputs a string of 0s?
  auto rng = views::zip_with(
      [](auto&& a, auto&& b) { return a == "" ? b : a; }, rng_fb, rng_is);

  // make the range finite and materialize with whitespace delimiters.
  return rng | views::take(n) | views::intersperse(" ") | actions::join;
}


// The Fizzbuzz main function, a compositor around the helper which does all
// the real work.
//
// Takes a count(n) and a pack of (string, count) pairs and returns the fizzbuzz
// string.
template <typename... pairs_of_name_num>
auto fizzbuzz(unsigned n, pairs_of_name_num&&... ps) -> string {
  // Pass vizzbuzz helper the count and formatted base vectors for expansion.
  return helper(n,           // count
                std::invoke( // Create base vectors with empty strings for
                             // count-1 duration, ending in "word",
                             // and expand the pack.
                    [](pair<string, unsigned>&& p) {
                      auto v   = vector<string>(p.second, "");
                      v.back() = p.first;
                      return v;
                    },
                    ps)...);
}

int main() {
  // call fizzbuzz and output string to stdout. input is a count of ints and a
  // sequence of (name, number) pairs. The order of input will be the order of
  // appearance should 2 words collide in divizibility.
  std::cout << fizzbuzz(1000, pair{ "Fizz", 3 }, pair{ "Buzz", 5 }
                        // , pair{ "Cazz", 7 }
                        // , pair{ "Rozz", 11 }
                        )
            << '\n';
}
