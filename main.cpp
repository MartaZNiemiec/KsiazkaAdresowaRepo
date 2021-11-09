#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <cstdio>

using namespace std;

struct KsiazkaAdresowa
{
    int idKontaktu;
    string imie, nazwisko, mail, adres;
    int telefon;
};

struct Uzytkownik
{
    int idUzytkownika;
    string nazwa, haslo;
};


int okreslenieNrIdKontaktu(vector<KsiazkaAdresowa> kontakty)
{
    int idKontaktu;

    fstream plik;
    plik.open("Lista kontaktow.txt", ios::in);

    string wierszZPliku;
    char znak = '|';
    int iloscZnakow = 1;

    if(plik.good()==false) idKontaktu=1;

    else
    {
        while(getline(plik, wierszZPliku))
        {
            switch(iloscZnakow)
            {
            case 1:
                idKontaktu = atoi(wierszZPliku.c_str()) + 1;
                break;
            }

            iloscZnakow = 1;
        }
    }

    return idKontaktu;
}

void nowyKontakt(vector<KsiazkaAdresowa>& kontakty, int idKontaktu)
{
    KsiazkaAdresowa kontakt;

    cout << "Imie: ";
    cin >> kontakt.imie;

    cout << "Nazwisko: ";
    cin >> kontakt.nazwisko;

    cout << "Nr telefonu: ";
    cin >> kontakt.telefon;

    cout << "E-mail: ";
    cin >> kontakt.mail;

    cout << "Adres zamieszkania: ";
    cin.sync();
    getline(cin,kontakt.adres);

    kontakt.idKontaktu = idKontaktu;

    kontakty.push_back(kontakt);

    cout << "Kontakt dodany" << endl;
    Sleep(1500);

}

void zapisDoPlikuKontaktow(vector<KsiazkaAdresowa> kontakty, int idUzytkownika)
{
    fstream plik;
    plik.open("Lista kontaktow.txt", ios::out | ios::app);


    plik << kontakty[kontakty.size()-1].idKontaktu << "|";
    plik << idUzytkownika << "|";
    plik << kontakty[kontakty.size()-1].imie << "|";
    plik << kontakty[kontakty.size()-1].nazwisko << "|";
    plik << kontakty[kontakty.size()-1].telefon << "|";
    plik << kontakty[kontakty.size()-1].mail << "|";
    plik << kontakty[kontakty.size()-1].adres << "|";
    plik << endl;

    plik.close();
}

void wczytaniePlikuKontaktow(vector<KsiazkaAdresowa>& kontakty, int idUzytkownika)
{
    fstream plik;
    plik.open("Lista kontaktow.txt", ios::in);

    string wierszZPliku;
    char znak = '|';
    int iloscZnakow = 1;

    int idUzytkownikaDoWeryfikacji;

    KsiazkaAdresowa kontakt;
    Uzytkownik uzytkownik;


    while(getline(plik, wierszZPliku, znak))
    {
        switch(iloscZnakow)
        {
        case 1:
            kontakt.idKontaktu = atoi(wierszZPliku.c_str());
            break;

        case 2:
            idUzytkownikaDoWeryfikacji = atoi(wierszZPliku.c_str());
            break;

        case 3:
            kontakt.imie = wierszZPliku;
            break;

        case 4:
            kontakt.nazwisko = wierszZPliku;
            break;

        case 5:
            kontakt.telefon = atoi(wierszZPliku.c_str());
            break;

        case 6:
            kontakt.mail = wierszZPliku;
            break;

        case 7:
            kontakt.adres = wierszZPliku;
            break;
        }

        iloscZnakow++;

        if(iloscZnakow==8)
        {
            if(idUzytkownikaDoWeryfikacji==idUzytkownika) kontakty.push_back(kontakt);
            iloscZnakow = 1;
        }
    }

    plik.close();
}

void wyswietlenieListyKontaktow(vector<KsiazkaAdresowa> kontakty, int i)
{
    cout <<  kontakty[i].imie << endl;
    cout <<  kontakty[i].nazwisko << endl;
    cout <<  kontakty[i].telefon << endl;
    cout <<  kontakty[i].mail << endl;
    cout <<  kontakty[i].adres << endl;
    cout << endl;
}

