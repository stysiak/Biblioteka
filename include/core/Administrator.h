#pragma once
#include "../models/Pracownik.h"
#include "../database/BazaKsiazek.h"
#include "../database/BazaPracownikow.h"

/**
 * @brief Klasa reprezentująca administratora systemu bibliotecznego
 */
class Administrator : public Pracownik {
public:
    Administrator();
    Administrator(const string& pesel, const string& imie, const string& nazwisko,
                 const string& login, const string& haslo, const string& funkcja);

    virtual ~Administrator() = default;

    void dodajKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) noexcept;
    void usunKsiazke(BazaKsiazek& baza, const Ksiazka& ksiazka) noexcept;
    void dodajPracownika(BazaPracownikow& baza, const Pracownik& pracownik) noexcept;
    void usunPracownika(BazaPracownikow& baza, const Pracownik& pracownik) noexcept;
    void wyswietlListePracownikow(const BazaPracownikow& baza) const noexcept;
};
