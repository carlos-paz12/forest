#include "forest/user.hpp"   // User definition
#include <cstdlib>           // EXIT_FAILURE, EXIT_SUCCESS
#include <filesystem>        // std::filesystem::path
#include <fstream>           // std::ifstream
#include <iostream>          // std::cerr, std::cout
#include <nlohmann/json.hpp> // nlohmann::json
#include <vector>            // std::vector
#include <random>            // std::random_device, std::mt19937, std::shuffle
#include "forest/tree.hpp"    //TreeNodePtr basic of tests 

using vec_users = std::vector<User>; //!< Alias for a vector of User objects.

void ramdomize(vec_users &users) {
  std::random_device rd; //<! Random number generator
  std::mt19937 g(rd());  //<! Seed the generator

  std::shuffle(users.begin(), users.end(), g); //<! Shuffle the vector
}

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
   ramdomize(users); //<! Randomize the order of users.

  // [!] Print all usert to debug.
  for (const auto &user : users) {
    std::cout << "Username: " << user.login << ", ID: " << user.userid << '\n';
  }
  TreeNodePtr tree{ nullptr }; //<! Initialize the tree pointer to nullptr.
  //!< Insert each user into the binary search tree.
  for (const auto &user : users) {
    auto key = create_key(user); //<! Create a unique key for the user.
    insert(tree, key, user);      //<! Insert the user into the tree.
  }
  print_tree(tree); //<! Print the tree structure.

  return EXIT_SUCCESS;
}
