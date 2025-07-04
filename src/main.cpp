//=== External includes ===
// JSON parsing library (from nlohmann)
#include "nlohmann/json.hpp" // nlohmann::json

//=== Internal includes ===
// Project-specific includes
#include "black_red.hpp"
#include "tree_example.hpp" // TreeNodePtr basic of tests
#include "user.hpp"         // User definition

//=== C++ Standard Library includes ===
#include <cstdlib>    // EXIT_FAILURE, EXIT_SUCCESS
#include <filesystem> // std::filesystem::path
#include <fstream>    // std::ifstream
#include <iostream>   // std::cerr, std::cout
#include <random>     // std::random_device, std::mt19937, std::shuffle
#include <vector>     // std::vector

std::vector<User> init_db()
{
  //!< Define the path to the user database file.
  std::filesystem::path db_path{ "database/users.json" };
  //!< Open the file for reading.
  std::ifstream db{ db_path };

  // [!] Check if the file was opened successfully.
  if (not db)
  {
    std::cerr << ">>> Error opening file: " << db_path << "\n";
    exit(EXIT_FAILURE);
  }

  // [!] Attempt to parse the JSON data from the file.
  nlohmann::json m_data{};
  try
  {
    db >> m_data;
  }
  catch (const nlohmann::json::parse_error& e)
  {
    std::cerr << ">>> JSON parse error: " << e.what() << "\n";
    exit(EXIT_FAILURE);
  }

  std::vector<User> users;
  try
  {
    users = m_data.get<std::vector<User>>();
  }
  catch (const nlohmann::json::type_error& e)
  {
    std::cerr << ">>> JSON type conversion error: " << e.what() << "\n";
    exit(EXIT_FAILURE);
  }

  // [!] Shuffle the list of users randomly using a secure seed
  std::shuffle(users.begin(), users.end(), std::mt19937(std::random_device{}()));

  return std::move(users);
}

void testandorbtree()
{
  redblacktree arvore;
  User usuario;
  arvore.insert(15, usuario);
  arvore.printtree();
  arvore.insert(8, usuario);
  arvore.printtree();
  arvore.insert(30, usuario);
  arvore.printtree();
  arvore.insert(12, usuario);
  std::cout << "\n\n";
  arvore.printtree();
  /*arvore.insert(13, usuario);*/ // <- esse caso funciona
  std::cout << "\n\n\ninserindo 10\n";
  arvore.insert(10, usuario); // esse caso nao funciona
  // o erro eh nas rotacoes, em um momento o node toma o valor de node->dad->key por alguma ra:(
  std::cout << "\n\n";
  arvore.printtree();
}

int main()
{
  std::cout << ">>> Implementation of the AVL and Black-Red trees. <<<\n\n";

  // [!] Attempt to convert the JSON data to a vector of User objects.
  std::vector<User> users{ init_db() };

  testandorbtree();

  return EXIT_SUCCESS;
}