#pragma once
#include "header.h"
#include "Egzemplarz.h"
#include "Data.h"

class Ksiazka {
private:
    int ID;
    string tytul;
    string nazwiskoAutora;
    //int iloscEgzemplarzy;
    int rokWydania;
    string stan = "dostepna";
    string dataZwrotu;
    vector<shared_ptr<Egzemplarz>> egzemplarze;

public:
    Ksiazka();
    Ksiazka(int ID, const string& tytul, const string& nazwiskoAutora, int rokWydania, string stan);
    Ksiazka(int ID);
    void wypiszDane(); 
    int getID() const;
    string getTytul() const;
    string getNazwiskoAutora() const;
    int getRokWydania() const;
    string getStan() const;
    void oznaczJakoWypozyczony();
    void oznaczJakoDostepny();
};

