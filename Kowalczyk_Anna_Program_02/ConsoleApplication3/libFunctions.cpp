#include "libFunctions.h"

// Inicjalizacja mapy priorytet�w operator�w
std::unordered_map<char, int> priorytety = {
    {'~', 5}, // Operator unarny
    {'^', 4}, // Operator pot�gowania
    {'*', 3}, {'/', 3}, {'%', 3}, // Operator multiplikatywny
    {'+', 2}, {'-', 2}, // Operator addytywny
    {'<', 1}, {'>', 1}, // Operator relacyjny
    {'=', 0} // Operator przypisania
};



//Funkcja sprawdzaj�ca, czy dany znak jest zdefiniowanym przez nas operatorem
bool f_jest_operatorem(char c) {
    return priorytety.find(c) != priorytety.end();
}



//Funkcja sprawdzaj�ca, czy dane wyra�enie jest typu ONP czy INF
string f_infCzyOnp(string wyrazenie) {
    string typ;
    //je�eli na pocz�tku wyra�enia s� odpowiednie litery to przypisuje ONP lub INF do zmiennej, w przeciwnym przypadku Error
    if (wyrazenie[0] == 'I' and wyrazenie[1] == 'N' and wyrazenie[2] == 'F' and wyrazenie[3] == ':') {
        typ = "INF";
    }
    else if (wyrazenie[0] == 'O' and wyrazenie[1] == 'N' and wyrazenie[2] == 'P' and wyrazenie[3] == ':') {
        typ = "ONP";
    }
    else {
        typ = "Error";
    }
    return typ;
}





//Funkcja zwracaj�ca wyra�enie bez zb�dnych znak�w
string f_usun_zbedne_znaki(string wyrazenie) {
    string poprawne_wyrazenie;
    //zmienne pomocnicze, je�eli pierwsza wczytana b�dzie litera to zmieni to zmienn� na true, co sprawi �e potem wczytane zostan� jedynie litery a cyfry b�d� usuwane
    bool litera = false;
    bool cyfra = false;

    //p�tla przechodz�ca przez wszystkie znaki w podanym wyra�eniu, pomijaj�c pierwsze zawieraj�ce info o typie(ONP,INF)
    for (int i = 4; i < wyrazenie.length(); i++) {
        char znak = wyrazenie[i];
        //je�eli znak jest liter�
        if (isalpha(znak)) {
            //je�eli cyfra nadal jest false, czyli nie wczytali�my wcze�niej �adnej cyfry
            if (!cyfra) {
                //zmieniamy litera na true, b�d� od teraz wczytywane litery a cyfry pomijane
                litera = true;
                //dodajemy znak do ko�cowego poprawionego wyra�enia
                poprawne_wyrazenie += znak;
            }
        }
        //je�eli znak jest cyfr�
        else if (isdigit(znak)) {
            if (!litera) {
                cyfra = true;
                poprawne_wyrazenie += znak;
            }
        }
        //je�eli znak jest operatorem, kt�ry zainicjowali�my lub nawiasem
        else if (f_jest_operatorem(znak) || znak == '(' || znak == ')') {
            poprawne_wyrazenie += znak;
        }
    }

    return poprawne_wyrazenie;
}






//Funkcja sprawdzaj�ca, czy dane wyra�enie ONP jest wykonalne
bool f_onp_wykonalne(string onp_wyrazenie) {
    stack<int> stos;

    for (size_t i = 0; i < onp_wyrazenie.size(); ++i) {
        char znak = onp_wyrazenie[i];
        if (isdigit(znak) || isalpha(znak)) {
            stos.push(0); // Wstawiamy na stos operand dla ka�dej cyfry lub litery
        }
        else if (f_jest_operatorem(znak)) {
            if (stos.size() < 2 && znak != '~') {
                return false; // Za ma�o operand�w, unarne operatory mog� mie� tylko jeden operand
            }
            if (znak != '~') {
                // Usuwamy dwa operandy ze stosu i dodajemy jeden wynik operacji
                stos.pop();
                stos.pop();
                stos.push(0); // Dodajemy operand po wykonaniu operacji
            }
            else {
                if (stos.empty()) {
                    return false; // Brak operandu dla operatora unarnego
                }
                stos.pop(); // Usuwamy jeden operand dla operatora unarnego
                stos.push(0); // Dodajemy operand po wykonaniu operacji unarnej
            }
        }
    }

    // Sprawdzamy, czy na ko�cu jest tylko jeden operand
    return stos.size() == 1;
}



