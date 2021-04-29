#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>


using namespace std;

struct przyjaciel {
    int id;
    int idUzytkownika;
    string imie="";
    string nazwisko="";
    string numer_telefonu="";
    string email="";
    string adres="";
};
struct Uzytkownik {
    int id;
    string nazwa, haslo;
};

vector <przyjaciel> przyjaciele;
vector <przyjaciel>::iterator itr;
vector <Uzytkownik> uzytkownicy;
vector <Uzytkownik>::iterator iter;
void wczytajAdresatow(int idZalogowanegoUzytkownika);

void menu_glowne(int idZalogowanegoUzytkownika);

void wczytajWszystkichAdresatow() {
    int ilosc_przyjaciol;
    int id_przyjaciela;
    przyjaciel wczytane_dane;
    fstream plik;
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::out|ios::app);
    plik.close();
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::in);
    if (plik.good()==false) {
        cout<<"Nie udalo sie wczytac pliku";

        exit(0);
    }
    string dane_przyjaciol;
    int i=0;
    while (getline(plik,dane_przyjaciol)) {

        string id_przyjaciela = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        wczytane_dane.id = atoi(id_przyjaciela.c_str());
        dane_przyjaciol.erase(0,id_przyjaciela.length()+1);

        string id_uzytkownika = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        wczytane_dane.idUzytkownika = atoi(id_uzytkownika.c_str());
        dane_przyjaciol.erase(0,id_uzytkownika.length()+1);

        wczytane_dane.imie = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        dane_przyjaciol.erase(0,wczytane_dane.imie.length()+1);

        wczytane_dane.nazwisko = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        dane_przyjaciol.erase(0,wczytane_dane.nazwisko.length()+1);

        wczytane_dane.numer_telefonu = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        dane_przyjaciol.erase(0,wczytane_dane.numer_telefonu.length()+1);

        wczytane_dane.email = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        dane_przyjaciol.erase(0,wczytane_dane.email.length()+1);

        wczytane_dane.adres = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        dane_przyjaciol.erase(0,wczytane_dane.adres.length()+1);

        przyjaciele.push_back(wczytane_dane);
    }

    if (!plik.fail()) {
        i++;
    }

    plik.close();
    ilosc_przyjaciol=i;
}

void zapiszPlik(int idZalogowanegoUzytkownika, przyjaciel nowy) {


    fstream plik;
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::out | ios::app);

    plik<<nowy.id<<"|";
    plik<<idZalogowanegoUzytkownika<<"|";
    plik<<nowy.imie<<"|";
    plik<<nowy.nazwisko<<"|";
    plik<<nowy.numer_telefonu<<"|";
    plik<<nowy.email<<"|";
    plik<<nowy.adres<<"|"<<endl;

    plik.close();
    cout<<"Wszystkie dane zostaly zapisane";
    Sleep(1500);
}

void wyswietlDanePrzyjaciol (int i) {
    cout<<"ID Adresata: "<<przyjaciele[i].id<<endl;
    cout<<"Imie: "<<przyjaciele[i].imie<<endl;
    cout<<"Nazwisko: "<<przyjaciele[i].nazwisko<<endl;
    cout<<"Numer telefonu: "<<przyjaciele[i].numer_telefonu<<endl;
    cout<<"Adres email: "<<przyjaciele[i].email<<endl;
    cout<<"Adres zamieszkania: "<<przyjaciele[i].adres<<endl<<endl;
}

