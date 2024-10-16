#include "Person.hpp"

Person::Person(const std::wstring& firstName,
               const std::wstring& lastName,
               const std::wstring& address,
               unsigned long pesel,
               Sex sex)
              : firstName_(firstName)
              , lastName_(lastName)
              , address_(address)
              , pesel_(pesel)
              , sex_(sex) {}

std::wstring Person::getFirstName() const {
    return firstName_;
}

std::wstring Person::getLastName() const {
    return lastName_;
}

std::wstring Person::getAddress() const {
    return address_;
}

std::wstring Person::getPesel() const {
    return std::to_wstring(pesel_);
}

Sex Person::getSex() const {
    return sex_;
}
