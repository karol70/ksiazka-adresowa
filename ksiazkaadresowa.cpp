#include <iostream>
#include <windows.h>
#include <fstream>
#include <vector>


using namespace std;

struct przyjaciel {
    int id;
    string imie="";
    string nazwisko="";
    string numer_telefonu="";
    string email="";
    string adres="";
};

vector <przyjaciel> przyjaciele;
vector< przyjaciel>::iterator itr;
void menu_glowne();

void zapiszPlik() {
    fstream plik;
    int i=0;
    plik.open("ulepszona_ksiazka_adresowa.txt",ios::out);
    for (itr = przyjaciele.begin(); itr!=przyjaciele.end(); itr++) {

        plik<<przyjaciele[i].id<<"|";
        plik<<przyjaciele[i].imie<<"|";
        plik<<przyjaciele[i].nazwisko<<"|";
        plik<<przyjaciele[i].numer_telefonu<<"|";
        plik<<przyjaciele[i].email<<"|";
        plik<<przyjaciele[i].adres<<"|"<<endl;
        ++i;
    }
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

void dodawaniePrzyjaciol() {
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

    przyjaciele.push_back(nowy);
}
bool sprawdzPoImieniu() {

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
}

bool sprawdzPoNazwisku() {

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
}

bool wyswietlPrzyjaciol() {
    if (przyjaciele.size()<1) {
        cout<<"Ksiazka adresowa jest pusta, wprowadz dane osob";
        Sleep(1500);
    } else {
        int i= 0;
        for (vector<przyjaciel>::iterator itr = przyjaciele.begin(),koniec= przyjaciele.end(); itr!=koniec; ++itr) {
            wyswietlDanePrzyjaciol(i);
            i++;
        }
    }
    cout<<"Wszystkie osoby zostaly wyswietlone, wcisnij dowolny klawisz aby kontynuowac.";
    getchar();
    getchar();
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

void edytujPrzyjaciol(int identyfikator) {
    char wybor;
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
        int i;
        string nowaWartosc;

        if (wybor=='1') {
            cout << "Wprowadz nowe imie adresata: ";
            i = ZnajdzAdresataZPodanymIdentyfikatorem (identyfikator);
            cin >> nowaWartosc;
            przyjaciele[i].imie = nowaWartosc;
        } else if (wybor=='2') {
            cout << "Wprowadz nowe nazwisko adresata: ";
            i = ZnajdzAdresataZPodanymIdentyfikatorem (identyfikator);
            cin >> nowaWartosc;
            przyjaciele[i].nazwisko = nowaWartosc;
        } else if (wybor=='3') {
            cout << "Wprowadz nowy numer telefonu adresata: ";
            i = ZnajdzAdresataZPodanymIdentyfikatorem (identyfikator);
            cin >> nowaWartosc;
            przyjaciele[i].numer_telefonu = nowaWartosc;
        } else if (wybor =='4') {
            cout << "Wprowadz nowy adres email adresata: ";
            i = ZnajdzAdresataZPodanymIdentyfikatorem (identyfikator);
            cin >> nowaWartosc;
            przyjaciele[i].email = nowaWartosc;
        } else if (wybor =='5') {
            cout << "Wprowadz nowy adres zamieszkania adresata: ";
            i = ZnajdzAdresataZPodanymIdentyfikatorem (identyfikator);
            cin >> nowaWartosc;
            przyjaciele[i].adres = nowaWartosc;
        } else if (wybor =='6') {
            menu_glowne();
        }

    }
}

void usunAdresata(int identyfikator) {
    char potwierdzenie;
    int i=0;
    cout << "Jezeli na pewno chcesz usunac adresata wcisnij 't'. ";
    cin >>potwierdzenie;
    if (potwierdzenie == 't') {
        for (itr = przyjaciele.begin(); itr!=przyjaciele.end(); ++itr) {
            if(przyjaciele[i].id == identyfikator) {
                przyjaciele.erase(itr);
                break;
            }
            i++;
        }
    }
}

void menu_glowne() {
    while(1) {
        system("cls");
        char wybor;
        cout<<"KSIAZKA ADRESOWA" << endl;
        cout<<"1.Dodaj adresata" << endl;
        cout<<"2.Wyszukaj po imieniu" << endl;
        cout<<"3.Wyszukaj po nazwisku" << endl;
        cout<<"4.Wyswietl wszystkich adresatow" << endl;
        cout<<"5.Usun adresata" << endl;
        cout<<"6.Edytuj adresata" << endl;
        cout<<"9.Zakoncz program i zapisz zmiany" << endl << endl;
        cout<<"Twoj wybor: ";
        cin>>wybor;

        if (wybor=='1') {
            dodawaniePrzyjaciol();
        } else if (wybor=='2') {
            sprawdzPoImieniu();
        } else if (wybor=='3') {
            sprawdzPoNazwisku();
        } else if (wybor=='4') {
            wyswietlPrzyjaciol();
        } else if (wybor=='5') {
            int identyfikator;
            cout<< "Podaj numer ID adresata, ktorego chcesz usunac: ";
            cin >> identyfikator;
            usunAdresata(identyfikator);
            cout << "Wybrany adresat zostal usuniety z ksiazki adresowej.";
            Sleep(1500);
        } else if (wybor=='6') {
            int identyfikator;
            cout<< "Podaj numer id adresata, ktorego dane chcesz zmienic: ";
            cin >> identyfikator;
            edytujPrzyjaciol(identyfikator);
            cout << "Dane wybranego adresata zostaly zaktualizowane.";
            Sleep(1500);
        } else if (wybor=='9') {
            zapiszPlik();
            exit(0);
        }
    }
}
int main() {
    int ilosc_przyjaciol;
    int id_przyjaciela;
    przyjaciel wczytane_dane;

    char wybor;
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

        if (!plik.fail()) {
            i++;
        } else
            break;
    }
    plik.close();
    ilosc_przyjaciol=i;

    menu_glowne();

    return 0;
}