void dodawaniePrzyjaciol(int idZalogowanegoUzytkownika) {

    string imie;
    string nazwisko;
    string numer_telefonu;
    string email;
    string adres;
    przyjaciel nowy;

    cout<<"Podaj imie osoby: ";
    cin>>imie;
    cout<<"Podaj nazwisko osoby: ";
    cin>>nazwisko;
    cout<<"Podaj numer telefonu: ";
    cin>>numer_telefonu;
    cout<<"Podaj adres email: ";
    cin>>email;
    cout<<"Podaj adres zamieszkania: ";
    cin.sync();
    getline(cin,adres);
    int id;
    if (przyjaciele.size()==0) {
        id = 1;
    } else {
        id = przyjaciele[przyjaciele.size()-1].id +1;
    }
    nowy.id = id;
    nowy.imie = imie;
    nowy.nazwisko = nazwisko;
    nowy.numer_telefonu = numer_telefonu;
    nowy.email = email;
    nowy.adres = adres;
    zapiszPlik(idZalogowanegoUzytkownika,nowy);
    przyjaciele.push_back(nowy);
    menu_glowne(idZalogowanegoUzytkownika);
}
bool sprawdzPoImieniu(int idZalogowanegoUzytkownika) {

    string sprawdzImie;

    if (przyjaciele.size()<1) {
        cout<<"Ksiazka adresowa jest pusta, wprowadz dane osob";
        Sleep(1500);
    } else {
        cout<<"Podaj imie: ";
        cin>>sprawdzImie;
        int ilosc_osob_o_podanym_imieniu=0;
        int i =0;
        while (i<przyjaciele.size()) {
            if (przyjaciele[i].imie==sprawdzImie) {
                wyswietlDanePrzyjaciol(i);
                ilosc_osob_o_podanym_imieniu++;
                i++;
            } else {
                i++;
            }
        }
        if (ilosc_osob_o_podanym_imieniu==0) {
            cout<<"W ksiazce nie ma zapisanych osob o podanym imieniu";
            Sleep(1500);
        } else {
            cout<<"Wszystkie osoby o podanym imieniu zostaly wyswietlone, wcisnij dowolny klawisz aby kontynuowac.";
            getchar();
            getchar();
        }
    }
    menu_glowne(idZalogowanegoUzytkownika);
}

bool sprawdzPoNazwisku(int idZalogowanegoUzytkownika) {

    string sprawdzNazwisko;

    if (przyjaciele.size()<1) {
        cout<<"Ksiazka adresowa jest pusta, wprowadz dane osob";
        Sleep(1500);
    } else {
        cout<<"Podaj nazwisko: ";
        cin>>sprawdzNazwisko;
        int ilosc_osob_o_podanym_nazwisku=0;
        int i =0;
        while (i<przyjaciele.size()) {
            if (przyjaciele[i].nazwisko==sprawdzNazwisko) {
                wyswietlDanePrzyjaciol(i);
                ilosc_osob_o_podanym_nazwisku++;
                i++;
            } else {
                i++;
            }
        }
        if (ilosc_osob_o_podanym_nazwisku==0) {
            cout<<"W ksiazce nie ma zapisanych osob o podanym nazwisku";
            Sleep(1500);
        } else {
            cout<<"Wszystkie osoby o podanym nazwisku zostaly wyswietlone, wcisnij dowolny klawisz aby kontynuowac.";
            getchar();
            getchar();
        }
    }
    menu_glowne(idZalogowanegoUzytkownika);
}

bool wyswietlPrzyjaciol(int idZalogowanegoUzytkownika) {
    if (przyjaciele.size()<1) {
        cout<<"Ksiazka adresowa jest pusta, wprowadz dane osob";
        Sleep(1500);
    } else {
        int i=0;
        for (vector<przyjaciel>::iterator itr = przyjaciele.begin(),koniec= przyjaciele.end(); itr!=koniec; ++itr) {
            wyswietlDanePrzyjaciol(i);
            i++;
        }
    }
    cout<<"Wszystkie osoby zostaly wyswietlone, wcisnij dowolny klawisz aby kontynuowac.";
    getchar();
    getchar();
    menu_glowne(idZalogowanegoUzytkownika);
}

