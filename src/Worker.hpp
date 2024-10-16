#pragma once

#include "Person.hpp"

class Worker : public Person {
private:
    double earnings_;
public:
    Worker(const std::wstring& firstName,
           const std::wstring& lastName,
           const std::wstring& address,
           double earnings,
           unsigned long pesel,
           Sex sex);
    std::wstring getIndexNumber() const override;
    std::wstring getEarnings() const override;
};
