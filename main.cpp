#include <iostream>
#include <windows.h>
#include <conio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cstdio>
using namespace std;

struct Osoba
{
    int id;
    string imie, nazwisko, numerTelefonu, email, adres;
};

struct Uzytkownik
{
    int idUzytkownika;
    string login, haslo;
};

string wczytajLinie()
{
    string wejscie = "";
    getline(cin, wejscie);
    return wejscie;
}

string zamianaPierwszejLiteryNaDuzaReszteNaMale(string wyraz)
{
    transform(wyraz.begin(), wyraz.end(), wyraz.begin(),:: tolower );
    wyraz[0] = toupper(wyraz[0]);
    return wyraz;
}

void dopiszOsobeDoPlikuTXT(Osoba dodanaOsoba)
{
    fstream plik;
    plik.open("ksiazkaadresowa.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << dodanaOsoba.id << "|";
        plik << dodanaOsoba.imie << "|";
        plik << dodanaOsoba.nazwisko << "|";
        plik << dodanaOsoba.numerTelefonu << "|";
        plik << dodanaOsoba.email << "|";
        plik << dodanaOsoba.adres << "|" <<endl;
        plik.close();
        cout << "Osoba zostala dodana do ksiazki adresowej" << endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie udalo sie dodac osoby do ksiazki adresowej" << endl;
        Sleep(1000);
    }
}

void dopiszUzytkownikaDoPlikuTXT(Uzytkownik dodanyUzytkownik)
{
    fstream plik;
    plik.open("Uzytkownicy.txt", ios::out | ios::app);

    if (plik.good() == true)
    {
        plik << dodanyUzytkownik.idUzytkownika << "|";
        plik << dodanyUzytkownik.login << "|";
        plik << dodanyUzytkownik.haslo << "|"<<endl;
        plik.close();
        cout<<"Konto zostalo zalozone"<<endl;
        Sleep(1000);
    }
    else
    {
        cout << "Nie udalo sie utworzyć konta" << endl;
        Sleep(1000);
    }
}

void dodajOsoby(vector <Osoba> &osoby)
{
    Osoba dodanaOsoba;

    system("cls");
    cout << ">>> DODAWANIE NOWEJ OSOBY <<<" << endl << endl;

    if (osoby.empty() == true)
    {
        dodanaOsoba.id = 1;
    }
    else
    {
        dodanaOsoba.id = osoby.back().id + 1;
    }

    cout << "Podaj imie osoby: ";
    cin.sync();
    dodanaOsoba.imie = wczytajLinie();
    dodanaOsoba.imie = zamianaPierwszejLiteryNaDuzaReszteNaMale(dodanaOsoba.imie);

    cout << "Podaj nazwisko osoby: ";
    cin.sync();
    dodanaOsoba.nazwisko = wczytajLinie();
    dodanaOsoba.nazwisko = zamianaPierwszejLiteryNaDuzaReszteNaMale(dodanaOsoba.nazwisko);

    cout << "Podaj numer telefonu: ";
    dodanaOsoba.numerTelefonu = wczytajLinie();

    cout << "Podaj email: ";
    dodanaOsoba.email = wczytajLinie();

    cout << "Podaj adres(ul. NazwaUlicy X, XX-XXX NazwaMiejscowosci): ";
    dodanaOsoba.adres = wczytajLinie();

    osoby.push_back(dodanaOsoba);

    dopiszOsobeDoPlikuTXT(dodanaOsoba);
}

Osoba pobierzDaneOsoby(string daneJednejOsobyOddzielonePionowymiKreskami)
{
    Osoba dodanaOsoba;
    string pojedynczaDanaOsoby = "";
    int numerPojedynczejDanejOsoby = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneJednejOsobyOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneJednejOsobyOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaOsoby += daneJednejOsobyOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczejDanejOsoby)
            {
            case 1:
                dodanaOsoba.id = atoi(pojedynczaDanaOsoby.c_str());
                break;
            case 2:
                dodanaOsoba.imie = pojedynczaDanaOsoby;
                break;
            case 3:
                dodanaOsoba.nazwisko = pojedynczaDanaOsoby;
                break;
            case 4:
                dodanaOsoba.numerTelefonu = pojedynczaDanaOsoby;
                break;
            case 5:
                dodanaOsoba.email = pojedynczaDanaOsoby;
                break;
            case 6:
                dodanaOsoba.adres = pojedynczaDanaOsoby;
                break;
            }
            pojedynczaDanaOsoby = "";
            numerPojedynczejDanejOsoby++;
        }
    }
    return dodanaOsoba;
}

