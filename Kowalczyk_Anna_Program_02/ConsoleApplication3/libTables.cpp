#include "libTables.h"
#include "libFunctions.h"

// Funkcja tworz¹ca dynamiczn¹ tablicê o podanym rozmiarze
int* f_utworzTablice(int rozmiarTablicy)
{
    int* wsk = nullptr; // Inicjalizacja wskaŸnika na nullptr

    try {
        wsk = new int[rozmiarTablicy] {}; // Próba utworzenia dynamicznej tablicy o rozmiarze rozmiarTablicy, inicjalizowana zerami
    }
    catch (bad_alloc) {
        cerr << "Blad przy utworzeniu"; // Komunikat o b³êdzie w przypadku niepowodzenia alokacji pamiêci
        exit(0); // Wyjœcie z programu
    }

    return wsk; // Zwrócenie wskaŸnika do nowo utworzonej tablicy
}

// Funkcja wype³niaj¹ca tablicê danymi wczytanymi z pliku
void f_wypelnijTablice(int* tab, int rozmiarTablicy, ifstream& odczyt) {
    int wczytana;
    for (int i = 0; i < rozmiarTablicy; i++) {
        odczyt >> wczytana; // Wczytanie liczby z pliku
        tab[i] = wczytana; // Przypisanie wczytanej liczby do odpowiedniego elementu tablicy
    }
}

// Funkcja wype³niaj¹ca tablicê danymi wygenerowanymi losowo z zadanego zakresu
void f_wypelnijTabliceGenerowanymi(int* tab, int rozmiarTablicy, long long poczatek, long long koniec) {
    long long liczba;
    for (int i = 0; i < rozmiarTablicy; i++) {
        liczba = f_generujLiczbe(poczatek, koniec); // Wygenerowanie losowej liczby z zadanego zakresu
        tab[i] = liczba; // Przypisanie wygenerowanej liczby do odpowiedniego elementu tablicy
    }
}

// Funkcja wyœwietlaj¹ca zawartoœæ tablicy
void f_wyswietlTablice(int* tab, int wymiarN) {
    for (int i = 0; i < wymiarN; i++) {
        cout << tab[i] << " ";  // Wyœwietlenie kolejnych elementów tablicy
    }
}

// Funkcja wypisuj¹ca zawartoœæ tablicy, wypisuj¹ca maksymalnie 200 pierwszych elementów w wierszu
void f_wypiszTablice(int* tablica, int rozmiar) {
    int iloscWypisanych = min(200, rozmiar); // Okreœlenie liczby elementów do wypisania (maksymalnie 200 lub ca³a tablica, jeœli jest krótsza)
    int wypisaneWiersze = iloscWypisanych / 50; // Obliczenie liczby pe³nych wierszy do wypisania

    for (int i = 0; i < wypisaneWiersze; ++i) {
        // Wypisanie kolejnych 50 elementów w wierszu
        for (int j = 0; j < 50; ++j) {
            cout << tablica[i * 50 + j] << " ";
        }
        cout << endl; // Przejœcie do nowej linii po ka¿dym wierszu
    }

    // Wypisanie pozosta³ych elementów (jeœli s¹) poza pe³nymi wierszami
    for (int i = wypisaneWiersze * 50; i < iloscWypisanych; ++i) {
        cout << tablica[i] << " ";
    }
}

