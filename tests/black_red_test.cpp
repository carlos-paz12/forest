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

void insert_test()
{
  std::cout << ">>> Testing insert method. <<<\n\n";
  redblacktree arvore;
  User usuario;

  arvore.insert(15, usuario);
  std::cout << '\n';

  arvore.insert(8, usuario);
  std::cout << '\n';

  arvore.insert(30, usuario);
  std::cout << '\n';

  arvore.insert(12, usuario);
  std::cout << "\n";

  arvore.insert(10, usuario);
  std::cout << "\n";

  arvore.insert(32, usuario);
  std::cout << "\n";

  arvore.insert(38, usuario);
  std::cout << "\n";
}

void delete_test()
{
  std::cout << ">>> Testing delete method. <<<\n\n";
  redblacktree arvore;
  User usuario;

  // arvore.deletenode(8, usuario); // ta dando seg fault
  // std::cout << '\n';
}

int main()
{
  std::cout << ">>> Black-Red tree tests. <<<\n\n";

  insert_test();
  delete_test();

  return EXIT_SUCCESS;
}