cmake_minimum_required(VERSION 3.31)
project(Biblioteka)

set(CMAKE_CXX_STANDARD 20)

add_executable(Biblioteka
        main.cpp
        BazaPracownikow.cpp
        BazaCzytelnikow.cpp
        BazaKsiazek.cpp
        Administrator.cpp
        Pracownik.cpp
        KontoCzytelnika.cpp
        Ksiazka.cpp
        Wypozyczenie.cpp
        Zwrot.cpp
)