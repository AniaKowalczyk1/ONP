#include "libTables.h"
#include "libFunctions.h"

// Funkcja tworz�ca dynamiczn� tablic� o podanym rozmiarze
int* f_utworzTablice(int rozmiarTablicy)
{
    int* wsk = nullptr; // Inicjalizacja wska�nika na nullptr

    try {
        wsk = new int[rozmiarTablicy] {}; // Pr�ba utworzenia dynamicznej tablicy o rozmiarze rozmiarTablicy, inicjalizowana zerami
    }
    catch (bad_alloc) {
        cerr << "Blad przy utworzeniu"; // Komunikat o b��dzie w przypadku niepowodzenia alokacji pami�ci
        exit(0); // Wyj�cie z programu
    }

    return wsk; // Zwr�cenie wska�nika do nowo utworzonej tablicy
}

// Funkcja wype�niaj�ca tablic� danymi wczytanymi z pliku
void f_wypelnijTablice(int* tab, int rozmiarTablicy, ifstream& odczyt) {
    int wczytana;
    for (int i = 0; i < rozmiarTablicy; i++) {
        odczyt >> wczytana; // Wczytanie liczby z pliku
        tab[i] = wczytana; // Przypisanie wczytanej liczby do odpowiedniego elementu tablicy
    }
}

// Funkcja wype�niaj�ca tablic� danymi wygenerowanymi losowo z zadanego zakresu
void f_wypelnijTabliceGenerowanymi(int* tab, int rozmiarTablicy, long long poczatek, long long koniec) {
    long long liczba;
    for (int i = 0; i < rozmiarTablicy; i++) {
        liczba = f_generujLiczbe(poczatek, koniec); // Wygenerowanie losowej liczby z zadanego zakresu
        tab[i] = liczba; // Przypisanie wygenerowanej liczby do odpowiedniego elementu tablicy
    }
}

// Funkcja wy�wietlaj�ca zawarto�� tablicy
void f_wyswietlTablice(int* tab, int wymiarN) {
    for (int i = 0; i < wymiarN; i++) {
        cout << tab[i] << " ";  // Wy�wietlenie kolejnych element�w tablicy
    }
}

// Funkcja wypisuj�ca zawarto�� tablicy, wypisuj�ca maksymalnie 200 pierwszych element�w w wierszu
void f_wypiszTablice(int* tablica, int rozmiar) {
    int iloscWypisanych = min(200, rozmiar); // Okre�lenie liczby element�w do wypisania (maksymalnie 200 lub ca�a tablica, je�li jest kr�tsza)
    int wypisaneWiersze = iloscWypisanych / 50; // Obliczenie liczby pe�nych wierszy do wypisania

    for (int i = 0; i < wypisaneWiersze; ++i) {
        // Wypisanie kolejnych 50 element�w w wierszu
        for (int j = 0; j < 50; ++j) {
            cout << tablica[i * 50 + j] << " ";
        }
        cout << endl; // Przej�cie do nowej linii po ka�dym wierszu
    }

    // Wypisanie pozosta�ych element�w (je�li s�) poza pe�nymi wierszami
    for (int i = wypisaneWiersze * 50; i < iloscWypisanych; ++i) {
        cout << tablica[i] << " ";
    }
}

