#include "PasswordManager.h"
#include<bits/stdc++.h>

using namespace std;



/**
 * It takes a vector of vectors of strings and a boolean as parameters, and then displays the vector of vectors of strings
 * and calls the operation function.
 *
 * @param vector vector<vector<string>> passwordsVec - vector of passwords
 * @param isCorect if the password is correct, it is true, otherwise it is false
 */
PasswordManager::PasswordManager(const std::vector<std::vector<std::string>>& passwordsVec, bool isCorect) {
    this->passwordsVec = passwordsVec;
    this->isCorect = isCorect;
    vector<string> null;
    display(passwordsVec, null);
    operation();
}



/**
 * It's a function that displays a menu and depending on the user's choice, it calls the appropriate function
 */
void PasswordManager::operation() {
    int op;
    cout << "======================" << endl;
    cout << "1.) Wyszukaj hasla" << endl;
    cout << "2.) Posortuj hasla" << endl;
    cout << "3.) Dodaj hasalo" << endl;
    cout << "4.) Edytuj haslo" << endl;
    cout << "5.) Usun haslo" << endl;
    cout << "6.) Dodaj kategorie" << endl;
    cout << "7.) Usun kategorie" << endl;
    cout << "8.) Zapisz i zamknij" << endl;
    cout << "Wybierz operacje: ";
    cin >> op;

    if (isCorect) {
        switch (op) {
            case 1: findPassword(); break;
            case 2: sortPasswords(); break;
            case 3: addPassword(); break;
            case 4: editPassword(); break;
            case 5: deletePassword(); break;
            case 6: addCategory(); break;
            case 7: deleteCategory(); break;
            default: break;
        }
    } else {
        cout << "Operacja niedostepna!!!" << endl;
    }
}



/**
 * It searches for a password in the vector of passwords and displays it
 */
void PasswordManager::findPassword() {
    string search;
    vector<string> null;
    std::vector<std::vector<std::string>> passwordsVEC;

    cout << "===============================================" << endl;
    cout << "Wyszukaj: ";
    cin >> search;

    for (int i = 0; i < passwordsVec.size(); i++) {
        bool found = false;
        for (int ii = 0; ii < passwordsVec.at(i).size(); ii++) {
            if (passwordsVec.at(i).at(ii).find(search) != string::npos && !found) {
                found = true;
                passwordsVEC.push_back(passwordsVec.at(i));
            }
        }
    }

    display(passwordsVEC, null);

    cout << "Wybierz operacje:" << endl;
    cout << "1.) Szukaj dalej 2.) Wroc" << endl;
    int op;
    cin >> op;

    switch (op) {
        case 1: findPassword(); break;
        case 2: display(passwordsVec, null); operation(); break;
    }
}



/**
 * It sorts the passwords by the user's choice
 */
void PasswordManager::sortPasswords() {
    int sort1, sort2;
    cout << "===============================================" << endl;
    cout << "Sortuj po pierwszym elemencie: ";
    cin >> sort1;
    cout << "Sortuj po drugim elemencie: ";
    cin >> sort2;

    std::vector<std::vector<std::string>> passwordsVEC;
    vector<string> title, password, category, login, page;

    for (int i = 0; i < passwordsVec.size(); i++) {
        title.push_back(passwordsVec.at(i).at(0));
        password.push_back(passwordsVec.at(i).at(1));
        category.push_back(passwordsVec.at(i).at(2));
        login.push_back(passwordsVec.at(i).at(3));
        page.push_back(passwordsVec.at(i).at(4));
    }

    vector<vector<string>> tmp1Vec = {title, password, category, login, page};
    vector<string> columnsNames1 = {"NAZWA", "HASLO", "KATEGORIA", "LOGIN", "STRONA"};

    vector<vector<string>> tmp2Vec;
    vector<string> columnsNames2;
    tmp2Vec.push_back(tmp1Vec.at(sort1 - 1));
    tmp2Vec.push_back(tmp1Vec.at(sort2 - 1));
    columnsNames2.push_back(columnsNames1.at(sort1 - 1));
    columnsNames2.push_back(columnsNames1.at(sort2 - 1));

    for (int i = 0; i < tmp1Vec.size(); i++) {
        if (i != sort1 - 1 && i != sort2 - 1) {
            tmp2Vec.push_back(tmp1Vec.at(i));
            columnsNames2.push_back(columnsNames1.at(i));
        }
    }

    vector<tuple<string, string, string, string, string>> VEC;
    for (int i = 0; i < passwordsVec.size(); i++) {
        VEC.push_back(make_tuple(tmp2Vec.at(0).at(i), tmp2Vec.at(1).at(i), tmp2Vec.at(2).at(i), tmp2Vec.at(3).at(i),
                                 tmp2Vec.at(4).at(i)));
    }

    sort(VEC.begin(), VEC.end());

    for (int i = 0; i < VEC.size(); i++) {
        vector<string> tmpEnd = {get<0>(VEC[i]), get<1>(VEC[i]), get<2>(VEC[i]), get<3>(VEC[i]), get<4>(VEC[i])};
        passwordsVEC.push_back(tmpEnd);
    }

    vector<string> null;
    cout<< "[ POSORTOWANE ]================" << endl;
    display(passwordsVEC, columnsNames2);
    cout<< "[ NORMALNE ]===================" << endl;
    display(passwordsVec, null);
    operation();
}


