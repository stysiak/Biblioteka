#include "TestBazaKsiazek/pch.h"
#include "CppUnitTest.h" 
#include "../Biblioteka/BazaKsiazek.h"  
#include "../Biblioteka/Ksiazka.h"
#include "BazaKsiazek.cpp"
#include "../Biblioteka/Ksiazka.cpp"


using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestProjekt
{
    TEST_CLASS(BazaKsiazekTest) 
    {
    public:

        TEST_METHOD(AktualizujStanDodaj)
        {
            ofstream outPlik("baza_ksiazek.txt");
            outPlik.close();  

            BazaKsiazek baza;
            Ksiazka ksiazka(999, "Testowa Ksiazka", "Autor", 2023, "Dostepna");

            int wynik = baza.aktualizujStanDodaj(ksiazka);

            Assert::AreEqual(999, wynik);  

            remove("baza_ksiazek.txt");
        }

        TEST_METHOD(AktualizujStanUsun)
        {
            ofstream outPlik("baza_ksiazek.txt");
            outPlik.close();  // Tworzenie pustego pliku

            BazaKsiazek baza;
            Ksiazka ksiazka(2, "Ksiazka Do Usuniecia", "Autor", 2023, "Dostepna");

            baza.aktualizujStanDodaj(ksiazka);  // Najpierw dodajemy ksi��k�
            int wynik = baza.aktualizujStanUsun(ksiazka);  // Potem usuwamy ksi��k�

            Assert::AreEqual(2, wynik);  // Sprawdzamy, czy ksi��ka zosta�a usuni�ta

            remove("baza_ksiazek.txt");
        }

        TEST_METHOD(WyswietlListeKsiazek)
        {
            // Stworzenie pliku z ksi��kami przed testem
            ofstream outPlik("baza_ksiazek.txt");
            outPlik << "1,Ksiazka 1,Autor 1,2025,dostepna\n";
            outPlik << "2,Ksiazka 2,Autor 2,2025,niedostepna\n";
            outPlik.close();

            BazaKsiazek baza;
            Ksiazka ksiazka(3, "Ksiazka do wyswietlenia", "Autor", 2025, "Dostepna");

            baza.aktualizujStanDodaj(ksiazka);

            // Capture stdout (przechwytywanie wyj�cia)
            ostringstream output;
            streambuf* original = std::cout.rdbuf(output.rdbuf());

            baza.wyswietlListeKsiazek();

            string capturedOutput = output.str();
            Assert::IsTrue(capturedOutput.find("Ksiazka do wyswietlenia") != string::npos); //Sprawdzenie czy ksiazka jest na liscie

            cout.rdbuf(original);  // Przywr�cenie oryginalnego strumienia

            remove("baza_ksiazek.txt");
        }

    };
}