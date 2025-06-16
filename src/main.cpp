#include <cstdlib>
#include <fstream>
#include <iostream>

#include <nlohmann/json.hpp>

using json = nlohmann::json;

int main() {
  std::cout << "Implementation of the AVL and Black-Red trees.\n";

  json j;
  std::ifstream ifs("database/users.json");
  ifs >> j;

  std::ofstream ofs("pretty.json");
  ofs << std::setw(4) << j << std::endl;

  std::cout << j;

  return EXIT_SUCCESS;
}