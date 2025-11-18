#include "BST.h"
#include <iostream>
#include <stack>
#include <algorithm>
#include <fstream>
#include <iomanip>

BST::BST() : root(nullptr), nodeCount(0) {}
BST::~BST() { clear(); }

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

Node* BST::findMin(Node* node) const {
    while (node && node->left) node = node->left;
    return node;
}

// removeRec: removed ustawiamy tylko wtedy gdy faktycznie usunięto węzeł;
// gdy węzeł ma dwóch dzieci -> kopiujemy sukcesora i wywołujemy remove na prawym poddrzewie
Node* BST::removeRec(Node* node, int value, bool& removed) {
    if (!node) return nullptr;
    if (value < node->value) {
        node->left = removeRec(node->left, value, removed);
    }
    else if (value > node->value) {
        node->right = removeRec(node->right, value, removed);
    }
    else {
        // node->value == value
        if (!node->left) {
            Node* r = node->right;
            delete node;
            removed = true;
            return r;
        }
        else if (!node->right) {
            Node* l = node->left;
            delete node;
            removed = true;
            return l;
        }
        else {
            // two children: replace value by successor and delete successor from right subtree
            Node* succ = findMin(node->right);
            node->value = succ->value;
            node->right = removeRec(node->right, succ->value, removed);
            // removed will be set by recursive call (when successor gets removed)
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

size_t BST::size() const { return nodeCount; }
bool BST::empty() const { return root == nullptr; }

bool BST::find(int value) const {
    Node* cur = root;
    while (cur) {
        if (value < cur->value) cur = cur->left;
        else if (value > cur->value) cur = cur->right;
        else return true;
    }
    return false;
}

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

void BST::preorder(const std::function<void(int)>& cb) const { preorderRec(root, cb); }
void BST::inorder(const std::function<void(int)>& cb) const { inorderRec(root, cb); }
void BST::postorder(const std::function<void(int)>& cb) const { postorderRec(root, cb); }

void BST::preorder_iterative(const std::function<void(int)>& cb) const {
    if (!root) return;
    std::stack<Node*> st;
    st.push(root);
    while (!st.empty()) {
        Node* cur = st.top(); st.pop();
        cb(cur->value);
        if (cur->right) st.push(cur->right);
        if (cur->left) st.push(cur->left);
    }
}

std::vector<int> BST::to_vector_inorder() const {
    std::vector<int> out;
    inorder([&](int v) { out.push_back(v); });
    return out;
}

bool BST::save_sorted(const std::string& filepath) const {
    std::vector<int> v = to_vector_inorder();
    std::sort(v.begin(), v.end()); // STL usage
    std::ofstream ofs(filepath);
    if (!ofs) return false;
    for (int x : v) ofs << x << "\n";
    return true;
}

void BST::printGraphicalRec(Node* node, int space) const {
    if (!node) return;
    const int INDENT = 6;
    space += INDENT;
    printGraphicalRec(node->right, space);
    std::cout << std::setw(space) << "" << node->value << "\n";
    printGraphicalRec(node->left, space);
}

void BST::printGraphical() const {
    if (!root) {
        std::cout << "(puste drzewo)\n";
        return;
    }
    printGraphicalRec(root, 0);
}

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
    path.pop_back();
    return false;
}

std::vector<int> BST::findPath(int value) const {
    std::vector<int> path;
    findPathRec(root, value, path);
    return path;
}
