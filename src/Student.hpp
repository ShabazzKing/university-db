#pragma once

#include <string>

enum class Sex {
    Woman,
    Man
};

class Student {
private:
    std::wstring firstName_;
    std::wstring lastName_;
    std::wstring address_;
    unsigned long indexNumber_;
    unsigned long pesel_;
    Sex sex_;
    Student() {};
public:
    Student(const std::wstring& firstName,
            const std::wstring& lastName,
            const std::wstring& address,
            unsigned long indexNumber,
            unsigned long pesel,
            Sex sex);
    std::wstring getFirstName() const;
    std::wstring getLastName() const;
    std::wstring getAddress() const;
    unsigned long getIndexNumber() const;
    unsigned long getPesel() const;
    Sex getSex() const;
};
