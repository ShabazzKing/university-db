#include "Database.hpp"

#include <clocale>
#include <filesystem>
#include <iostream>
#include <string>

void addStudent(Database& database);
void removeStudent(Database& database);
void searchByLastName(const Database& database);
void searchByPesel(const Database& database);
void writeToFile(const Database& database);

int main() {
    std::setlocale(LC_ALL, "pl_PL.UTF-8");
    Database database;
    while (true) {
        std::wcout << L"Wybierz operację:\n";
        std::wcout << L"    1 Wyświetl bazę danych\n";
        std::wcout << L"    2 Dodaj studenta\n";
        std::wcout << L"    3 Usuń studenta\n";
        std::wcout << L"    4 Sortuj po nazwisku i wyświetl bazę danych\n";
        std::wcout << L"    5 Sortuj po numerze PESEL i wyświetl bazę danych\n";
        std::wcout << L"    6 Wyszukaj studentów po nazwisku i wyświetl\n";
        std::wcout << L"    7 Wyszukaj studenta po numerze PESEL i wyświetl\n";
        std::wcout << L"    8 Zapisz bazę do pliku\n";
        std::wcout << L"    9 Zakończ program\n";
        unsigned answer;
        std::wcin >> answer;
        switch (answer) {
            case 1:
                database.printDatabase();
                break;
            case 2:
                addStudent(database);
                break;
            case 3:
                removeStudent(database);
                break;
            case 4:
                database.sortByLastName().printDatabase();
                break;
            case 5:
                database.sortByPesel().printDatabase();
                break;
            case 6:
                searchByLastName(database);
                break;
            case 7:
                searchByPesel(database);
                break;
            case 8:
                writeToFile(database);
                break;
            case 9:
                return 0;
            default:
                std::wcout << L"Nieprawidłowa opcja\n";
        }
    }
    return 0;
}

void addStudent(Database& database) {
    std::wstring name, surname, address, sex;
    unsigned long indexNumber, pesel;
    std::wcout << L"Imię: ";
    std::wcin >> name;
    std::wcout << L"Nazwisko: ";
    std::wcin >> surname;
    std::wcin.get();
    std::wcout << L"Adres: ";
    std::getline(std::wcin, address);
    std::wcout << L"Numer indeksu: ";
    std::wcin >> indexNumber;
    std::wcout << L"PESEL: ";
    std::wcin >> pesel;
    std::wcin.get();
    std::wcout << L"Płeć (k/m): ";
    std::wcin >> sex;
    if (! database.addStudent(Student(name,
                                      surname,
                                      address,
                                      indexNumber,
                                      pesel,
                                      sex == L"k" ? Sex::Woman : Sex::Man))) {
        std::wcout << L"Nie udało się dodać studenta.\n";
    }
}

void removeStudent(Database& database) {
    unsigned long indexNumber;
    std::wcout << L"Numer indeksu: ";
    std::wcin >> indexNumber;
    if (! database.removeStudent(indexNumber)) {
        std::wcout << L"Nie udało się usunąć studenta.\n";
    }
}

void searchByLastName(const Database& database) {
    std::wstring surname;
    std::wcout << L"Nazwisko: ";
    std::wcin >> surname;
    database.findByLastName(surname).printDatabase();
}

void searchByPesel(const Database& database) {
    unsigned long pesel;
    std::wcout << L"PESEL: ";
    std::wcin >> pesel;
    database.findByPesel(pesel).printDatabase();
}

void writeToFile(const Database& database) {
    std::wcout << L"Podaj ściężkę do pliku (nazwę): ";
    std::wstring filename;
    std::wcin.get();
    std::getline(std::wcin, filename);
    if (! database.storeInFile(std::filesystem::path(filename))) {
        std::wcout << L"Nie udało się zapisać do pliku.\n";
    }
}
