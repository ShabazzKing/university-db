#include "Database.hpp"

#include <clocale>
#include <filesystem>
#include <iostream>
#include <string>

void addStudent(Database& database);
void addWorker(Database& database);
void removeStudent(Database& database);
void removePerson(Database& database);
void searchByLastName(const Database& database);
void searchByPesel(const Database& database);
void modifyEarnings(Database& database);
void writeToFile(const Database& database);
void readFromFile(Database& database);

int main() {
    std::setlocale(LC_ALL, "pl_PL.UTF-8");
    Database database;
    while (true) {
        std::wcout << L"Wybierz operację:\n";
        std::wcout << L"    1 Wyświetl bazę danych\n";
        std::wcout << L"    2 Dodaj studenta\n";
        std::wcout << L"    3 Dodaj pracownika\n";
        std::wcout << L"    4 Usuń studenta po numerze indeksu\n";
        std::wcout << L"    5 Usuń osobę po numerze PESEL\n";
        std::wcout << L"    6 Sortuj po nazwisku i wyświetl bazę danych\n";
        std::wcout << L"    7 Sortuj po numerze PESEL i wyświetl bazę danych\n";
        std::wcout << L"    8 Wyszukaj osoby po nazwisku i wyświetl\n";
        std::wcout << L"    9 Wyszukaj osobę po numerze PESEL i wyświetl\n";
        std::wcout << L"    10 Wyszukaj osobę po numerze PESEL i modyfikuj zarobki\n";
        std::wcout << L"    11 Zapisz bazę do pliku\n";
        std::wcout << L"    12 Załaduj bazę z pliku\n";
        std::wcout << L"    13 Zakończ program\n";
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
                addWorker(database);
                break;
            case 4:
                removeStudent(database);
                break;
            case 5:
                removePerson(database);
                break;
            case 6:
                database.sortByLastName().printDatabase();
                break;
            case 7:
                database.sortByPesel().printDatabase();
                break;
            case 8:
                searchByLastName(database);
                break;
            case 9:
                searchByPesel(database);
                break;
            case 10:
                modifyEarnings(database);
                break;
            case 11:
                writeToFile(database);
                break;
            case 12:
                readFromFile(database);
                break;
            case 13:
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

void addWorker(Database& database) {
    std::wstring name, surname, address, sex;
    double earnings;
    unsigned long pesel;
    std::wcout << L"Imię: ";
    std::wcin >> name;
    std::wcout << L"Nazwisko: ";
    std::wcin >> surname;
    std::wcin.get();
    std::wcout << L"Adres: ";
    std::getline(std::wcin, address);
    std::wcout << L"Zarobki: ";
    std::wcin >> earnings;
    std::wcout << L"PESEL: ";
    std::wcin >> pesel;
    std::wcin.get();
    std::wcout << L"Płeć (k/m): ";
    std::wcin >> sex;
    if (! database.addWorker(Worker(name,
                                    surname,
                                    address,
                                    earnings,
                                    pesel,
                                    sex == L"k" ? Sex::Woman : Sex::Man))) {
        std::wcout << L"Nie udało się dodać pracownika.\n";
    }
}

void removeStudent(Database& database) {
    unsigned long indexNumber;
    std::wcout << L"Numer indeksu: ";
    std::wcin >> indexNumber;
    if (! database.removeStudentByIndexNumber(indexNumber)) {
        std::wcout << L"Nie udało się usunąć studenta.\n";
    }
}

void removePerson(Database& database) {
    unsigned long pesel;
    std::wcout << L"PESEL: ";
    std::wcin >> pesel;
    if (! database.removePersonByPesel(pesel)) {
        std::wcout << L"Nie udało się usunąć osoby.\n";
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

void modifyEarnings(Database& database){
    unsigned long pesel;
    std::wcout << L"PESEL: ";
    std::wcin >> pesel;
    std::shared_ptr<Person> person = database.getByPesel(pesel);
    if (person == nullptr) {
        std::wcout << L"Nie znaleziono osoby o podanym numerze PESEL.\n";
        return;
    }
    if (person->getEarnings() == L"") {
        std::wcout << L"To jest student, nie ma zarobków.\n";
        return;
    }
    double earnings;
    std::wcout << L"Nowe zarobki: ";
    std::wcin >> earnings;
    person->setEarnings(earnings);
}


void writeToFile(const Database& database) {
    std::wcout << L"Podaj ścieżkę do pliku (nazwę): ";
    std::wstring filename;
    std::wcin.get();
    std::getline(std::wcin, filename);
    if (! database.storeInFile(std::filesystem::path(filename))) {
        std::wcout << L"Nie udało się zapisać do pliku.\n";
    }
}

void readFromFile(Database& database) {
    std::wcout << L"Podaj ścieżkę do pliku (nazwę): ";
    std::wstring filename;
    std::wcin.get();
    std::getline(std::wcin, filename);
    if (! database.restoreFromFile(std::filesystem::path(filename))) {
        std::wcout << L"Nie udało się załadować z pliku.\n";
    }
}
