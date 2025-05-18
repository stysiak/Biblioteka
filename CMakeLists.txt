
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
)

# Dodanie ścieżek include
include_directories(
        ${PROJECT_SOURCE_DIR}/include
        ${PROJECT_SOURCE_DIR}/include/models
)

# Znalezienie wszystkich plików źródłowych w odpowiednich katalogach
file(GLOB_RECURSE CORE_SOURCES
        "src/core/*.cpp"
)

file(GLOB_RECURSE MODEL_SOURCES
        "src/models/*.cpp"
)

file(GLOB_RECURSE DATABASE_SOURCES
        "src/database/*.cpp"
)

file(GLOB_RECURSE UTILS_SOURCES
        "src/utils/*.cpp"
)

# Wszystkie pliki źródłowe
set(SOURCES
        ${CORE_SOURCES}
        ${MODEL_SOURCES}
        ${DATABASE_SOURCES}
        ${UTILS_SOURCES}
        src/main.cpp
)

# Wszystkie pliki nagłówkowe
file(GLOB_RECURSE HEADERS
        "include/*.h"
)

# Główny plik wykonywalny
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

option(BUILD_TESTS "Build the tests" OFF)  # Zmień ON na OFF

if(BUILD_TESTS)
    # Dodanie testów jako osobny target
    file(GLOB_RECURSE TEST_SOURCES
            "tests/*.cpp"
    )

    add_executable(BibliotekaTests ${TEST_SOURCES} ${MODEL_SOURCES} ${DATABASE_SOURCES} ${UTILS_SOURCES}
            tests/TestBazaKsiazek.cpp
            tests/TestBazaKsiazek.h)
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

# Instalacja (opcjonalna)
install(TARGETS ${PROJECT_NAME}
        RUNTIME DESTINATION bin
)

# Instalacja plików danych
install(DIRECTORY ${PROJECT_SOURCE_DIR}/data/
        DESTINATION share/${PROJECT_NAME}/data
)


# Informacje o konfiguracji
message(STATUS "Project name: ${PROJECT_NAME}")
message(STATUS "C++ Standard: ${CMAKE_CXX_STANDARD}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")