#ifndef PROJEKT_PJC_FILEHANDLER_H
#define PROJEKT_PJC_FILEHANDLER_H

#include <iostream>
#include <vector>
#include <map>

class FileHandler {
private:
    std::vector<std::vector<std::string>> passwordsVec;
    std::string timestamp, passwordToFile, path;

    void fileLoaderHome();
    void fileLoader();
    void openFile();

public:
    FileHandler() = default;;

    void chooseLocation();
    void closeFile(std::string password);
    void decodeMap(const std::string& password);
    void encodeMap(std::string password);

    std::vector<std::vector<std::string>> getPasswordsVec();
    void setPasswordsVec(std::vector<std::vector<std::string>> passwordVec);
    [[nodiscard]] const std::string &getTimestamp() const;
    bool isPasswordCorect(std::string password);
};

#endif //PROJEKT_PJC_FILEHANDLER_H
