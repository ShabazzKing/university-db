#pragma once

#include "Student.hpp"

#include <vector>

class Database {
private:
    struct printingValues {
        const unsigned fNameCol = 4;
        const unsigned lNameCol = 8;
        const unsigned addressCol = 5;
        const unsigned indexNumberCol = 12;
        const unsigned peselCol = 5;
        const unsigned sexCol = 4;
        unsigned fNameSize = 0;
        unsigned lNameSize = 0;
        unsigned addressSize = 0;
        unsigned indexNumberSize = 0;
        const unsigned peselSize = 13;
        const unsigned sexSize = 11;
    };
    std::vector<Student> db_;
    bool peselExists(unsigned pesel) const;
    bool indexNumberExists(unsigned indexNumber) const;
    void printHeader(const printingValues& pv) const;
    void printDashes(const printingValues& pv) const;
    void printRow(const printingValues& pv, const Student& s) const;
public:
    Database();
    unsigned studentsCount() const;
    bool addStudent(const Student& student);
    bool removeStudent(unsigned indexNumber);
    void printDatabase() const;
    std::vector<Student> findByLastName(const std::string& lastName) const;
    Student findByPesel(unsigned pesel) const;
    void sortByLastName();
    void sortByPesel();
};
