#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <sstream>
#include <conio.h>
#include <limits>

struct User {
    int id;
    std::string login, password;
};

struct Contact {
    int id;
    std::string name, surname, email, address, phoneNumber;
};

std::string readLine() {

    std::string input = "";
    std::cin.sync();
    getline(std::cin, input);
    return input;
}

char readChar() {

    std::string input = readLine();
    char character;

    if ( input.length() == 1) {
        character = input[0];
    }
    else {
        std::cout << "This is not a single sign, try again" << std::endl;
        system("pause");
        return readChar();
    }
    return character;
}

int readInt() {

    std::string input = readLine();

    for (char x : input) {
        if (!isdigit(x)) {
            std::cout << "Please try again and enter number" << std::endl;
            return readInt();
        }
    }

    int readInt = stoi(input);

    return readInt;
}

void handleFileSwap(std::string oldFileName, std::string tempFileName) {

    if (std::remove(oldFileName.c_str()) != 0) {
        perror("Error removing file");
    }

    if (rename(tempFileName.c_str(), oldFileName.c_str()) != 0) {
        perror ("Error renaming file");
    }
}

std::string showAvailableIDs (std::vector<Contact>& contacts) {

    std::string id, IDsToDelete = "";

    for (const Contact& contact : contacts) {
        std::stringstream ss;
        ss << contact.id;
        id = ss.str();

        IDsToDelete.append(id);
        IDsToDelete.append(" ");
    }

    return IDsToDelete;
}

bool isFileEmpty (std::vector<Contact>& contacts) {

    bool contactBookStatus = false;

    if (contacts.empty()) {
        std::cout << "Contact book empty." << std::endl;
        system("pause");
        contactBookStatus = true;
    }

    return contactBookStatus;
}

void menu (int number) {

    if (number == 1) {
        std::cout << "===WELCOME IN YOUR ADRESS BOOK ===" << std::endl;
        std::cout << ""                                   << std::endl;
        std::cout << "===============MENU===============" << std::endl;
        std::cout << "1.        Registration"             << std::endl;
        std::cout << "2.           Log in"                << std::endl;
        std::cout << "9.        Exit program"             << std::endl;
        std::cout << "==================================" << std::endl;
        std::cout << ""                                   << std::endl;
    }
    else if (number == 2) {
        std::cout << " "                                 << std::endl;
        std::cout << "===========ADDRESS BOOK==========" << std::endl;
        std::cout << " "                                 << std::endl;
        std::cout << "===============MENU==============" << std::endl;
        std::cout << "1.         Add contact"            << std::endl;
        std::cout << "2.       Search by name"           << std::endl;
        std::cout << "3.      Search by surname"         << std::endl;
        std::cout << "4.     Display all contacts"       << std::endl;
        std::cout << "5.      Change contact data"       << std::endl;
        std::cout << "6.       Delete contact"           << std::endl;
        std::cout << "7.       Change password"          << std::endl;
        std::cout << "8.           Log out"              << std::endl;
        std::cout << "9.        Exit program"            << std::endl;
        std::cout << "=================================" << std::endl;
        std::cout << ""                                  << std::endl;
    }
    else if (number == 3) {
        std::cout << "===CHOOSE OPTION TO MODIFY===" << std::endl;
        std::cout << " "                             << std::endl;
        std::cout << "==============MENU===========" << std::endl;
        std::cout << "1.           name"             << std::endl;
        std::cout << "2.         surname"            << std::endl;
        std::cout << "3.       phone number"         << std::endl;
        std::cout << "4.          e-mail"            << std::endl;
        std::cout << "5.         address"            << std::endl;
        std::cout << "6.       back to menu"         << std::endl;
        std::cout << "=============================" << std::endl;
        std::cout << ""                              << std::endl;
    }
}

void displayContact(const Contact& contact) {

    std::cout << ""                                        << std::endl;
    std::cout << "ID: "             << contact.id          << std::endl;
    std::cout << "name: "           << contact.name        << std::endl;
    std::cout << "surname: "        << contact.surname     << std::endl;
    std::cout << "e-mail: "         << contact.email       << std::endl;
    std::cout << "address: "        << contact.address     << std::endl;
    std::cout << "phone number: "   << contact.phoneNumber << std::endl;
}

void displayAllContacts(std::vector<Contact>& contacts) {

    system("cls");

    if(isFileEmpty(contacts)) {
        return;
    }
    else {

        for (const Contact& contact : contacts) {
            displayContact(contact);
        }

        system("pause");
        return;
    }
}