Uzytkownik pobierzDaneUzytkownika(string daneJednegoUzytkownikaOddzielonePionowymiKreskami)
{
    Uzytkownik dodanyUzytkownik;
    string pojedynczaDanaUzytkownika = "";
    int numerPojedynczegoUzytkownika = 1;

    for (int pozycjaZnaku = 0; pozycjaZnaku < daneJednegoUzytkownikaOddzielonePionowymiKreskami.length(); pozycjaZnaku++)
    {
        if (daneJednegoUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku] != '|')
        {
            pojedynczaDanaUzytkownika += daneJednegoUzytkownikaOddzielonePionowymiKreskami[pozycjaZnaku];
        }
        else
        {
            switch(numerPojedynczegoUzytkownika)
            {
            case 1:
                dodanyUzytkownik.idUzytkownika = atoi(pojedynczaDanaUzytkownika.c_str());
                break;
            case 2:
                dodanyUzytkownik.login = pojedynczaDanaUzytkownika;
                break;
            case 3:
                dodanyUzytkownik.haslo = pojedynczaDanaUzytkownika;
                break;
            }
            pojedynczaDanaUzytkownika = "";
            numerPojedynczegoUzytkownika++;
        }
    }
    return dodanyUzytkownik;
}


void wczytajOsobeZPliku(vector<Osoba> &osoby)
{
    Osoba dodanaOsoba;
    string daneJednejOsobyOddzielonePionowymiKreskami = "";
    ///UWAGA CZYSZCZENIE CAŁEGO WEKTORA
    osoby.clear();

    fstream plikTekstowy;
    plikTekstowy.open("ksiazkaadresowa.txt", ios::in);

    if (plikTekstowy.good() == false)
    {
        cout << "Plik nie istnieje!!!";
        Sleep(3000);
    }

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednejOsobyOddzielonePionowymiKreskami))
        {
            dodanaOsoba = pobierzDaneOsoby(daneJednejOsobyOddzielonePionowymiKreskami);

            osoby.push_back(dodanaOsoba);
        }
        plikTekstowy.close();
    }
}

void wyswietlanieZapisanychOsoby(vector <Osoba> &osoby)
{
    int i = 0;
    system("cls");
    while(i < osoby.size())
    {
        cout << "Osoba nr "<<osoby[i].id<<":" << endl;
        cout << osoby[i].imie << "|" << osoby[i].nazwisko << "|" << osoby[i].numerTelefonu << "|" << osoby[i].email <<"|" <<osoby[i].adres <<"|" << endl;
        cout << endl;
        i++;
    }
    cout << "Aby zakonczyc wcisnij dowolny klawisz... ";
    getch();
    return void();
}

void wyszukiwanieOsobyPoImieniu(vector <Osoba> &osoby)
{

    string imie;

    system("cls");
    cout << "Podaj imie szukanej osoby:";
    cin>>imie; // powiedzmy, ¿e to jest id szukanego pacjenta


    for(vector<Osoba>::iterator i = osoby.begin(); i < osoby.end(); i++)
    {
        if(i->imie == imie)
        {
            cout << i->id << " " <<i->imie << " " << i->nazwisko << " " << i->numerTelefonu << " " << i->email <<" " <<i->adres <<" " << endl;
        }
    }
    cout << "Aby zakonczyc wcisnij dowolny klawisz... ";
    getch();
    return void();

}

void wyszukiwanieOsobyPoNazwisku(vector <Osoba> &osoby)
{

    string nazwisko;

    system("cls");
    cout << "Podaj nawisko szukanej osoby:";
    cin>>nazwisko; // powiedzmy, ¿e to jest id szukanego pacjenta


    for(vector<Osoba>::iterator i = osoby.begin(); i < osoby.end(); i++)
    {
        if(i->nazwisko == nazwisko)
        {
            cout << i->id << " " <<i->imie << " " << i->nazwisko << " " << i->numerTelefonu << " " << i->email <<" " <<i->adres <<" " << endl;
        }
    }
    cout << "Aby zakonczyc wcisnij dowolny klawisz... ";
    getch();
    return void();

}

void czyszczeniePlikuPrzedPonownymZapisem(vector <Osoba> &osoby)
{
    int i = 0;
    fstream plik;
    plik.open("ksiazkaadresowa.txt", ios::out | ios::trunc);

    if(plik.good() == true)
    {

        while(i < osoby.size())
        {
            plik << osoby[i].id << "|";
            plik << osoby[i].imie << "|";
            plik << osoby[i].nazwisko << "|";
            plik << osoby[i].numerTelefonu << "|";
            plik << osoby[i].email << "|";
            plik << osoby[i].adres << "|" <<endl;
            i++;
        }
        plik.close();
    }
}

