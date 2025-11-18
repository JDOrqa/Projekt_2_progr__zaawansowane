#ifndef FILEHANDLER_H
#define FILEHANDLER_H

#include <string>
#include <vector>
#include "BST.h"

//Klasa pomocnicza do zapisu / odczytu
class FileHandler {
public:
    //saveBinary/loadBinary (binarnie: uint64_t n + n * int)
    static bool saveBinary(const BST& tree, const std::string& filepath);
    static bool loadBinary(std::vector<int>& out_vals, const std::string& filepath);
    //loadTextNumbers (wczytuje liczby calkowite z pliku tekstowego)
    static bool loadTextNumbers(std::vector<int>& out_vals, const std::string& filepath); //jest git
};

#endif // FILEHANDLER_H


