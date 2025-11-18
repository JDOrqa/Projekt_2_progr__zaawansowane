#ifndef BST_H
#define BST_H

#include <vector>

/**
 * Proste BST — tylko funkcjonalnoœæ: insert, remove, clear.
 */

struct Node {
    int wartosc; //edycja
    Node* left;
    Node* right;
    Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    // Dodaj element (jeœli istnieje wstawiamy go w prawo )
    void insert(int value);

    // Usun element — zwraca true jeœli usuniêto
    bool remove(int value);

    // Usun ca³e drzewo
    void clear();

   
    void printInorder() const;

private:
    Node* root;

    Node* insertRec(Node* node, int value);
    Node* removeRec(Node* node, int value, bool& removed);
    Node* findMin(Node* node) const;
    void clearRec(Node* node);
    void inorderRec(Node* node) const;
};

#endif // BST_H
