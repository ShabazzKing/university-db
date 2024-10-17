#include "Database.hpp"

#include <algorithm>
#include <codecvt>
#include <fstream>
#include <iostream>
#include <locale>
#include <numeric>
#include <string>

#include <json/json.h>

#include <unistd.h>
#include <sys/types.h>
#include <pwd.h>
#include <sys/stat.h>

Database::Database() : db_() {}

Database::Database(const std::vector<std::shared_ptr<Person>>& persons) : db_(persons) {}

unsigned Database::personsCount() const {
    return db_.size();
}

bool Database::addStudent(const Student& student) {
    if (! peselIsValid(student.getPesel()) || peselExists(student.getPesel()) || indexNumberExists(student.getIndexNumber())) {
        return false;
    }
    db_.push_back(std::make_shared<Student>(student));
    return true;
}

bool Database::addWorker(const Worker& worker) {
    if (! peselIsValid(worker.getPesel()) || peselExists(worker.getPesel())) {
        return false;
    }
    db_.push_back(std::make_shared<Worker>(worker));
    return true;
}

bool Database::peselIsValid(const std::wstring& pesel) const {
    unsigned long p = std::stoul(pesel);
    unsigned i = 0;
    std::vector<unsigned> digits;
    while (p != 0) {
        digits.push_back(p % 10);
        p -= digits[i++];
        p /= 10;
    }
    if (i != 11) {
        return false;
    }
    std::reverse(digits.begin(), digits.end());
    std::vector<unsigned> weights{1, 3, 7, 9, 1, 3, 7, 9, 1, 3};
    unsigned product = std::inner_product(weights.cbegin(), weights.cend(), digits.cbegin(), 0);
    unsigned controlDigit = product % 10 == 0 ? 0 : 10 - product % 10;
    if (controlDigit != digits[10]) {
        return false;
    }
    return true;
}

bool Database::peselExists(const std::wstring& pesel) const {
    if (std::find_if(db_.cbegin(), db_.cend(), [&pesel](const auto& elem) { return elem->getPesel() == pesel; }) != db_.cend()) {
        return true;
    }
    return false;
}

bool Database::removeStudentByIndexNumber(unsigned long indexNumber) {
    if (! indexNumberExists(std::to_wstring(indexNumber))) {
        return false;
    }
    db_.erase(std::remove_if(db_.begin(), db_.end(), [&indexNumber](const auto& elem) {
        return elem->getIndexNumber() == std::to_wstring(indexNumber);
    }), db_.end());
    return true;
}

bool Database::removePersonByPesel(unsigned long pesel) {
    if (! peselExists(std::to_wstring(pesel))) {
        return false;
    }
    db_.erase(std::remove_if(db_.begin(), db_.end(), [&pesel](const auto& elem) {
        return elem->getPesel() == std::to_wstring(pesel);
    }), db_.end());
    return true;
}

bool Database::indexNumberExists(const std::wstring& indexNumber) const {
    if (std::find_if(db_.cbegin(), db_.cend(), [&indexNumber](const auto& elem) {
        return elem->getIndexNumber() == indexNumber;
    }) != db_.cend()) {
        return true;
    }
    return false;
}

