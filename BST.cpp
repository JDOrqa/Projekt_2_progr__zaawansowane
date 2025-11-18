#include "BST.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <fstream>
#include <iomanip>

// Konstruktor i destruktor
BST::BST() : root(nullptr), nodeCount(0) {}
BST::~BST() { clear(); }

/**
 * @brief Rekurencyjne wstawianie elementu do drzewa
 */
Node* BST::insertRec(Node* node, int value) {
    if (!node) {
        return new Node(value);
    }
    if (value < node->value) node->left = insertRec(node->left, value);
    else node->right = insertRec(node->right, value); // duplikaty idą w prawo
    return node;
}

void BST::insert(int value) {
    root = insertRec(root, value);
    ++nodeCount;
}

/**
 * @brief Znajduje minimalny element w poddrzewie
 */
Node* BST::findMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

/**
 * @brief Rekurencyjne usuwanie elementu z drzewa
 * Obsługuje trzy przypadki: brak dzieci, jedno dziecko, dwa dzieci
 */
Node* BST::removeRec(Node* node, int value, bool& removed) {
    if (!node) return nullptr;
    if (value < node->value) {
        node->left = removeRec(node->left, value, removed);
    }
    else if (value > node->value) {
        node->right = removeRec(node->right, value, removed);
    }
    else {
        // Znaleziono element do usunięcia
        if (!node->left) {
            // Przypadek 1: Brak lewego dziecka
            Node* r = node->right;
            delete node;
            removed = true;
            return r;
        }
        else if (!node->right) {
            // Przypadek 2: Brak prawego dziecka
            Node* l = node->left;
            delete node;
            removed = true;
            return l;
        }
        else {
            // Przypadek 3: Dwoje dzieci - zastąp przez następnika inorder
            Node* succ = findMin(node->right);
            node->value = succ->value;
            node->right = removeRec(node->right, succ->value, removed);
        }
    }
    return node;
}

bool BST::erase(int value) {
    bool removed = false;
    root = removeRec(root, value, removed);
    if (removed && nodeCount > 0) --nodeCount;
    return removed;
}

/**
 * @brief Rekurencyjne usuwanie całego drzewa (postorder)
 */
void BST::clearRec(Node* node) {
    if (!node) return;
    clearRec(node->left);
    clearRec(node->right);
    delete node;
}

void BST::clear() {
    clearRec(root);
    root = nullptr;
    nodeCount = 0;
}

// Metody informacyjne
size_t BST::size() const { return nodeCount; }
bool BST::empty() const { return root == nullptr; }

/**
 * @brief Iteracyjne wyszukiwanie elementu w drzewie
 */
bool BST::find(int value) const {
    Node* cur = root;
    while (cur) {
        if (value < cur->value) cur = cur->left;
        else if (value > cur->value) cur = cur->right;
        else return true;
    }
    return false;
}

// Metody przechodzenia drzewa (rekurencyjne)
void BST::preorderRec(Node* node, const std::function<void(int)>& cb) const {
    if (!node) return;
    cb(node->value);
    preorderRec(node->left, cb);
    preorderRec(node->right, cb);
}

void BST::inorderRec(Node* node, const std::function<void(int)>& cb) const {
    if (!node) return;
    inorderRec(node->left, cb);
    cb(node->value);
    inorderRec(node->right, cb);
}

void BST::postorderRec(Node* node, const std::function<void(int)>& cb) const {
    if (!node) return;
    postorderRec(node->left, cb);
    postorderRec(node->right, cb);
    cb(node->value);
}

// Publiczne metody przechodzenia
void BST::preorder(const std::function<void(int)>& cb) const { preorderRec(root, cb); }
void BST::inorder(const std::function<void(int)>& cb) const { inorderRec(root, cb); }
void BST::postorder(const std::function<void(int)>& cb) const { postorderRec(root, cb); }

/**
 * @brief Iteracyjne przechodzenie preorder z użyciem stosu
 * Stos przechowuje węzły do odwiedzenia w odpowiedniej kolejności
 */
void BST::preorder_iterative(const std::function<void(int)>& cb) const {
    if (!root) return;
    std::stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* cur = st.top(); st.pop();
        cb(cur->value);
        // Najpierw prawe, potem lewe - bo stos jest LIFO
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
    }
}

/**
 * @brief Konwersja drzewa do wekta w porządku inorder
 */
std::vector<int> BST::to_vector_inorder() const {
    std::vector<int> out;
    inorder([&](int v) { out.push_back(v); });
    return out;
}

/**
 * @brief Zapis posortowanych wartości do pliku tekstowego
 * Wykorzystuje std::sort do sortowania wartości
 */
bool BST::save_sorted(const std::string& filepath) const {
    std::vector<int> v = to_vector_inorder();
    std::sort(v.begin(), v.end()); // STL używany
    std::ofstream ofs(filepath);
    if (!ofs) return false;
    for (int x : v) ofs << x << "\n";
    return true;
}

/**
 * @brief Graficzne wyświetlanie drzewa (obrócone o 90 stopni)
 */
void BST::printGraphicalRec(Node* node, int space) const {
    if (!node) return;
    const int INDENT = 6;
    space += INDENT;
    printGraphicalRec(node->right, space); // Najpierw prawe poddrzewo
    std::cout << std::setw(space) << "" << node->value << "\n";
    printGraphicalRec(node->left, space);  // Potem lewe poddrzewo
}

void BST::printGraphical() const {
    if (!root) {
        std::cout << "(puste drzewo)\n";
        return;
    }
    printGraphicalRec(root, 0);
}

/**
 * @brief Rekurencyjne wyszukiwanie ścieżki do elementu
 * Zwraca true jeśli znaleziono element, false w przeciwnym przypadku
 */
bool BST::findPathRec(Node* node, int value, std::vector<int>& path) const {
    if (!node) return false;
    path.push_back(node->value);
    if (node->value == value) return true;
    if (value < node->value) {
        if (findPathRec(node->left, value, path)) return true;
    }
    else {
        if (findPathRec(node->right, value, path)) return true;
    }
    path.pop_back(); // Backtrack jeśli nie znaleziono
    return false;
}

std::vector<int> BST::findPath(int value) const {
    std::vector<int> path;
    findPathRec(root, value, path);
    return path;
}