void szukanieKontaktu(vector<KsiazkaAdresowa> kontakty)
{
    string imie, nazwisko;
    int liczbaWynikow = 0;
    int wybor;

    system("cls");

    cout << "1. Szukaj kontaktu po imieniu" << endl;
    cout << "2. Szukaj kontaktu po nazwisku" << endl;
    cin >> wybor;

    switch(wybor)
    {
    case 1:
        cout << "Podaj imie: ";
        cin >> imie;

        for (int i=0; i<kontakty.size(); i++)
        {
            if(kontakty[i].imie==imie)
            {
                wyswietlenieListyKontaktow(kontakty, i);

                liczbaWynikow++;
            }
        }

        if(liczbaWynikow==0)
        {
            cout << "Brak osoby o takim imieniu";
            break;
        }
        Sleep(1500);
        break;

    case 2:
        cout << "Podaj nazwisko: ";
        cin >> nazwisko;

        for (int i=0; i<kontakty.size(); i++)
        {
            if(kontakty[i].nazwisko == nazwisko)
            {
                wyswietlenieListyKontaktow(kontakty, i);

                liczbaWynikow++;
            }
        }

        if(liczbaWynikow == 0)
        {
            cout << "Brak osoby o takim nazwisku";
            break;
        }
        Sleep(1500);
        break;
    }
}

void zapisDoPlikuTymczasowegoZWektora(vector<KsiazkaAdresowa> kontakty, int idUzytkownika, int liczbaPorzadkowaKontaktu)
{
    fstream plik;

    plik.open("Tymczasowy.txt", ios::out | ios::app);


    plik << kontakty[liczbaPorzadkowaKontaktu].idKontaktu << "|";
    plik << idUzytkownika << "|";
    plik << kontakty[liczbaPorzadkowaKontaktu].imie << "|";
    plik << kontakty[liczbaPorzadkowaKontaktu].nazwisko << "|";
    plik << kontakty[liczbaPorzadkowaKontaktu].telefon << "|";
    plik << kontakty[liczbaPorzadkowaKontaktu].mail << "|";
    plik << kontakty[liczbaPorzadkowaKontaktu].adres << "|";
    plik << endl;

    plik.close();
}

void zapisDoPlikuTymczasowegoZPliku(KsiazkaAdresowa kontakt, int idUzytkownika)
{
    fstream plik;

    plik.open("Tymczasowy.txt", ios::out | ios::app);

    plik << kontakt.idKontaktu << "|";
    plik << idUzytkownika << "|";
    plik << kontakt.imie << "|";
    plik << kontakt.nazwisko << "|";
    plik << kontakt.telefon << "|";
    plik << kontakt.mail << "|";
    plik << kontakt.adres << "|";
    plik << endl;

    plik.close();
}

void porownanieListyKontaktow(vector<KsiazkaAdresowa> kontakty, int idAktywnegoUzytkownika, int idUsuwanegoKontaktu)
{
    fstream plikPierwotny, plikTymczasowy;
    plikPierwotny.open("Lista kontaktow.txt", ios::in);
    plikTymczasowy.open("Tymczasowy.txt", ios::out | ios::app);

    string wierszZPliku;
    char znak = '|';
    int iloscZnakow = 1;

    int idKontaktu, idUzytkownika;
    string imie, nazwisko, mail, adres;
    int liczbaKontaktow = 0;

    bool zmianaKontaktu = false;
    int liczbaPorzadkowaKontaktu;

    KsiazkaAdresowa kontakt;

    while(getline(plikPierwotny, wierszZPliku, znak))
    {
        switch(iloscZnakow)
        {
        case 1:
            idKontaktu = atoi(wierszZPliku.c_str());

            if (idKontaktu==idUsuwanegoKontaktu) zmianaKontaktu = true;
            else
            {
                for(int i=0; i<kontakty.size(); i++)
                {
                    if(idKontaktu==kontakty[i].idKontaktu)
                    {
                        zmianaKontaktu = true;
                        liczbaPorzadkowaKontaktu = i;
                        break;
                    }
                    else if (idKontaktu!=kontakty[i].idKontaktu) zmianaKontaktu = false;
                }
            }

            if(zmianaKontaktu==false) kontakt.idKontaktu = atoi(wierszZPliku.c_str());
            else if (idKontaktu!=idUsuwanegoKontaktu)
                zapisDoPlikuTymczasowegoZWektora(kontakty, idAktywnegoUzytkownika, liczbaPorzadkowaKontaktu);
            break;

        case 2:
            idUzytkownika = atoi(wierszZPliku.c_str());
            break;

        case 3:
            if(zmianaKontaktu==false) kontakt.imie = wierszZPliku;
            break;

        case 4:
            if(zmianaKontaktu==false) kontakt.nazwisko = wierszZPliku;
            break;

        case 5:
            if(zmianaKontaktu==false) kontakt.telefon = atoi(wierszZPliku.c_str());
            break;

        case 6:
            if(zmianaKontaktu==false) kontakt.mail = wierszZPliku;
            break;

        case 7:
            if(zmianaKontaktu==false) kontakt.adres = wierszZPliku;
            break;
        }

        iloscZnakow++;

        if(iloscZnakow>7)
        {
            iloscZnakow = 1;
            if(zmianaKontaktu==false) zapisDoPlikuTymczasowegoZPliku(kontakt, idUzytkownika);
        }
    }

    plikPierwotny.close();
    plikTymczasowy.close();

    remove("Lista kontaktow.txt");
    rename("Tymczasowy.txt", "Lista kontaktow.txt" );
}