void usuwanieZapisanychOsob(vector <Osoba> &osoby)
{
    int id;
    char znak;
    system("cls");
    cout << "Podaj id osoby do usuniecia:";
    cin >> id;

    for(vector<Osoba>::iterator i = osoby.begin(); i < osoby.end(); i++)
    {
        if(i -> id == id)
        {
            cout << "Czy na pewno chcesz usunac osobe: " << i -> id << "|" << i -> imie << "|" << i -> nazwisko << "?" << endl;
            cout << "Aby zaakceptowac wcisnij 't'||Inny klawisz anuluje rozkaz... " << endl;
            znak = getch();
            if (znak =='t')
            {
                osoby.erase(i);
                cout << "Osoba zostala usunieta!!!";
                Sleep(1000);
                czyszczeniePlikuPrzedPonownymZapisem(osoby);
                wczytajOsobeZPliku(osoby);
                return void();
            }
            else
                return void();
        }
    }
    cout << "Uzytkownik nie istnieje!!!";
    Sleep(1000);
    return void();
}

void edytowanieZapisanychOsob(vector <Osoba> &osoby)
{
    Osoba dodanaOsoba;
    int id;
    char wybor, znak;

    system("cls");

    cout << ">>>EDYCJA OSOBY <<<" << endl;
    cout << "Podaj id uzytkownika ktorego chcesz zmodyfikowac: ";
    cin >> id;

    for(vector<Osoba>::iterator i = osoby.begin(); i < osoby.end(); i++)
    {
        if(i -> id == id)
        {
            dodanaOsoba.id = i -> id;
            dodanaOsoba.imie = i -> imie;
            dodanaOsoba.nazwisko = i -> nazwisko;
            dodanaOsoba.numerTelefonu = i -> numerTelefonu;
            dodanaOsoba.email = i -> email;
            dodanaOsoba.adres = i -> adres;

            while(true)
            {
                system("cls");
                cout << "Edycja osoby: " << i -> id << "|" << i -> imie << "|" << i -> nazwisko << endl;
                cout << "1.Zmien imie" << endl;
                cout << "2.Zmien nazwisko" << endl;
                cout << "3.Zmien numer telefonu" << endl;
                cout << "4.Zmien email" << endl;
                cout << "5.Zmien adres" << endl;
                cout << "6.Powrot do menu" << endl;
                cin >> wybor;


                switch(wybor)
                {
                case '1':
                {
                    cout << i -> imie << endl;
                    cout << "Aby zmienic imie wcisnij 't'||Inny klawisz anuluje rozkaz... " << endl;
                    znak = getch();
                    if (znak =='t')
                    {
                        cout << "Wpisz nowe imie:" << endl;
                        cin.sync();
                        dodanaOsoba.imie = wczytajLinie();
                        dodanaOsoba.imie = zamianaPierwszejLiteryNaDuzaReszteNaMale(dodanaOsoba.imie);
                        i -> imie = dodanaOsoba.imie;
                        czyszczeniePlikuPrzedPonownymZapisem(osoby);
                        break;
                    }
                    else
                        break;
                }
                case '2':
                {
                    cout << i -> nazwisko << endl;
                    cout << "Aby zmienic nazwisko wcisnij 't'||Inny klawisz anuluje rozkaz... " << endl;
                    znak = getch();
                    if (znak =='t')
                    {
                        cout << "Wpisz nowe nazwisko:" << endl;
                        cin.sync();
                        dodanaOsoba.nazwisko = wczytajLinie();
                        dodanaOsoba.nazwisko = zamianaPierwszejLiteryNaDuzaReszteNaMale(dodanaOsoba.nazwisko);
                        i -> nazwisko = dodanaOsoba.nazwisko;
                        czyszczeniePlikuPrzedPonownymZapisem(osoby);
                        break;
                    }
                    else
                        break;
                }
                case '3':
                {
                    cout << i -> numerTelefonu << endl;
                    cout << "Aby zmienic numer telefonu wcisnij 't'||Inny klawisz anuluje rozkaz... " << endl;
                    znak = getch();
                    if (znak =='t')
                    {
                        cout << "Wpisz nowy numer telefonu:" << endl;
                        cin.sync();
                        dodanaOsoba.numerTelefonu = wczytajLinie();
                        i -> numerTelefonu = dodanaOsoba.numerTelefonu;
                        czyszczeniePlikuPrzedPonownymZapisem(osoby);
                        break;
                    }
                    else
                        break;
                }
                case '4':
                {
                    cout << i -> email << endl;
                    cout << "Aby zmienic email wcisnij 't'||Inny klawisz anuluje rozkaz... " << endl;
                    znak = getch();
                    if (znak =='t')
                    {
                        cout << "Wpisz nowy email:" << endl;
                        cin.sync();
                        dodanaOsoba.email = wczytajLinie();
                        i -> email = dodanaOsoba.email;
                        czyszczeniePlikuPrzedPonownymZapisem(osoby);
                        break;
                    }
                    else
                        break;
                }
                case '5':
                {
                    cout << i -> adres << endl;
                    cout << "Aby zmienic adres wcisnij 't'||Inny klawisz anuluje rozkaz... " << endl;
                    znak = getch();
                    if (znak =='t')
                    {
                        cout << "Wpisz nowy numer adres:" << endl;
                        cin.sync();
                        dodanaOsoba.adres = wczytajLinie();
                        i -> adres = dodanaOsoba.adres;
                        czyszczeniePlikuPrzedPonownymZapisem(osoby);
                        break;
                    }
                    else
                        break;
                }
                case '6':
                {
                    return void();
                }
                }
            }
        }
    }
    cout << "Uzytkownik nie istnieje!!!";
    Sleep(1000);
    return void();
}