void readUsersFromFile(std::vector<User>& users) {

    std::fstream file;
    file.open("usersDatabase.txt", std::ios::in);

    std::string fileLine;
    char separator = '|';
    User loadedUser;

    while (getline(file, fileLine)) {
        if (!fileLine.empty()) {
            std::stringstream ss(fileLine);
            std::string word;

            int wordCounter = 1;

            while (!ss.eof()) {
                getline(ss, word, separator);
                switch (wordCounter) {
                case 1: loadedUser.id = std::stoi(word); break;
                case 2: loadedUser.login = word;         break;
                case 3: loadedUser.password = word;      break;
                }
                wordCounter++;
            }
            users.push_back(loadedUser);
        }
    }
    file.close();
}

int readContactsFromFile(std::vector<Contact>& contacts, int loggedInUserID) {

    std::fstream file;
    file.open("contactsDatabase.txt", std::ios::in);

    std::string fileLine, lastContctID;
    char separator = '|';
    int lastContactID;
    Contact loadedContact;

    while (getline(file, fileLine)) {
        if (!fileLine.empty()) {
            std::stringstream ss(fileLine);
            std::string word;
            getline(ss, word, separator);
            loadedContact.id = std::stoi(word);
            lastContactID = loadedContact.id;

            getline(ss, word, separator);

            if (loggedInUserID == std::stoi(word)) {
                int wordCounter = 3;
                while (!ss.eof()) {
                    getline(ss, word, separator);
                    switch (wordCounter) {
                    case 3: loadedContact.name = word;        break;
                    case 4: loadedContact.surname = word;     break;
                    case 5: loadedContact.email = word;       break;
                    case 6: loadedContact.address = word;     break;
                    case 7: loadedContact.phoneNumber = word; break;
                    }
                    wordCounter++;
                }
                contacts.push_back(loadedContact);
            }
        }
    }
    file.close();
    return lastContactID;
}

void saveUserToFile(const User &user) {

    std::fstream file;
    file.open("usersDatabase.txt", std::ios::out | std::ios::app);

    if (!file.is_open()) {
        std::cout << "Failed to open file" << std::endl;
        return;
    }
    file << user.id       << '|';
    file << user.login    << '|';
    file << user.password << '|' << std::endl;

    file.close();
}

void saveContactToFile(const Contact &contact, int loggedInUserID) {

    std::fstream file;
    file.open("contactsDatabase.txt", std::ios::out | std::ios::app);

    if (!file.is_open()) {
        std::cout << "Failed to open file" << std::endl;
        return;
    }
    file << contact.id          << '|';
    file << loggedInUserID      << '|';
    file << contact.name        << '|';
    file << contact.surname     << '|';
    file << contact.email       << '|';
    file << contact.address     << '|';
    file << contact.phoneNumber << '|' << std::endl;

    file.close();
}

int modifyContactFileAfterDelete(int id) {

    int lastContactID = 0;
    std::string line, field, oldFileName = "contactsDatabase.txt", tempFileName = "temp_contacts.txt";
    std::ifstream file(oldFileName);
    std::ofstream tempFile (tempFileName);

    while(getline(file, line)) {
        std::istringstream iss(line);

        getline(iss, field, '|');

        if (stoi(field) != id) {
            tempFile << line << std::endl;
            lastContactID = stoi(field);
        }
    }

    file.close();
    tempFile.close();

    handleFileSwap(oldFileName, tempFileName);

    std::cout << "Contact deleted succesfully." << std::endl;
    system("pause");

    return lastContactID;
}

void modifyContactFileAfterEdit(const Contact& contact, int loggedInUserID) {

    std::string line, field, oldFileName = "contactsDatabase.txt", tempFileName = "temp_contacts.txt";
    std::ifstream file(oldFileName);
    std::ofstream tempFile(tempFileName);
    int id = contact.id;

    while(getline(file, line)) {
        std::istringstream iss(line);

        getline(iss, field, '|');

        if (std::stoi(field) != id) {
            tempFile << line << std::endl;
        }
        else {
            tempFile << contact.id          << '|';
            tempFile << loggedInUserID      << '|';
            tempFile << contact.name        << '|';
            tempFile << contact.surname     << '|';
            tempFile << contact.email       << '|';
            tempFile << contact.address     << '|';
            tempFile << contact.phoneNumber << '|' << std::endl;
        }
    }

    file.close();
    tempFile.close();

    handleFileSwap(oldFileName, tempFileName);

    std::cout << "Contact edited succesfully." << std::endl;
    system("pause");
}

