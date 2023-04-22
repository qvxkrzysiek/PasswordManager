#include <vector>
#include <algorithm>
#include "Cryptor.h"

using namespace std;



/**
 * It takes a string and a key, and returns the decrypted string
 *
 * @param str The string to be decrypted
 * @param key The key used to encrypt the string
 *
 * @return A decrypted string
 */
string Cryptor::deCrypto(string str, std::string key){
    vector<string> numbersStr;
    int index = 0;
    string tmp;

    for (int i = 0 ; i < str.size() ; i++){
        if((str.at(i)) != ';'){
            tmp.push_back(str.at(i));
        } else {
            numbersStr.push_back(tmp);
            index++;
            tmp.clear();
        }
    }
    numbersStr.push_back(tmp);

    vector<int> numbersInt;

    for(int i = 0 ; i < numbersStr.size() ; i++){
        numbersInt.push_back(stoi(numbersStr.at(i)));
    }

    string end;

    for(int i = 0 ; i < numbersInt.size() ; i++){
        char c = numbersInt.at(i) / key.size();
        end.push_back(c);
    }

    std::reverse(end.begin(), end.end());

    return end;
}



/**
 * It takes a string and a key, and returns an encrypted string
 *
 * @param str The string you want to encrypt
 * @param key The key used to encrypt the string
 *
 * @return A encrypted string
 */
string Cryptor::enCrypto(string str, std::string key){
    vector<int> numbersInt;

    for(int i = 0 ; i < str.size() ; i++){
        char c = str.at(i);
        numbersInt.push_back((int)c);
    }

    string end;

    for(int i = 0 ; i < numbersInt.size() ; i++){
        string tmp = to_string(numbersInt.at(i) * key.size());

        std::reverse(tmp.begin(), tmp.end());


        for(int ii = 0 ; ii < tmp.size() ; ii++){
            end.push_back(tmp.at(ii));

        }

        if(i != numbersInt.size()-1){
            end.push_back(';');
        }
    }

    std::reverse(end.begin(), end.end());

    return end;
}
