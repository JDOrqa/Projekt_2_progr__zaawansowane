#include "FileHandler.h"
#include <fstream>
#include <sstream>
#include <cstdint>

static void collectPreorder(const BST& tree, std::vector<int>& out) {
    tree.preorder([&](int v) { out.push_back(v); });
}

bool FileHandler::saveBinary(const BST& tree, const std::string& filepath) {
    std::ofstream ofs(filepath, std::ios::binary);
    if (!ofs) return false;
    std::vector<int> vals;
    collectPreorder(tree, vals); // zapis preorder (wybieramy)
    uint64_t n = vals.size();
    ofs.write(reinterpret_cast<const char*>(&n), sizeof(n));
    if (n) ofs.write(reinterpret_cast<const char*>(vals.data()), sizeof(int) * vals.size());
    return ofs.good();
}

bool FileHandler::loadBinary(std::vector<int>& out_vals, const std::string& filepath) {
    std::ifstream ifs(filepath, std::ios::binary);
    if (!ifs) return false;
    uint64_t n = 0;
    ifs.read(reinterpret_cast<char*>(&n), sizeof(n));
    if (!ifs) return false;
    out_vals.resize(n);
    if (n) ifs.read(reinterpret_cast<char*>(out_vals.data()), sizeof(int) * n);
    return ifs.good();
}

bool FileHandler::loadTextNumbers(std::vector<int>& out_vals, const std::string& filepath) {
    std::ifstream ifs(filepath);
    if (!ifs) return false;
    out_vals.clear();
    std::string line;
    while (std::getline(ifs, line)) {
        std::istringstream iss(line);
        int x;
        while (iss >> x) out_vals.push_back(x);
    }
    return true;
}
