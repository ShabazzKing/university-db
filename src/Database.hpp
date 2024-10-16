#pragma once

#include "Person.hpp"
#include "Student.hpp"
#include "Worker.hpp"

#include <filesystem>
#include <memory>
#include <vector>

class Database {
private:
    struct printingValues {
        const unsigned fNameCol = 4; // Length of "Imię" word
        const unsigned lNameCol = 8; // Length of "Nazwisko" word
        const unsigned addressCol = 5; // Length of "Adres" word
        const unsigned indexNumberCol = 13; // Length of "Numer indeksu" phrase
        const unsigned peselCol = 5; // Length of "Pesel" word
        const unsigned sexCol = 4; // Length of "Płeć" word
        const unsigned earningsCol = 7; // Length of "Zarobki" word
        unsigned fNameSize = 0;
        unsigned lNameSize = 0;
        unsigned addressSize = 0;
        unsigned indexNumberSize = 0;
        unsigned peselSize = 0;
        const unsigned sexSize = 11;
        unsigned earningsSize = 0;
    };
    std::vector<std::shared_ptr<Person>> db_;
    bool peselIsValid(const std::wstring& pesel) const;
    bool peselExists(const std::wstring& pesel) const;
    bool indexNumberExists(const std::wstring& indexNumber) const;
    void printHeader(const printingValues& pv) const;
    void printDashes(const printingValues& pv) const;
    void printRow(const printingValues& pv, const std::shared_ptr<Person>& p) const;
    void writeFile(std::filesystem::path file) const;
public:
    Database();
    Database(const std::vector<std::shared_ptr<Person>>& persons);
    unsigned personsCount() const;
    bool addStudent(const Student& student);
    bool addWorker(const Worker& worker);
    bool removeStudentByIndexNumber(unsigned long indexNumber);
    bool removePersonByPesel(unsigned long pesel);
    void printDatabase() const;
    Database findByLastName(const std::wstring& lastName) const;
    Database findByPesel(unsigned long pesel) const;
    Database& sortByLastName();
    Database& sortByPesel();
    bool storeInFile(std::filesystem::path file) const;
    bool restoreFromFile(std::filesystem::path file);
};
