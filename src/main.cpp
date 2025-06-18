#include "forest/user.hpp"   // User definition
#include <cstdlib>           // EXIT_FAILURE, EXIT_SUCCESS
#include <filesystem>        // std::filesystem::path
#include <fstream>           // std::ifstream
#include <iostream>          // std::cerr, std::cout
#include <nlohmann/json.hpp> // nlohmann::json
#include <vector>            // std::vector

int main() {
  std::cout << ">>> Implementation of the AVL and Black-Red trees. <<<\n\n";

  //!< Define the path to the user database file.
  std::filesystem::path db_path{"database/users.json"};
  //!< Open the file for reading.
  std::ifstream db{db_path};

  // [!] Check if the file was opened successfully.
  if (not db) {
    std::cerr << ">>> Error opening file: " << db_path << "\n";
    return EXIT_FAILURE;
  }

  // [!] Attempt to parse the JSON data from the file.
  nlohmann::json m_data{};
  try {
    db >> m_data;
  } catch (const nlohmann::json::parse_error &e) {
    std::cerr << ">>> JSON parse error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  // [!] Attempt to convert the JSON data to a vector of User objects.
  std::vector<User> users{};
  try {
    users = m_data.get<std::vector<User>>();
  } catch (const nlohmann::json::type_error &e) {
    std::cerr << ">>> JSON type conversion error: " << e.what() << "\n";
    return EXIT_FAILURE;
  }

  // [!] Print all usert to debug.
  for (const auto &user : users) {
    std::cout << "Username: " << user.login << ", ID: " << user.userid << '\n';
  }

  return EXIT_SUCCESS;
}
