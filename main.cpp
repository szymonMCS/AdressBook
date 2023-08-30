#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

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

bool isFileEmpty (std::vector<Contact>& contacts) {

    if (contacts.empty()) {
        std::cout << "Contact book empty." << std::endl;
        system("pause");
        return true;
    }
}

bool isContactWithSpecifiedIDExists (std::vector<Contact>& contacts) {

    bool flagContactExist;
    int input, position;

    std::cin >> input;

    for (int i = 0; i < contacts.size(); i++) {
        if (contacts[i].id == input) {
        flagContactExist = true;
        position = i;
        break;
        }
    }

    if (!flagContactExist) {
        std::cout << "Contact with the following ID doesn't exist..." << std::endl;
    }

    return flagContactExist;
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
        std::cout << "6.      back to menu"          << std::endl;
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
    if(isFileEmpty(contacts)){
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

int readUsersFromFile(std::vector<User>& users, int usersAmount) {

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
                case 1: loadedUser.id = std::stoi(word);  break;
                case 2: loadedUser.login = word;          break;
                case 3: loadedUser.password = word;       break;
                }
                wordCounter++;
            }
            users.push_back(loadedUser);
            usersAmount ++;
        }
    }
    file.close();

    return usersAmount;
}

void readContactsFromFile(std::vector<Contact>& contacts, int loggedInUserID) {

    std::fstream file;
    file.open("contactsDatabase.txt", std::ios::in);

    std::string fileLine;
    char separator = '|';
    Contact loadedContact;

    while (getline(file, fileLine)) {
        if (!fileLine.empty()) {
            std::stringstream ss(fileLine);
            std::string word;
            ss.seekg(2, std::ios::beg);
            getline(ss, word, separator);

            if (loggedInUserID == std::stoi(word)){
                ss.seekg(0, std::ios::beg);
                word = "";
                int wordCounter = 1;
                while (!ss.eof()) {
                    getline(ss, word, separator);
                    switch (wordCounter) {
                    case 1: loadedContact.id = std::stoi(word); break;
                    case 3: loadedContact.name = word;          break;
                    case 4: loadedContact.surname = word;       break;
                    case 5: loadedContact.email = word;         break;
                    case 6: loadedContact.address = word;       break;
                    case 7: loadedContact.phoneNumber = word;   break;
                    }
                    wordCounter++;
                }
                contacts.push_back(loadedContact);
            }
        }
    }
    file.close();
}

void saveUserToFile(std::vector<User>& users, int positionInVector) {

    std::fstream file;
    file.open("usersDatabase.txt", std::ios::out | std::ios::app);

    file << users[positionInVector].id       << '|';
    file << users[positionInVector].login    << '|';
    file << users[positionInVector].password << '|' << std::endl;

    file.close();
}

void saveContactToFile(std::vector<Contact>& contacts, int positionInVector, int loggedInUserID) {

    std::fstream file;
    file.open("contactsDatabase.txt", std::ios::out | std::ios::app);

    file << contacts[positionInVector].id          << '|';
    file << loggedInUserID                         << '|';
    file << contacts[positionInVector].name        << '|';
    file << contacts[positionInVector].surname     << '|';
    file << contacts[positionInVector].email       << '|';
    file << contacts[positionInVector].address     << '|';
    file << contacts[positionInVector].phoneNumber << '|' << std::endl;

    file.close();
}

