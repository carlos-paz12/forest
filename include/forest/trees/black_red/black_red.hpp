#include <bits/stdc++.h>
#include "../../user.hpp"
#include "../../tree.hpp"
#include "../../utils/rotations.hpp"
#include "node_black_red.hpp"

/*the 5 key properties of a red black tree:

1 - every node is red or black
2 - the root node is black
3 - every leaf node (nil node) is black
4 - if a node is red, both of its children are black
5 - starting from any nodem all simple paths down to leaf nodes
    hold the same number of black nodes

*/


enum class colors {
    red,
    black,
    redblack,
    superblack
};

struct rbnode
{
  
  value_type key{}; //!< Chave do nó, usada para ordenação na árvore.
  User m_data; //!< Dados associados ao nó, representados como uma estrutura User.
  rbnode *m_left{};  //!< Ponteiro para o filho à esquerda.
  rbnode *m_right{}; //!< Ponteiro para o filho à direita.
  rbnode *dad{};
  colors cor;
  bool nil = 0;
  // encontrar maneira de lidar com os nil nodes

  value_type height{0}; //!< Altura do nó na árvore, usada para balanceamento 
  
    /**
     * @brief Construtor padrão para Node.
     * @param key Chave do nó (default é value_type()).
     * @param data Dados associados ao nó, representados como um par ordenado (default é User()).
     */
  rbnode(const value_type &key = value_type(),const User &data = User())
    : key(key), m_data(data), m_left(nullptr), m_right(nullptr), dad(nullptr), cor(colors::black) { /* empty */ }
};

class redblacktree {

    rbnode * root;
    value_type altura;

    // construtor que recebe uma chave e um valor, constrói o nó raiz

    redblacktree(const value_type &key,const User &data){
        // nao coloquei valores inicializadores pra nao dar problema na insercao. toda insercao eh
        // automaticamente valida por causa disso (nao precisamos nos preocupar com insercao vazia)
        // perguntar se pode !
        // tive uma ideia!!!!!!!!! eu posso criar literalmente apenas um nil aqui
        /*rbnode * raiz;
        rbnode * nil1;
        rbnode * nil2;
        raiz->key = key;
        raiz->m_data = data;
        raiz->m_left = nil1;
        raiz->m_right = nil2;
        raiz->dad = nullptr;
        raiz->cor = colors::black;
        raiz->height = 0;

        nil1->nil = true;
        nil1->cor = colors::black;
        nil1->dad = raiz;

        nil2->nil = true;
        nil2->cor = colors::black;
        nil2->dad = raiz;

        root = raiz;*/

        rbnode * nill;

        nill->nil = true; // o pai ja eh nulptr
        nill->cor = colors::black;

        root = nill;
    }

    
    void simple_left(rbnode * &node);
    void simple_right(rbnode * &node);
    void double_left(rbnode * &node);
    void double_right(rbnode * &node);
    void fix_violations(rbnode * &node);
    void shifting(rbnode * &antigo, rbnode * &node);
    rbnode * search (value_type key, User data);
    void fix_delete_violations(rbnode * &node);

    public:

    void insert(value_type key, User data);
    void deletenode(value_type key, User data); // a palavra "delete" ja teh usada, tive que mudar o nome

};

void redblacktree::simple_left(rbnode * &node) {
    //if (node == nullptr || node->m_left == nullptr) return node; //checks for null pointers

    rbnode * dir = node->m_right;
    node->m_right = dir->m_left;
    if (dir->m_left->nil != 0) { // eh um nil node
        node->m_left->dad = dir;
    }
    dir->dad = node->dad;
    if (node->dad == nullptr) { // eh a root!
        // iguala a raiz da arvore
        root = dir;
    }
    else if (node->dad->m_left == node) { // eh o filho da esquerda?
        node->dad->m_left = dir;
    }
    else {
        node->dad->m_right = dir;
    }

    dir->m_left = node;
    node->dad = dir;


}

void redblacktree::simple_right(rbnode * &node) {
    //if (node == nullptr || node->m_right == nullptr) return node; //checks for null pointers

    rbnode * esq = node->m_left;
    node->m_left = esq->m_right;
    if (esq->m_right->nil != 0) { // eh um nil node
        node->m_right->dad = esq;
    }
    esq->dad = node->dad;
    if (node->dad == nullptr) { // eh a root!
        // iguala a raiz da arvore
        root = esq;
    }
    else if (node->dad->m_right == node) { // eh o filho da direita?
        node->dad->m_right = esq;
    }
    else {
        node->dad->m_left = esq;
    }

    esq->m_right = node;
    node->dad = esq;

}

void redblacktree::double_left(rbnode * &node) {
    rbnode * outro = node->dad;
    simple_left(node);
    simple_right(outro);
}


void redblacktree::double_right(rbnode * &node) {
    rbnode * outro = node->dad;
    simple_right(node);
    simple_left(outro);
}




// INSERTION: 
//   - insert normally
//   - color it either red or black
//   - we gotta handle several cases