//Funkcja zamieniaj�ca wyrazenie ONP na INF
string f_onp_do_infiks(const string& onp_wyrazenie) {
    stack<string> stos; // Tworzenie stosu do przechowywania cz�ciowych wynik�w

    // Iteracja po wszystkich znakach wyra�enia ONP
    for (size_t i = 0; i < onp_wyrazenie.size(); ++i) {
        char znak = onp_wyrazenie[i]; // Aktualnie rozpatrywany znak

        // Je�li znak jest alfanumeryczny (cyfr� lub liter�)
        if (isalnum(znak)) {
            string operand(1, znak); // Tworzenie stringa zawieraj�cego pojedynczy znak
            stos.push(operand); // Umieszczanie operandu na stosie
        }
        else if (f_jest_operatorem(znak)) {
            // Obs�uga unarnego operatora '~'
            if (znak == '~') {
                if (stos.empty()) { // Sprawdzenie, czy stos nie jest pusty
                    return "ONP: error"; // B��d: brak operandu dla operatora unarnego
                }
                string operand2 = stos.top(); // Pobranie operandu z wierzcho�ka stosu
                stos.pop(); // Usuni�cie operandu ze stosu
                string wynik = znak + operand2; // Po��czenie operatora z operandem
                stos.push(wynik); // Umieszczenie wyniku na stosie
            }
            else {
                if (stos.size() < 2) { // Sprawdzenie, czy na stosie s� co najmniej dwa operandy
                    return "B��d: Niepoprawne wyra�enie ONP."; // B��d: niepoprawne wyra�enie ONP
                }
                string operand2 = stos.top(); // Pobranie drugiego operandu z wierzcho�ka stosu
                stos.pop(); // Usuni�cie drugiego operandu ze stosu
                string operand1 = stos.top(); // Pobranie pierwszego operandu z wierzcho�ka stosu
                stos.pop(); // Usuni�cie pierwszego operandu ze stosu

                string wynik; // Zmienna przechowuj�ca wynik operacji

                bool same_priority = false; // Flaga okre�laj�ca, czy operator ma taki sam priorytet jak kolejny operator
                if (i + 1 < onp_wyrazenie.size() && f_jest_operatorem(onp_wyrazenie[i + 1]) &&
                    priorytety[onp_wyrazenie[i + 1]] == priorytety[znak]) {
                    same_priority = true; // Ustawienie flagi, je�li kolejny operator ma ten sam priorytet
                }
                // Je�li stos nie jest pusty, kolejny znak nie jest operatorem, bie��cy znak nie jest pierwszym
                // w wyra�eniu i operator nie ma takiego samego priorytetu jak kolejny operator
                if (!stos.empty() && !f_jest_operatorem(onp_wyrazenie[i + 1]) && i != 0 && !same_priority) {
                    wynik = operand1 + " " + znak + " " + operand2; // Tworzenie cz�ciowego wyniku
                }
                // Zawijanie w nawiasy, je�li kolejny operator ma taki sam priorytet
                else if (same_priority) {
                    wynik = "(" + operand1 + " " + znak + " " + operand2 + ")";
                }
                else {
                    wynik = operand1 + " " + znak + " " + operand2;
                }
                stos.push(wynik); // Umieszczenie wyniku na stosie
            }
        }
    }

    // Sprawdzenie, czy stos jest pusty po przej�ciu ca�ego wyra�enia ONP
    if (stos.empty()) {
        return "B��d: Niepoprawne wyra�enie ONP."; // B��d: niepoprawne wyra�enie ONP
    }

    return stos.top(); // Zwr�cenie wyniku jako wynikowa posta� INF
}





