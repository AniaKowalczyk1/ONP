#include "libFunctions.h"

// Inicjalizacja mapy priorytetów operatorów
std::unordered_map<char, int> priorytety = {
    {'~', 5}, // Operator unarny
    {'^', 4}, // Operator potêgowania
    {'*', 3}, {'/', 3}, {'%', 3}, // Operator multiplikatywny
    {'+', 2}, {'-', 2}, // Operator addytywny
    {'<', 1}, {'>', 1}, // Operator relacyjny
    {'=', 0} // Operator przypisania
};



//Funkcja sprawdzaj¹ca, czy dany znak jest zdefiniowanym przez nas operatorem
bool f_jest_operatorem(char c) {
    return priorytety.find(c) != priorytety.end();
}



//Funkcja sprawdzaj¹ca, czy dane wyra¿enie jest typu ONP czy INF
string f_infCzyOnp(string wyrazenie) {
    string typ;
    //je¿eli na pocz¹tku wyra¿enia s¹ odpowiednie litery to przypisuje ONP lub INF do zmiennej, w przeciwnym przypadku Error
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





//Funkcja zwracaj¹ca wyra¿enie bez zbêdnych znaków
string f_usun_zbedne_znaki(string wyrazenie) {
    string poprawne_wyrazenie;
    //zmienne pomocnicze, je¿eli pierwsza wczytana bêdzie litera to zmieni to zmienn¹ na true, co sprawi ¿e potem wczytane zostan¹ jedynie litery a cyfry bêd¹ usuwane
    bool litera = false;
    bool cyfra = false;

    //pêtla przechodz¹ca przez wszystkie znaki w podanym wyra¿eniu, pomijaj¹c pierwsze zawieraj¹ce info o typie(ONP,INF)
    for (int i = 4; i < wyrazenie.length(); i++) {
        char znak = wyrazenie[i];
        //je¿eli znak jest liter¹
        if (isalpha(znak)) {
            //je¿eli cyfra nadal jest false, czyli nie wczytaliœmy wczeœniej ¿adnej cyfry
            if (!cyfra) {
                //zmieniamy litera na true, bêd¹ od teraz wczytywane litery a cyfry pomijane
                litera = true;
                //dodajemy znak do koñcowego poprawionego wyra¿enia
                poprawne_wyrazenie += znak;
            }
        }
        //je¿eli znak jest cyfr¹
        else if (isdigit(znak)) {
            if (!litera) {
                cyfra = true;
                poprawne_wyrazenie += znak;
            }
        }
        //je¿eli znak jest operatorem, który zainicjowaliœmy lub nawiasem
        else if (f_jest_operatorem(znak) || znak == '(' || znak == ')') {
            poprawne_wyrazenie += znak;
        }
    }

    return poprawne_wyrazenie;
}






//Funkcja sprawdzaj¹ca, czy dane wyra¿enie ONP jest wykonalne
bool f_onp_wykonalne(string onp_wyrazenie) {
    stack<int> stos;

    for (size_t i = 0; i < onp_wyrazenie.size(); ++i) {
        char znak = onp_wyrazenie[i];
        if (isdigit(znak) || isalpha(znak)) {
            stos.push(0); // Wstawiamy na stos operand dla ka¿dej cyfry lub litery
        }
        else if (f_jest_operatorem(znak)) {
            if (stos.size() < 2 && znak != '~') {
                return false; // Za ma³o operandów, unarne operatory mog¹ mieæ tylko jeden operand
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

    // Sprawdzamy, czy na koñcu jest tylko jeden operand
    return stos.size() == 1;
}



//Funkcja zamieniaj¹ca wyrazenie ONP na INF
string f_onp_do_infiks(const string& onp_wyrazenie) {
    stack<string> stos; // Tworzenie stosu do przechowywania czêœciowych wyników

    // Iteracja po wszystkich znakach wyra¿enia ONP
    for (size_t i = 0; i < onp_wyrazenie.size(); ++i) {
        char znak = onp_wyrazenie[i]; // Aktualnie rozpatrywany znak

        // Jeœli znak jest alfanumeryczny (cyfr¹ lub liter¹)
        if (isalnum(znak)) {
            string operand(1, znak); // Tworzenie stringa zawieraj¹cego pojedynczy znak
            stos.push(operand); // Umieszczanie operandu na stosie
        }
        else if (f_jest_operatorem(znak)) {
            // Obs³uga unarnego operatora '~'
            if (znak == '~') {
                if (stos.empty()) { // Sprawdzenie, czy stos nie jest pusty
                    return "ONP: error"; // B³¹d: brak operandu dla operatora unarnego
                }
                string operand2 = stos.top(); // Pobranie operandu z wierzcho³ka stosu
                stos.pop(); // Usuniêcie operandu ze stosu
                string wynik = znak + operand2; // Po³¹czenie operatora z operandem
                stos.push(wynik); // Umieszczenie wyniku na stosie
            }
            else {
                if (stos.size() < 2) { // Sprawdzenie, czy na stosie s¹ co najmniej dwa operandy
                    return "B³¹d: Niepoprawne wyra¿enie ONP."; // B³¹d: niepoprawne wyra¿enie ONP
                }
                string operand2 = stos.top(); // Pobranie drugiego operandu z wierzcho³ka stosu
                stos.pop(); // Usuniêcie drugiego operandu ze stosu
                string operand1 = stos.top(); // Pobranie pierwszego operandu z wierzcho³ka stosu
                stos.pop(); // Usuniêcie pierwszego operandu ze stosu

                string wynik; // Zmienna przechowuj¹ca wynik operacji

                bool same_priority = false; // Flaga okreœlaj¹ca, czy operator ma taki sam priorytet jak kolejny operator
                if (i + 1 < onp_wyrazenie.size() && f_jest_operatorem(onp_wyrazenie[i + 1]) &&
                    priorytety[onp_wyrazenie[i + 1]] == priorytety[znak]) {
                    same_priority = true; // Ustawienie flagi, jeœli kolejny operator ma ten sam priorytet
                }
                // Jeœli stos nie jest pusty, kolejny znak nie jest operatorem, bie¿¹cy znak nie jest pierwszym
                // w wyra¿eniu i operator nie ma takiego samego priorytetu jak kolejny operator
                if (!stos.empty() && !f_jest_operatorem(onp_wyrazenie[i + 1]) && i != 0 && !same_priority) {
                    wynik = operand1 + " " + znak + " " + operand2; // Tworzenie czêœciowego wyniku
                }
                // Zawijanie w nawiasy, jeœli kolejny operator ma taki sam priorytet
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

    // Sprawdzenie, czy stos jest pusty po przejœciu ca³ego wyra¿enia ONP
    if (stos.empty()) {
        return "B³¹d: Niepoprawne wyra¿enie ONP."; // B³¹d: niepoprawne wyra¿enie ONP
    }

    return stos.top(); // Zwrócenie wyniku jako wynikowa postaæ INF
}





//Funkcja zamieniaj¹ca wyrazenie INF na ONP
string f_infiks_do_onp(string infiksowe_wyrazenie) {
    stack<char> stos_operacji; // Stos przechowuj¹cy operatory
    string onp_wyrazenie; // Zmienna przechowuj¹ca wyra¿enie w postaci ONP

    // Iteracja po wszystkich znakach wyra¿enia infiksowego
    for (int i = 0; i < infiksowe_wyrazenie.length(); i++) {
        char znak = infiksowe_wyrazenie[i]; // Aktualnie rozpatrywany znak

        // Dodawanie cyfr i liter do wyra¿enia ONP
        if (isdigit(znak) || isalpha(znak)) {
            onp_wyrazenie += znak;
        }
        // Obs³uga otwieraj¹cych nawiasów
        else if (znak == '(') {
            stos_operacji.push(znak); // Umieszczanie otwartego nawiasu na stosie
        }
        // Obs³uga zamykaj¹cych nawiasów
        else if (znak == ')') {
            // Dopóki stos nie jest pusty i na jego szczycie nie ma otwartego nawiasu
            while (!stos_operacji.empty() && stos_operacji.top() != '(') {
                onp_wyrazenie += stos_operacji.top(); // Dodawanie operatorów do wyra¿enia ONP
                stos_operacji.pop(); // Usuwanie operatorów ze stosu
            }
            if (stos_operacji.empty()) {
                throw logic_error("Error"); // B³¹d: niepoprawne sparowanie nawiasów
            }
            stos_operacji.pop(); // Usuñ '(' ze stosu
        }
        // Obs³uga operatorów
        else if (f_jest_operatorem(znak)) {
            // Obs³uga operatora  
            if (znak == '=' || znak == '^' || znak == '~') {
                // Dopóki stos nie jest pusty i na jego szczycie jest operator o wy¿szym priorytecie 
                while (!stos_operacji.empty() && priorytety[stos_operacji.top()] > priorytety[znak]) {
                    onp_wyrazenie += stos_operacji.top(); // Dodawanie operatorów do wyra¿enia ONP
                    stos_operacji.pop(); // Usuwanie operatorów ze stosu
                }
                stos_operacji.push(znak); // Umieszczenie  na stosie
            }
            // Obs³uga pozosta³ych operatorów
            else {
                // Dopóki stos nie jest pusty i na jego szczycie jest operator o wy¿szym lub równym priorytecie ni¿ bie¿¹cy operator
                while (!stos_operacji.empty() && priorytety[stos_operacji.top()] >= priorytety[znak]) {
                    onp_wyrazenie += stos_operacji.top(); // Dodawanie operatorów do wyra¿enia ONP
                    stos_operacji.pop(); // Usuwanie operatorów ze stosu
                }
                stos_operacji.push(znak); // Umieszczenie bie¿¹cego operatora na stosie
            }
        }
    }

    // Dodanie pozosta³ych operatorów ze stosu do wyra¿enia ONP
    while (!stos_operacji.empty()) {
        onp_wyrazenie += stos_operacji.top();
        stos_operacji.pop();
    }

    return onp_wyrazenie; // Zwrócenie wyra¿enia w postaci ONP
}





//Funkcja sprawdzaj¹ca, czy dane wyra¿enie INF jest poprawne
bool f_sprawdz_poprawnosc_infiksu(const string& infiksowe_wyrazenie) {
    stack<char> nawiasy;

    for (size_t i = 0; i < infiksowe_wyrazenie.size(); ++i) {
        char znak = infiksowe_wyrazenie[i];

        // Sprawdzenie czy nawiasy s¹ poprawnie sparowane
        if (znak == '(') {
            nawiasy.push(znak);
        }
        else if (znak == ')') {
            if (nawiasy.empty()) {
                return false; // Niepoprawne sparowanie nawiasów
            }
            nawiasy.pop();
        }

        // Sprawdzenie czy dwie litery nie stoj¹ obok siebie
        if (i > 0 && isalpha(znak) && isalpha(infiksowe_wyrazenie[i - 1])) {
            return false; // Dwie litery stoj¹ obok siebie
        }
    }

    return nawiasy.empty(); // Poprawne sparowanie nawiasów, jeœli stos jest pusty
}

























// Funkcja sprawdzaj¹ca, czy podana liczba znajduje siê w okreœlonym zakresie
bool f_czyWzakresie(int podana, int poczatek, int koniec)
{
    if (podana >= poczatek and podana <= koniec) {
        return true;  // Zwraca true, jeœli liczba znajduje siê w zakresie
    }
    else {
        return false; // Zwraca false, jeœli liczba nie znajduje siê w zakresie
    }
}

// Funkcja generuj¹ca losow¹ liczbê z zadanego zakresu
long long f_generujLiczbe(long long poczatek, long long koniec) {
    long long liczba;  // Zmienna przechowuj¹ca wygenerowan¹ liczbê
    random_device rd;  // Inicjalizacja generatora liczb losowych
    mt19937 mt(rd());
    uniform_int_distribution<long long> dist(poczatek, koniec);
    liczba = dist(mt);

    return liczba; // Zwraca wygenerowan¹ losow¹ liczbê
}

// Funkcja zliczaj¹ca iloœæ wyst¹pieñ danej liczby w posortowanej tablicy
int f_iloscPodanejLiczby(int* tab, int rozmiar, int szukana)
{
    int licznik = 0;  //zmienna przechowuj¹ca iloœæ wyst¹pieñ danej liczby
    int srodek = 0;  //indeks œrodka tablicy
    int lewa = 0;  //indeks lewego koñca tablicy
    int prawa = rozmiar - 1;  //indeks prawego koñca tablicy

    while (lewa <= prawa) {
        srodek = (lewa + prawa) / 2;  //obliczenie œrodka zakresu

        if (tab[srodek] == szukana) {
            licznik++;

            // Znajdowanie wszystkich wyst¹pieñ danej liczby na lewo od œrodka
            int i = srodek - 1;
            while (tab[i] == szukana && i >= 0) {
                i--;
                licznik++;
            }
            // Znajdowanie wszystkich wyst¹pieñ danej liczby na prawo od œrodka
            int j = srodek + 1;
            while (tab[j] == szukana && j < rozmiar) {
                j++;
                licznik++;
            }
            break;
        }
        if (tab[srodek] > szukana) {
            prawa = srodek - 1;  //przesuniêcie zakresu na lew¹ po³owê, je¿eli szukana jest mniejsza ni¿ wartoœæ œrodkowa
        }
        else {
            lewa = srodek + 1;  //przesuniêcie zakresu na praw¹ po³owê, je¿eli szukana jest wiêksza ni¿ wartoœæ œrodkowa
        }
    }
    return licznik; // Zwraca liczbê wyst¹pieñ szukanej liczby w tablicy
}

// Funkcja znajduj¹ca indeks wyst¹pienia podanej liczby w posortowanej tablicy
int f_indeksPodanegoElementu(int* tab, int rozmiar, int szukana, int licznik) {
    if (licznik == rozmiar) {
        return 0; // Tablica zawiera tylko szukan¹ liczbê, zwraca indeks 0
    }

    int ip = 0;  //indeks pocz¹tkowy
    int ik = rozmiar - 1;  //indeks koñcowy

    while (ip <= ik && szukana >= tab[ip] && szukana <= tab[ik]) {
        int isr = ip + (((double)(ik - ip) / (tab[ik] - tab[ip])) * (szukana - tab[ip]));

        if (isr < 0 || isr >= rozmiar) {
            return -1; // Zabezpieczenie przed wyjœciem poza zakres tablicy
        }

        if (tab[isr] == szukana)
            return isr; // Zwraca indeks wyst¹pienia szukanej liczby

        if (tab[isr] < szukana)
            ip = isr + 1;
        else
            ik = isr - 1;
    }

    return -1; // Brak znalezionego elementu
}

// Funkcja usuwaj¹ca duplikaty z tablicy oraz zmniejszaj¹ca jej rozmiar
int* f_usunDuplikaty(int* tab, int& rozmiar) {

    int j = 0; // Zmienna przechowuj¹ca indeks ostatniego unikalnego elementu w nowej tablicy
    for (int i = 0; i < rozmiar ; i++) {
        // Sprawdzenie, czy aktualny element jest ró¿ny od nastêpnego
        if (tab[i] != tab[i + 1]) {
            j++;
            tab[j] = tab[i + 1]; // Przepisanie nastêpnego elementu do "nowej" tablicy
        }
    }


    // Tworzenie nowej tablicy bez duplikatów
    int* nowaTablica = new int[j + 1];
    for (int i = 0; i < j; i++) {
        nowaTablica[i] = tab[i]; // Przepisanie unikalnych elementów do nowej tablicy
    }
    rozmiar = j; // Aktualizacja rozmiaru tablicy

    delete[] tab; // Zwolnienie pamiêci poprzedniej tablicy
    return nowaTablica; // Zwraca now¹ tablicê bez duplikatów
}