/**
 * It adds a password to the vector.
 */
void PasswordManager::addPassword() {
    string title, password, category, login = "brak", page = "brak";

    cout << "===============================================" << endl;
    cout << "Podaj nazwe: ";
    cin >> title;

    bool again = true;
    do {
        password.clear();
        int op;
        cout << "Chcesz? 1.) Podac haslo 2.) Wygenerowac haslo: ";
        cin >> op;
        switch (op) {
            case 1: {
                cout << "Podaj haslo: ";
                cin >> password;
                break;
            }
            case 2: {
                string male = "abcdefghijklmnopqrstuvwxyz";
                string duze = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
                string znaki = "!@#$%^&*";
                int ile, md, z;

                cout << "Z ilu znakow ma byc haslo: " << endl;
                cin >> ile;
                cout << "Ma zawierac: 1.) Male litery 2.) Male i duze litery: " << endl;
                cin >> md;
                cout << "Czy ma zawierac znaki specjalne 1.) Tak 2.) Nie: " << endl;
                cin >> z;

                string pula = male;

                if (md == 2) { pula += duze; }
                if (z == 1) { pula += znaki; }

                for (int i = 0; i < ile; i++) {
                    int random = rand() % pula.size();
                    password.push_back(pula.at(random));
                }
            }
        }
        string power;
        if (password.size() < 6) {
            power = "slabe";
        } else if (password.size() >= 6 && password.size() < 16) {
            power = "srednie";
        } else {
            power = "mocne";
        }

        int used = 0;
        for (int i = 0; i < passwordsVec.size(); i++) {
            if (passwordsVec.at(i).at(1) == password) {
                used++;
            }
        }

        cout << "Moc hasla: " << power << endl;
        cout << "Ile razy zostalo uzyte: " << used << endl;

        int op1;
        cout << "Czy haslo " << password << " jest w porzadku? 1.) Tak 2.) Nie:" << endl;
        cin >> op1;


        switch (op1) {
            case 1: again = false; break;
            case 2: again = true; break;
        }

    } while (again);

    int op;
    cout << "Wybierz kategorie: " << endl;

    vector<string> cat = generateCategoriesList();
    for (int i = 0; i < cat.size(); i++) {
        cout << i + 1 << " - " << cat.at(i) << endl;
    }
    cin >> op;
    category = generateCategoriesList().at(op - 1);

    int op1;
    cout << "Chcesz podac login? 1.) Tak 2.) Nie: ";
    cin >> op1;
    if (op1 == 1) {
        cin >> login;
    }

    int op2;
    cout << "Chcesz podac strone? 1.) Tak 2.) Nie: ";
    cin >> op2;
    if (op2 == 1) {
        cin >> page;
    }

    vector<string> end = {title, password, category, login, page};
    passwordsVec.push_back(end);

    vector<string> null;
    display(passwordsVec, null);
    operation();
}



/**
 * It allows you to edit a password.
 */
void PasswordManager::editPassword() {
    int editLine, editColumn;
    string edit;
    cout << "===============================================" << endl;
    cout << "Ktora linie chcesz edytowac: ";
    cin >> editLine;
    cout << "Ktora kolumne chcesz edytowac: ";
    cin >> editColumn;
    cout << "Na co chcesz edytowac: ";
    cin >> edit;


    passwordsVec.at(editLine - 1).at(editColumn - 1) = edit;

    vector<string> null;
    display(passwordsVec, null);
    operation();
}



/**
 * It deletes the lines that the user wants to delete.
 */
void PasswordManager::deletePassword() {
    vector<int> toDelete;
    cout << "===============================================" << endl;
    cout << "Po kolei podawaj linie do usuniecia (podaj liczbe 0 aby zakonczyc):" << endl;
    for (;;) {
        int tmp;
        cin >> tmp;
        if (tmp == 0) {
            break;
        } else {
            toDelete.push_back(tmp);
        }
    }
    cout << "Czy na pewno chcesz usunac linijki?" << endl;
    for (int i = 0; i < toDelete.size(); i++) {
        cout << toDelete.at(i) << ", ";
    }
    cout << "w sumie " << toDelete.size() << " element/y" << endl;
    for (;;) {
        cout << "(Y/N): ";
        char decision;
        cin >> decision;
        if (decision == 'Y' || decision == 'y') {

            std::vector<std::vector<std::string>> passwordsVEC;

            for (int i = 0; i < passwordsVec.size(); i++) {
                bool was = false;
                for (int ii = 0; ii < toDelete.size(); ii++) {
                    if (toDelete.at(ii) == i + 1) {
                        was = true;
                    }
                }
                if (!was) { passwordsVEC.push_back(passwordsVec.at(i)); }
            }

            passwordsVec = passwordsVEC;

            break;
        }
    }

    vector<string> null;
    display(passwordsVec, null);
    operation();
}



