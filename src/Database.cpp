#include "Database.hpp"

#include <algorithm>
#include <iostream>
#include <string>

Database::Database() : db_() {}

unsigned Database::studentsCount() const {
    return db_.size();
}

bool Database::addStudent(const Student& student) {
    if (peselExists(student.getPesel())) {
        return false;
    }
    db_.push_back(student);
    return true;
}

bool Database::peselExists(unsigned pesel) const {
    if (std::find_if(db_.cbegin(), db_.cend(), [pesel](const auto& elem) { return elem.getPesel() == pesel; }) != db_.cend()) {
        return true;
    }
    return false;
}

bool Database::removeStudent(unsigned indexNumber) {
    if (! indexNumberExists(indexNumber)) {
        return false;
    }
    db_.erase(std::remove_if(db_.begin(), db_.end(), [indexNumber](const auto& elem) {
        return elem.getIndexNumber() == indexNumber;
    }), db_.end());
    return true;
}

bool Database::indexNumberExists(unsigned indexNumber) const {
    if (std::find_if(db_.cbegin(), db_.cend(), [indexNumber](const auto& elem) {
        return elem.getIndexNumber() == indexNumber;
    }) != db_.cend()) {
        return true;
    }
    return false;
}

void Database::printDatabase() const {
    printingValues pv;
    std::for_each(db_.cbegin(), db_.cend(), [&pv](const auto& elem) {
        if (elem.getFirstName().size() > pv.fNameSize) {
            pv.fNameSize = elem.getFirstName().size();
        }
        if (elem.getLastName().size() > pv.lNameSize) {
            pv.lNameSize = elem.getLastName().size();
        }
        if (elem.getAddress().size() > pv.addressSize) {
            pv.addressSize = elem.getAddress().size();
        }
        if (std::to_string(elem.getIndexNumber()).size() > pv.indexNumberSize) {
            pv.indexNumberSize = std::to_string(elem.getIndexNumber()).size();
        }
    });
    pv.fNameSize = pv.fNameSize < pv.fNameCol ? pv.fNameCol : pv.fNameSize;
    pv.lNameSize = pv.lNameSize < pv.lNameCol ? pv.lNameCol : pv.lNameSize;
    pv.addressSize = pv.addressSize < pv.addressCol ? pv.addressCol : pv.addressSize;
    pv.indexNumberSize = pv.indexNumberSize < pv.indexNumberCol ? pv.indexNumberCol : pv.indexNumberSize;
    pv.fNameSize += 2;
    pv.lNameSize += 2;
    pv.addressSize += 2;
    pv.indexNumberSize += 2;
    printHeader(pv);
    for (const Student& student : db_) {
        printRow(pv, student);
    }
    printDashes(pv);
}

void Database::printHeader(const printingValues& pv) const {
    printDashes(pv);
    std::cout << "| ";
    std::cout << "Imię";
    for (unsigned i = 0; i < pv.fNameSize - pv.fNameCol - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << "Nazwisko";
    for (unsigned i = 0; i < pv.lNameSize - pv.lNameCol - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << "Adres";
    for (unsigned i = 0; i < pv.addressSize - pv.addressCol - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << "Numer indeksu";
    for (unsigned i = 0; i < pv.indexNumberSize - pv.indexNumberCol - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << "Pesel";
    for (unsigned i = 0; i < pv.peselSize - pv.peselCol - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << "Płeć";
    for (unsigned i = 0; i < pv.sexSize - pv.sexCol - 1; i++) {
        std::cout << " ";
    }
    std::cout << "|\n";
    printDashes(pv);
}

void Database::printDashes(const printingValues& pv) const {
    std::cout << "+";
    for (unsigned i = 0; i < pv.fNameSize; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    for (unsigned i = 0; i < pv.lNameSize; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    for (unsigned i = 0; i < pv.addressSize; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    for (unsigned i = 0; i < pv.indexNumberSize; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    for (unsigned i = 0; i < pv.peselSize; i++) {
        std::cout << "-";
    }
    std::cout << "+";
    for (unsigned i = 0; i < pv.sexSize; i++) {
        std::cout << "-";
    }
    std::cout << "+\n";
}

void Database::printRow(const printingValues& pv, const Student& s) const {
    std::cout << "| ";
    std::cout << s.getFirstName();
    for (unsigned i = 0; i < pv.fNameSize - s.getFirstName().size() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << s.getLastName();
    for (unsigned i = 0; i < pv.lNameSize - s.getLastName().size() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << s.getAddress();
    for (unsigned i = 0; i < pv.addressSize - s.getAddress().size() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << s.getIndexNumber();
    for (unsigned i = 0; i < pv.indexNumberSize - std::to_string(s.getIndexNumber()).size() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::cout << s.getPesel();
    for (unsigned i = 0; i < pv.peselSize - std::to_string(s.getPesel()).size() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "| ";
    std::string sex = s.getSex() == Sex::Woman ? "kobieta" : "mężczyzna";
    std::cout << sex;
    for (unsigned i = 0; i < pv.sexSize - sex.size() - 1; i++) {
        std::cout << " ";
    }
    std::cout << "|\n";
}

std::vector<Student> Database::findByLastName(const std::string& lastName) const {
    std::vector<Student> result;
    std::for_each(db_.cbegin(), db_.cend(), [&result, lastName](const auto& elem) {
        if (elem.getLastName() == lastName) {
            result.push_back(elem);
        }
    });
    return result;
}

Student Database::findByPesel(unsigned pesel) const {
    for (const Student& student : db_) {
        if (student.getPesel() == pesel) {
            return student;
        }
    }
    throw "Student o peselu " + std::to_string(pesel) + " nie istnieje.\n";
}

void Database::sortByLastName() {
    std::sort(db_.begin(), db_.end(), [](const auto& elem1, const auto& elem2) {
        return elem1.getLastName() < elem2.getLastName();
    });
}


void Database::sortByPesel() {
    std::sort(db_.begin(), db_.end(), [](const auto& elem1, const auto& elem2) {
        return elem1.getPesel() < elem2.getPesel();
    });
}
