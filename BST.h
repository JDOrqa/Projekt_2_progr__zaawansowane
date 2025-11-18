#ifndef BST_H
#define BST_H

#include <functional>
#include <string>
#include <vector>

/**
 * @brief Prosty BST (własna implementacja węzłów na wskaźnikach).
 *
 * Zawiera metody: insert, remove (erase), clear, find, size, empty,
 * preorder/inorder/postorder (reakcyjne i iteracyjne), graficzne wyświetlanie,
 * zapis posortowany do pliku (wykorzystuje std::vector + std::sort).
 *
 * Dodatkowo expose funkcję inorder(...) która przyjmuje callback (użyteczna).
 */

struct Node {
    int value;
    Node* left;
    Node* right;
    explicit Node(int v) : value(v), left(nullptr), right(nullptr) {}
};

class BST {
public:
    BST();
    ~BST();

    // podstawowe operacje
    void insert(int value);          // wstaw (duplikaty idą w prawo)
    bool erase(int value);           // usuń element (true jeśli usunięto)
    void clear();                    // usuń całe drzewo

    // query podobne do STL
    size_t size() const;
    bool empty() const;
    bool find(int value) const;      // czy istnieje element

    // przeszukiwania (rekurencyjne, callback)
    void preorder(const std::function<void(int)>& cb) const;
    void inorder(const std::function<void(int)>& cb) const;
    void postorder(const std::function<void(int)>& cb) const;

    // iteracyjne preorder (używa std::stack) — metoda STL-like używająca kontenera
    void preorder_iterative(const std::function<void(int)>& cb) const;

    // zwraca wektor (std::vector) wartości w kolejności inorder
    std::vector<int> to_vector_inorder() const;

    // zapis posortowany do pliku (używa std::sort)
    bool save_sorted(const std::string& filepath) const;

    // graficzne wyświetlenie (rotated)
    void printGraphical() const;

    // szukaj drogi — zwraca wektor wartości od korzenia do elementu (pusty jeśli brak)
    std::vector<int> findPath(int value) const;

private:
    Node* root;
    size_t nodeCount;

    // helpery rekurencyjne
    Node* insertRec(Node* node, int value);
    Node* removeRec(Node* node, int value, bool& removed);
    Node* findMin(Node* node) const;
    void clearRec(Node* node);

    void preorderRec(Node* node, const std::function<void(int)>& cb) const;
    void inorderRec(Node* node, const std::function<void(int)>& cb) const;
    void postorderRec(Node* node, const std::function<void(int)>& cb) const;

    bool findPathRec(Node* node, int value, std::vector<int>& path) const;

    void printGraphicalRec(Node* node, int space) const;
};

#endif // BST_H
