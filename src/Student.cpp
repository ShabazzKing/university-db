#include "Student.hpp"

Student::Student(const std::string& firstName,
                 const std::string& lastName,
                 const std::string& address,
                 unsigned indexNumber,
                 unsigned pesel,
                 Sex sex)
                : firstName_(firstName)
                , lastName_(lastName)
                , address_(address)
                , indexNumber_(indexNumber)
                , pesel_(pesel)
                , sex_(sex) {}

std::string Student::getFirstName() const {
    return firstName_;
}

std::string Student::getLastName() const {
    return lastName_;
}

std::string Student::getAddress() const {
    return address_;
}

unsigned Student::getIndexNumber() const {
    return indexNumber_;
}

unsigned Student::getPesel() const {
    return pesel_;
}

Sex Student::getSex() const {
    return sex_;
}
