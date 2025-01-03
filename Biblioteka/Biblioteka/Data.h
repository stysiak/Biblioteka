#pragma once
#include "header.h"

class Data {
private:
    int dzien;
    int miesiac;
    int rok;

public:
    Data(int d, int m, int r);

    Data();

    Data zwrocDate();  

    void ustawDate(int d, int m, int r);  
};
