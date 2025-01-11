#include "Data.h"

Data::Data(int d, int m, int r) : dzien(d), miesiac(m), rok(r) {}

Data::Data() = default; 

Data Data::zwrocDate() {
    return *this;
}

void Data::ustawDate(int d, int m, int r) {
    dzien = d;
    miesiac = m;
    rok = r;
}
