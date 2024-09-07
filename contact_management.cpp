#include<bits/stdc++.h>
#include<fstream>
using namespace std;

class temp {
    string phoneNo, Name, address, description, search;
    fstream file;

public:
    void addContact();
    void showAll();
    void searchContact();
    void deleteContact();
} obj;

int main() {
    char choice;
    do {
        cout << "1---> Add Contact" << endl;
        cout << "2---> Show All Contacts" << endl;
        cout << "3---> Search Contact" << endl;
        cout << "4---> Delete Contact" << endl;
        cout << "0---> Exit" << endl;
        cin >> choice;
        cin.ignore();  

        switch (choice) {
            case '1':
                obj.addContact();
                break;
            case '2':
                obj.showAll();
                break;
            case '3':
                obj.searchContact();
                break;
            case '4':
                obj.deleteContact();
                break;
            case '0':
                return 0;
            default:
                cout << "Invalid Selection...!" << endl;
                break;
        }
    } while (choice != '0');
    
    return 0;
}

void temp::addContact() {
    cout << "Enter Phone Number :: ";
    getline(cin, phoneNo);
    cout << "Enter Name :: ";
    getline(cin, Name);
    cout << "Enter Address :: ";
    getline(cin, address);
    cout << "Enter Description :: ";
    getline(cin, description);

    file.open("data.csv", ios::out | ios::app);
    file << phoneNo << "," << Name << "," << address << "," << description << "\n";
    file.close();
}

void temp::showAll() {
    file.open("data.csv", ios::in);
    if (!file) {
        cout << "No contacts found!" << endl;
        return;
    }
    
    while (file.good()) {
        getline(file, phoneNo, ',');
        getline(file, Name, ',');
        getline(file, address, ',');
        getline(file, description, '\n');

        if (!phoneNo.empty()) {
            cout << "Phone Number :: " << phoneNo << endl;
            cout << "Name         :: " << Name << endl;
            cout << "Address      :: " << address << endl;
            cout << "Description  :: " << description << endl << endl;
        }
    }
    file.close();
}

void temp::searchContact() {
    cout << "Enter Phone Number to search :: ";
    getline(cin, search);

    file.open("data.csv", ios::in);
    if (!file) {
        cout << "No contacts found!" << endl;
        return;
    }
    
    bool found = false;
    while (file.good()) {
        getline(file, phoneNo, ',');
        getline(file, Name, ',');
        getline(file, address, ',');
        getline(file, description, '\n');

        if (phoneNo == search) {
            cout << "Phone Number :: " << phoneNo << endl;
            cout << "Name         :: " << Name << endl;
            cout << "Address      :: " << address << endl;
            cout << "Description  :: " << description << endl << endl;
            found = true;
            break; 
        }
    }

    if (!found) {
        cout << "Contact not found!" << endl;
    }

    file.close();
}

void temp::deleteContact() {
    cout << "Enter Phone Number to delete :: ";
    getline(cin, search);

    file.open("data.csv", ios::in);
    if (!file) {
        cout << "No contacts found!" << endl;
        return;
    }

    fstream tempFile;
    tempFile.open("temp.csv", ios::out); 

    bool found = false;
    while (file.good()) {
        getline(file, phoneNo, ',');
        getline(file, Name, ',');
        getline(file, address, ',');
        getline(file, description, '\n');

        if (phoneNo == search) {
            found = true;
            cout << "Deleting contact with Phone Number: " << phoneNo << endl;
        } else if (!phoneNo.empty()) {
            tempFile << phoneNo << "," << Name << "," << address << "," << description << "\n";
        }
    }

    file.close();
    tempFile.close();

    if (found) {
        remove("data.csv");
        rename("temp.csv", "data.csv");
        cout << "Contact deleted successfully!" << endl;
    } else {
        cout << "Contact not found!" << endl;
        remove("temp.csv");
    }
}
