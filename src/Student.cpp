#include "Student.hpp"

Student::Student(const std::wstring& firstName,
                 const std::wstring& lastName,
                 const std::wstring& address,
                 unsigned long indexNumber,
                 unsigned long pesel,
                 Sex sex)
                : firstName_(firstName)
                , lastName_(lastName)
                , address_(address)
                , indexNumber_(indexNumber)
                , pesel_(pesel)
                , sex_(sex) {}

std::wstring Student::getFirstName() const {
    return firstName_;
}

std::wstring Student::getLastName() const {
    return lastName_;
}

std::wstring Student::getAddress() const {
    return address_;
}

unsigned long Student::getIndexNumber() const {
    return indexNumber_;
}

unsigned long Student::getPesel() const {
    return pesel_;
}

Sex Student::getSex() const {
    return sex_;
}
