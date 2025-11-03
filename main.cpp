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
int main() {
    BST tree;
    bool running = true;
    while (running) {
        int wybor = menu();
        switch (wybor) {
        case 1: {
            std::cout << "Podaj liczbe calkowita do dodania: ";
            int v;
            if (!(std::cin >> v)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Niepoprawne dane\n";
            }
            else {
                tree.insert(v);
                std::cout << "Dodano " << v;
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 2: {
            std::cout << "Podaj liczbe do usuniecia: ";
            int v;
            if (!(std::cin >> v)) {
                std::cin.clear();
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
                std::cout << "Niepoprawne dane\n";
            }
            else {
                bool ok = tree.remove(v);
                if (ok) std::cout << "Usunieto " << v << "!\n";
                else std::cout << "Nie znaleziono " << v << " w drzewie\n";
            }
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            break;
        }
        case 3: {
            tree.clear();
            std::cout << "Usunieto cale drzewo\n";
            break;
        }
        case 4: {
            std::cout << "Inorder: ";
            tree.printInorder();
            break;
        }
        case 0:
            running = false;
            break;
        default:
            std::cout << "Nieprawidlowy wybor !\n";
        }
    }

    std::cout << "Koniec programu !\n";
    return 0;
}


