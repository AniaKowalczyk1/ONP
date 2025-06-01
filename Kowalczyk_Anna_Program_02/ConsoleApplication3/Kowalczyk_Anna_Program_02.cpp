#include <iostream>
#include <stack>
#include <string>
#include <unordered_map>
#include "libFiles.h"
#include "libFunctions.h"
using namespace std;



int main() {
    // Otwarcie strumienia odczytu z pliku
    ifstream odczyt;
    string nazwaPliku = "dane";
    f_odczytZpliku(odczyt, nazwaPliku);

    // Odczytanie liczby linii z pliku
    string liczbaLinii;
    getline(odczyt, liczbaLinii);

    // Sprawdzenie poprawności liczby linii
    if (!f_czyWzakresie(stoi(liczbaLinii), 1, 32768)) {
        cout << "bledna liczba linii";
        exit(0);
    }

    string wyrazenie; // Zmienna przechowująca aktualne wyrażenie
    string typWejsciowy; // Zmienna przechowująca typ wejściowy wyrażenia

    // Otwarcie strumienia zapisu do pliku
    ofstream zapis;
    string plikWyjsciowy = "zamienione";
    f_zapisDoPliku(zapis, plikWyjsciowy);

    string wynik; // Zmienna przechowująca wynik przetwarzania wyrażenia

    // Pętla wykonująca się dla każdego wyrażenia
    for (int i = 0; i < stoi(liczbaLinii); i++) {
        // Odczytanie kolejnego wyrażenia z pliku
        getline(odczyt, wyrazenie);

        // Sprawdzenie poprawności długości linii
        if (!f_czyWzakresie(wyrazenie.size(), 6, 256)) {
            cout << "Zla dlugos linii";
            exit(0);
        }

        // Sprawdzenie typu wejściowego wyrażenia (ONP lub INF)
        typWejsciowy = f_infCzyOnp(wyrazenie);

        // Wykonanie odpowiedniego przetwarzania w zależności od typu wyrażenia
        if (typWejsciowy == "Error") {
            cout << "Błąd, wyrażenie nie jest typu INF lub ONP!" << endl;
        }
        else if (typWejsciowy == "ONP") {
            // Usunięcie zbędnych znaków z wyrażenia
            wyrazenie = f_usun_zbedne_znaki(wyrazenie);

            // Sprawdzenie czy wyrażenie ONP jest wykonalne
            if (f_onp_wykonalne(wyrazenie)) {
                // Zamiana wyrażenia ONP na INF
                wynik = f_onp_do_infiks(wyrazenie);
                cout << "INF: " << wynik << endl;
                zapis << "INF: " << wynik << endl;
            }
            else {
                cout << "INF: Error" << endl;
                zapis << "INF: Error" << endl;
            }
        }
        else if (typWejsciowy == "INF") {
            // Usunięcie zbędnych znaków z wyrażenia
            wyrazenie = f_usun_zbedne_znaki(wyrazenie);

            // Sprawdzenie poprawności wyrażenia INF
            if (f_sprawdz_poprawnosc_infiksu(wyrazenie)) {
                // Zamiana wyrażenia INF na ONP
                wynik = f_infiks_do_onp(wyrazenie);
                cout << "ONP: " << wynik << endl;
                zapis << "ONP: " << wynik << endl;
            }
            else {
                cout << "ONP: error " << endl;
                zapis << "ONP: error " << endl;
            }
        }
        else {
            cout << "Inszy blad T-T" << endl;
        }
    }

    // Zamknięcie strumieni plików
    odczyt.close();
    zapis.close();

    return 0;
}
