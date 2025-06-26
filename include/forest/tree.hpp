
/**
 * @file tree.hpp
 * @brief  Implementação de uma árvore binária de busca com nós contendo pares ordenados.
 * @details Esta árvore permite a inserção, remoção e busca de nós baseados em chaves geradas a partir de pares ordenados.
 * A chave é gerada usando a fórmula de Cantor, garantindo que cada par ordenado tenha uma chave única.
 * A árvore é impressa de forma legível, mostrando a estrutura hierárquica dos nós.
 * @version 0.1
 * @date 2025-06-16
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <cstdlib> //<! Necessário para o uso de nullptr e outras funções de alocação dinâmica.
#include <iostream> //<! Necessário para entrada e saída padrão.
#include "user.hpp" //<! Inclui a definição da estrutura User

using value_type = long long; //<! Define o tipo de valor armazenado nos nós da árvore.



/**
 * @brief Estrutura que representa um nó na árvore binária de busca.
 * @details Cada nó contém uma chave, um par ordenado de dados e ponteiros para os filhos esquerdo e direito.
 */
struct Node
{
  
  value_type key{}; //!< Chave do nó, usada para ordenação na árvore.
  User m_data; //!< Dados associados ao nó, representados como uma estrutura User.
  Node *m_left{};  //!< Ponteiro para o filho à esquerda.
  Node *m_right{}; //!< Ponteiro para o filho à direita.
  value_type height{0}; //!< Altura do nó na árvore, usada para balanceamento 
  
    /**
     * @brief Construtor padrão para Node.
     * @param key Chave do nó (default é value_type()).
     * @param data Dados associados ao nó, representados como um par ordenado (default é User()).
     */
  Node(const value_type &key = value_type(),const User &data = User())
    : key(key), m_data(data), m_left(nullptr), m_right(nullptr) { /* empty */ }
};

using TreeNodePtr = Node *; //<! Define um ponteiro para o tipo Node, representando um nó na árvore binária.

/**
 * @brief Cria uma chave única para um par ordenado usando a fórmula de Cantor.
 * @param pair Par ordenado cujos valores serão usados para gerar a chave.
 * @return value_type Chave única gerada a partir do par ordenado.
 */
value_type create_key(User user) {
  return user.userid; //<! Usa o userid como chave única para o usuário.
}

/**
 * @brief Insere um novo nó na árvore binária de busca.
 * @param tree Referência para o ponteiro da árvore onde o nó será inserido.
 * @param key Chave do novo nó a ser inserido.
 * @param data Dados associados ao novo nó, representados como um par ordenado.
 * @return TreeNodePtr Ponteiro para a árvore após a inserção.
 */
TreeNodePtr insert(TreeNodePtr &tree, const value_type key, const User &data) {
  if (tree == nullptr) {
    tree = new Node(key, data);
    return tree; //<! Cria um novo nó se a árvore estiver vazia.
  }

  if (key < tree->key){ insert(tree->m_left, key, data);} //<! Se a chave for menor que a chave do nó atual, insere à esquerda.
   
  else if (key > tree->key){insert(tree->m_right, key, data); //se a chave for maior, insere à direita.
  }
    return tree; //<! Retorna o ponteiro para a árvore após a inserção 
}

/**
 * @brief Remove um nó da árvore binária de busca.
 * @param tree Referência para o ponteiro da árvore onde o nó será removido.
 * @param key Chave do nó a ser removido.
 * @return TreeNodePtr Ponteiro para a árvore após a remoção.
 */
TreeNodePtr remove(TreeNodePtr &tree, const value_type key) {
  if (tree == nullptr) {
    return nullptr; //<! Retorna nullptr se a árvore estiver vazia.
  }

  if (key < tree->key) {
    tree->m_left = remove(tree->m_left, key); //<! Busca à esquerda.
  } else if (key > tree->key) {
    tree->m_right = remove(tree->m_right, key); //<! Busca à direita.
  } 
  else
{
    //<! Nó encontrado
    if (tree->m_left == nullptr) 
    {
      TreeNodePtr temp = tree->m_right; //<! Se não houver filho esquerdo, retorna o filho direito.
      delete tree; //<! Exclui o nó atual.
      return temp; //<! Retorna o filho direito.
    } 
    else if (tree->m_right == nullptr) {
      TreeNodePtr temp = tree->m_left; //<! Se não houver filho direito, retorna o filho esquerdo.
      delete tree; //<! Exclui o nó atual.
      return temp; //<! Retorna o filho esquerdo.
    }

    //<! Nó com dois filhos: encontra o menor valor no subárvore direito
    TreeNodePtr temp = tree->m_right; //incia o ponteiro temporário para o filho direito.
    while (temp and temp->m_left != nullptr) {
      temp = temp->m_left; //<! Encontra o menor nó na subárvore direita.
    }
    tree->key = temp->key; //<! Substitui a chave do nó atual pela chave do sucessor.
    tree->m_data = temp->m_data; //<! Substitui os dados do nó atual pelos dados do sucessor.
    tree->m_right = remove(tree->m_right, temp->key); //<! Remove o sucessor.
  }
  return tree; //<! Retorna o ponteiro para a árvore após a remoção.
}

/**
 * @brief Busca um nó na árvore binária de busca.
 * @param tree Ponteiro para a árvore onde a busca será realizada.
 * @param key Chave do nó a ser buscado.
 * @return User* Ponteiro para os dados do nó encontrado ou nullptr se não encontrado.
 */
User *search(TreeNodePtr tree, const value_type key) {
  if (tree == nullptr) {
    return nullptr; //<! Retorna nullptr se a árvore estiver vazia.
  }

  if (key < tree->key) {
    return search(tree->m_left, key); //<! Busca à esquerda.
  } else if (key > tree->key) {
    return search(tree->m_right, key); //<! Busca à direita.
  } else {
    return &tree->m_data; //<! Retorna os dados do nó encontrado.
  }
}



/*
 * The following function have been provided by:
 * <https://stackoverflow.com/questions/36802354/print-binary-tree-in-a-pretty-way-using-c>
 *
 * And modified as necessary...
 */
void print_tree(const TreeNodePtr &tree, const std::string &prefix = "",
                bool is_left = false, bool is_root = true) {
  std::cout << prefix;
  std::cout << (is_root ? ".\n└──" : (is_left ? "├──" : "└──"));

  if (tree != nullptr) {
    std::cout << "\033[32m[ key:" << tree->key << "] { \"name:\" \"" << tree->m_data.login << "\", \"userid:\" "
              << tree->m_data.userid << ", \"region:\""<<tree->m_data.region <<", \"passoword:\" \""<<tree->m_data.password<<"}\033[0m\n";

    print_tree(tree->m_right, prefix + (is_left ? "│  " : "   "), true, false);
    print_tree(tree->m_left, prefix + (is_left ? "│  " : "   "), false, false);
  } else {
    std::cout << "\033[31mx\033[0m\n";
  }
}

