#include "Database.hpp"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <string>

Database::Database() : db_() {}

Database::Database(const std::vector<Student>& students) : db_(students) {}

unsigned Database::studentsCount() const {
    return db_.size();
}

bool Database::addStudent(const Student& student) {
    if (! peselIsValid(student.getPesel()) || peselExists(student.getPesel()) || indexNumberExists(student.getIndexNumber())) {
        return false;
    }
    db_.push_back(student);
    return true;
}

bool Database::peselIsValid(unsigned long pesel) const {
    unsigned i = 0;
    std::vector<unsigned> digits;
    while (pesel != 0) {
        digits.push_back(pesel % 10);
        pesel -= digits[i++];
        pesel /= 10;
    }
    if (i != 11) {
        return false;
    }
    std::reverse(digits.begin(), digits.end());
    std::vector<unsigned> weights{1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
    unsigned product = std::inner_product(weights.cbegin(), weights.cend(), digits.cbegin(), 0);
    unsigned controlDigit = product % 10 == 0 ? 0 : 10 - product % 10;
    if (controlDigit != digits[10]) {
        return false;
    }
    return true;
}



bool Database::peselExists(unsigned long pesel) const {
    if (std::find_if(db_.cbegin(), db_.cend(), [pesel](const auto& elem) { return elem.getPesel() == pesel; }) != db_.cend()) {
        return true;
    }
    return false;
}

bool Database::removeStudent(unsigned long indexNumber) {
    if (! indexNumberExists(indexNumber)) {
        return false;
    }
    db_.erase(std::remove_if(db_.begin(), db_.end(), [indexNumber](const auto& elem) {
        return elem.getIndexNumber() == indexNumber;
    }), db_.end());
    return true;
}

bool Database::indexNumberExists(unsigned long indexNumber) const {
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
        if (std::to_wstring(elem.getIndexNumber()).size() > pv.indexNumberSize) {
            pv.indexNumberSize = std::to_wstring(elem.getIndexNumber()).size();
        }
        if (std::to_wstring(elem.getPesel()).size() > pv.peselSize) {
            pv.peselSize = std::to_wstring(elem.getPesel()).size();
        }
    });
    pv.fNameSize = pv.fNameSize < pv.fNameCol ? pv.fNameCol : pv.fNameSize;
    pv.lNameSize = pv.lNameSize < pv.lNameCol ? pv.lNameCol : pv.lNameSize;
    pv.addressSize = pv.addressSize < pv.addressCol ? pv.addressCol : pv.addressSize;
    pv.indexNumberSize = pv.indexNumberSize < pv.indexNumberCol ? pv.indexNumberCol : pv.indexNumberSize;
    pv.peselSize = pv.peselSize < pv.peselCol ? pv.peselCol : pv.peselSize;
    pv.fNameSize += 2;
    pv.lNameSize += 2;
    pv.addressSize += 2;
    pv.indexNumberSize += 2;
    pv.peselSize += 2;
    printHeader(pv);
    for (const Student& student : db_) {
        printRow(pv, student);
    }
    printDashes(pv);
}

void Database::printHeader(const printingValues& pv) const {
    printDashes(pv);
    std::wcout << L"| ";
    std::wcout << L"Imię";
    for (unsigned i = 0; i < pv.fNameSize - pv.fNameCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Nazwisko";
    for (unsigned i = 0; i < pv.lNameSize - pv.lNameCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Adres";
    for (unsigned i = 0; i < pv.addressSize - pv.addressCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Numer indeksu";
    for (unsigned i = 0; i < pv.indexNumberSize - pv.indexNumberCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Pesel";
    for (unsigned i = 0; i < pv.peselSize - pv.peselCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Płeć";
    for (unsigned i = 0; i < pv.sexSize - pv.sexCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"|\n";
    printDashes(pv);
}

void Database::printDashes(const printingValues& pv) const {
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.fNameSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.lNameSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.addressSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.indexNumberSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.peselSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.sexSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+\n";
}

void Database::printRow(const printingValues& pv, const Student& s) const {
    std::wcout << L"| ";
    std::wcout << s.getFirstName();
    for (unsigned i = 0; i < pv.fNameSize - s.getFirstName().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << s.getLastName();
    for (unsigned i = 0; i < pv.lNameSize - s.getLastName().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << s.getAddress();
    for (unsigned i = 0; i < pv.addressSize - s.getAddress().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << s.getIndexNumber();
    for (unsigned i = 0; i < pv.indexNumberSize - std::to_wstring(s.getIndexNumber()).size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << s.getPesel();
    for (unsigned i = 0; i < pv.peselSize - std::to_wstring(s.getPesel()).size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wstring sex = s.getSex() == Sex::Woman ? L"kobieta" : L"mężczyzna";
    std::wcout << sex;
    for (unsigned i = 0; i < pv.sexSize - sex.size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"|\n";
}

Database Database::findByLastName(const std::wstring& lastName) const {
    std::vector<Student> result;
    std::for_each(db_.cbegin(), db_.cend(), [&result, lastName](const auto& elem) {
        if (elem.getLastName() == lastName) {
            result.push_back(elem);
        }
    });
    return Database(result);
}

Database Database::findByPesel(unsigned long pesel) const {
    std::vector<Student> result;
    std::for_each(db_.cbegin(), db_.cend(), [&result, pesel](const auto& elem) {
        if (elem.getPesel() == pesel) {
            result.push_back(elem);
        }
    });
    return Database(result);
}

Database& Database::sortByLastName() {
    std::sort(db_.begin(), db_.end(), [](const auto& elem1, const auto& elem2) {
        return elem1.getLastName() < elem2.getLastName();
    });
    return *this;
}


Database& Database::sortByPesel() {
    std::sort(db_.begin(), db_.end(), [](const auto& elem1, const auto& elem2) {
        return elem1.getPesel() < elem2.getPesel();
    });
    return *this;
}