/**
 * It adds a new category to the list of categories.
 */
void PasswordManager::addCategory() {

    cout << "Istniejace kategorie:" << endl;

    vector<string> catList = generateCategoriesList();

    for (int i = 0; i < catList.size(); i++) {
        cout << i + 1 << " - " << catList.at(i) << endl;
    }

    string cat;
    cout << "Co chcesz dodac: ";
    cin >> cat;

    categories.push_back(cat);
    std::sort(categories.begin(), categories.end());

    cout << "Obecne kategorie po dodaniu:" << endl;
    for (int i = 0; i < categories.size(); i++) {
        cout << i + 1 << " - " << categories.at(i) << endl;
    }

    vector<string> null;
    display(passwordsVec, null);
    operation();
}



/**
 * It deletes a category and all passwords in it.
 */
void PasswordManager::deleteCategory() {
    cout << "Istniejace kategorie:" << endl;

    std::vector<std::vector<std::string>> passwordsVEC;
    vector<string> catList = generateCategoriesList();

    for (int i = 0; i < catList.size(); i++) {
        cout << i + 1 << " - " << catList.at(i) << endl;
    }

    int del;
    cout << "Co chcesz usunac: ";
    cin >> del;

    for (int i = 0; i < passwordsVec.size(); i++) {
        bool was = false;
        for (int ii = 0; ii < catList.size(); ii++) {
            if (passwordsVec.at(i).at(2) == catList.at(del - 1)) {
                was = true;
            }
        }
        if (!was) { passwordsVEC.push_back(passwordsVec.at(i)); }
    }

    passwordsVec = passwordsVEC;

    categories.erase(categories.begin() + (del - 1));
    std::sort(categories.begin(), categories.end());

    cout << endl;
    cout << "Obecne kategorie po usunieciu:" << endl;
    for (int i = 0; i < categories.size(); i++) {
        cout << i + 1 << " - " << categories.at(i) << endl;
    }

    vector<string> null;
    display(passwordsVec, null);
    operation();
}



/**
 * It displays a vector of vectors of strings in a table
 *
 * @param passwordsVec vector of vectors of strings, each vector of strings represents a single password
 * @param columnsNames vector of strings, which are the names of the columns.
 */
void PasswordManager::display(std::vector<std::vector<std::string>> passwordsVec, std::vector<string> columnsNames) {
    if (columnsNames.empty()) {
        columnsNames = {"NAZWA", "HASLO", "KATEGORIA", "LOGIN", "STRONA"};
    }

    int maxSize = 9;

    for (int i = 0; i < passwordsVec.size(); i++) {
        for (int ii = 0; ii < passwordsVec.at(i).size(); ii++) {
            if (passwordsVec.at(i).at(ii).size() > maxSize) {
                maxSize = passwordsVec.at(i).at(ii).size();
            }
        }
    }

    for (int i = 0; i < (maxSize * 5) + 9; i++) {
        cout << "=";
    }
    cout << endl;
    cout << "NR |";

    for (int i = 0; i < columnsNames.size(); i++) {
        cout << columnsNames.at(i);
        int size = maxSize - columnsNames.at(i).size();
        while (size > 0) {
            cout << " ";
            size--;
        }
        cout << "|";
    }
    cout << endl;
    for (int i = 0; i < (maxSize * 5) + 9; i++) {
        cout << "=";
    }
    cout << endl;

    for (int i = 0; i < passwordsVec.size(); i++) {
        for (int ii = 0; ii < passwordsVec.at(i).size(); ii++) {
            if (ii == 0) {
                cout << i + 1 << "  |";
            }
            cout << passwordsVec.at(i).at(ii);
            int size = maxSize - passwordsVec.at(i).at(ii).size();
            while (size > 0) {
                cout << " ";
                size--;
            }
            cout << "|";
        }
        cout << endl;
    }
}



/**
 * It generates a list of categories from the passwords vector
 *
 * @return Vector of strings
 */
std::vector<std::string> PasswordManager::generateCategoriesList() {
    if(categories.empty()){
        categories.push_back(passwordsVec.at(0).at(2));
    }

    for (int i = 1; i < passwordsVec.size(); i++) {
        bool was = false;
        for (int ii = 0; ii < categories.size(); ii++) {
            if (categories.at(ii) == passwordsVec.at(i).at(2)) {
                was = true;
            }
        }
        if (!was) { categories.push_back(passwordsVec.at(i).at(2)); }
    }

    std::sort(categories.begin(), categories.end());

    return categories;
}



/**
 * It returns a reference to the passwordsVec vector
 *
 * @return vector of vector of strings
 */
const vector<std::vector<std::string>> &PasswordManager::getPassMap() const {
    return passwordsVec;
}