string sprawdzanieDostepnosciLoginuUzytkownika(vector <Uzytkownik> &uzytkownicy)
{

    string login;
    cout << "Podaj Login uzytkownika: ";
    cin.sync();
    login = wczytajLinie();

    for(vector<Uzytkownik>::iterator i = uzytkownicy.begin(); i < uzytkownicy.end(); i++)
    {
        if(i->login == login)
        {
            cout <<"<<<" << i->login << ">>>"<< endl;
            cout << "Taki uzytkownik istnieje!!!" << endl;
            cout << "Wpisz inna nazwe uzytkownika: ";
            cin >> login;
            i = uzytkownicy.begin();
        }
    }
    return login;
}

bool sprawdzanieObecnosciLoginuUzytkownikaWBazie(vector <Uzytkownik> &uzytkownicy, string login)
{

    for(vector<Uzytkownik>::iterator i = uzytkownicy.begin(); i < uzytkownicy.end(); i++)
    {
        if(i->login == login)
        {
            return true;

        }
    }
    system ("cls");
    cout <<"<<" << login << ">>"<< endl;
    cout << "Taki uzytkownik nie istnieje!!!" << endl;
    cout << "Sprawdz poprawnosc nazwy uzytkownika, lub stworz nowe konto.";
    Sleep(5000);
    return false;
}

string wprowadzenieHasla()
{
    string haslo,haslo2;
    cout << "Podaj haslo uzytkownika: ";
    cin.sync();
    haslo = wczytajLinie();

    cout << "Ponownie podaj haslo uzytkownika: ";
    cin.sync();
    haslo2 = wczytajLinie();

    if (haslo2 != haslo)
    {
        cout << "Podane hasła różnią się od siebie!!! Powtórz operację!!!" << endl;
        Sleep(1000);
        wprowadzenieHasla();
    }
    else
        return haslo;
}

void rejestracjaUzytkownikow(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik dodanyUzytkownik;
    system("cls");
    cout << ">>> REJESTRACJA NOWEGO UZYTKOWNIKA <<<" << endl << endl;

    if (uzytkownicy.empty() == true)
    {
        dodanyUzytkownik.idUzytkownika = 1;
    }
    else
    {
        dodanyUzytkownik.idUzytkownika = uzytkownicy.back().idUzytkownika + 1;
    }

    //SPRAWDZENIECZU UZYTKOWNIK ISTNIEJE!!!
    dodanyUzytkownik.login = sprawdzanieDostepnosciLoginuUzytkownika(uzytkownicy);

    //SPRAWDZENIE CZY Hasło jest wpisane poprawnie (2x) !!!
    dodanyUzytkownik.haslo = wprowadzenieHasla();

    uzytkownicy.push_back(dodanyUzytkownik);

    dopiszUzytkownikaDoPlikuTXT(dodanyUzytkownik);
}