int registration(std::vector <User>& users) {

    int vectorSize = users.size();
    std::string login, password;

    User newUser;

    std::cout << "Enter your login: " ;
    login = readLine();
    int i = 0;

    while (i < vectorSize) {
        if (users[i].login == login) {
            std::cout << "This login has been already in use. Enter different user login: ";
            login = readLine();
            i = 0;
        }
        else {
            i++;
        }
    }
    std::cout << "Enter password: " ;
    password = readLine();


    if (users.empty()) {
        newUser.id = 1;
    }
    else {
        int newID = users.back().id + 1;
        newUser.id = newID;
    }

    newUser.login = login;
    newUser.password = password;
    newUser.id = vectorSize + 1;

    users.push_back(newUser);
    saveUserToFile(newUser);

    std::cout << "Account has been created..." << std::endl;
    Sleep(1000);
    return vectorSize + 1;
}

int loggingIn (std::vector <User>& users) {

    std::string login, password;
    int i = 0;
    int vectorSize = users.size();

    std::cout << "Enter login: ";
    login = readLine();

    while (i < vectorSize) {
        if (users[i].login == login) {
            for (int attempts = 0; attempts < 3; attempts++) {
                std::cout << "Enter password: ";
                password = readLine();
                if (users[i].password == password) {
                    std::cout << "You have been logged in." << std::endl;
                    Sleep(1000);
                    return users[i].id;
                }
            }
            std::cout << "You have typed wrong password 3 times. Wait 3sec. before next try..." << std::endl;
            Sleep(3000);
            return 0;

        }
        i++;
    }
    std::cout << "No Account with the following login exists" << std::endl;
    Sleep(3000);

    return 0;
}

int loggingOut (std::vector<Contact>& contacts, int loggedInUserID) {

    loggedInUserID = 0;
    std::cout << "You have been logged out :)";
    contacts.clear();
    Sleep(500);

    return loggedInUserID;
}

int addContact(std::vector<Contact>& contacts, int loggedInUserID, int lastContactID) {

    Contact newContact;

    std::cout << "Enter contact name: "         << std::endl;
    newContact.name = readLine();

    std::cout << "Enter contact surname: "      << std::endl;
    newContact.surname = readLine();

    std::cout << "Enter contact e-mail: "       << std::endl;
    newContact.email = readLine();

    std::cout << "Enter contact address: "      << std::endl;
    newContact.address = readLine();

    std::cout << "Write contact phone number: " << std::endl;
    newContact.phoneNumber = readLine();

    newContact.id = ++lastContactID;

    contacts.push_back(newContact);
    saveContactToFile(newContact, loggedInUserID);

    std::cout << std::endl << "Contact has been added" << std::endl;
    system("pause");

    return lastContactID;
}

int deleteContact(std::vector<Contact>& contacts, int lastContactID) {

    int id = 0;
    char option;
    std::string availableIDs = showAvailableIDs(contacts);

    if (contacts.empty()) {
        std::cout << "Contact Book empty." << std::endl;
        system("pause");
        return lastContactID;
    }

    std::cout << "Choose ID of contact to delete. Available IDs: " << availableIDs << std::endl;
    id = readInt();

    for (std::vector <Contact>::iterator itr = contacts.begin(); itr != contacts.end(); ++itr) {
        if(itr->id == id) {
            displayContact(*itr);

            std::cout << "Do you want to delete that contact? Press Y for YES or N for No." << std::endl;
            option = toupper(readChar());

            switch (option) {
            case 'Y':
                contacts.erase(itr);
                lastContactID = modifyContactFileAfterDelete(id);
                break;
            case 'N':
                std::cout << "Contact will NOT be deleted." << std::endl;
                break;
            default:
                std::cout << "Wrong character. You will be redirectered to main menu." << std::endl;
                break;
            }

            system("pause");
            return lastContactID;
        }
    }

    std::cout << "No such ID was found..." << std::endl;
    system("pause");
    return lastContactID;
}

void searchContactByName(std::vector<Contact>& contacts) {

    if(isFileEmpty(contacts)) {
        return;
    }
    else {
        std::string name;
        bool contactWithSpecifiedNameExist;

        if (contacts.empty()) {
            std::cout << "Contact book empty." << std::endl;
            system("pause");
            return;
        }

        std::cout << "Enter name of the contacts to be shown " << std::endl;
        name = readLine();

        for (const Contact& contact : contacts) {
            if (contact.name == name) {
                contactWithSpecifiedNameExist = true;
                displayContact(contact);
            }
        }

        if (!contactWithSpecifiedNameExist) {
            std::cout << std::endl << "No contact for given name exists"; << std::endl;
        }

        system("pause");
        return;
    }
}

void searchContactsBySurname(std::vector<Contact>& contacts) {

    if(isFileEmpty(contacts)) {
        return;
    }
    else {

        std::string surname;
        bool contactWithSpecifiedSurnameExist;

        std::cout << "Enter surname of the contacts to be shown" << std::endl;
        surname = readLine();

        for (const Contact& contact : contacts) {
            if (contact.surname == surname) {
                contactWithSpecifiedSurnameExist = true;
                displayContact(contact);
            }
        }

        if (!contactWithSpecifiedSurnameExist) {
            std::cout << std::endl << "No contact for given surname exists"; << std::endl;
        }

        system("pause");
        return;
    }
}

