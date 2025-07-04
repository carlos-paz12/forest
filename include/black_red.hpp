
#ifndef BLACK_RED_HPP
#define BLACK_RED_HPP

#include "node_black_red.hpp"
#include "rotations.hpp"
#include "tree_example.hpp"
#include "user.hpp"
#include <bits/stdc++.h>

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
  // if (node == nullptr || node->m_left == nullptr) return node; //checks for null pointers

  rbnode* dir = node->m_right;
  node->m_right = dir->m_left;
  if (dir->m_left->nil != 0)
  { // eh um nil node
    dir->m_left->dad = node;
  }
  dir->dad = node->dad;
  if (node->dad == nullptr)
  { // eh a root!
    // iguala a raiz da arvore
    root = dir;
  }
  else if (node->dad->m_left == node)
  { // eh o filho da esquerda?
    node->dad->m_left = dir;
  }
  else
  {
    node->dad->m_right = dir;
  }

  dir->m_left = node;
  node->dad = dir;
}

/**
 * Implements a simple right rotation
 */
void redblacktree::simple_right(rbnode*& node)
{
  // if (node == nullptr || node->m_right == nullptr) return node; //checks for null pointers

  rbnode* esq = node->m_left;
  node->m_left = esq->m_right;
  if (esq->m_right->nil != 0)
  { // eh um nil node
    esq->m_right->dad = node;
  }
  esq->dad = node->dad;
  if (node->dad == nullptr)
  { // eh a root!
    // iguala a raiz da arvore
    root = esq;
  }
  else if (node->dad->m_right == node)
  { // eh o filho da direita?
    node->dad->m_right = esq;
  }
  else
  {
    node->dad->m_left = esq;
  }

  esq->m_right = node;
  node->dad = esq;
}

/**
 * Implements a double left rotation
 */
void redblacktree::double_left(rbnode*& node)
{
  rbnode* outro = node->dad;
  simple_left(node);
  simple_right(outro);
}

/**
 * Implements a double right rotation
 */
void redblacktree::double_right(rbnode*& node)
{
  rbnode* outro = node->dad;
  simple_right(node);
  simple_left(outro);
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
void redblacktree::fix_violations(rbnode*& node)
{

  rbnode* uncle;
  rbnode* grandpa;
  bool uncleesq = false;
  bool nodeesq = false;

  if (node == root)
  {
    if (root->cor == colors::red)
    {
      root->cor = colors::black;
    }
    return;
  }

  if (node->dad->cor == colors::black)
  {
    node->cor = colors::red;
    return;
  }

  // se o pai nao eh preto, obrigatoriamente tem um avo, porque a raiz precisa ser preta
  grandpa = node->dad->dad;
  // checo se o node eh left ou right pra ajudar no caso 3

  if (node->dad->m_left == node)
  {
    nodeesq = true;
  }

  // significa que o pai esta a direita. logo, o tio esta a esquerda
  // a partir daqui, tenho a direcao do no tio e do no filho

  if (grandpa->m_right == node->dad)
  { // node eh o filho direito. uncle eh esquerdo
    uncle = grandpa->m_left;
    uncleesq = true;
  }
  else
  {
    uncle = grandpa->m_right;
  }

  // a partir de agora o pai ja eh vermelho

  if (uncle->cor == colors::red)
  {
    node->cor = colors::red;
    node->dad->cor = colors::black;
    uncle->cor = colors::black;
    grandpa->cor = colors::red;
    fix_violations(node->dad->dad); // eu chamo recursivamente ou uso um while e atualizo os valores?
  }

  else if (uncle->cor == colors::black)
  {

    // if its away from its uncle. wtf. how is this a thing.
    if ((uncleesq && nodeesq) || (!uncleesq && !nodeesq))
    { // ou os 2 vao pra a direita ou os 2 pra a esquerda

      if (uncleesq)
      {
        simple_right(node->dad);
        simple_left(grandpa);
      }
      else
      {
        simple_left(node->dad);
        simple_right(grandpa);
      }
      node->cor = colors::black;
      grandpa->cor = colors::red;
      return;
    }

    else
    {
      if (nodeesq == 1)
      {
        simple_right(grandpa);
      }
      else
      {
        simple_left(grandpa);
      }
      node->cor = colors::red;
      node->dad->cor = colors::black;
      grandpa->cor = colors::red;

      // cabo aqui
      return;
    }
  }

  else
  { //
    if (node->dad == nullptr)
    {
      node->cor = colors::black;
    }
  }

  // caso 1: node has a black parent
  // just recolor node i guess;

  /* caso 2: parent of u is red
      & its uncle is red

      uncle and dad become black
      node becomes red




  */

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

  /* node has no parent
      color u black
      isso eh tipo um caso

  */

  // caso 4:
}

/**
 * Inserts received value onto the tree and calls helper funciton "fix_violations"
 * to deal with violations caused by said insertion
 */
void redblacktree::insert(value_type key, User data)
{

  rbnode* temp = root;
  rbnode* painho;
  rbnode* novo = new rbnode(key, data); // ja inicializa pai como nullptr
  /*novo->key = key;
  novo->m_data = data;*/

  bool direita = 0;

  while (temp->nil != 1)
  { // enquanto nao for nil !
    painho = temp;
    if (key < temp->key)
    {
      direita = 0;
      temp = temp->m_left;
    }
    else
    {
      direita = 1;
      temp = temp->m_right;
    }
  }

  // chegamos a um nil; o nosso no deve ficar no lugar dele

  if (temp->dad == nullptr)
  {
    // a árvore está vazia, somente com o nó inicial nil
    // adiciona o novo como raiz, faz jogo de ponteiros com o resto
    temp->dad = novo;
    novo->m_right = temp;
    root = novo;

    rbnode* nill = new rbnode;
    nill->nil = true;
    nill->dad = novo;
    novo->m_left = nill;

    return; // i dont think we have any violations to fix here??
  }

  else
  {

    // novo->height = (painho->height) + 1; // i dont think we actually need this tho

    rbnode* nil1 = new rbnode;
    nil1->cor = colors::black;
    nil1->nil = true;

    novo->dad = painho;
    novo->m_right = temp; // esse eh nil
    novo->m_left = nil1;

    temp->dad = novo;
    nil1->dad = novo;

    if (direita)
    {
      painho->m_right = novo;
    }
    else
    { // eh o filho da esquerda
      painho->m_left = novo;
    }
  }

  fix_violations(novo);
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
void redblacktree::printtree(rbnode* raiz, std::string s, int a)
{
  // (Node * raiz, string s = "\t↳", int a = 0)

  if (a == 0)
  {
    raiz = root;
    std::cout << s << " " << raiz->key << "( root )";
  }
  else if (raiz->nil != true)
  {
    std::cout << s << " " << raiz->key;
  }
  else
  {
    std::cout << s << "null";
  }

  if (a == 1)
  {
    std::cout << " ( L )";
  }

  else if (a == 2)
  {
    std::cout << " ( R )";
  }

  if (raiz->cor == colors::black)
  {
    std::cout << " - black";
  }
  else
  {
    std::cout << " - red";
  }

  std::cout << "\n";

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