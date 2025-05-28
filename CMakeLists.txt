# Minimalna wymagana wersja CMake
cmake_minimum_required(VERSION 3.10)

# Nazwa projektu
project(Biblioteka)

# Ustawienie standardu C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ustawienie katalogu dla plików wykonywalnych
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Ustawienie katalogu dla bibliotek
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Dodanie ścieżek include
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/models
)

# Explicite wymienienie wszystkich plików źródłowych
set(SOURCES
        src/core/Administrator.cpp
        src/models/Employee.cpp
        src/models/ReaderAccount.cpp
        src/models/Book.cpp
        src/database/BookDatabase.cpp
        src/database/ReaderDatabase.cpp
        src/database/EmployeeDatabase.cpp
        src/utils/Borrowing.cpp
        src/utils/Return.cpp
        src/main.cpp
        src/utils/Logger.cpp
        include/utils/Logger.h
)

# Wszystkie pliki nagłówkowe
file(GLOB_RECURSE HEADERS
        "include/*.h"
)

# Główny plik wykonywalny
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

option(BUILD_TESTS "Build the tests" OFF)

if(BUILD_TESTS)
    set(TEST_SOURCES
            tests/BookDatabaseTest.cpp
            src/models/Employee.cpp
            src/models/ReaderAccount.cpp
            src/models/Book.cpp
            src/database/BookDatabase.cpp
            src/database/ReaderDatabase.cpp
            src/database/EmployeeDatabase.cpp
            src/utils/Borrowing.cpp
            src/utils/Return.cpp
    )

    add_executable(BibliotekaTests ${TEST_SOURCES})
    target_include_directories(BibliotekaTests PRIVATE ${PROJECT_SOURCE_DIR}/include)
endif()

# Kopiowanie plików danych do katalogu build
file(GLOB DATA_FILES "data/*")
file(COPY ${DATA_FILES} DESTINATION ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/data)

# Ustawienia debug/release
if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -g)
else()
    target_compile_options(${PROJECT_NAME} PRIVATE -O3)
endif()

# Instalacja
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/
        DESTINATION share/${PROJECT_NAME}/data
)

# Informacje o konfiguracji
message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")