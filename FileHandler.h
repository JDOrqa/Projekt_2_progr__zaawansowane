#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "BST.h"

/**
 * Klasa pomocnicza do zapisu / odczytu:
 * - saveBinary/loadBinary (binarnie: uint64_t n + n * int)
 * - loadTextNumbers (wczytuje liczby ca³kowite z pliku tekstowego)
 */
class FileHandler {
public:
    static bool saveBinary(const BST& tree, const std::string& filepath);
    static bool loadBinary(std::vector<int>& out_vals, const std::string& filepath);

    static bool loadTextNumbers(std::vector<int>& out_vals, const std::string& filepath);
};

#endif // FILEHANDLER_H