void overwriteModifiedTextFile(std::vector<Contact>& contacts, int loggedInUserID, int deletedID) {

    std::fstream baseFile ("contactsDatabase.txt", std::ios::in);
    std::fstream temporaryFile ("temporaryContactsDatabase.txt", std::ios::out | std::ofstream::app);

    std::string textLine;
    int contactsCounter = 0;
    char separator = '|';

    while(getline(baseFile, textLine)) {
        if (!textLine.empty()) {
            std::stringstream ss(textLine);
            std::string idFromFile;
            getline(ss, idFromFile, separator);

            if (deletedID == std::stoi(idFromFile)) {
                continue;
            }
            else if ((contacts.size() >= contactsCounter) && (contacts[contactsCounter].id == std::stoi(idFromFile))){
                temporaryFile << contacts[contactsCounter].id          << '|';
                temporaryFile << loggedInUserID                        << '|';
                temporaryFile << contacts[contactsCounter].name        << '|';
                temporaryFile << contacts[contactsCounter].surname     << '|';
                temporaryFile << contacts[contactsCounter].email       << '|';
                temporaryFile << contacts[contactsCounter].address     << '|';
                temporaryFile << contacts[contactsCounter].phoneNumber << '|' << std::endl;
                contactsCounter ++;
            }
            else {
                temporaryFile << textLine << std::endl;
            }
        }
    }
    baseFile.close();
    std::remove("contactsDatabase.txt");

    temporaryFile.close();
    std::rename("temporaryContactsDatabase.txt", "contactsDatabase.txt");
}