int ZnajdzAdresataZPodanymIdentyfikatorem (int identyfikator) {
    int i =0;
    for (itr = przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {
        if((przyjaciele[i].id) == identyfikator) {
            return i;
            break;
        }
        i++;
    }
}
void zapiszEdycje (int identyfikator, vector <przyjaciel>::iterator itr) {
    fstream plik, plik2;
    przyjaciel wczytane_dane;
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::in);
    plik2.open("tymczasowy_plik.txt", ios::out);
    if (plik.good()==false) {
        cout<<"Nie udalo sie wczytac pliku";

        exit(0);
    }
    string dane_przyjaciol;

    while (getline(plik,dane_przyjaciol)) {

        string id_przyjaciela = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        wczytane_dane.id = atoi(id_przyjaciela.c_str());
        dane_przyjaciol.erase(0,id_przyjaciela.length()+1);

        if (wczytane_dane.id==identyfikator) {
            plik2<<itr->id<<"|";
            plik2<<itr->idUzytkownika<<"|";
            plik2<<itr->imie<<"|";
            plik2<<itr->nazwisko<<"|";
            plik2<<itr->numer_telefonu<<"|";
            plik2<<itr->email<<"|";
            plik2<<itr->adres<<"|"<<endl;
        } else {
            string id_uzytkownika = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            wczytane_dane.idUzytkownika = atoi(id_uzytkownika.c_str());
            dane_przyjaciol.erase(0,id_uzytkownika.length()+1);

            wczytane_dane.imie = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.imie.length()+1);

            wczytane_dane.nazwisko = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.nazwisko.length()+1);

            wczytane_dane.numer_telefonu = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.numer_telefonu.length()+1);

            wczytane_dane.email = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.email.length()+1);

            wczytane_dane.adres = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.adres.length()+1);

            plik2<<wczytane_dane.id<<"|";
            plik2<<wczytane_dane.idUzytkownika<<"|";
            plik2<<wczytane_dane.imie<<"|";
            plik2<<wczytane_dane.nazwisko<<"|";
            plik2<<wczytane_dane.numer_telefonu<<"|";
            plik2<<wczytane_dane.email<<"|";
            plik2<<wczytane_dane.adres<<"|"<<endl;
        }
    }
    plik.close();
    remove ("ulepszona_ksiazka_adresowa.txt");
    plik2.close();
    rename("tymczasowy_plik.txt","ulepszona_ksiazka_adresowa.txt");
}

void zapiszUsuniecie (int identyfikator) {
    fstream plik, plik2;
    przyjaciel wczytane_dane;
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::in);
    plik2.open("tymczasowy_plik.txt", ios::out);
    if (plik.good()==false) {
        cout<<"Nie udalo sie wczytac pliku";

        exit(0);
    }
    string dane_przyjaciol;

    while (getline(plik,dane_przyjaciol)) {

        string id_przyjaciela = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        wczytane_dane.id = atoi(id_przyjaciela.c_str());
        dane_przyjaciol.erase(0,id_przyjaciela.length()+1);

        if (wczytane_dane.id==identyfikator ) {
            plik2<<"";
        } else {
            string id_uzytkownika = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            wczytane_dane.idUzytkownika = atoi(id_uzytkownika.c_str());
            dane_przyjaciol.erase(0,id_uzytkownika.length()+1);

            wczytane_dane.imie = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.imie.length()+1);

            wczytane_dane.nazwisko = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.nazwisko.length()+1);

            wczytane_dane.numer_telefonu = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.numer_telefonu.length()+1);

            wczytane_dane.email = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.email.length()+1);

            wczytane_dane.adres = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.adres.length()+1);

            plik2<<wczytane_dane.id<<"|";
            plik2<<wczytane_dane.idUzytkownika<<"|";
            plik2<<wczytane_dane.imie<<"|";
            plik2<<wczytane_dane.nazwisko<<"|";
            plik2<<wczytane_dane.numer_telefonu<<"|";
            plik2<<wczytane_dane.email<<"|";
            plik2<<wczytane_dane.adres<<"|"<<endl;
        }
    }
    plik.close();
    remove ("ulepszona_ksiazka_adresowa.txt");
    plik2.close();
    rename("tymczasowy_plik.txt","ulepszona_ksiazka_adresowa.txt");
}
void edytujPrzyjaciol(int identyfikator, int idZalogowanegoUzytkownika) {
    char wybor;
    int i;
    i = ZnajdzAdresataZPodanymIdentyfikatorem (identyfikator);
    if (i<przyjaciele.size()) {

        while(1) {
            system("cls");
            cout<< "Wybierz ktora dana chcesz zmienic: "<<endl;
            cout<<"1.Imie"<<endl;
            cout<<"2.Nazwisko"<<endl;
            cout<<"3.Numer Telefonu"<<endl;
            cout<<"4.Email"<<endl;
            cout<<"5.Adres"<<endl;
            cout<<"6.Powrot do menu"<<endl;
            cin>>wybor;

            string nowaWartosc;

            for (itr = przyjaciele.begin(); itr!=przyjaciele.end(); ++itr) {
                int i=0;
                if(itr->id == identyfikator) {

                    if (wybor=='1') {
                        cout << "Wprowadz nowe imie adresata: ";
                        cin >> nowaWartosc;
                        itr->imie = nowaWartosc;
                        i++;
                        zapiszEdycje(identyfikator,itr);
                    } else if (wybor=='2') {
                        cout << "Wprowadz nowe nazwisko adresata: ";
                        cin >> nowaWartosc;
                        itr->nazwisko = nowaWartosc;
                        i++;
                        zapiszEdycje(identyfikator,itr);
                    } else if (wybor=='3') {
                        cout << "Wprowadz nowy numer telefonu adresata: ";
                        cin >> nowaWartosc;
                        itr->numer_telefonu = nowaWartosc;
                        i++;
                        zapiszEdycje(identyfikator,itr);
                    } else if (wybor =='4') {
                        cout << "Wprowadz nowy adres email adresata: ";
                        cin >> nowaWartosc;
                        itr->email = nowaWartosc;
                        i++;
                        zapiszEdycje(identyfikator,itr);
                    } else if (wybor =='5') {
                        cout << "Wprowadz nowy adres zamieszkania adresata: ";
                        cin >> nowaWartosc;
                        itr->adres = nowaWartosc;
                        i++;
                        zapiszEdycje(identyfikator,itr);
                    } else if (wybor =='6') {
                        menu_glowne(idZalogowanegoUzytkownika);
                    }
                }
            }
        }
    }
    if (i==0) cout <<"W Twojej liscie przyjaciol nie ma adresata z podanym id";
    Sleep(1500);
    menu_glowne(idZalogowanegoUzytkownika);
}

