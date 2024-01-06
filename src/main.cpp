#include "Database.hpp"

#include <iostream>
#include <string>

void addStudent(Database& database);
void removeStudent(Database& database);
void searchByLastName(const Database& database);
void searchByPesel(const Database& database);

int main() {
    Database database;
    while (true) {
        std::cout << "Wybierz operację:\n";
        std::cout << "    1 Wyświetl bazę danych\n";
        std::cout << "    2 Dodaj studenta\n";
        std::cout << "    3 Usuń studenta\n";
        std::cout << "    4 Sortuj po nazwisku i wyświetl bazę danych\n";
        std::cout << "    5 Sortuj po numerze PESEL i wyświetl bazę danych\n";
        std::cout << "    6 Wyszukaj studentów po nazwisku i wyświetl\n";
        std::cout << "    7 Wyszukaj studenta po numerze PESEL i wyświetl\n";
        std::cout << "    8 Zakończ program\n";
        unsigned answer;
        std::cin >> answer;
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
                return 0;
            default:
                std::cout << "Nieprawidłowa opcja\n";
        }
    }
    return 0;
}

void addStudent(Database& database) {
    std::string name, surname, address;
    unsigned indexNumber, pesel;
    char sex;
    std::cout << "Imię: ";
    std::cin >> name;
    std::cout << "Nazwisko: ";
    std::cin >> surname;
    std::cout << "Adres: ";
    std::cin >> address;
    std::cout << "Numer indeksu: ";
    std::cin >> indexNumber;
    std::cout << "PESEL: ";
    std::cin >> pesel;
    std::cout << "Płeć (k/m): ";
    std::cin >> sex;
    if (! database.addStudent(Student(name, surname, address, indexNumber, pesel, sex == 'k' ? Sex::Woman : Sex::Man))) {
        std::cout << "Nie udało się dodać studenta.\n";
    }
}

void removeStudent(Database& database) {
    unsigned indexNumber;
    std::cout << "Numer indeksu: ";
    std::cin >> indexNumber;
    if (! database.removeStudent(indexNumber)) {
        std::cout << "Nie udało się usunąć studenta.\n";
    }
}

void searchByLastName(const Database& database) {
    std::string surname;
    std::cout << "Nazwisko: ";
    std::cin >> surname;
    database.findByLastName(surname).printDatabase();
}

void searchByPesel(const Database& database) {
    unsigned pesel;
    std::cout << "PESEL: ";
    std::cin >> pesel;
    database.findByPesel(pesel).printDatabase();
}