int registration(std::vector <User>& users, int usersAmount) {

    int vectorSize = users.size();
    std::string login, password;

    User newUser;

    std::cout << "Enter your login: " ;
    login = readLine();
    int i = 0;

    while (i < usersAmount)
    {
       if (users[i].login == login)
       {
           std::cout << "This login has been already in use. Enter different user login: ";
           std::cin >> login;
           i = 0;
       }
       else
       {
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
    newUser.id = usersAmount+1;

    users.push_back(newUser);
    saveUserToFile(users, vectorSize);

    std::cout << "Account has been created..." << std::endl;
    Sleep(1000);
    return usersAmount+1;
}

int loggingIn (std::vector <User>& users, int usersAmount) {

    std::string login, password;
    int i = 0;

    std::cout << "Enter login: ";
    login = readLine();

    while (i < usersAmount)
    {
       if (users[i].login == login)
       {
           for (int attempts = 0; attempts < 3; attempts++)
           {
                std::cout << "Enter password: ";
                std::cin >> password;
                if (users[i].password == password)
                {
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

void addContact(std::vector<Contact>& contacts, int loggedInUserID) {

    int vectorSize = contacts.size();
    std::string name, surname, email, address, phoneNumber;

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

    if (contacts.empty()) {
     newContact.id = 1;
    }
    else {
        int newID = contacts.back().id + 1;
        newContact.id = newID;
    }

    contacts.push_back(newContact);
    saveContactToFile(contacts, vectorSize, loggedInUserID);

    std::cout << std::endl << "Contact has been added" << std::endl;
    Sleep(1500);
}

void deleteContact(std::vector<Contact>& contacts, int loggedInUserID) {

    if(isFileEmpty(contacts)){
        return;
    }
    else {

        bool flagContactExist;
        int input,position;
        char choice;

        system("cls");
        std::cout << "Enter ID of contact to be removed:" << std::endl;

        if (!isContactWithSpecifiedIDExists(contacts)) {
            Sleep(1000);
            system("pause");
            return;
        }

        std::cout << "Press \"t\" to confirm deletion or \"n\" key to abort " << std::endl;

        while(true) {

          choice = getch();

          if(choice == 't' || choice == 'T') {
            contacts.erase(contacts.begin() + position);
            overwriteModifiedTextFile(contacts, loggedInUserID, input);
            std::cout << " " << std::endl;
            std::cout << "Contact has been deleted... " << std::endl;
            Sleep(1000);
            break;
          } if(choice == 'n' || choice == 'N'){
              std::cout << "Action aborted..." << std::endl;
              Sleep(1000);
              break;
          } else {
              std::cout << "Invalid choice, try again" << std::endl;
              Sleep(1000);
          }
        }
    }
}

void searchContactByName(std::vector<Contact>& contacts) {

    if(isFileEmpty(contacts)){
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
            std::cout << std::endl << "No contact for given name exists";
        }

        system("pause");
        return;
    }
}

void searchContactsBySurname(std::vector<Contact>& contacts) {

    if(isFileEmpty(contacts)){
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
            std::cout << std::endl << "No contact for given surname exists";
        }

        system("pause");
        return;
    }
}

void passwordChange (int loggedInUserID, std::vector <User>& users, int usersAmount) {
    std::string password;
    std::cout << "Enter password: ";
    std::cin >> password;
    for ( int i = 0; i < usersAmount; i++)
    {
        if (users[i].id == loggedInUserID)
        {
            users[i].password = password;
            std::cout << "Password has been changed :)" << std::endl;
            Sleep(1500);
        }
    }
}

void editContactData(std::vector<Contact>& contacts, int loggedInUserID) {

    int nothingDeleted = -1;

    if(isFileEmpty(contacts)){
        return;
    }
    else {

        bool flagContactExist;
        int input, position;
        char choice;

        system("cls");
        std::cout << "Enter ID of contact to be edited: " << std::endl;

        if (!isContactWithSpecifiedIDExists(contacts)) {
            Sleep(1000);
            system("pause");
            return;
        }

        std::cin.ignore();
        while (true) {
            system("cls");
            menu(3);
            choice = getch();

            switch (choice) {
            case '1':
                system("cls");
                std::cout << "Enter new name: " << std::endl;
                contacts[position].name = readLine();
                overwriteModifiedTextFile(contacts, loggedInUserID, nothingDeleted);
                std::cout << " " << std::endl;
                std::cout << "Name has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '2':
                system("cls");
                std::cout << "Enter new surname: " << std::endl;
                contacts[position].surname = readLine();
                overwriteModifiedTextFile(contacts, loggedInUserID, nothingDeleted);
                std::cout << " " << std::endl;
                std::cout << "Surname has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '3':
                system("cls");
                std::cout << "Enter new phone number " << std::endl;
                contacts[position].phoneNumber = readLine();
                overwriteModifiedTextFile(contacts, loggedInUserID, nothingDeleted);
                std::cout << " " << std::endl;
                std::cout << "Phone number has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '4':
                system("cls");
                std::cout << "Enter new email " << std::endl;
                contacts[position].email = readLine();
                overwriteModifiedTextFile(contacts, loggedInUserID, nothingDeleted);
                std::cout << " " << std::endl;
                std::cout << "E-mail has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '5':
                system("cls");
                std::cout << "Enter new address " << std::endl;
                contacts[position].address = readLine();
                overwriteModifiedTextFile(contacts, loggedInUserID, nothingDeleted);
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
}

int main() {
    std::vector <User> users;
    std::vector<Contact> contacts;

    int loggedInUserID = 0;
    int usersAmount = 0;
    char choice,secondChoice;

    usersAmount = readUsersFromFile(users,usersAmount);

    while(true)
    {
        if (loggedInUserID == 0)
        {
            system("cls");
            menu(1);
            choice = getch();

            switch(choice) {
            case '1': usersAmount = registration(users,usersAmount);  break;
            case '2': loggedInUserID = loggingIn(users, usersAmount); break;
            case '9': exit(0);                                        break;
            }
        }
        else
        {
            readContactsFromFile(contacts, loggedInUserID);

            while (loggedInUserID != 0) {

                system("cls");
                menu(2);
                secondChoice = getch();

                switch (secondChoice) {
                case '1': addContact(contacts, loggedInUserID);                  break;
                case '2': searchContactByName(contacts);                         break;
                case '3': searchContactsBySurname(contacts);                     break;
                case '4': displayAllContacts(contacts);                          break;
                case '5': editContactData(contacts, loggedInUserID);             break;
                case '6': deleteContact(contacts, loggedInUserID);               break;
                case '7': passwordChange(loggedInUserID, users, usersAmount);    break;
                case '8': loggedInUserID = loggingOut(contacts, loggedInUserID); break;
                case '9': exit(0);                                               break;
                }
            }
        }
    }

    return 0;
}
