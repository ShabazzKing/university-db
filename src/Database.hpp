#pragma once

#include "Student.hpp"

#include <filesystem>
#include <vector>

class Database {
private:
    struct printingValues {
        const unsigned fNameCol = 4;
        const unsigned lNameCol = 8;
        const unsigned addressCol = 5;
        const unsigned indexNumberCol = 13;
        const unsigned peselCol = 5;
        const unsigned sexCol = 4;
        unsigned fNameSize = 0;
        unsigned lNameSize = 0;
        unsigned addressSize = 0;
        unsigned indexNumberSize = 0;
        unsigned peselSize = 0;
        const unsigned sexSize = 11;
    };
    std::vector<Student> db_;
    bool peselIsValid(unsigned long pesel) const;
    bool peselExists(unsigned long pesel) const;
    bool indexNumberExists(unsigned long indexNumber) const;
    void printHeader(const printingValues& pv) const;
    void printDashes(const printingValues& pv) const;
    void printRow(const printingValues& pv, const Student& s) const;
    void writeFile(std::filesystem::path file) const;
public:
    Database();
    Database(const std::vector<Student>& students);
    unsigned studentsCount() const;
    bool addStudent(const Student& student);
    bool removeStudent(unsigned long indexNumber);
    void printDatabase() const;
    Database findByLastName(const std::wstring& lastName) const;
    Database findByPesel(unsigned long pesel) const;
    Database& sortByLastName();
    Database& sortByPesel();
    bool storeInFile(std::filesystem::path file) const;
    bool restoreFromFile(std::filesystem::path file);
};