//Funkcja zamieniaj�ca wyrazenie INF na ONP
string f_infiks_do_onp(string infiksowe_wyrazenie) {
    stack<char> stos_operacji; // Stos przechowuj�cy operatory
    string onp_wyrazenie; // Zmienna przechowuj�ca wyra�enie w postaci ONP

    // Iteracja po wszystkich znakach wyra�enia infiksowego
    for (int i = 0; i < infiksowe_wyrazenie.length(); i++) {
        char znak = infiksowe_wyrazenie[i]; // Aktualnie rozpatrywany znak

        // Dodawanie cyfr i liter do wyra�enia ONP
        if (isdigit(znak) || isalpha(znak)) {
            onp_wyrazenie += znak;
        }
        // Obs�uga otwieraj�cych nawias�w
        else if (znak == '(') {
            stos_operacji.push(znak); // Umieszczanie otwartego nawiasu na stosie
        }
        // Obs�uga zamykaj�cych nawias�w
        else if (znak == ')') {
            // Dop�ki stos nie jest pusty i na jego szczycie nie ma otwartego nawiasu
            while (!stos_operacji.empty() && stos_operacji.top() != '(') {
                onp_wyrazenie += stos_operacji.top(); // Dodawanie operator�w do wyra�enia ONP
                stos_operacji.pop(); // Usuwanie operator�w ze stosu
            }
            if (stos_operacji.empty()) {
                throw logic_error("Error"); // B��d: niepoprawne sparowanie nawias�w
            }
            stos_operacji.pop(); // Usu� '(' ze stosu
        }
        // Obs�uga operator�w
        else if (f_jest_operatorem(znak)) {
            // Obs�uga operatora  
            if (znak == '=' || znak == '^' || znak == '~') {
                // Dop�ki stos nie jest pusty i na jego szczycie jest operator o wy�szym priorytecie 
                while (!stos_operacji.empty() && priorytety[stos_operacji.top()] > priorytety[znak]) {
                    onp_wyrazenie += stos_operacji.top(); // Dodawanie operator�w do wyra�enia ONP
                    stos_operacji.pop(); // Usuwanie operator�w ze stosu
                }
                stos_operacji.push(znak); // Umieszczenie  na stosie
            }
            // Obs�uga pozosta�ych operator�w
            else {
                // Dop�ki stos nie jest pusty i na jego szczycie jest operator o wy�szym lub r�wnym priorytecie ni� bie��cy operator
                while (!stos_operacji.empty() && priorytety[stos_operacji.top()] >= priorytety[znak]) {
                    onp_wyrazenie += stos_operacji.top(); // Dodawanie operator�w do wyra�enia ONP
                    stos_operacji.pop(); // Usuwanie operator�w ze stosu
                }
                stos_operacji.push(znak); // Umieszczenie bie��cego operatora na stosie
            }
        }
    }

    // Dodanie pozosta�ych operator�w ze stosu do wyra�enia ONP
    while (!stos_operacji.empty()) {
        onp_wyrazenie += stos_operacji.top();
        stos_operacji.pop();
    }

    return onp_wyrazenie; // Zwr�cenie wyra�enia w postaci ONP
}





//Funkcja sprawdzaj�ca, czy dane wyra�enie INF jest poprawne
bool f_sprawdz_poprawnosc_infiksu(const string& infiksowe_wyrazenie) {
    stack<char> nawiasy;

    for (size_t i = 0; i < infiksowe_wyrazenie.size(); ++i) {
        char znak = infiksowe_wyrazenie[i];

        // Sprawdzenie czy nawiasy s� poprawnie sparowane
        if (znak == '(') {
            nawiasy.push(znak);
        }
        else if (znak == ')') {
            if (nawiasy.empty()) {
                return false; // Niepoprawne sparowanie nawias�w
            }
            nawiasy.pop();
        }

        // Sprawdzenie czy dwie litery nie stoj� obok siebie
        if (i > 0 && isalpha(znak) && isalpha(infiksowe_wyrazenie[i - 1])) {
            return false; // Dwie litery stoj� obok siebie
        }
    }

    return nawiasy.empty(); // Poprawne sparowanie nawias�w, je�li stos jest pusty
}

























// Funkcja sprawdzaj�ca, czy podana liczba znajduje si� w okre�lonym zakresie
bool f_czyWzakresie(int podana, int poczatek, int koniec)
{
    if (podana >= poczatek and podana <= koniec) {
        return true;  // Zwraca true, je�li liczba znajduje si� w zakresie
    }
    else {
        return false; // Zwraca false, je�li liczba nie znajduje si� w zakresie
    }
}

