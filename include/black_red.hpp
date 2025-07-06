
#ifndef BLACK_RED_HPP
#define BLACK_RED_HPP

#include "node_black_red.hpp"
#include "rotations.hpp"
#include "tree_example.hpp"
#include "user.hpp"
#include <bits/stdc++.h>
#include <cstdlib>
#include <sys/types.h>

/*the 5 key properties of a red black tree:

1 - every node is red or black
2 - the root node is black
3 - every leaf node (nil node) is black
4 - if a node is red, both of its children are black
5 - starting from any nodem all simple paths down to leaf nodes
    hold the same number of black nodes

*/

class redblacktree
{

  rbnode* root;
  value_type altura;

  // construtor que recebe uma chave e um valor, constrói o nó raiz

  void simple_left(rbnode*& node);
  void simple_right(rbnode*& node);
  void double_left(rbnode*& node);
  void double_right(rbnode*& node);
  void fix_violations(rbnode*& node);
  void shifting(rbnode*& antigo, rbnode*& node);
  rbnode* search(value_type key, User data);
  void fix_delete_violations(rbnode*& node);

public:
  redblacktree(/*const value_type &key,const User &data*/)
  {
    root = new rbnode();
    root->nil = true;
    root->cor = colors::black;
  }

  void insert(value_type key, User data);
  void deletenode(value_type key, User data); // a palavra "delete" ja teh usada, tive que mudar o nome
  void printtree(rbnode* raiz = nullptr, std::string s = "\t↳", int a = 0);
  bool is_empty()
  {
    if (root->nil == true) return true;
  }
};

/**
 * Implements a simple left rotation
 */
void redblacktree::simple_left(rbnode*& node)
{
  if (not node /*node == nullptr*/ or node->nil or not node->m_right or node->m_right->nil) return;

  auto R = node->m_right;
  auto t2 = R->m_left;

  R->m_left = node;
  R->dad = node->dad;

  if (t2 /*t2 != nullptr*/)
  {
    node->m_right = t2;
    t2->dad = node;
  }
  else
  {
    node->m_right = nullptr;
  }

  if (not node->dad /*node->dad == nullptr*/)
  {
    root = R; // node era a raiz
  }
  else
  {
    if (node == node->dad->m_left)
    {
      node->dad->m_left = R;
    }
    else
    {
      node->dad->m_right = R;
    }
  }

  node->dad = R;
  // // if (node == nullptr || node->m_left == nullptr) return node; //checks for null pointers

  // if (not node->nil)
  // {
  //   rbnode* dir = node->m_right;
  //   node->m_right = dir->m_left;
  //   if (dir->m_left->nil != 0)
  //   { // eh um nil node
  //     dir->m_left->dad = node;
  //   }
  //   dir->dad = node->dad;
  //   if (node->dad == nullptr)
  //   { // eh a root!
  //     // iguala a raiz da arvore
  //     root = dir;
  //   }
  //   else if (node->dad->m_left == node)
  //   { // eh o filho da esquerda?
  //     node->dad->m_left = dir;
  //   }
  //   else
  //   {
  //     node->dad->m_right = dir;
  //   }

  //   dir->m_left = node;
  //   node->dad = dir;
  // }
}

/**
 * Implements a simple right rotation
 */
void redblacktree::simple_right(rbnode*& node)
{
  if (not node /*node == nullptr*/ or node->nil or not node->m_left or node->m_left->nil) return;

  rbnode* L = node->m_left;
  rbnode* t3 = L->m_right;

  L->m_right = node;
  L->dad = node->dad;

  if (t3 /*t3 != nullptr*/)
  {
    node->m_left = t3;
    t3->dad = node;
  }
  else
  {
    node->m_left = nullptr;
  }

  // Atualizar o pai de t0 para apontar para L
  if (not node->dad /*node->dad == nullptr*/)
  {
    root = L; // t0 era a raiz
  }
  else
  {
    if (node == node->dad->m_left)
    {
      node->dad->m_left = L;
    }
    else
    {
      node->dad->m_right = L;
    }
  }

  node->dad = L;

  // t0 = L;  // faz t0 apontar para nova subárvore raiz

  // t0->m_left = L->m_right;
  // if (L->m_right->nil)
  // { // eh um nil node
  //   L->m_right->dad = t0;
  // }
  // L->dad = t0->dad;
  // if (t0->dad == nullptr)
  // { // eh a root!
  //   // iguala a raiz da arvore
  //   root = L;
  // }
  // else if (t0->dad->m_right == t0)
  // { // eh o filho da direita?
  //   t0->dad->m_right = L;
  // }
  // else
  // {
  //   t0->dad->m_left = L;
  // }

  // L->m_right = t0;
  // t0->dad = L;
}