int usuniecieKontaktu(vector<KsiazkaAdresowa>& kontakty)
{
    string imie, nazwisko, odpowiedz;
    bool istnienieKontaktu = false;
    int idUsuwanegoKontaktu = 0;

    cout << "Podaj imie kontaktu do usuniecia: ";
    cin >> imie;

    cout << "Podaj nazwisko kontaktu do usuniecia: ";
    cin >> nazwisko;

    for(int j=0; j<kontakty.size(); j++)
    {
        if(kontakty[j].imie==imie && kontakty[j].nazwisko == nazwisko)
        {
            istnienieKontaktu = true;
            idUsuwanegoKontaktu = kontakty[j].idKontaktu;
            cout << "Czy chcesz usunac " << imie << " " << nazwisko << "? <t/n>" << endl;
            cin >> odpowiedz;

            if(odpowiedz=="t")
            {
                kontakty.erase(kontakty.begin()+j);
                cout << "Kontakt zostal usuniety ";
            }

            else cout << "Powrot do menu glownego";
        }
    }

    if(istnienieKontaktu==false)
    {
        cout << "Nie ma takiej osoby na liscie kontaktowej";
        idUsuwanegoKontaktu = 0;
    }

    Sleep(1500);

    return idUsuwanegoKontaktu;
}

bool edycjaKontaktu(vector<KsiazkaAdresowa>& kontakty)
{
    string imie, nazwisko, odpowiedz;
    char wybor;
    int liczbaPorzadkowaKontaktu;
    bool istnienieKontaktu = false;


    cout << "Podaj imie kontaktu do edycji: ";
    cin >> imie;

    cout << "Podaj nazwisko kontaktu do edycji: ";
    cin >> nazwisko;

    for(int j=0; j<kontakty.size(); j++)
    {
        if(kontakty[j].imie==imie && kontakty[j].nazwisko==nazwisko)
        {
            liczbaPorzadkowaKontaktu = j;
            istnienieKontaktu = true;
        }
    }

    if(istnienieKontaktu==false)
    {
        cout << "Nie ma takiej osoby na liscie kontaktowej" << endl;
        cout << "Powrot do menu glownego" << endl;
        Sleep(1500);
        wybor='6';
    }

    while(wybor!='6')
    {
        system("cls");

        cout << "1. Zmien imie" << endl;
        cout << "2. Zmien nazwisko" << endl;
        cout << "3. Zmien numer telefonu" << endl;
        cout << "4. Zmien e-mail" << endl;
        cout << "5. Zmien adres" << endl;
        cout << "6. Powrot do menu glownego" << endl;
        cin >> wybor;

        switch(wybor)
        {
        case '1':
            cout << "Podaj nowe imie: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].imie;
            cout << "Zapisano zmiane kontaktu";
            Sleep(1000);
            break;

        case '2':
            cout << "Podaj nowe nazwisko: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].nazwisko;
            cout << "Zapisano zmiane kontaktu";
            Sleep(1000);
            break;

        case '3':
            cout << "Podaj nowy numer telefonu: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].telefon;
            cout << "Zapisano zmiane kontaktu";
            Sleep(1000);
            break;

        case '4':
            cout << "Podaj nowy e-mail: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].mail;
            cout << "Zapisano zmiane kontaktu";
            Sleep(1000);
            break;

        case '5':
            cout << "Podaj nowy adres: ";
            cin.sync();
            getline(cin, kontakty[liczbaPorzadkowaKontaktu].adres);
            cout << "Zapisano zmiane kontaktu";
            Sleep(1000);
            break;

        case '6':
            break;

        default:
            cout << "Wybierz numer od 1 do 6";
            Sleep(1000);
        }
    }

    return istnienieKontaktu;
}

