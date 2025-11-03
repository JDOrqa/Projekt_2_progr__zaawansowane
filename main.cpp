#include <iostream>
#include <limits>
#include "BST.h"

void waitEnter() {
    std::cout << "Nacisnij Enter !";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int menu() {
    std::cout << "\n---- Proste BST - menu ----\n";
    std::cout << "1 - Dodaj element\n";
    std::cout << "2 - Usun element\n";
    std::cout << "3 - Usun cale drzewo\n";
    std::cout << "4 - Pokaz inorder \n";
    std::cout << "0 - Wyjscie\n";
    std::cout << "Wybor: ";
    int c;
    if (!(std::cin >> c)) {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return -1;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return c;
}


