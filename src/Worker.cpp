#include "Worker.hpp"

Worker::Worker(const std::wstring& firstName,
               const std::wstring& lastName,
               const std::wstring& address,
               double earnings,
               unsigned long pesel,
               Sex sex)
              : Person(firstName, lastName, address, pesel, sex)
              , earnings_(earnings) {}

std::wstring Worker::getIndexNumber() const {
    return L"";
}

std::wstring Worker::getEarnings() const {
    return std::to_wstring(earnings_);
}

void Worker::setEarnings(double e) {
    earnings_ = e;
}