// Funkcja generuj�ca losow� liczb� z zadanego zakresu
long long f_generujLiczbe(long long poczatek, long long koniec) {
    long long liczba;  // Zmienna przechowuj�ca wygenerowan� liczb�
    random_device rd;  // Inicjalizacja generatora liczb losowych
    mt19937 mt(rd());
    uniform_int_distribution<long long> dist(poczatek, koniec);
    liczba = dist(mt);

    return liczba; // Zwraca wygenerowan� losow� liczb�
}

// Funkcja zliczaj�ca ilo�� wyst�pie� danej liczby w posortowanej tablicy
int f_iloscPodanejLiczby(int* tab, int rozmiar, int szukana)
{
    int licznik = 0;  //zmienna przechowuj�ca ilo�� wyst�pie� danej liczby
    int srodek = 0;  //indeks �rodka tablicy
    int lewa = 0;  //indeks lewego ko�ca tablicy
    int prawa = rozmiar - 1;  //indeks prawego ko�ca tablicy

    while (lewa <= prawa) {
        srodek = (lewa + prawa) / 2;  //obliczenie �rodka zakresu

        if (tab[srodek] == szukana) {
            licznik++;

            // Znajdowanie wszystkich wyst�pie� danej liczby na lewo od �rodka
            int i = srodek - 1;
            while (tab[i] == szukana && i >= 0) {
                i--;
                licznik++;
            }
            // Znajdowanie wszystkich wyst�pie� danej liczby na prawo od �rodka
            int j = srodek + 1;
            while (tab[j] == szukana && j < rozmiar) {
                j++;
                licznik++;
            }
            break;
        }
        if (tab[srodek] > szukana) {
            prawa = srodek - 1;  //przesuni�cie zakresu na lew� po�ow�, je�eli szukana jest mniejsza ni� warto�� �rodkowa
        }
        else {
            lewa = srodek + 1;  //przesuni�cie zakresu na praw� po�ow�, je�eli szukana jest wi�ksza ni� warto�� �rodkowa
        }
    }
    return licznik; // Zwraca liczb� wyst�pie� szukanej liczby w tablicy
}

// Funkcja znajduj�ca indeks wyst�pienia podanej liczby w posortowanej tablicy
int f_indeksPodanegoElementu(int* tab, int rozmiar, int szukana, int licznik) {
    if (licznik == rozmiar) {
        return 0; // Tablica zawiera tylko szukan� liczb�, zwraca indeks 0
    }

    int ip = 0;  //indeks pocz�tkowy
    int ik = rozmiar - 1;  //indeks ko�cowy

    while (ip <= ik && szukana >= tab[ip] && szukana <= tab[ik]) {
        int isr = ip + (((double)(ik - ip) / (tab[ik] - tab[ip])) * (szukana - tab[ip]));

        if (isr < 0 || isr >= rozmiar) {
            return -1; // Zabezpieczenie przed wyj�ciem poza zakres tablicy
        }

        if (tab[isr] == szukana)
            return isr; // Zwraca indeks wyst�pienia szukanej liczby

        if (tab[isr] < szukana)
            ip = isr + 1;
        else
            ik = isr - 1;
    }

    return -1; // Brak znalezionego elementu
}

// Funkcja usuwaj�ca duplikaty z tablicy oraz zmniejszaj�ca jej rozmiar
int* f_usunDuplikaty(int* tab, int& rozmiar) {

    int j = 0; // Zmienna przechowuj�ca indeks ostatniego unikalnego elementu w nowej tablicy
    for (int i = 0; i < rozmiar ; i++) {
        // Sprawdzenie, czy aktualny element jest r�ny od nast�pnego
        if (tab[i] != tab[i + 1]) {
            j++;
            tab[j] = tab[i + 1]; // Przepisanie nast�pnego elementu do "nowej" tablicy
        }
    }


    // Tworzenie nowej tablicy bez duplikat�w
    int* nowaTablica = new int[j + 1];
    for (int i = 0; i < j; i++) {
        nowaTablica[i] = tab[i]; // Przepisanie unikalnych element�w do nowej tablicy
    }
    rozmiar = j; // Aktualizacja rozmiaru tablicy

    delete[] tab; // Zwolnienie pami�ci poprzedniej tablicy
    return nowaTablica; // Zwraca now� tablic� bez duplikat�w
}