void usunAdresata(int identyfikator, int idZalogowanegoUzytkownika) {
    char potwierdzenie;
    int i =0;
    for (itr = przyjaciele.begin(); itr!=przyjaciele.end(); ++itr) {
        if(itr->id == identyfikator) {
            cout << "Jezeli na pewno chcesz usunac adresata wcisnij 't'. ";
            cin >>potwierdzenie;
            if (potwierdzenie == 't') {
                przyjaciele.erase(itr);
                i++;
                cout << "Adresat o podanym numerze id zostal usuniety";
                Sleep(1500);
                zapiszUsuniecie(identyfikator);
                break;
            }
        }
    }
    if (i==0) cout<<"W Twojej ksiazce adresowej nie ma adresatow w tym numerem id";
    Sleep(1500);
    menu_glowne(idZalogowanegoUzytkownika);


}
void zapiszZmianeHaslaUzytkownika() {
    fstream plik2;
    plik2.open("Uzytkownicy.txt",ios::out);
    for(vector <Uzytkownik>::iterator iter = uzytkownicy.begin(), koniec = uzytkownicy.end(); iter!=koniec ; iter++) {
        plik2<<iter->id<<"|";
        plik2<<iter->nazwa<<"|";
        plik2<<iter->haslo<<"|"<<endl;
    }
    plik2.close();
}

void zmianaHasla(int idZalogowanegoUzytkownika) {
    string haslo;
    cout<<"Podaj nowe haslo: ";
    cin>>haslo;
    for (int i =0; i<uzytkownicy.size(); i++) {
        if (uzytkownicy[i].id==idZalogowanegoUzytkownika) {
            uzytkownicy[i].haslo = haslo;
            cout<< "Haslo zostalo zmienione"<<endl;
            Sleep(1500);
        }
    }
    zapiszZmianeHaslaUzytkownika();
    menu_glowne(idZalogowanegoUzytkownika);
}