void wczytajUzytkownikaZPliku(vector <Uzytkownik> &uzytkownicy)
{
    Uzytkownik dodanyUzytkownik;

    string daneJednegoUzytkownikaOddzielonePionowymiKreskami = "";
    ///UWAGA CZYSZCZENIE CAŁEGO WEKTORA
    uzytkownicy.clear();

    fstream plikTekstowy;
    plikTekstowy.open("uzytkownicy.txt", ios::in);

    if (plikTekstowy.good() == false)
    {
        cout << "Plik nie istnieje!!!";
        Sleep(3000);
    }

    if (plikTekstowy.good() == true)
    {
        while (getline(plikTekstowy, daneJednegoUzytkownikaOddzielonePionowymiKreskami))
        {
            dodanyUzytkownik = pobierzDaneUzytkownika(daneJednegoUzytkownikaOddzielonePionowymiKreskami);

            uzytkownicy.push_back(dodanyUzytkownik);
        }
        plikTekstowy.close();
    }
}

void wczytajOknoLogowania()
{
    vector <Osoba> osoby;
    wczytajOsobeZPliku(osoby);
    char wybor;

    while(true)
    {
        system("cls");
        cout << ">>> MENU UZYTKOWNIKA <<<" << endl;
        cout << "1.Dodaj osobe" << endl;
        cout << "2.Wyszukaj osobe po imieniu" << endl;
        cout << "3.Wyszukaj osobe po nazwisku" << endl;
        cout << "4.Wyswietl wszystkich zapisane osoby" << endl;
        cout << "5.Usun osoby" << endl;
        cout << "6.Edytuj osoby" << endl;
        cout << "7.Zmien haslo" << endl;
        cout << "9.Wyloguj" << endl;

        cin >> wybor;
        switch(wybor)
        {
        case '1':
        {
            dodajOsoby(osoby);
            break;
        }
        case '2':
        {
            wyszukiwanieOsobyPoImieniu(osoby);
            break;
        }
        case '3':
        {

            wyszukiwanieOsobyPoNazwisku(osoby);
            break;
        }
        case '4':
        {

            wyswietlanieZapisanychOsoby(osoby);
            break;
        }
        case '5':
        {

            usuwanieZapisanychOsob(osoby);
            break;
        }
        case '6':
        {

            edytowanieZapisanychOsob(osoby);
            break;
        }
        case '9':
        {
            return void();
        }
        }

    }

}
string sprawdzaniehasla(vector <Uzytkownik> &uzytkownicy, string login, string haslo)
{
    for(vector<Uzytkownik>::iterator i = uzytkownicy.begin(); i < uzytkownicy.end(); i++)
    {
        if(i->login == login && i->haslo == haslo)
        {
            return i->haslo;
        }
    }
}

void logowanieUzytkownika (vector <Uzytkownik> &uzytkownicy)
{
    string login, haslo;
    cout << "Podaj login: ";
    cin.sync();
    login = wczytajLinie();

    if (sprawdzanieObecnosciLoginuUzytkownikaWBazie(uzytkownicy, login) == false)
    {
        return void();
    }

    for (int proby = 0; proby < 3; proby ++)
    {
        cout<<"Podaj haslo. Pozostalo prob " << 3 - proby <<": " ;
        cin.sync();
        haslo = wczytajLinie();
        if (haslo == sprawdzaniehasla(uzytkownicy,login, haslo))
        {
            cout << login <<" zalogowales sie!!!" << endl;
            Sleep(1000);
            wczytajOknoLogowania();
            return void();
        }
    }
    cout<<"Podales 3 razy niepoprawne haslo. Poczekaj 5 sekund przed kolejna proba"<<endl;
    Sleep(5000);
    return void();
}

void operacjaLogowania (vector <Uzytkownik> &uzytkownicy)
{
    char wybor;
    while (true)
    {
        system("cls");
        cout << ">>> LOGOWANIE UZYTKOWNIKA <<<" << endl;
        cout << "1.Zaloguj uzytkownika" << endl;
        cout << "9.Wroc do menu glownego" << endl;
        cin >>wybor;

        switch(wybor)
        {
        case '1':
        {
            logowanieUzytkownika(uzytkownicy);
            break;
        }
        case '9':
        {
            return void();
        }
        }
    }
}

    int main()
    {

        vector <Uzytkownik> uzytkownicy;

        wczytajUzytkownikaZPliku(uzytkownicy);

        char wybor;
        while (true)
        {
            system("cls");

            cout << "1.Zaloguj uzytkownika" << endl;
            cout << "2.Rejestracja uzytkownika" << endl;
            cout << "9.Zakoncz program" << endl;
            cin >>wybor;

            switch(wybor)
            {
            case '1':
            {
                operacjaLogowania(uzytkownicy);
                break;
            }
            case '2':
            {
                rejestracjaUzytkownikow(uzytkownicy);
                break;
            }
            case '9':
            {
                exit(0);
            }
            }
        }

        return 0;
    }
