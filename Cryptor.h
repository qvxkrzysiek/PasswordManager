#ifndef PROJEKT_PJC_CRYPTOR_H
#define PROJEKT_PJC_CRYPTOR_H

#include <string>

class Cryptor {
public:
    Cryptor()= default;;

    std::string deCrypto(std::string str, std::string key);
    std::string enCrypto(std::string str, std::string key);
};

#endif //PROJEKT_PJC_CRYPTOR_H