void Database::printDatabase() const {
    printingValues pv;
    std::for_each(db_.cbegin(), db_.cend(), [&pv](const auto& elem) {
        if (elem->getFirstName().size() > pv.fNameSize) {
            pv.fNameSize = elem->getFirstName().size();
        }
        if (elem->getLastName().size() > pv.lNameSize) {
            pv.lNameSize = elem->getLastName().size();
        }
        if (elem->getAddress().size() > pv.addressSize) {
            pv.addressSize = elem->getAddress().size();
        }
        if (elem->getIndexNumber().size() > pv.indexNumberSize) {
            pv.indexNumberSize = elem->getIndexNumber().size();
        }
        if (elem->getEarnings().size() > pv.earningsSize) {
            pv.earningsSize = elem->getEarnings().size();
        }
        if (elem->getPesel().size() > pv.peselSize) {
            pv.peselSize = elem->getPesel().size();
        }
    });
    pv.fNameSize = pv.fNameSize < pv.fNameCol ? pv.fNameCol : pv.fNameSize;
    pv.lNameSize = pv.lNameSize < pv.lNameCol ? pv.lNameCol : pv.lNameSize;
    pv.addressSize = pv.addressSize < pv.addressCol ? pv.addressCol : pv.addressSize;
    pv.indexNumberSize = pv.indexNumberSize < pv.indexNumberCol ? pv.indexNumberCol : pv.indexNumberSize;
    pv.earningsSize = pv.earningsSize < pv.earningsCol ? pv.earningsCol : pv.earningsSize;
    pv.peselSize = pv.peselSize < pv.peselCol ? pv.peselCol : pv.peselSize;
    pv.fNameSize += 2;
    pv.lNameSize += 2;
    pv.addressSize += 2;
    pv.indexNumberSize += 2;
    pv.earningsSize += 2;
    pv.peselSize += 2;
    printHeader(pv);
    for (const std::shared_ptr<Person>& person : db_) {
        printRow(pv, person);
    }
    printDashes(pv);
}

