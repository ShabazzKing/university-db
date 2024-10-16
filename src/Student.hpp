#pragma once

#include "Person.hpp"

class Student : public Person {
private:
    unsigned long indexNumber_;
public:
    Student(const std::wstring& firstName,
            const std::wstring& lastName,
            const std::wstring& address,
            unsigned long indexNumber,
            unsigned long pesel,
            Sex sex);
    std::wstring getIndexNumber() const override;
    std::wstring getEarnings() const override;
    void setEarnings(double) override {};
};
