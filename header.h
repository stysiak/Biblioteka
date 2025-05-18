#pragma once

// wszystkie #include
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <fstream>
#include <sstream>
#include <ctime>
#include <iomanip>
#include <algorithm>

// Zewnętrzna biblioteka JSON (jeśli jej używasz)
#include <nlohmann/json.hpp>

// Używamy aliasu, by nie pisać nlohmann::json wszędzie
using json = nlohmann::json;

using namespace std;
//wszystkie nazwy klas
class Book;
class ReaderAccount;
class Employee;
class ReaderDatabase;
class BookDatabase;
class EmployeeDatabase;
class Wypozyczene;
class Return;
//plik header do wszystkich nag��wk�w
//jesli klasa korzysta z obiektow innych klas, to nag��wek te klasy doda� do nag��wku klasy u�ywaj�cej