void Database::printHeader(const printingValues& pv) const {
    printDashes(pv);
    std::wcout << L"| ";
    std::wcout << L"Imię";
    for (unsigned i = 0; i < pv.fNameSize - pv.fNameCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Nazwisko";
    for (unsigned i = 0; i < pv.lNameSize - pv.lNameCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Adres";
    for (unsigned i = 0; i < pv.addressSize - pv.addressCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Numer indeksu";
    for (unsigned i = 0; i < pv.indexNumberSize - pv.indexNumberCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Zarobki";
    for (unsigned i = 0; i < pv.earningsSize - pv.earningsCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Pesel";
    for (unsigned i = 0; i < pv.peselSize - pv.peselCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << L"Płeć";
    for (unsigned i = 0; i < pv.sexSize - pv.sexCol - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"|\n";
    printDashes(pv);
}

void Database::printDashes(const printingValues& pv) const {
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.fNameSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.lNameSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.addressSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.indexNumberSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.earningsSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.peselSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+";
    for (unsigned i = 0; i < pv.sexSize; i++) {
        std::wcout << L"-";
    }
    std::wcout << L"+\n";
}

void Database::printRow(const printingValues& pv, const std::shared_ptr<Person>& p) const {
    std::wcout << L"| ";
    std::wcout << p->getFirstName();
    for (unsigned i = 0; i < pv.fNameSize - p->getFirstName().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << p->getLastName();
    for (unsigned i = 0; i < pv.lNameSize - p->getLastName().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << p->getAddress();
    for (unsigned i = 0; i < pv.addressSize - p->getAddress().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << p->getIndexNumber();
    for (unsigned i = 0; i < pv.indexNumberSize - p->getIndexNumber().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << p->getEarnings();
    for (unsigned i = 0; i < pv.earningsSize - p->getEarnings().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wcout << p->getPesel();
    for (unsigned i = 0; i < pv.peselSize - p->getPesel().size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"| ";
    std::wstring sex = p->getSex() == Sex::Woman ? L"kobieta" : L"mężczyzna";
    std::wcout << sex;
    for (unsigned i = 0; i < pv.sexSize - sex.size() - 1; i++) {
        std::wcout << L" ";
    }
    std::wcout << L"|\n";
}

Database Database::findByLastName(const std::wstring& lastName) const {
    std::vector<std::shared_ptr<Person>> result;
    std::for_each(db_.cbegin(), db_.cend(), [&result, &lastName](const auto& elem) {
        if (elem->getLastName() == lastName) {
            result.push_back(elem);
        }
    });
    return Database(result);
}

Database Database::findByPesel(unsigned long pesel) const {
    std::vector<std::shared_ptr<Person>> result;
    std::for_each(db_.cbegin(), db_.cend(), [&result, pesel](const auto& elem) {
        if (elem->getPesel() == std::to_wstring(pesel)) {
            result.push_back(elem);
        }
    });
    return Database(result);
}

Database& Database::sortByLastName() {
    std::sort(db_.begin(), db_.end(), [](const auto& elem1, const auto& elem2) {
        return elem1->getLastName() < elem2->getLastName();
    });
    return *this;
}


Database& Database::sortByPesel() {
    std::sort(db_.begin(), db_.end(), [](const auto& elem1, const auto& elem2) {
        return std::stoul(elem1->getPesel()) < std::stoul(elem2->getPesel());
    });
    return *this;
}

Database& Database::sortByEarnings() {
    std::sort(db_.begin(), db_.end(), [](const auto& elem1, const auto& elem2) {
        std::wstring e1 = elem1->getEarnings();
        std::wstring e2 = elem2->getEarnings();
        return std::stod(e1 != L"" ? e1 : L"-1.0") < std::stod(e2 != L"" ? e2 : L"-1.0");
    });
    return *this;
}

std::shared_ptr<Person> Database::getByPesel(unsigned long pesel) {
    for (const auto& elem : db_) {
        if (elem->getPesel() == std::to_wstring(pesel)) {
            return elem;
        }
    }
    return nullptr;
}

bool Database::storeInFile(std::filesystem::path file) const {
    if (file.string()[0] != '/') {
        std::filesystem::path leadingDot(".");
        leadingDot /= file;
        file = leadingDot;
    }
    if (std::filesystem::exists(file)) {
        return false;
    }
    bool canWriteToDirectory = false;
    unsigned UID = getuid();
    unsigned GID = getpwuid(UID)->pw_gid;
    std::unique_ptr<unsigned[]> supplementaryGroups = std::make_unique<unsigned[]>(1);
    unsigned numberOfSupplementaryGroups = getgroups(0, supplementaryGroups.get());
    supplementaryGroups.reset(nullptr);
    supplementaryGroups = std::make_unique<unsigned[]>(numberOfSupplementaryGroups);
    getgroups(numberOfSupplementaryGroups, supplementaryGroups.get());
    if (std::filesystem::exists(file.parent_path())) {
        struct stat info;
        if (stat(file.parent_path().c_str(), &info) == -1) {
            return false;
        }
        unsigned fileUID = info.st_uid;
        unsigned fileGID = getpwuid(info.st_uid)->pw_gid;
        bool fileGIDBelongsToUserSupplementaryGroups = false;
        for (unsigned i = 0; i < numberOfSupplementaryGroups; i++) {
            if (supplementaryGroups[i] == fileGID) {
                fileGIDBelongsToUserSupplementaryGroups = true;
                break;
            }
        }
        std::filesystem::perms filePerms = std::filesystem::status(file.parent_path()).permissions();
        if (UID == fileUID
            && (filePerms & (std::filesystem::perms::owner_write | std::filesystem::perms::owner_exec))
                == (std::filesystem::perms::owner_write | std::filesystem::perms::owner_exec)) {
            canWriteToDirectory = true;
        } else if ((GID == fileGID || fileGIDBelongsToUserSupplementaryGroups)
            && (filePerms & (std::filesystem::perms::group_write | std::filesystem::perms::group_exec))
                == (std::filesystem::perms::group_write | std::filesystem::perms::group_exec)) {
            canWriteToDirectory = true;
        } else if ((filePerms & (std::filesystem::perms::others_write | std::filesystem::perms::others_exec))
            == (std::filesystem::perms::others_write | std::filesystem::perms::others_exec)) {
            canWriteToDirectory = true;
        }
        if (canWriteToDirectory) {
            writeFile(file);
            return true;
        } else {
            return false;
        }
    } else {
        if (! std::filesystem::create_directories(file.parent_path())) {
            return false;
        }
        writeFile(file);
        return true;
    }
}

void Database::writeFile(std::filesystem::path file) const {
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    Json::Value root;
    std::for_each(db_.cbegin(), db_.cend(), [&root, &converter](const auto& elem) {
        Json::Value databaseEntry;
        databaseEntry["firstName"] = Json::Value(converter.to_bytes(elem->getFirstName()));
        databaseEntry["lastName"] = Json::Value(converter.to_bytes(elem->getLastName()));
        databaseEntry["address"] = Json::Value(converter.to_bytes(elem->getAddress()));;
        databaseEntry["indexNumber"] = elem->getIndexNumber() != L"" ? Json::Value(std::stoul(elem->getIndexNumber())) : Json::Value(0);
        databaseEntry["earnings"] = elem->getEarnings() != L"" ? Json::Value(std::stod(elem->getEarnings())) : Json::Value(0.0);
        databaseEntry["pesel"] = Json::Value(std::stoul(elem->getPesel()));
        databaseEntry["sex"] = Json::Value(elem->getSex() == Sex::Woman ? "w" : "m");
        databaseEntry["isStudent"] = Json::Value(elem->getIndexNumber() != L"" ? "y" : "n");
        root.append(databaseEntry);
    });
    std::ofstream outfile(file);
    outfile << root;
    outfile.close();
}

bool Database::restoreFromFile(std::filesystem::path file) {
    if (personsCount() > 0) {
        return false;
    }
    if (file.string()[0] != '/') {
        std::filesystem::path leadingDot(".");
        leadingDot /= file;
        file = leadingDot;
    }
    if (! std::filesystem::exists(file)) {
        return false;
    }
    bool canReadFromFile = false;
    unsigned UID = getuid();
    unsigned GID = getpwuid(UID)->pw_gid;
    std::unique_ptr<unsigned[]> supplementaryGroups = std::make_unique<unsigned[]>(1);
    unsigned numberOfSupplementaryGroups = getgroups(0, supplementaryGroups.get());
    supplementaryGroups.reset(nullptr);
    supplementaryGroups = std::make_unique<unsigned[]>(numberOfSupplementaryGroups);
    getgroups(numberOfSupplementaryGroups, supplementaryGroups.get());
    struct stat info;
    if (stat(file.c_str(), &info) == -1) {
        return false;
    }
    unsigned fileUID = info.st_uid;
    unsigned fileGID = getpwuid(info.st_uid)->pw_gid;
    bool fileGIDBelongsToUserSupplementaryGroups = false;
    for (unsigned i = 0; i < numberOfSupplementaryGroups; i++) {
        if (supplementaryGroups[i] == fileGID) {
            fileGIDBelongsToUserSupplementaryGroups = true;
            break;
        }
    }
    std::filesystem::perms filePerms = std::filesystem::status(file).permissions();
    if (UID == fileUID && (filePerms & std::filesystem::perms::owner_read) == std::filesystem::perms::owner_read) {
        canReadFromFile = true;
    } else if ((GID == fileGID || fileGIDBelongsToUserSupplementaryGroups)
        && (filePerms & std::filesystem::perms::group_read) == std::filesystem::perms::group_read) {
        canReadFromFile = true;
    } else if ((filePerms & std::filesystem::perms::others_read) == std::filesystem::perms::others_read) {
        canReadFromFile = true;
    }
    if (canReadFromFile) {
        std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
        Json::Value root;
        std::ifstream infile(file);
        infile >> root;
        infile.close();
        for (unsigned i = 0; i < root.size(); i++) {
            if (root[i]["isStudent"].asString() == "y") {
                addStudent(Student(converter.from_bytes(root[i]["firstName"].asString()),
                                   converter.from_bytes(root[i]["lastName"].asString()),
                                   converter.from_bytes(root[i]["address"].asString()),
                                   root[i]["indexNumber"].asUInt64(),
                                   root[i]["pesel"].asUInt64(),
                                   root[i]["sex"].asString() == "w" ? Sex::Woman : Sex::Man));
            } else {
                addWorker(Worker(converter.from_bytes(root[i]["firstName"].asString()),
                                 converter.from_bytes(root[i]["lastName"].asString()),
                                 converter.from_bytes(root[i]["address"].asString()),
                                 root[i]["earnings"].asDouble(),
                                 root[i]["pesel"].asUInt64(),
                                 root[i]["sex"].asString() == "w" ? Sex::Woman : Sex::Man));
            }
        }
        return true;
    } else {
        return false;
    }
}