void wykonywaniePolecenNaKsiazceAdresowej(int idUzytkownika)
{
    KsiazkaAdresowa kontakt;
    vector<KsiazkaAdresowa> kontakty;

    fstream plik;

    char wybor;
    int idKontaktu = 0;
    int idUsuwanegoKontaktu = 0;
    bool aktualizacjaKontaktu;

    if(plik.good()) wczytaniePlikuKontaktow(kontakty, idUzytkownika);

    system("cls");

    while(wybor!=7)
    {
        cout << "Wybierz jedno z ponizszych:" << endl;
        cout << "1. Dodanie nowego kontaktu" << endl;
        cout << "2. Wyszukanie kontaktu" << endl;
        cout << "3. Wyswietlenie wszystkich kontaktow" << endl;
        cout << "4. Usun kontakt" << endl;
        cout << "5. Edytuj kontakt" << endl;
        cout << "6. Wyswietl liczbe kontaktow" << endl;
        cout << "7. Wyloguj sie" << endl;
        cin >> wybor;

        switch(wybor)
        {
        case '1':
            idKontaktu = okreslenieNrIdKontaktu(kontakty);
            nowyKontakt(kontakty, idKontaktu);
            zapisDoPlikuKontaktow(kontakty, idUzytkownika);
            break;

        case '2':
            szukanieKontaktu(kontakty);
            break;

        case '3':
            for(int i=0; i<kontakty.size(); i++)
            {
                wyswietlenieListyKontaktow(kontakty, i);
            }
            Sleep(3500);
            break;

        case '4':
            idUsuwanegoKontaktu = usuniecieKontaktu(kontakty);
            if(idUsuwanegoKontaktu!=0) porownanieListyKontaktow(kontakty, idUzytkownika, idUsuwanegoKontaktu);
            break;

        case '5':
            aktualizacjaKontaktu = edycjaKontaktu(kontakty);
            if(aktualizacjaKontaktu==true) porownanieListyKontaktow(kontakty, idUzytkownika, idUsuwanegoKontaktu);
            break;

        case '6':
            cout << kontakty.size();
            Sleep(1000);
            break;

        case '7':
            return;

        default:
            cout << "Wybierz numer od 1 do 7";
            Sleep(1000);
        }

        system("cls");
    }
}

int okreslenieNrIdUzytkownika(vector<Uzytkownik> uzytkownicy)
{
    int idUzytkownika;
    if(uzytkownicy.size()==0) idUzytkownika = 1;
    else idUzytkownika = uzytkownicy[uzytkownicy.size()-1].idUzytkownika + 1;

    return idUzytkownika;
}

bool sprawdzenieCzyNazwaUzytkownikaIstnieje(vector<Uzytkownik>& uzytkownicy, int idUzytkownika, Uzytkownik uzytkownik)
{

    bool akceptacjaNazwyUzytkownika;
    for(int i=0; i<uzytkownicy.size(); i++)
    {
        if(uzytkownik.nazwa==uzytkownicy[i].nazwa)
        {
            akceptacjaNazwyUzytkownika = false;
            Sleep(1000);
            break;
        }

        else akceptacjaNazwyUzytkownika = true;
    }

    return akceptacjaNazwyUzytkownika;
}