/**
 * Implements a double left rotation
 */
void redblacktree::double_left(rbnode*& node)
{
  simple_right(node->m_right);
  simple_left(node);
}

/**
 * Implements a double right rotation
 */

void redblacktree::double_right(rbnode*& node)
{
  simple_left(node->m_left);
  simple_right(node);
}

/**
 * This function handles the violations that come after doing a typical binary search tree
 * insertion onto a red-black tree
 * That is done by handling several cases and using, as apparati, previously mentioned rotations
 * and recolors
 *
 * CASE 1: node has a black parent
 * CASE 2: parent and uncle node are both red
 * CASE 3: parent is red and uncle is black
 *      CASE 3.1: the node is leaning away from its uncle
 *      CASE 3.2: the node is leaning towards its uncle
 *
 * CASE 4: node has no parent
 *
 */
void redblacktree::fix_violations(rbnode*& no_inserido) //!< *node_inserted* é o nó que acabou de ser inserido.
{
  //!< Tio do nó que acabou de ser inserido.
  rbnode* tio_do_no_inserido;
  //!< Avô do nó que acabou de ser inserido.
  rbnode* avo_do_no_inserido;
  //!< Pai do nó que acabou de ser inserido.
  rbnode* pai_do_no_inserido;
  //!< Define se o tio do nó que acabou de ser inserido está à esquerda.
  bool tio_esta_a_esquerda_do_no_inserido = false;
  //!< Define se o nó inserido está à esquerda ou à direita do pai.
  bool no_inserido_eh_filho_a_esquerda = false;

  // Nó raíz.
  if (no_inserido == root)
  {
    if (root->cor == colors::red)
    {
      root->cor = colors::black;
    }
    return;
  }

  // caso 1: node has a black parent
  // just recolor node i guess;
  // Nó inserido é filho de pai preto.

  pai_do_no_inserido = no_inserido->dad;

  if (pai_do_no_inserido->cor == colors::black)
  {
    no_inserido->cor = colors::red;
    return;
  }

  // se o pai nao eh preto, obrigatoriamente tem um avo, porque a raiz precisa ser preta
  avo_do_no_inserido = pai_do_no_inserido->dad;

  // checo se o node eh left ou right pra ajudar no caso 3
  if (pai_do_no_inserido->m_left == no_inserido)
  {
    no_inserido_eh_filho_a_esquerda = true;
  }

  // significa que o pai esta a direita. logo, o tio esta a esquerda
  // a partir daqui, tenho a direcao do no tio e do no filho
  if (avo_do_no_inserido->m_right == pai_do_no_inserido)
  {
    tio_do_no_inserido = avo_do_no_inserido->m_left;
    tio_esta_a_esquerda_do_no_inserido = true;
  }
  else
  {
    tio_do_no_inserido = avo_do_no_inserido->m_right;
  }

  // a partir de agora o pai ja eh vermelho

  /* caso 2: parent of u is red
      & its uncle is red

      uncle and dad become black
      node becomes red
  */
  if (tio_do_no_inserido->cor == colors::red)
  {
    no_inserido->cor = colors::red;
    pai_do_no_inserido->cor = colors::black;
    tio_do_no_inserido->cor = colors::black;
    avo_do_no_inserido->cor = colors::red;
    fix_violations(avo_do_no_inserido); // eu chamo recursivamente ou uso um while e atualizo os valores?
  }

  /* caso 3: red parent, black uncle

      caso 3a
      node is away from its uncle

      right rotation to the grandpa (w)

      node is now red

      its parent is now black

      w (formerly known as grandpa) is now red


      caso 3b
      node is towards its uncle

      right rotation to the dad

      left rotation to the grandpa

      node is now black

      recolor w (ex grandpa) as red



  */
  else if (tio_do_no_inserido->cor == colors::black)
  {

    if (tio_esta_a_esquerda_do_no_inserido) // pai está à direita
    {
      if (no_inserido_eh_filho_a_esquerda) // filho está à esquerda
      {
        //            Avô
        //           /   \
        //          /     \
        //         /       \
        //       Tio       Pai
        //      /   \     /   \
        //     t0    t1 Filho  t2
        std::cout << "Breakpoint 1 (Rotação dupla à esquerda):\n";
        double_left(avo_do_no_inserido);
        no_inserido->cor = colors::black;
        avo_do_no_inserido->cor = colors::red;
      }
      else if (not no_inserido_eh_filho_a_esquerda) // filho está à direita
      {
        //            Avô
        //           /   \
        //          /     \
        //         /       \
        //       Tio       Pai
        //      /   \     /   \
        //     t0    t1  t2  Filho
        std::cout << "Breakpoint 2 (Rotação simples à esquerda):\n";
        simple_left(avo_do_no_inserido);
        no_inserido->cor = colors::red;
        pai_do_no_inserido->cor = colors::black;
        avo_do_no_inserido->cor = colors::red;
      }
    }
    else if (not tio_esta_a_esquerda_do_no_inserido) // pai está à esquerda
    {

      if (no_inserido_eh_filho_a_esquerda) // filho está à esquerda
      {
        //            Avô
        //           /   \
        //          /     \
        //         /       \
        //       Pai       Tio
        //      /   \     /   \
        //   Filho   t0  t1    t2
        std::cout << "Breakpoint 3 (Rotação simples à direita):\n";
        simple_right(avo_do_no_inserido);
        no_inserido->cor = colors::red;
        pai_do_no_inserido->cor = colors::black;
        avo_do_no_inserido->cor = colors::red;
      }
      else if (not no_inserido_eh_filho_a_esquerda) // filho está à direita
      {
        //            Avô
        //           /   \
        //          /     \
        //         /       \
        //       Pai       Tio
        //      /   \     /   \
        //    t0   filho t1    t2
        std::cout << "Breakpoint 4 (Rotação dupla à direita):\n";
        double_right(avo_do_no_inserido);
        no_inserido->cor = colors::black;
        avo_do_no_inserido->cor = colors::red;
      }
    }
  }
  else
  {
    /* node has no parent
        color u black
        isso eh tipo um caso
    */
    if (no_inserido->dad == nullptr)
    {
      no_inserido->cor = colors::black;
    }
  }
}

