//
// Created by Samuel Vieira on 09/10/20.
//

#include <iostream>
#include <queue>
#include <stack>

#include "NodeT.h"

#ifndef TREE_BST_H
#define TREE_BST_H

class BST {
public:
    BST();
    ~BST();
    bool search(int data);
    void add(int data);
    void remove(int data);
    int size();
    void visit(int type);
    int height();
    void ancestors(int data);
    int whatLevelAmI(int data);
private:
    NodeT *root;
    void preOrden(NodeT *r);
    void inOrden(NodeT *r);
    void posOrden(NodeT *r);
    void levelByLevel();
    void destruye(NodeT *r);
    int howManyChildren(NodeT *r);
    int pred(NodeT *r);
    int succ(NodeT *r);
    int sizeHelper(NodeT *r);
    int heightHelper(NodeT *r);
};

BST::BST() {
    root = nullptr;
}

BST::~BST() {
    destruye(root);
}

//Complejidad O(n)
void BST::destruye(NodeT *r) {
    if (r != nullptr) {
        destruye(r->getLeft());
        destruye(r->getRight());
        delete r;
    }
}

//Complejidad O(1)
int BST::howManyChildren(NodeT *r) {
    int cont = 0;
    if (r->getLeft() != nullptr) {
        cont++;
    }
    if (r->getRight() != nullptr) {
        cont++;
    }
    return cont;
}

//Complejidad O(n)
int BST::pred(NodeT *r) {
    NodeT *curr = r->getLeft();
    while (curr->getRight() != nullptr) {
        curr = curr->getRight();
    }
    return curr->getData();
}

//Complejidad O(n)
int BST::succ(NodeT *r) {
    NodeT *curr = r->getRight();
    while (curr->getLeft() != nullptr) {
        curr = curr->getLeft();
    }
    return curr->getData();
}

//Complejidad O(n)
int BST::sizeHelper(NodeT *r) {
    if (r == nullptr) {
        return 0;
    }
    return 1 + sizeHelper(r->getLeft()) + sizeHelper(r->getRight());
}

//Complejidad O(n)
int BST::heightHelper(NodeT *r) {
    if (r == nullptr) {
        std::cout << "0 ";
        return 0;
    }
    std::cout << "1 + ";
    return 1 + max(heightHelper(r->getLeft()), heightHelper(r->getRight()));
}

//Complejidad O(n)
bool BST::search(int data) {
    NodeT *curr = root;
    while (curr != nullptr) {
        if (curr->getData() == data) {
            return true;
        }
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    return false;
}

//Complejidad O(n)
void BST::add(int data) {
    NodeT *curr = root;
    NodeT *father = nullptr;
    while (curr != nullptr) {
        if (curr->getData() == data) {
            return;
        }
        father = curr;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    if (father == nullptr) {
        root = new NodeT(data);
    } else {
        (father->getData() > data) ? father->setLeft(new NodeT(data)) : father->setRight(new NodeT(data));
    }
}

//Complejidad O(1)
void BST::remove(int data) {
    NodeT *curr = root;
    NodeT *father = nullptr;
    while (curr != nullptr && curr->getData() != data) {
        father = curr;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    if (curr == nullptr) {
        return;
    }
    int cantHijos = howManyChildren(curr);
    switch (cantHijos) {
        case 0:
            if (father == nullptr) {
                root = nullptr;
            } else {
                if (father->getData() > data) {
                    father->setLeft(nullptr);
                } else {
                    father->setRight(nullptr);
                }
            }
            delete curr;
            break;
        case 1:
            if (father == nullptr) {
                if (curr->getLeft() != nullptr) {
                    root = curr->getLeft();
                } else {
                    root = curr->getRight();
                }
            } else {
                if (father->getData() > data) {
                    if (curr->getLeft() != nullptr) {
                        father->setLeft(curr->getLeft());
                    } else {
                        father->setLeft(curr->getRight());
                    }
                } else {
                    if (curr->getLeft() != nullptr) {
                        father->setRight(curr->getLeft());
                    } else {
                        father->setRight(curr->getRight());
                    }
                }
            }
            delete curr;
            break;
        case 2:
            int sucesor = succ(curr);
            remove(sucesor);
            curr->setData(sucesor);
            break;
    }
}

//Complejidad O(n)
void BST::preOrden(NodeT *r) {
    if (r != nullptr) {
        std::cout << r->getData() << " ";
        preOrden(r->getLeft());
        preOrden(r->getRight());
    }
}

//Complejidad O(n)
void BST::inOrden(NodeT *r) {
    if (r != nullptr) {
        inOrden(r->getLeft());
        std::cout << r->getData() << " ";
        inOrden(r->getRight());
    }
}

//Complejidad O(n)
void BST::posOrden(NodeT *r) {
    if (r != nullptr) {
        posOrden(r->getLeft());
        posOrden(r->getRight());
        std::cout << r->getData() << " ";
    }
}

//Complejidad O(n)
void BST::levelByLevel() {
    queue<NodeT*> levels;
    levels.push(root);
    while (!levels.empty()) {
        std::cout << levels.front()->getData() << " ";
        if (levels.front()->getLeft() != nullptr) {
            levels.push(levels.front()->getLeft());
        }
        if (levels.front()->getRight() != nullptr) {
            levels.push(levels.front()->getRight());
        }
        levels.pop();
    }
}

int BST::size() {
    return sizeHelper(root);
}

// La complejidad esta en la respectiva funcion
void BST::visit(int type) {
    switch (type) {
        case 1:
            preOrden(root);
            std::cout << endl;
            break;
        case 2:
            inOrden(root);
            std::cout << endl;
            break;
        case 3:
            posOrden(root);
            std::cout << endl;
            break;
        case 4:
            levelByLevel();
            std::cout << endl;
            break;
    }
}

int BST::height() {
    return heightHelper(root);
}

//Complejidad O(n)
void BST::ancestors(int data) {
    stack<int> dataAncestors;
    NodeT *curr = root;
    int currentAncestor;
    while (curr->getData() != data) {
        dataAncestors.push(curr->getData());
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    while (!dataAncestors.empty()) {
        std::cout << dataAncestors.top() << " ";
        dataAncestors.pop();
    }
}
//Complejidad O(n)
int BST::whatLevelAmI(int data) {
    NodeT *curr = root;
    int level = 0;
    while (curr != nullptr && curr->getData() != data) {
        level++;
        curr = (curr->getData() > data) ? curr->getLeft() : curr->getRight();
    }
    if (curr->getData() == data) {
        return level;
    } else {
        return -1;
    }
}
#endif //TREE_BST_H