void passwordChange (int loggedInUserID, std::vector <User>& users) {

    std::string password;
    std::cout << "Enter password: ";
    int vectorSize = users.size();

    password = readLine();

    for ( int i = 0; i < vectorSize; i++) {
        if (users[i].id == loggedInUserID) {
            users[i].password = password;
            std::cout << "Password has been changed :)" << std::endl;
            Sleep(1500);
        }
    }
}

void editContactData(std::vector<Contact>& contacts, int loggedInUserID) {

    int id = 0;
    char choice;
    std::string availableIDs = showAvailableIDs(contacts);

    if (contacts.empty()) {
        std::cout << "Contact Book empty." << std::endl;
        system("pause");
        return;

    }

    std::cout << "Choose ID of contact to edit. Available IDs: " << availableIDs << std::endl;
    id = readInt();
    int position = 0;

    for (std::vector <Contact>::iterator itr = contacts.begin(); itr != contacts.end(); ++itr) {
        if(itr -> id == id) {
            while (true) {
                system("cls");
                menu(3);
                choice = readChar();

                switch (choice) {
                case '1':
                    system("cls");
                    std::cout << "Enter new name: " << std::endl;
                    contacts[position].name = readLine();
                    modifyContactFileAfterEdit(*itr, loggedInUserID);
                    std::cout << " " << std::endl;
                    std::cout << "Name has been changed... " << std::endl;
                    Sleep(1000);
                    break;

                case '2':
                    system("cls");
                    std::cout << "Enter new surname: " << std::endl;
                    contacts[position].surname = readLine();
                    modifyContactFileAfterEdit(*itr, loggedInUserID);
                    std::cout << " " << std::endl;
                    std::cout << "Surname has been changed... " << std::endl;
                    Sleep(1000);
                    break;

                case '3':
                    system("cls");
                    std::cout << "Enter new phone number " << std::endl;
                    contacts[position].phoneNumber = readLine();
                    modifyContactFileAfterEdit(*itr, loggedInUserID);
                    std::cout << " " << std::endl;
                    std::cout << "Phone number has been changed... " << std::endl;
                    Sleep(1000);
                    break;

                case '4':
                    system("cls");
                    std::cout << "Enter new email " << std::endl;
                    contacts[position].email = readLine();
                    modifyContactFileAfterEdit(*itr, loggedInUserID);
                    std::cout << " " << std::endl;
                    std::cout << "E-mail has been changed... " << std::endl;
                    Sleep(1000);
                    break;

                case '5':
                    system("cls");
                    std::cout << "Enter new address " << std::endl;
                    contacts[position].address = readLine();
                    modifyContactFileAfterEdit(*itr, loggedInUserID);
                    std::cout << " " << std::endl;
                    std::cout << "address has been changed... " << std::endl;
                    Sleep(1000);
                    break;
                case '6':
                    system("pause");
                    return;
                }
            }
        }
        position ++;
    }

    std::cout << "No such ID was found..." << std::endl;
    system("pause");
}

int main() {

    std::vector <User> users;
    std::vector<Contact> contacts;

    int loggedInUserID = 0, lastContactID = 0;
    char choice, secondChoice;

    readUsersFromFile(users);

    while(true) {
        if (loggedInUserID == 0) {
            system("cls");
            menu(1);
            choice = readChar();

            switch(choice) {
            case '1': registration(users);                                            break;
            case '2': loggedInUserID = loggingIn(users);
                      lastContactID = readContactsFromFile(contacts, loggedInUserID); break;
            case '9': exit(0);                                                        break;
            default:
                std::cout << "There is no such option. Try again." << std::endl;
                system("pause");
            }
        }

        else {
            while (loggedInUserID != 0) {

                system("cls");
                menu(2);
                secondChoice = readChar();

                switch (secondChoice) {
                case '1': lastContactID = addContact(contacts, loggedInUserID, lastContactID); break;
                case '2': searchContactByName(contacts);                                       break;
                case '3': searchContactsBySurname(contacts);                                   break;
                case '4': displayAllContacts(contacts);                                        break;
                case '5': editContactData(contacts, loggedInUserID);                           break;
                case '6': lastContactID = deleteContact(contacts, lastContactID);              break;
                case '7': passwordChange(loggedInUserID, users);                               break;
                case '8': loggedInUserID = loggingOut(contacts, loggedInUserID);               break;
                case '9': exit(0);                                                             break;
                default:
                    std::cout << "There is no such option. Try again." << std::endl;
                    system("pause");
                }
            }
        }
    }

    return 0;
}