void zapiszNowegoUzytkownika(Uzytkownik nowy) {

    fstream plik2;
    plik2.open("Uzytkownicy.txt",ios::out | ios::app);

    plik2<<nowy.id<<"|";
    plik2<<nowy.nazwa<<"|";
    plik2<<nowy.haslo<<"|"<<endl;

    plik2.close();
}

int rejestracja(int iloscUzytkownikow) {
    string nazwa,haslo;
    int id;
    Uzytkownik nowy;
    cout<<"Podaj nazwe uzytkownika: ";
    cin>>nazwa;
    int i =0;
    while (i<uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa==nazwa) {
            cout<<"Taki uzytkownik istnieje. Wpisz inna nazwe uzytkownika: ";
            cin>>nazwa;
            i=0;
        } else {
            i++;
        }
    }
    cout<<"Podaj haslo: ";
    cin>>haslo;
    if (uzytkownicy.size()==0) {
        id = 1;
    } else {
        id = uzytkownicy[uzytkownicy.size()-1].id +1;
    }
    nowy.id = id;
    nowy.nazwa = nazwa;
    nowy.haslo = haslo;

    zapiszNowegoUzytkownika(nowy);
    uzytkownicy.push_back(nowy);

    cout<<"Konto zalozone"<<endl;
    Sleep(1000);
    return iloscUzytkownikow+1;

    zapiszNowegoUzytkownika(nowy);
}

int logowanie( int iloscUzytkownikow) {
    string nazwa, haslo;
    cout<<"Podaj login: ";
    cin>>nazwa;
    int i =0;
    while (i<uzytkownicy.size()) {
        if (uzytkownicy[i].nazwa==nazwa) {
            for (int iloscProb=0; iloscProb<3; iloscProb++) {
                cout<<"Podaj haslo. Pozostalo prob "<<3-iloscProb<<": ";
                cin>>haslo;
                if (uzytkownicy[i].haslo == haslo) {
                    cout<<"Zalogowales sie."<<endl;
                    Sleep(1000);
                    return uzytkownicy[i].id;
                }
            }
            cout<<"Podales 3 razy bledne haslo. Poczekaj 3 sekundy przed kolejna proba"<<endl;
            Sleep(3000);
            return 0;
        }
        i++;
    }
    cout<<"Nie ma uzytkownika z takim loginem"<<endl;
    Sleep(1500);
    return 0;
}
void panelLogowania() {
    int idZalogowanegoUzytkownika=0;
    int iloscUzytkownikow=0;

    char wybor;

    while(1) {
        if(idZalogowanegoUzytkownika==0) {
            przyjaciele.clear();
            system("cls");
            cout<<"1.Rejestracja"<<endl;
            cout<<"2.Logowanie"<<endl;
            cout<<"9.Zakoncz program" <<endl;
            cin>>wybor;

            if (wybor=='1') {
                iloscUzytkownikow = rejestracja(iloscUzytkownikow);
            } else if (wybor=='2') {
                idZalogowanegoUzytkownika = logowanie(iloscUzytkownikow);
                if (idZalogowanegoUzytkownika !=0) {
                    menu_glowne(idZalogowanegoUzytkownika);
                }

            } else if (wybor=='9') {
                exit(0);
            }
        }
    }
}
void menu_glowne(int idZalogowanegoUzytkownika) {


    przyjaciele.clear();
    wczytajAdresatow(idZalogowanegoUzytkownika);

    system("cls");
    char wybor;
    cout<<"KSIAZKA ADRESOWA" << endl;
    cout<<"1.Dodaj adresata" << endl;
    cout<<"2.Wyszukaj po imieniu" << endl;
    cout<<"3.Wyszukaj po nazwisku" << endl;
    cout<<"4.Wyswietl wszystkich adresatow" << endl;
    cout<<"5.Usun adresata" << endl;
    cout<<"6.Edytuj adresata" << endl;
    cout<<"7.Zmien haslo" << endl;
    cout<<"8.Wyloguj sie" << endl;
    cout<<"Twoj wybor: ";
    cin>>wybor;
    cout<<endl;

    if (wybor=='1') {
        przyjaciele.clear();
        wczytajWszystkichAdresatow();
        dodawaniePrzyjaciol(idZalogowanegoUzytkownika);

    } else if (wybor=='2') {
        sprawdzPoImieniu(idZalogowanegoUzytkownika);
    } else if (wybor=='3') {
        sprawdzPoNazwisku(idZalogowanegoUzytkownika);
    } else if (wybor=='4') {
        wyswietlPrzyjaciol(idZalogowanegoUzytkownika);
    } else if (wybor=='5') {
        int identyfikator;
        cout<< "Podaj numer ID adresata, ktorego chcesz usunac: ";
        cin >> identyfikator;
        usunAdresata(identyfikator, idZalogowanegoUzytkownika);
    } else if (wybor=='6') {
        int identyfikator;
        cout<< "Podaj numer id adresata, ktorego dane chcesz zmienic: ";
        cin >> identyfikator;
        edytujPrzyjaciol(identyfikator, idZalogowanegoUzytkownika);
        Sleep(1500);
    } else if (wybor =='7') {
        zmianaHasla(idZalogowanegoUzytkownika);
    } else if (wybor=='8') {
        panelLogowania();
    }
}