void zapisDoPlikuUzytkownika(vector<Uzytkownik> uzytkownicy)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    plik << uzytkownicy[uzytkownicy.size()-1].idUzytkownika << "|";
    plik << uzytkownicy[uzytkownicy.size()-1].nazwa << "|";
    plik << uzytkownicy[uzytkownicy.size()-1].haslo << "|";
    plik << endl;

    plik.close();
}

void rejestracjaUzytkownika(vector<Uzytkownik>& uzytkownicy, int idUzytkownika)
{
    Uzytkownik uzytkownik;
    bool akceptacjaNazwyUzytkownika=false;

    cout << "Podaj nazwe uzytkownika: ";
    cin.sync();
    getline(cin,uzytkownik.nazwa);

    cout << "Podaj haslo: ";
    cin >> uzytkownik.haslo;

    akceptacjaNazwyUzytkownika = sprawdzenieCzyNazwaUzytkownikaIstnieje(uzytkownicy, idUzytkownika, uzytkownik);

    if(uzytkownicy.size()==0 || akceptacjaNazwyUzytkownika==true)
    {
        uzytkownik.idUzytkownika = idUzytkownika;

        uzytkownicy.push_back(uzytkownik);

        zapisDoPlikuUzytkownika(uzytkownicy);

        cout << "Rejestracja zakonczona pomyslnie" << endl;
        Sleep(1500);
    }

    else
    {
        cout << "Podana nazwa uzytkownika juz istnieje" << endl;
        Sleep(1500);
    }
}

void wczytaniePlikuUZytkownikow(vector<Uzytkownik>& uzytkownicy)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::in);

    string wierszZPliku;
    char znak = '|';
    int iloscZnakow = 1;

    Uzytkownik uzytkownik;

    while(getline(plik, wierszZPliku, znak))
    {
        switch(iloscZnakow)
        {
        case 1:
            uzytkownik.idUzytkownika = atoi(wierszZPliku.c_str());
            break;

        case 2:
            uzytkownik.nazwa = wierszZPliku;
            break;

        case 3:
            uzytkownik.haslo = wierszZPliku;
            break;
        }

        iloscZnakow++;

        if(iloscZnakow==4)
        {
            iloscZnakow = 1;
            uzytkownicy.push_back(uzytkownik);
        }
    }

    plik.close();
}


void logowanieUzytkownika(vector<Uzytkownik> uzytkownicy)
{
    Uzytkownik uzytkownik;
    string nazwa, haslo;
    bool prawidloweLogowanie;

    cout << "Podaj nazwe uzytkownika: ";
    cin.sync();
    getline(cin, nazwa);

    cout << "Podaj haslo: ";
    cin >> haslo;

    for(int j=0; j<uzytkownicy.size(); j++)
    {
        if(uzytkownicy[j].nazwa==nazwa && uzytkownicy[j].haslo==haslo)
        {
            cout << "Logowanie powiodlo sie" << endl;
            Sleep(1500);
            wykonywaniePolecenNaKsiazceAdresowej(uzytkownicy[j].idUzytkownika);
            prawidloweLogowanie = true;
        }
    }

    if(prawidloweLogowanie==false)
    {
        cout << "Niepoprawny login lub haslo" << endl;
        Sleep(1000);
    }

}

int main()
{
    Uzytkownik uzytkownik;
    vector<Uzytkownik> uzytkownicy;

    fstream plik;

    char wybor;
    int idUzytkownika;

    if(plik.good()) wczytaniePlikuUZytkownikow(uzytkownicy);

    while(1)
    {
        cout << "Wybierz jedno z ponizszych:" << endl;
        cout << "1. Logowanie" << endl;
        cout << "2. Rejestracja" << endl;
        cout << "3. Zamknij program" << endl;
        cin >> wybor;

        switch(wybor)
        {
        case '1':

            logowanieUzytkownika(uzytkownicy);
            break;

        case '2':
            idUzytkownika = okreslenieNrIdUzytkownika(uzytkownicy);
            rejestracjaUzytkownika(uzytkownicy, idUzytkownika);
            break;

        case '3':
            exit(0);
            break;

        default:
            cout << "Wybierz numer od 1 do 3";
            Sleep(1000);
        }

        system("cls");
    }

    return 0;
}