/**
 * Inserts received value onto the tree and calls helper funciton "fix_violations"
 * to deal with violations caused by said insertion
 */
void redblacktree::insert(value_type key, User data)
{
  rbnode* novo = new rbnode(key, data);
  novo->cor = colors::red;
  if (root->nil)
  {
    root = novo;
  }
  else
  {
    rbnode* temp = root;
    rbnode* painho = nullptr;
    novo->nil = false;
    bool direita = false;

    while (temp != nullptr && temp->nil != true)
    {
      painho = temp;
      if (key < temp->key)
      {
        direita = false;
        temp = temp->m_left;
      }
      else
      {
        direita = true;
        temp = temp->m_right;
      }
    }

    novo->dad = painho;

    rbnode* nilL = new rbnode;
    nilL->nil = true;
    nilL->cor = colors::black;
    nilL->dad = novo;

    rbnode* nilR = new rbnode;
    nilR->nil = true;
    nilR->cor = colors::black;
    nilR->dad = novo;

    novo->m_left = nilL;
    novo->m_right = nilR;

    if (direita)
      painho->m_right = novo;
    else
      painho->m_left = novo;
  }

  std::cout << "Apos insercao:\n";
  printtree();
  std::cout << "Apos balanceamento:\n";
  fix_violations(novo);
  printtree();
}

