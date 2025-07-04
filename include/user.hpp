#ifndef USER_HPP
#define USER_HPP

#include "nlohmann/json.hpp" // NLOHMANN_DEFINE_TYPE_INTRUSIVE
#include <cstddef>           // std::size_t
#include <string>            // std::string

/// @brief Structure that represents a system user.
struct User
{
  std::size_t userid{};   //!< User's unique identifier.
  std::string login{};    //!< User's login name.
  std::string password{}; //!< User's password.
  std::size_t region{};   //!< Region code associated with the user.

  /**
   * @brief Performs automatic mapping between User and JSON
   * (serialization/deserialization).
   *
   * This macro defines how the attributes of the User struct are converted
   * to JSON and read from JSON using the nlohmann::json library.
   */
  NLOHMANN_DEFINE_TYPE_INTRUSIVE(User, userid, login, password, region)
};

#endif //!< USER_HPP
