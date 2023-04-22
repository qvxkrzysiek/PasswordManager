#include "FileHandler.h"
#include "Cryptor.h"
#include <filesystem>
#include <iostream>
#include <fstream>

using namespace std;
namespace fs = std::filesystem;



/**
 * It's a function that allows the user to choose the location of the file from which the passwords will be taken.
 */
void FileHandler::chooseLocation() {
    cout << "Wybierz skad chcesz, aby byly czerpane twoje hasla?:" << endl;
    cout << "1.) Z folderu programu" << endl;
    cout << "2.) Z innej sciezki" << endl;

    char choosenLocation;
    bool again = true;
    while(again){
        cin >> choosenLocation;
        switch (choosenLocation) {
            case '1':
                FileHandler::fileLoaderHome(); again = false; break;
            case '2': FileHandler::fileLoader(); again = false; break;
            default: cout << "Bledny wybor, podaj liczbe z zakresu od 1 do 2!:" << endl; break;
        }
    }
}



/**
 * It's a function that allows you to choose a file from the current directory
 */
void FileHandler::fileLoaderHome() {
    vector<string> homeFilesList;
    int choose;

    cout << "Wybierz opcje:" << endl;

    for (auto const &file: fs::directory_iterator(fs::current_path())) {
        if (file.path().extension() == ".txt" && file.path().filename() != "CMakeCache.txt") {
            homeFilesList.push_back(file.path().string());
        }
    }

    for (int i = 0; i < homeFilesList.size(); i++) {
        cout << i + 1 << ".) " << homeFilesList.at(i) << endl;
    }

    for (;;) {
        cin >> choose;
        if (choose > homeFilesList.size() || choose <= 0) {
            cout << "Bledny numer" << endl;
        } else {
            path = homeFilesList.at(choose - 1);
            FileHandler::openFile();
            break;
        }
    }
}



/**
 * It asks for a path to a file, checks if it exists, and if it does, it opens it
 */
void FileHandler::fileLoader() {
    for (;;) {
        cout << "Podaj sciezke do pliku:" << endl;
        cin >> path;
        if (fs::exists(path)) {
            break;
        } else {
            cout << "Podano zla lokalizacje!!!" << endl;
        }
    }
    FileHandler::openFile();
}



/**
 * It opens the file, reads the first line, and then reads the rest of the file into a vector of vectors
 */
void FileHandler::openFile() {
    ifstream passFile(path);

    int loop = 0;
    string title, password, category, login, page;

    while (passFile >> title >> password >> category >> login >> page) {
        if (loop == 0) {
            passwordToFile = title;
            timestamp = password;
        } else {
            vector<string> vec{title, password, category, login, page};
            passwordsVec.push_back(vec);
        }
        loop++;
    }
}



/**
 * @return The timestamp of the file.
 */
const string &FileHandler::getTimestamp() const {
    return timestamp;
}



/**
 * It writes the password to the file, and if the password is correct, it writes the passwords to the file
 *
 * @param password the password that the user entered
 */
void FileHandler::closeFile(string password) {
    ofstream passFile(path);

    auto *obj = new Cryptor();
    std::time_t time = std::time(nullptr);
    string CryptTime = obj->enCrypto(to_string(time), password);

    passFile << passwordToFile << " " << CryptTime << " x" << " x" << " x" << endl;

    for (int i = 0; i < passwordsVec.size(); i++) {
        passFile << passwordsVec.at(i).at(0) << " " << passwordsVec.at(i).at(1) << " " << passwordsVec.at(i).at(2)
        << " " << passwordsVec.at(i).at(3) << " " << passwordsVec.at(i).at(4) << endl;
    }

    passFile.close();
}



/**
 * It decrypts the passwords in the passwordsVec vector
 *
 * @param key The key used to encrypt the file.
 */
void FileHandler::decodeMap(const std::string &key) {
    auto *obj = new Cryptor();

    for (auto &i: passwordsVec) {
        vector<string> startVec = i;
        vector<string> endVec;
        for (auto &str: startVec) {
            string text = obj->deCrypto(str, key);
            endVec.push_back(text);
        }
        i = endVec;
    }
}



/**
 * It takes a key, creates a new Cryptor object, loops through the passwordsVec, loops through the vector inside the
 * vector, encrypts the string, and pushes it back into the vector
 *
 * @param key The key used to encrypt the data.
 */
void FileHandler::encodeMap(std::string key) {
    auto *obj = new Cryptor();

    for (auto &i: passwordsVec) {
        vector<string> startVec = i;
        vector<string> endVec;
        for (auto &ii: startVec) {
            string text = obj->enCrypto(ii, key);
            endVec.push_back(text);
        }
        i = endVec;
    }
}



/**
 * It returns a vector of vectors of strings
 *
 * @return A vector of vectors of strings.
 */
std::vector<std::vector<std::string>> FileHandler::getPasswordsVec() {
    return passwordsVec;
}



/**
 * This function sets the passwordsVec variable to the passwordVec parameter
 *
 * @param passwordVec A vector of vectors of strings. The outer vector represents the rows of the file, and the inner
 * vector represents the columns.
 */
void FileHandler::setPasswordsVec(std::vector<std::vector<std::string>> passwordVec) {
    this->passwordsVec = passwordVec;
}



/**
 * It checks if the password is correct.
 *
 * @param key The key to encrypt the file with.
 *
 * @return a boolean value.
 */
bool FileHandler::isPasswordCorect(std::string key) {
    auto *obj = new Cryptor();

    if (obj->deCrypto(passwordToFile, "B&E)H@McQfTjWnZr") == key) {
        return true;
    } else {
        return false;
    }
}




