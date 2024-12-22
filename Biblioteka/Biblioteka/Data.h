#pragma once
#include "header.h"

class Data {
private:
    int dzien{ 1 };
    int miesiac{ 1 };
    int rok{ 2000 };

public:
    Data(int d, int m, int r);

    Data();

    Data zwrocDate();  

    void ustawDate(int d, int m, int r);  
};
