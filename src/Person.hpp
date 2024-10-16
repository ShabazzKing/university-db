#pragma once

#include <string>

enum class Sex {
    Woman,
    Man
};

class Person {
private:
    std::wstring firstName_;
    std::wstring lastName_;
    std::wstring address_;
    unsigned long pesel_;
    Sex sex_;
    Person() = default;
public:
    Person(const std::wstring& firstName,
           const std::wstring& lastName,
           const std::wstring& address,
           unsigned long pesel,
           Sex sex);
    virtual ~Person() = default;
    std::wstring getFirstName() const;
    std::wstring getLastName() const;
    std::wstring getAddress() const;
    virtual std::wstring getIndexNumber() const = 0;
    virtual std::wstring getEarnings() const = 0;
    virtual void setEarnings(double) = 0;
    std::wstring getPesel() const;
    Sex getSex() const;
};
