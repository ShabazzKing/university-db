#include "Student.hpp"

Student::Student(const std::wstring& firstName,
                 const std::wstring& lastName,
                 const std::wstring& address,
                 unsigned long indexNumber,
                 unsigned long pesel,
                 Sex sex)
                : Person(firstName, lastName, address, pesel, sex)
                , indexNumber_(indexNumber) {}

std::wstring Student::getIndexNumber() const {
    return std::to_wstring(indexNumber_);
}

std::wstring Student::getEarnings() const {
    return L"";
}
