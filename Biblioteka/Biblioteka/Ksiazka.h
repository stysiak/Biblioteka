#pragma once
#include "header.h"

class Ksiazka {
private:
    int ID;
    string tytul;
    string nazwiskoAutora;
    int rokWydania;
    string stan;
    string dataZwrotu;

public:
    Ksiazka();
    Ksiazka(int ID, const string& tytul, const string& nazwiskoAutora, int rokWydania, string stan);
    Ksiazka(int ID);
    int getID() const;
    string getTytul() const;
    string getNazwiskoAutora() const;
    int getRokWydania() const;
    string getStan() const;
  
};

