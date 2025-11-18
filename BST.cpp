#include "BST.h"
#include <iostream>

BST::BST() : root(nullptr) {}

BST::~BST() {
    clear();
}

Node* BST::insertRec(Node* node, int value) {
    if (!node) {
        return new Node(wartosc); //edycja
    }
    if (value < node->value) node->left = insertRec(node->left, value);
    else node->right = insertRec(node->right, value); // duplikaty idą w prawo
    return node;
}

void BST::insert(int wartosc) { //edycja
    root = insertRec(root, value);
}

Node* BST::findMin(Node* node) const {
    if (!node) return nullptr;
    while (node->left) node = node->left;
    return node;
}

Node* BST::removeRec(Node* node, int value, bool& removed) {
    if (!node) return nullptr;
    if (value < node->value) {
        node->left = removeRec(node->left, value, removed);
    }
    else if (value > node->value) {
        node->right = removeRec(node->right, value, removed);
    }
    else {
        // found node to delete
        removed = true;
        if (!node->left) {
            Node* r = node->right;
            delete node;
            return r;
        }
        else if (!node->right) {
            Node* l = node->left;
            delete node;
            return l;
        }
        else {
            
            Node* succ = findMin(node->right);
            node->value = succ->value;
            node->right = removeRec(node->right, succ->value, removed);
          
        }
    }
    return node;
}

bool BST::remove(int value) {
    bool removed = false;
    root = removeRec(root, value, removed);
    return removed;
}

void BST::clearRec(Node* node) {
    if (!node) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}

void BST::clear() {
    clearRec(root);
    root = nullptr;
}

void BST::inorderRec(Node* node) const {
    if (!node) return;
    inorderRec(node->left);
    std::cout << node->value << " ";
    inorderRec(node->right);
}

void BST::printInorder() const {
    if (!root) {
        std::cout << "(puste drzewo)\n";
        return;
    }
    inorderRec(root);
    std::cout << "\n";
}