void redblacktree::fix_violations(rbnode * &node) {

    rbnode * uncle;
    rbnode * grandpa;
    bool uncleesq = false;
    bool nodeesq = false;
    
    if (node->dad->cor == colors::black) {
        node->cor = colors::red;
        return;
    }

    // se o pai nao eh preto, obrigatoriamente tem um avo, porque a raiz precisa ser preta
    grandpa = node->dad->dad;
    // checo se o node eh left ou right pra ajudar no caso 3

    if (node->dad->m_left == node) {
        nodeesq = true;
    }

    // significa que o pai esta a direita. logo, o tio esta a esquerda
    // a partir daqui, tenho a direcao do no tio e do no filho

    if (grandpa->m_right == node->dad) { // node eh o filho direito. uncle eh esquerdo
        uncle =  grandpa->m_left;
        uncleesq = true;
    }
    else {
        uncle = node->dad->dad->m_right;
    }


    // a partir de agora o pai ja eh vermelho

    if(uncle->cor == colors::red) {
        node->cor = colors::red;
        node->dad->cor = colors::black;
        uncle->cor = colors::black;
        fix_violations(node->dad->dad); // eu chamo recursivamente ou uso um while e atualizo os valores?
    }

    else if (uncle->cor == colors::black) {


        // if its away from its uncle. wtf. how is this a thing.
        if ((uncleesq && nodeesq) || (!uncleesq && !nodeesq)) { //ou os 2 vao pra a direita ou os 2 pra a esquerda
            simple_right(grandpa);
            node->cor = colors::red;
            node->dad->cor = colors::red;
            grandpa->cor = colors::red;

            //cabo aqui
            return;
        }

        else {
            simple_left(node->dad);
            simple_right(grandpa);
            node->cor = colors::black;
            grandpa->cor = colors::red;
            return;

        }


    }

    else { //
        if (node->dad==nullptr) {
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

// typical binary tree insertion
void redblacktree::insert(value_type key, User data) {

    rbnode * temp = root;
    rbnode * painho;
    rbnode * novo; // ja inicializa pai como nullptr
    novo->key = key;
    novo->m_data = data;

    bool direita = 0;

    while (temp->nil != 1) { // enquanto nao for nil !
        painho = temp;
        if (key < temp->key) {
            direita = 0;
            temp = temp->m_right;
        }
        else {
            direita = 1;
            temp = temp->m_right;
        }
    }

    // chegamos a um nil; o nosso no deve ficar no lugar dele

    if (temp->dad == nullptr) {
        // a árvore está vazia, somente com o nó inicial nil
        // adiciona o novo como raiz, faz jogo de ponteiros com o resto
        temp->dad = novo;
        novo->m_right = temp;
        root = novo;

        rbnode * nill;
        nill->nil = true;
        nill->dad = novo;
        novo->m_left = nill;

        return; // i dont think we have any violations to fix here??

    }

    else {

        novo->height = (painho->height) + 1; // i dont think we actually need this tho
    
        rbnode * nil1;
        nil1->cor = colors::black;
        nil1->nil = true;
    
    
        novo->dad = painho;
        novo->m_right = temp; // esse eh nil
        novo->m_left = nil1;
    
        temp->dad = novo;
        nil1->dad = novo;
    
        if (direita) {
            painho->m_right = novo;
        }
        else { // eh o filho da esquerda
            painho->m_left = novo;
        }

    }

    fix_violations(novo);
    
}

// isso aqui basicamente retira o no que a gente quer tirar da arvore.
// tipo. a arvore nao sabe mais que ele existe, mesmo que ele esteja ligado ao resto dela

void redblacktree::shifting (rbnode * &antigo, rbnode * &node) {
    if (antigo == root) {
        root = node;
    }

    else if (antigo == antigo->dad->m_left) { // is a left child
        antigo->dad->m_left = node;
    }
    else {
        antigo->dad->m_right = node;
    }

    node->dad = antigo->dad;

    delete antigo; // i think?????

    // preciso fazer um delete aqui
}

rbnode * redblacktree::search(value_type key, User data) {
    // retorna null se nao tiver na arvore
    rbnode * node = root;

    bool deuerrado = 0;

    while (key != node->key) {

        if (node->nil == true) { // chegamos no fim e nao achamos
            deuerrado = true;
            break;
        }

        if (key > node->key) {
            node = node->m_right;
        }

        else if (key < node->key) {
            node = node->m_left;
        }

    }

    if (deuerrado) {
        return root; // i guess; nao sei o que retornar;
    }

    return node;
}

void redblacktree::fix_delete_violations(rbnode * &node) {

}

// :(
// recebe um no ou uma key e um value?
void redblacktree::deletenode(value_type key, User data) {


    // fazer uma funcao de search

    rbnode * node = search(key, data);
    rbnode * backup = node;
    colors hue = node->cor;
    rbnode * mais;

    // se a esquerda do mano eh nil

    if (node->m_left->nil == true) {
        mais = node->m_left;
        shifting(node, mais); // move o no nulo pro lugar do mano
    }
    else if (node->m_right->nil == true) {
        mais = node->m_right;
        shifting(node, mais); // ^
    }

    else { // o mano tem 2 filhos que existem

    }

    if (hue == colors::black) {
        fix_delete_violations(mais);
    }

}
