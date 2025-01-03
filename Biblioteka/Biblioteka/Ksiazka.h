#pragma once
#include "header.h"
#include "Egzemplarz.h"

class Ksiazka {
private:
    int ID;
    string tytul;
    string nazwiskoAutora;
    //int iloscEgzemplarzy;
    int rokWydania;
    vector<shared_ptr<Egzemplarz>> egzemplarze;

public:
    Ksiazka();
    Ksiazka(int ID, const string& tytul, const string& nazwiskoAutora, int rokWydania);
    Ksiazka(int ID);
    void wypiszDane();
    //void dodajEgzemplarz(int egzID); 

    int getID() const;
    string getTytul() const;
    string getNazwiskoAutora() const;
    int getRokWydania() const;
};

