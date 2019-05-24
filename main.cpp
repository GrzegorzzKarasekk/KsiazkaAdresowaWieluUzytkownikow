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

int main()
{
    vector <Osoba> osoby;
    char wybor;
    wczytajOsobeZPliku(osoby);
    while(true)
    {

        system("cls");
        cout << "1.Dodaj osobe" << endl;
        cout << "2.Wyszukaj osobe po imieniu" << endl;
        cout << "3.Wyszukaj osobe po nazwisku" << endl;
        cout << "4.Wyswietl wszystkich zapisane osoby" << endl;
        cout << "5.Usun osoby" << endl;
        cout << "6.Edytuj osoby" << endl;
        cout << "9.Zakoncz program" << endl;

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
            exit(0);
        }
        }

    }

    return 0;
}
