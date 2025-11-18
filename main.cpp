#include <iostream>
#include <limits>
#include <string>
#include <fstream>
#include "BST.h"
#include "FileHandler.h"

// Funkcja pomocnicza do pauzowania programu
void pause() {
    std::cout << "Nacisnij Enter";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

// Menu główne programu
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
    // Zabezpieczenie przed błędnym wprowadzeniem
    if (!(std::cin >> c)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        return -1;
    }
    std::cin.ignore(10000, '\n');
    return c;
}

int main() {
    BST tree; // Główne drzewo BST
    bool running = true;
    
    while (running) {
        int choice = menu();
        switch (choice) {
        case 1: {
            // Dodawanie elementu do drzewa
            std::cout << "Podaj liczbe calkowita do dodania: ";
            int v;
            if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
            tree.insert(v);
            std::cout << "Dodano " << v << ".\n";
            std::cin.ignore(10000, '\n');
            break;
        }
        case 2: {
            // Usuwanie elementu z drzewa
            std::cout << "Podaj liczbe do usuniecia: ";
            int v;
            if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
            bool ok = tree.erase(v);
            std::cout << (ok ? "Usunieto\n" : "Nie znaleziono elementu\n");
            std::cin.ignore(10000, '\n');
            break;
        }
        case 3: {
            // Usuwanie całego drzewa
            tree.clear();
            std::cout << "Usunieto cale drzewo\n";
            break;
        }
        case 4: {
            // Wyszukiwanie ścieżki do elementu
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
            // Wyświetlanie drzewa różnymi metodami
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
        case 6: {
            // Iteracyjne wyświetlanie preorder z użyciem stosu
            std::cout << "Iteracyjne preorder: ";
            tree.preorder_iterative([](int v) { std::cout << v << " "; });
            std::cout << "\n";
            break;
        }
        case 7: {
            // Graficzne wyświetlanie drzewa
            tree.printGraphical();
            break;
        }
        case 8: {
            // Zapis drzewa do pliku tekstowego w porządku inorder
            std::cout << "Podaj sciezke pliku tekstowego do zapisu: ";
            std::string path; std::getline(std::cin, path);
            if (tree.save_sorted(path) == false) { 
                // Alternatywny zapis jeśli główna metoda zawiedzie
                tree.to_vector_inorder();
                std::ofstream ofs(path);
                if (ofs) {
                    tree.inorder([&](int v) { ofs << v << "\n"; });
                    ofs.close();
                    std::cout << "Zapisano inorder\n";
                }
                else {
                    std::cout << "Blad zapisu\n";
                }
            }
            else {
                std::cout << "Zapisano posortowane\n";
            }
            break;
        }
        case 9: {
            // Zapis posortowanych wartości do pliku
            std::cout << "Podaj sciezke pliku do zapisu posortowanego: ";
            std::string path; std::getline(std::cin, path);
            if (tree.save_sorted(path)) std::cout << "Zapisano posortowane\n";
            else std::cout << "Blad zapisu\n";
            break;
        }
        case 10: {
            // Zapis drzewa do pliku binarnego
            std::cout << "Podaj sciezke pliku binarnego do zapisu: ";
            std::string path; std::getline(std::cin, path);
            if (FileHandler::saveBinary(tree, path)) std::cout << "Zapisano binarnie\n";
            else std::cout << "Blad zapisu\n";
            break;
        }
        case 11: {
            // Wczytywanie drzewa z pliku binarnego
            std::cout << "Podaj sciezke pliku binarnego do wczytania: ";
            std::string path; std::getline(std::cin, path);
            std::vector<int> vals;
            if (!FileHandler::loadBinary(vals, path)) {
                std::cout << "Blad odczytu\n";
            }
            else {
                std::cout << "Wczytano " << vals.size() << " elementow Wczytac do: 1) pustego drzewa 2) istniejacego drzewa ? ";
                int mode; if (!(std::cin >> mode)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
                if (mode == 1) tree.clear();
                for (int x : vals) tree.insert(x);
                std::cout << "Wstawiono elementy\n";
                std::cin.ignore(10000, '\n');
            }
            break;
        }
        case 12: {
            // Wczytywanie liczb z pliku tekstowego
            std::cout << "Podaj sciezke pliku tekstowego do wczytania : ";
            std::string path; std::getline(std::cin, path);
            std::vector<int> vals;
            if (!FileHandler::loadTextNumbers(vals, path)) {
                std::cout << "Blad odczytu\n";
            }
            else {
                std::cout << "Wczytano " << vals.size() << " liczb - Wczytac do: 1) pustego drzewa 2) istniejacego drzewa ? ";
                int mode; if (!(std::cin >> mode)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
                if (mode == 1) tree.clear();
                for (int x : vals) tree.insert(x);
                std::cout << "Wstawiono elementy\n";
                std::cin.ignore(10000, '\n');
            }
            break;
        }
        case 13: {
            // Informacje o drzewie i wyszukiwanie
            std::cout << "Size: " << tree.size() << "\n";
            std::cout << "Empty: " << (tree.empty() ? "tak" : "nie") << "\n";
            std::cout << "Podaj wartosc do find(): ";
            int v; if (!(std::cin >> v)) { std::cin.clear(); std::cin.ignore(10000, '\n'); break; }
            std::cout << (tree.find(v) ? "Znaleziono\n" : "Nie znaleziono\n");
            std::cin.ignore(10000, '\n');
            break;
        }
        case 0:
            running = false;
            break;
        default:
            std::cout << "Nieprawidlowy wybor\n";
        }
    }
    std::cout << "Koniec programu \n";
    return 0;
}
