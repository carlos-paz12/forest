#include "rotations.hpp"
#include "tree_example.hpp"
#include "user.hpp"
#include <bits/stdc++.h>

enum class colors
{
  red,
  black,
  redblack,
  superblack
};

struct rbnode
{

  value_type key{};  //!< Chave do nó, usada para ordenação na árvore.
  User m_data;       //!< Dados associados ao nó, representados como uma estrutura User.
  rbnode* m_left{};  //!< Ponteiro para o filho à esquerda.
  rbnode* m_right{}; //!< Ponteiro para o filho à direita.
  rbnode* dad{};
  colors cor;
  bool nil = 0;
  // encontrar maneira de lidar com os nil nodes

  // value_type height{0}; //!< Altura do nó na árvore, usada para balanceamento

  /**
   * @brief Construtor padrão para Node.
   * @param key Chave do nó (default é value_type()).
   * @param data Dados associados ao nó, representados como um par ordenado (default é User()).
   */
  rbnode(const value_type& key = value_type(), const User& data = User())
  : key(key), m_data(data), m_left(nullptr), m_right(nullptr), dad(nullptr), cor(colors::black)
  { /* empty */
  }
};