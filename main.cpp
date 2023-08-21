#include <iostream>
#include <windows.h>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <conio.h>

struct Contact {

    int id;
    std::string name, surname, email, address, phoneNumber;
};

void displayContact(const Contact& contact) {

    std::cout << ""                                        << std::endl;
    std::cout << "ID: "             << contact.id          << std::endl;
    std::cout << "name: "           << contact.name        << std::endl;
    std::cout << "surname: "        << contact.surname     << std::endl;
    std::cout << "e-mail: "         << contact.email       << std::endl;
    std::cout << "address: "        << contact.address     << std::endl;
    std::cout << "phone number: "   << contact.phoneNumber << std::endl;
}

void saveToFile(std::vector<Contact>& contacts, int positionInVector) {

    std::fstream file;
    file.open("contactsDatabase.txt", std::ios::out | std::ios::app);

    file << contacts[positionInVector].id          << '|';
    file << contacts[positionInVector].name        << '|';
    file << contacts[positionInVector].surname     << '|';
    file << contacts[positionInVector].email       << '|';
    file << contacts[positionInVector].address     << '|';
    file << contacts[positionInVector].phoneNumber << '|' << std::endl;

    file.close();
}

void readDataFromFile(std::vector<Contact>& contacts) {

    std::fstream file;
    file.open("contactsDatabase.txt", std::ios::in);

    std::string fileLine;
    char separator = '|';
    Contact loadedContact;

    while (getline(file, fileLine)) {
        if (!fileLine.empty()) {
            std::stringstream ss(fileLine);
            std::string word;
            int wordCounter = 1;
            while (!ss.eof()) {
                getline(ss, word, separator);
                switch (wordCounter) {
                case 1: loadedContact.id = std::stoi(word); break;
                case 2: loadedContact.name = word;          break;
                case 3: loadedContact.surname = word;       break;
                case 4: loadedContact.email = word;         break;
                case 5: loadedContact.address = word;       break;
                case 6: loadedContact.phoneNumber = word;   break;
                }
                wordCounter++;
            }
            contacts.push_back(loadedContact);
        }
    }
    file.close();
}

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

void addContact(std::vector<Contact>& contacts) {

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
    saveToFile(contacts, vectorSize);

    std::cout << std::endl << "Contact added" << std::endl;
    Sleep(1500);
}

void searchByName(std::vector<Contact>& contacts) {

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

        std::cout << "Enter name of the contacts to be showed " << std::endl;
        name = readLine();

        for (const Contact& contact : contacts) {
            if (contact.name == name) {
                contactWithSpecifiedNameExist = true;
                displayContact(contact);
            }
        }

        if (!contactWithSpecifiedNameExist) {
            std::cout << std::endl << "No contacts for given name exist";
        }

        system("pause");
        return;
    }
}

void searchBySurname(std::vector<Contact>& contacts) {

    if(isFileEmpty(contacts)){
        return;
    }
    else {

        std::string surname;
        bool contactWithSpecifiedSurnameExist;

        std::cout << "Enter surname of the contacts to be showed" << std::endl;
        surname = readLine();

        for (const Contact& contact : contacts) {
            if (contact.surname == surname) {
                contactWithSpecifiedSurnameExist = true;
                displayContact(contact);
            }
        }

        if (!contactWithSpecifiedSurnameExist) {
            std::cout << std::endl << "No contacts for given surname exist";
        }

        system("pause");
        return;
    }
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

void overwriteModifiedTextFile(std::vector<Contact>& contacts) {

    std::ofstream file;
    file.open("contactsDatabase.txt", std::ios::out | std::ofstream::trunc);

    for (const Contact& contact : contacts) {
        file << contact.id          << '|';
        file << contact.name        << '|';
        file << contact.surname     << '|';
        file << contact.email       << '|';
        file << contact.address     << '|';
        file << contact.phoneNumber << '|' << std::endl;
    }
    file.close();
}

void deleteContact(std::vector<Contact>& contacts) {

    if(isFileEmpty(contacts)){
        return;
    }
    else {

        int input;

        system("cls");
        std::cout << "Enter ID of contact to be removed:" << std::endl;
        std::cin >> input;

        if (input > contacts.size() + 1 || input <= 0) {
            std::cout << "Contact with the following ID doesn't exist..." << std::endl;
            Sleep(1000);
            system("pause");
            return;
        }

        input -= 1;

        char choice;
        std::cout << "Press \"t\" to confirm deletion or \"n\" key to abort " << std::endl;

        while(true) {

          choice = getch();

          if(choice == 't' || choice == 'T') {
            contacts.erase(contacts.begin() + input);
            overwriteModifiedTextFile(contacts);
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

void editContactData(std::vector<Contact>& contacts) {

    if(isFileEmpty(contacts)){
        return;
    }
    else {

        int input;
        char choice;

        system("cls");
        std::cout << "Enter ID of contact to be edited: " << std::endl;
        std::cin >> input;
        input -= 1;

        if (input > contacts.size() + 1 || input <= 0) {
            std::cout << "Contact with the following ID doesn't exist..." << std::endl;
            Sleep(1000);
            system("pause");
            return;
        }

        std::cin.ignore();
        while (true) {
            system("cls");
            std::cout << " CHOOSE OPTION TO MODIFY: " << std::endl;
            std::cout << " "                          << std::endl;
            std::cout << "1.        name"             << std::endl;
            std::cout << "2.      surname"            << std::endl;
            std::cout << "3.    phone number"         << std::endl;
            std::cout << "4.       e-mail"            << std::endl;
            std::cout << "5.       address"           << std::endl;
            std::cout << "6.    back to menu"         << std::endl;
            std::cout << ""                           << std::endl;
            choice = getch();

            switch (choice) {
            case '1':
                system("cls");
                std::cout << "Enter new name: " << std::endl;
                contacts[input].name = readLine();
                overwriteModifiedTextFile(contacts);
                std::cout << " " << std::endl;
                std::cout << "Name has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '2':
                system("cls");
                std::cout << "Enter new surname: " << std::endl;
                contacts[input].surname = readLine();
                overwriteModifiedTextFile(contacts);
                std::cout << " " << std::endl;
                std::cout << "Surname has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '3':
                system("cls");
                std::cout << "Enter new phone number " << std::endl;
                contacts[input].phoneNumber = readLine();
                overwriteModifiedTextFile(contacts);
                std::cout << " " << std::endl;
                std::cout << "Phone number has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '4':
                system("cls");
                std::cout << "Enter new email " << std::endl;
                contacts[input].email = readLine();
                overwriteModifiedTextFile(contacts);
                std::cout << " " << std::endl;
                std::cout << "E-mail has been changed... " << std::endl;
                Sleep(1000);
                break;

            case '5':
                system("cls");
                std::cout << "Enter new address " << std::endl;
                contacts[input].address = readLine();
                overwriteModifiedTextFile(contacts);
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

    std::vector<Contact> contacts;
    char choice;

    readDataFromFile(contacts);

    while (true) {
        system("cls");
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
        std::cout << "9.        Exit program"            << std::endl;
        std::cout << "=================================" << std::endl;

        choice = getch();

        switch (choice) {
        case '1': addContact(contacts);         break;
        case '2': searchByName(contacts);       break;
        case '3': searchBySurname(contacts);    break;
        case '4': displayAllContacts(contacts); break;
        case '5': editContactData(contacts);    break;
        case '6': deleteContact(contacts);      break;
        case '9': exit(0);                      break;
        }
    }
    return 0;
}
