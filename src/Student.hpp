#pragma once

#include <string>

enum class Sex {
    Woman,
    Man
};

class Student {
private:
    std::string firstName_;
    std::string lastName_;
    std::string address_;
    unsigned indexNumber_;
    unsigned pesel_;
    Sex sex_;
    Student() {};
public:
    Student(const std::string& firstName,
            const std::string& lastName,
            const std::string& address,
            unsigned indexNumber,
            unsigned pesel,
            Sex sex);
    std::string getFirstName() const;
    std::string getLastName() const;
    std::string getAddress() const;
    unsigned getIndexNumber() const;
    unsigned getPesel() const;
    Sex getSex() const;
};
