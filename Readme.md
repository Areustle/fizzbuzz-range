# Fizzbuzz with C++ range-v3 and parameter packs

This is my crack at a flexible fizzbuzz like application with range-v3.

My fizzbuzz extends other range-based fizzbuzz implimentations while adding
support for multiple inputs beyond just "fizz" and "buzz" as well as
variable spacing on word trigger, just in case the requirements change ;).

In writing this I found a peculiar lack of support between ranges and
pack expansion, hence the need for the helper function.  ¯\_(ツ)_/¯.

Requires a C++17 compiler and range-v3. Doesn't work with C++20 ranges because
the latter lack support for views::cycle and views::zip_with.
