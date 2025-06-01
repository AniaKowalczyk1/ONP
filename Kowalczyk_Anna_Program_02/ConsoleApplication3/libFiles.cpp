#include "libFiles.h"

// Funkcja otwieraj¹ca plik do zapisu
void f_zapisDoPliku(ofstream& zapis, string& nazwaPliku) {

    int dlugosc = nazwaPliku.size();  // Pobranie d³ugoœci nazwy pliku
    // Sprawdzenie, czy nazwa pliku ma rozszerzenie ".txt", jeœli nie, dodaj je
    if ((dlugosc <= 4) or (nazwaPliku[dlugosc - 4] != '.' or nazwaPliku[dlugosc - 3] != 't' or nazwaPliku[dlugosc - 2] != 'x' or nazwaPliku[dlugosc - 1] != 't')) {
        nazwaPliku += ".txt"; // Dodanie rozszerzenia ".txt", jeœli nie zosta³o podane
    }

    zapis.open(nazwaPliku); // Otwarcie pliku o podanej nazwie do zapisu

    // Sprawdzenie, czy plik zosta³ poprawnie otwarty
    if (!zapis) {
        cout << "\n Nie moge otworzyc pliku!"; // Komunikat o b³êdzie
        cin.ignore();
        (void)getchar();
        exit(0); // Wyjœcie z programu w przypadku b³êdu
    }
}

// Funkcja otwieraj¹ca plik do odczytu
void f_odczytZpliku(ifstream& odczyt, string& nazwaPliku) {

    int dlugosc = nazwaPliku.size();  // Pobranie d³ugoœci nazwy pliku
    // Sprawdzenie, czy nazwa pliku ma rozszerzenie ".txt", jeœli nie, dodaj je
    if ((dlugosc <= 4) or (nazwaPliku[dlugosc - 4] != '.' or nazwaPliku[dlugosc - 3] != 't' or nazwaPliku[dlugosc - 2] != 'x' or nazwaPliku[dlugosc - 1] != 't')) {
        nazwaPliku += ".txt"; // Dodanie rozszerzenia ".txt", jeœli nie zosta³o podane
    }

    odczyt.open(nazwaPliku); // Otwarcie pliku o podanej nazwie do odczytu

    // Sprawdzenie, czy plik zosta³ poprawnie otwarty
    if (!odczyt) {
        cout << "\n Nie moge utworzyc pliku!"; // Komunikat o b³êdzie
        cin.ignore();
        (void)getchar();
        exit(0); // Wyjœcie z programu w przypadku b³êdu
    }
}
