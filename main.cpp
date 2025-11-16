#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include "BST.h"
#include "FileHandler.h"

void pause() {
    std::cout << "Nacisnij Enter";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int menu() {
    std::cout << "\n Menu \n";
    std::cout << "1. Dodaj element\n";
    std::cout << "2. Usun element\n";
    std::cout << "3. Usun cale drzewo\n";
    std::cout << "4. Szukaj drogi do elementu\n";
    std::cout << "5. Wyswietl drzewo (preorder/inorder/postorder)\n";
    std::cout << "6. Wyswietl drzewo (iteracyjne preorder - std::stack)\n";
    std::cout << "7. Wyswietl drzewo graficznie\n";
    std::cout << "8. Zapisz drzewo do pliku tekstowego (inorder)\n";
    std::cout << "9. Zapisz drzewo posortowane (std::sort)\n";
    std::cout << "10. Zapisz drzewo binarnie (preorder)\n";
    std::cout << "11. Wczytaj drzewo binarnie\n";
    std::cout << "12. Wczytaj plik tekstowy z liczbami\n";
    std::cout << "13. Pokaz size/empty/find\n";
    std::cout << "0. Wyjscie\n";
    std::cout << "Wybor: ";
    int c;
    if (!(std::cin >> c)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return -1;
    }
    std::cin.ignore(10000, '\n');
    return c;
}

int main() {
    BST tree;
    bool running = true;
    while (running) {
        int choice = menu();
        switch (choice) {
        case 1: {
            std::cout << "Podaj liczbe calkowita do dodania: ";
            int v;
            if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
            tree.insert(v);
            std::cout << "Dodano " << v << ".\n";
            std::cin.ignore(10000, '\n');
            break;
        }
        case 2: {
            std::cout << "Podaj liczbe do usuniecia: ";
            int v;
            if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
            bool ok = tree.erase(v);
            std::cout << (ok ? "Usunieto\n" : "Nie znaleziono elementu\n");
            std::cin.ignore(10000, '\n');
            break;
        }
        case 3: {
            tree.clear();
            std::cout << "Usunieto cale drzewo\n";
            break;
        }
        case 4: {
            std::cout << "Podaj szukany element: ";
            int v; if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
            auto path = tree.findPath(v);
            if (path.empty()) std::cout << "Element nie istnieje w drzewie\n";
            else {
                std::cout << "Sciezka: ";
                for (size_t i = 0; i < path.size(); ++i) {
                    if (i) std::cout << " -> ";
                    std::cout << path[i];
                }
                std::cout << "\n";
            }
            std::cin.ignore(10000, '\n');
            break;
        }
        case 5: {
            std::cout << "Wybierz metode: 1) preorder 2) inorder 3) postorder : ";
            int t; if (!(std::cin >> t)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
            if (t == 1) {
                tree.preorder([](int v) { std::cout << v << " "; });
            }
            else if (t == 2) {
                tree.inorder([](int v) { std::cout << v << " "; });
            }
            else {
                tree.postorder([](int v) { std::cout << v << " "; });
            }
            std::cout << "\n";
            std::cin.ignore(10000, '\n');
            break;
        }