void wczytajAdresatow (int idZalogowanegoUzytkownika) {
    int ilosc_przyjaciol;
    int id_przyjaciela;
    przyjaciel wczytane_dane;
    fstream plik;
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::out|ios::app);
    plik.close();
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::in);
    if (plik.good()==false) {
        cout<<"Nie udalo sie wczytac pliku";

        exit(0);
    }
    string dane_przyjaciol;
    int i=0;
    while (getline(plik,dane_przyjaciol)) {

        string id_przyjaciela = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        wczytane_dane.id = atoi(id_przyjaciela.c_str());
        dane_przyjaciol.erase(0,id_przyjaciela.length()+1);

        string id_uzytkownika = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
        wczytane_dane.idUzytkownika = atoi(id_uzytkownika.c_str());
        dane_przyjaciol.erase(0,id_uzytkownika.length()+1);

        if (wczytane_dane.idUzytkownika==idZalogowanegoUzytkownika) {
            wczytane_dane.imie = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.imie.length()+1);

            wczytane_dane.nazwisko = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.nazwisko.length()+1);

            wczytane_dane.numer_telefonu = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.numer_telefonu.length()+1);

            wczytane_dane.email = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.email.length()+1);

            wczytane_dane.adres = dane_przyjaciol.substr(0,dane_przyjaciol.find("|"));
            dane_przyjaciol.erase(0,wczytane_dane.adres.length()+1);

            przyjaciele.push_back(wczytane_dane);
        }


        if (!plik.fail()) {
            i++;
        } else
            break;
    }
    plik.close();
    ilosc_przyjaciol=i;
}
void wczytajUzytkownikow() {
    string daneUzytkownikow;
    Uzytkownik wczytaneDane;

    fstream plik;
    plik.open("Uzytkownicy.txt",ios::out|ios::app);
    plik.close();
    plik.open("Uzytkownicy.txt",ios::in);
    if (plik.good()==false) {
        cout<<"Nie udalo sie wczytac pliku";

        exit(0);
    }
    int i=0;
    while (getline(plik,daneUzytkownikow)) {

        string id_uzytkownika = daneUzytkownikow.substr(0,daneUzytkownikow.find("|"));
        wczytaneDane.id = atoi(id_uzytkownika.c_str());
        daneUzytkownikow.erase(0,id_uzytkownika.length()+1);

        wczytaneDane.nazwa = daneUzytkownikow.substr(0,daneUzytkownikow.find("|"));
        daneUzytkownikow.erase(0,wczytaneDane.nazwa.length()+1);

        wczytaneDane.haslo = daneUzytkownikow.substr(0,daneUzytkownikow.find("|"));
        daneUzytkownikow.erase(0,wczytaneDane.haslo.length()+1);

        uzytkownicy.push_back(wczytaneDane);

        if (!plik.fail()) {
            i++;
        } else
            break;
    }
    plik.close();
}
int main() {

    wczytajUzytkownikow();

    panelLogowania();

    return 0;
}


