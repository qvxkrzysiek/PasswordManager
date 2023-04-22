#ifndef PROJEKT_PJC_PASSWORDMANAGER_H
#define PROJEKT_PJC_PASSWORDMANAGER_H

#include <iostream>
#include <vector>
#include <map>

class PasswordManager {

private:
    std::vector<std::vector<std::string>> passwordsVec;
    std::vector<std::string> categories;
    bool isCorect;

    std::vector<std::string> generateCategoriesList();
public:
    PasswordManager(const std::vector<std::vector<std::string>>& passwordsVec, bool isCorect);

    void operation();

    void findPassword();
    void sortPasswords();
    void addPassword();
    void editPassword();
    void deletePassword();
    void addCategory();
    void deleteCategory();

    void display(std::vector<std::vector<std::string>> passwordsVec, std::vector<std::string> columnsNames);
    [[nodiscard]] const std::vector<std::vector<std::string>> &getPassMap() const;
};

#endif //PROJEKT_PJC_PASSWORDMANAGER_H