// isso aqui basicamente retira o no que a gente quer tirar da arvore.
// tipo. a arvore nao sabe mais que ele existe, mesmo que ele esteja ligado ao resto dela

/**
 * helper function for the deletion of a node
 */
void redblacktree::shifting(rbnode*& antigo, rbnode*& node)
{
  if (antigo == root)
  {
    root = node;
  }

  else if (antigo == antigo->dad->m_left)
  { // is a left child
    antigo->dad->m_left = node;
  }
  else
  {
    antigo->dad->m_right = node;
  }

  node->dad = antigo->dad;

  delete antigo; // i think?????

  // preciso fazer um delete aqui!!! i think!!!!
}

/**
 * helper function that searches a node's position in the tree.
 * if the element doesnt exist in the tree, returns a pointer to the root node
 */
rbnode* redblacktree::search(value_type key, User data)
{
  // retorna null se nao tiver na arvore
  rbnode* node = root;

  bool deuerrado = 0;

  while (key != node->key)
  {

    if (node->nil == true)
    { // chegamos no fim e nao achamos
      deuerrado = true;
      break;
    }

    if (key > node->key)
    {
      node = node->m_right;
    }

    else if (key < node->key)
    {
      node = node->m_left;
    }
  }

  if (deuerrado)
  {
    return root; // i guess; nao sei o que retornar;
  }

  return node;
}

/**
 * deals with the violations caused by the deletion of a node in a red black tree
 */
void redblacktree::fix_delete_violations(rbnode*& node) { }

/**
 * Deletes, with the use of helper functions "search", "shift" and "fix_delete_violations",
 * a node in the red black tree.
 */
void redblacktree::deletenode(value_type key, User data)
{

  // fazer uma funcao de search

  rbnode* node = search(key, data);
  rbnode* backup = node;
  colors hue = node->cor;
  rbnode* mais;

  // se a esquerda do mano eh nil

  if (node->m_left->nil == true)
  {
    mais = node->m_left;
    shifting(node, mais); // move o no nulo pro lugar do mano
  }
  else if (node->m_right->nil == true)
  {
    mais = node->m_right;
    shifting(node, mais); // ^
  }

  else
  { // o mano tem 2 filhos que existem
  }

  if (hue == colors::black)
  {
    fix_delete_violations(mais);
  }
}

/**
 * temporary funtion that prints (very poorly) a red black tree!
 */
constexpr const char* RED_BG = "\033[41m";   // Fundo vermelho
constexpr const char* BLACK_BG = "\033[40m"; // Fundo preto
constexpr const char* RESET = "\033[0m";

void redblacktree::printtree(rbnode* raiz, std::string s, int a)
{
  if (a == 0)
  {
    raiz = root;
    const char* cor = (raiz->cor == colors::red) ? RED_BG : BLACK_BG;
    std::cout << cor << s << " " << raiz->key << " ( root )" << RESET << "\n";
  }
  else if (raiz->nil != true)
  {
    const char* cor = (raiz->cor == colors::red) ? RED_BG : BLACK_BG;
    std::cout << cor << s << " " << raiz->key;
    if (a == 1)
      std::cout << " ( L )";
    else if (a == 2)
      std::cout << " ( R )";
    std::cout << RESET << "\n";
  }
  else
  {
    std::cout << BLACK_BG << s << "null";
    if (a == 1)
      std::cout << " ( L )";
    else if (a == 2)
      std::cout << " ( R )";
    std::cout << RESET << "\n";
    return;
  }

  if (raiz->m_right != nullptr)
  {
    printtree(raiz->m_right, '\t' + s, 2);
  }

  if (raiz->m_left != nullptr)
  {
    printtree(raiz->m_left, '\t' + s, 1);
  }
}

#endif