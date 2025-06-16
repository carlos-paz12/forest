#ifndef USER_HPP
#define USER_HPP

#include <cstddef> // std::size_t
#include <string>  // std::string

struct User {
  std::size_t id{};
  std::string login{};
  std::string password{};
  std::size_t region{};
};

#endif