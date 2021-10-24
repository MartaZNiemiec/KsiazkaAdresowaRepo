#include <iostream>
#include <windows.h>
#include <fstream>
#include <cstdlib>
#include <vector>

using namespace std;

struct KsiazkaAdresowa
{
    int id;
    string imie, nazwisko, mail, adres;
    int telefon;
};

int okreslenieNrId(vector<KsiazkaAdresowa> kontakty)
{
    int id;
    if(kontakty.size()==0) id = 1;
    else id = kontakty[kontakty.size()-1].id + 1;

    return id;
}


void nowyKontakt(vector<KsiazkaAdresowa>& kontakty, int id)
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

    kontakt.id = id;

    kontakty.push_back(kontakt);

    cout << "Kontakt dodany" << endl;
    Sleep(1500);

}

void zapisDoPliku(vector<KsiazkaAdresowa> kontakty)
{
    fstream plik;
    plik.open("Lista kontaktow.txt", ios::out | ios::app);

    plik << kontakty[kontakty.size()-1].id << "|";
    plik << kontakty[kontakty.size()-1].imie << "|";
    plik << kontakty[kontakty.size()-1].nazwisko << "|";
    plik << kontakty[kontakty.size()-1].telefon << "|";
    plik << kontakty[kontakty.size()-1].mail << "|";
    plik << kontakty[kontakty.size()-1].adres << "|";
    plik << endl;

    plik.close();
}

void wczytaniePliku(vector<KsiazkaAdresowa>& kontakty)
{
    fstream plik;
    plik.open("Lista kontaktow.txt", ios::in);

    string wierszZPliku;
    int dlugoscWierszaZPliku;
    char znak = '|';
    int iloscZnakow = 1;

    KsiazkaAdresowa kontakt;

    while(getline(plik, wierszZPliku, znak))
    {
        switch(iloscZnakow)
        {
        case 1:
            kontakt.id = atoi(wierszZPliku.c_str());
            break;

        case 2:
            kontakt.imie = wierszZPliku;
            break;

        case 3:
            kontakt.nazwisko = wierszZPliku;
            break;

        case 4:
            kontakt.telefon = atoi(wierszZPliku.c_str());
            break;

        case 5:
            kontakt.mail = wierszZPliku;
            break;

        case 6:
            kontakt.adres = wierszZPliku;
            break;
        }

        iloscZnakow++;

        if(iloscZnakow == 7)
        {
            iloscZnakow = 1;
            kontakty.push_back(kontakt);
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

void szukaj(vector<KsiazkaAdresowa> kontakty)
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
            if(kontakty[i].imie == imie)
            {
                wyswietlenieListyKontaktow(kontakty, i);

                liczbaWynikow++;
            }
        }

        Sleep(2000);

        if(liczbaWynikow == 0)
        {
            cout << "Brak osoby o takim imieniu";
            Sleep(1500);
            break;
        }
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

        Sleep(2000);

        if(liczbaWynikow == 0)
        {
            cout << "Brak osoby o takim nazwisku";
            Sleep(1500);
            break;
        }
        break;
    }
}

void usuniecieKontaktu(vector<KsiazkaAdresowa>& kontakty)
{
    string imie, nazwisko, odpowiedz;
    bool istniejeKontaktu;

    cout << "Podaj imie kontaktu do usuniecia: ";
    cin >> imie;

    cout << "Podaj nazwisko kontaktu do usuniecia: ";
    cin >> nazwisko;

    for(int j=0; j<kontakty.size(); j++)
    {
        if(kontakty[j].imie==imie && kontakty[j].nazwisko == nazwisko)
        {
            istniejeKontaktu = true;
            cout << "Czy chcesz usunac " << imie << " " << nazwisko << "?" << endl;
            cin >> odpowiedz;

            if(odpowiedz=="t")
            {
                kontakty.erase(kontakty.begin()+j);
                cout << "Kontakt zostal usuniety";
            }

            else cout << "Powrot do menu glownego";
        }
    }

    if(istniejeKontaktu==false) cout << "Nie ma takiego kontaktu. Powrot do menu glownego";

    Sleep(1500);
}

void nadpisaniePliku(vector<KsiazkaAdresowa> kontakty)
{
    fstream plik;
    plik.open("Lista kontaktow.txt", ios::out);

    for(int i=0; i<kontakty.size(); i++)
    {
        plik << kontakty[i].id << "|";
        plik << kontakty[i].imie << "|";
        plik << kontakty[i].nazwisko << "|";
        plik << kontakty[i].telefon << "|";
        plik << kontakty[i].mail << "|";
        plik << kontakty[i].adres << "|";
        plik << endl;
    }

    plik.close();
}

void edycjaKontaktu(vector<KsiazkaAdresowa>& kontakty)
{
    string imie, nazwisko, odpowiedz;
    int wybor;
    int liczbaPorzadkowaKontaktu;
    bool istnienieKontaktu;


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
        Sleep(1000);
        wybor=6;
    }

    while(wybor!=6)
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
        case 1:
            cout << "Podaj nowe imie: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].imie;
            break;

        case 2:
            cout << "Podaj nowe nazwisko: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].nazwisko;
            break;

        case 3:
            cout << "Podaj nowy numer telefonu: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].telefon;
            break;

        case 4:
            cout << "Podaj nowy e-mail: ";
            cin >> kontakty[liczbaPorzadkowaKontaktu].mail;
            break;

        case 5:
            cout << "Podaj nowy adres: ";
            cin.sync();
            getline(cin, kontakty[liczbaPorzadkowaKontaktu].adres);
            break;

            Sleep(1500);
        }
    }
}

int main()
{
    KsiazkaAdresowa kontakt;
    vector<KsiazkaAdresowa> kontakty;

    fstream plik;

    int wybor;
    int id;

    if(plik.good()) wczytaniePliku(kontakty);



    while(1)
    {
        cout << "Wybierz jedno z ponizszych:" << endl;
        cout << "1. Dodanie nowego kontaktu" << endl;
        cout << "2. Wyszukanie kontaktu" << endl;
        cout << "3. Wyswietlenie wszystkich kontaktow" << endl;
        cout << "4. Usun kontakt" << endl;
        cout << "5. Edytuj kontakt" << endl;
        cout << "6. Wyswietl liczbe kontaktow" << endl;
        cout << "7. Zakoncz program" << endl;
        cin >> wybor;

        switch(wybor)
        {
        case 1:
            id = okreslenieNrId(kontakty);
            nowyKontakt(kontakty, id);
            zapisDoPliku(kontakty);
            break;

        case 2:
            szukaj(kontakty);
            break;

        case 3:
            for(int i=0; i<kontakty.size(); i++)
            {
                wyswietlenieListyKontaktow(kontakty, i);
            }
            Sleep(2000);
            break;

        case 4:
            usuniecieKontaktu(kontakty);
            nadpisaniePliku(kontakty);
            break;

        case 5:
            edycjaKontaktu(kontakty);
            nadpisaniePliku(kontakty);
            break;

        case 6:
            cout << kontakty.size();
            Sleep(1000);
            break;

        case 7:
            exit(0);
            break;

        default:
            cout << "Wybierz numer od 1 do 7";
            Sleep(1000);
        }

        system("cls");
    }

    return 0;
}
