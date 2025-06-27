#include "forest/utils/rotations.hpp"

#define pt(x) std::cout << x << "\n"

void test_simple_left() {
    pt("== Teste: Rotação simples à esquerda ==");
    TreeNodePtr tree{nullptr};
    User u1{3, "user1", "pass1", 100};
    User u2{2, "user2", "pass2", 200};
    tree = insert(tree, create_key(u1), u1);
    tree = insert(tree, create_key(u2), u2);
    print_tree(tree);
    r_simple_left(tree);
    pt("Após rotação simples à esquerda:");
    print_tree(tree);
}

void test_simple_right() {
    pt("== Teste: Rotação simples à direita ==");
    TreeNodePtr tree{nullptr};
    User u1{1, "user1", "pass1", 100};
    User u2{2, "user2", "pass2", 200};
    tree = insert(tree, create_key(u1), u1);
    tree = insert(tree, create_key(u2), u2);
    print_tree(tree);
    r_simple_right(tree);
    pt("Após rotação simples à direita:");
    print_tree(tree);
}

void test_double_left() {
    pt("== Teste: Rotação dupla à esquerda ==");
    TreeNodePtr tree{nullptr};
    User u1{3, "user1", "pass1", 100};
    User u2{1, "user2", "pass2", 200};
    User u3{2, "user3", "pass3", 300};
    tree = insert(tree, create_key(u1), u1);
    tree = insert(tree, create_key(u2), u2);
    tree = insert(tree, create_key(u3), u3);
    print_tree(tree);
    r_double_left(tree);
    pt("Após rotação dupla à esquerda:");
    print_tree(tree);
}

void test_double_right() {
    pt("== Teste: Rotação dupla à direita ==");
    TreeNodePtr tree{nullptr};
    User u1{1, "user1", "pass1", 100};
    User u2{3, "user2", "pass2", 200};
    User u3{2, "user3", "pass3", 300};
    tree = insert(tree, create_key(u1), u1);
    tree = insert(tree, create_key(u2), u2);
    tree = insert(tree, create_key(u3), u3);
    print_tree(tree);
    r_double_right(tree);
    pt("Após rotação dupla à direita:");
    print_tree(tree);
}

int main() {
    test_simple_left();
    pt("\n");
    test_simple_right();
    pt("\n");
    test_double_left();
    pt("\n");
    test_double_right();
    return 0;
}