/***********************************
 * Project: Password Manager
 * Author: Krzysztof Bartoszek
 * Nick: qvx
 **********************************/

#include <iostream>
#include <ctime>
#include "FileHandler.h"
#include "PasswordManager.h"
#include "Cryptor.h"



/**
 * It's a function initialize a whole program step by step
 */
int main() {

    // Initialize FileHandler which manage input/output file data
    auto *fileHandler = new FileHandler();
    fileHandler->chooseLocation();

    // Entering a password to file
    std::string password;
    std::cout << "Podaj haslo: ";
    std::cin >> password;

    // Decrypting a whole file by password and displaying timestamp
    fileHandler->decodeMap(password);
    auto *cryptor = new Cryptor();
    std::time_t result = stoi(cryptor->deCrypto(fileHandler->getTimestamp(), password));
    std::cout << "Ostatnio otwarty: " << std::asctime(std::localtime(&result));

    // Running a password management subroutine
    auto *passwordMenager = new PasswordManager(fileHandler->getPasswordsVec(), fileHandler->isPasswordCorect(password));

    // Closing a program and saving data to file
    fileHandler->setPasswordsVec(passwordMenager->getPassMap());
    fileHandler->encodeMap(password);
    fileHandler->closeFile(password);

    return 0;

}