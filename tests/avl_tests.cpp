#include "avl.hpp"
#include "user.hpp"
#include "nlohmann/json.hpp"

#include <algorithm>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#define pt(x) std::cout << x << "\n"

std::vector<User> init_db() {
    std::filesystem::path db_path{"database/users.json"};
    std::ifstream db{db_path};

    if (not db) {
        std::cerr << ">>> Error opening file: " << db_path << "\n";
        exit(EXIT_FAILURE);
    }

    nlohmann::json m_data{};
    try {
        db >> m_data;
    } catch (const nlohmann::json::parse_error& e) {
        std::cerr << ">>> JSON parse error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    }

    std::vector<User> users;
    try {
        users = m_data.get<std::vector<User>>();
    } catch (const nlohmann::json::type_error& e) {
        std::cerr << ">>> JSON type conversion error: " << e.what() << "\n";
        exit(EXIT_FAILURE);
    }

    std::shuffle(users.begin(), users.end(), std::mt19937(std::random_device{}()));
    return users;
}

void insert_test() {
    pt(">>> Testing AVL Tree Insert Method. <<<");
    AVLTree tree;
    std::vector<User> users = init_db();

    pt("\n--- Inserting elements ---");
    for (const auto& user : users) {
        pt("Inserting User ID: " << user.userid << " (Login: " << user.login << ")");
        tree.insert(create_key(user), user);
        tree.print();
        pt("-----------------------------------");
    }
}

void search_test() {
    pt("\n>>> Testing AVL Tree Search Method. <<<");
    AVLTree tree;
    std::vector<User> users = init_db();

    for (size_t i = 0; i < std::min((size_t)5, users.size()); ++i) {
        tree.insert(create_key(users[i]), users[i]);
    }
    pt("\n--- Current Tree for Search Test ---");
    tree.print();
    pt("------------------------------------");

    pt("\n--- Searching for existing users ---");
    if (users.size() >= 2) {
        User* found_user1 = tree.search(create_key(users[0]));
        if (found_user1) {
            pt("Found user ID: " << found_user1->userid << " (Login: " << found_user1->login << ")");
        } else {
            pt("User ID: " << users[0].userid << " not found (ERROR)");
        }

        User* found_user2 = tree.search(create_key(users[1]));
        if (found_user2) {
            pt("Found user ID: " << found_user2->userid << " (Login: " << found_user2->login << ")");
        } else {
            pt("User ID: " << users[1].userid << " not found (ERROR)");
        }
    }

    pt("\n--- Searching for non-existing users ---");
    User* not_found_user = tree.search(-55);
    if (not_found_user) {
        pt("Found user ID: -55 (ERROR)");
    } else {
        pt("User ID: -55 not found (Expected)");
    }
}

void delete_test() {
    pt("\n>>> Testing AVL Tree Delete Method. <<<");
    AVLTree tree;
    std::vector<User> users = init_db();

    pt("\n--- Building Tree for Deletion Test ---");
    for (size_t i = 0; i < std::min((size_t)10, users.size()); ++i) {
        tree.insert(create_key(users[i]), users[i]);
    }
    pt("\n--- Initial Tree for Deletion Test ---");
    tree.print();
    pt("--------------------------------------");

    pt("\n--- Deleting existing elements ---");
    if (users.size() >= 3) {
        value_type key_to_delete1 = create_key(users[0]);
        pt("Deleting User ID: " << key_to_delete1);
        tree.remove(key_to_delete1);
        tree.print();
        pt("-----------------------------------");

        value_type key_to_delete2 = create_key(users[2]);
        pt("Deleting User ID: " << key_to_delete2);
        tree.remove(key_to_delete2);
        tree.print();
        pt("-----------------------------------");
    }

    pt("\n--- Attempting to delete non-existing element ---");
    value_type non_existent_key = -55;
    pt("Deleting User ID: " << non_existent_key);
    tree.remove(non_existent_key);
    tree.print();
    pt("-----------------------------------");
}

int main() {
    pt(">>> AVL tree tests. <<<\n");

    insert_test();
    pt("\n");
    search_test();
    pt("\n");
    delete_test();

    return EXIT_SUCCESS;
}