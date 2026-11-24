#include "SIGNArray.h"
#include "TextProcessor.h"

#include <iostream>
#include <limits>
#include <stdexcept>
#include <string>

using namespace std;

void printMenu() {
    cout << "\n=== Menu ===\n";
    cout << "1. Add record to the end\n";
    cout << "2. Insert record at position\n";
    cout << "3. Delete record by index\n";
    cout << "4. Edit record by index\n";
    cout << "5. Print all records\n";
    cout << "6. Sort by birth date\n";
    cout << "7. Search by surname\n";
    cout << "8. Task 2: longest word in file\n";
    cout << "0. Exit\n";
}

int readInt(const string& prompt) {
    int x;
    cout << prompt;
    if (!(cin >> x)) {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        throw runtime_error("Invalid number input");
    }
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    return x;
}

int main() {
    SIGNArray arr;

    while (true) {
        try {
            printMenu();
            int choice = readInt("Choice: ");

            switch (choice) {
            case 1: {
                cout << "Enter: Surname Name Zodiac DD MM YYYY\n";
                SIGN s;
                cin >> s;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                arr.add(s);
                cout << "Added.\n";
                break;
            }
            case 2: {
                int pos = readInt("Insert position (0.." + to_string(arr.getSize()) + "): ");
                cout << "Enter: Surname Name Zodiac DD MM YYYY\n";
                SIGN s;
                cin >> s;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                arr.insertAt(pos, s);
                cout << "Inserted.\n";
                break;
            }
            case 3: {
                int idx = readInt("Index to delete: ");
                arr.removeAt(idx);
                cout << "Deleted.\n";
                break;
            }
            case 4: {
                int idx = readInt("Index to edit: ");
                cout << "Enter new data: Surname Name Zodiac DD MM YYYY\n";
                SIGN s;
                cin >> s;
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                arr.editAt(idx, s);
                cout << "Edited.\n";
                break;
            }
            case 5:
                arr.printAll(cout);
                break;
            case 6:
                arr.sortByBirthDate();
                cout << "Sorted by birth date.\n";
                break;
            case 7: {
                string surname;
                cout << "Enter surname: ";
                getline(cin, surname);

                int idx = arr.findBySurname(surname.c_str());
                if (idx == -1) {
                    cout << "Person with this surname not found.\n";
                }
                else {
                    cout << "Found: " << arr.at(idx) << "\n";
                }
                break;
            }
            case 8: {
                string filename;
                cout << "Enter filename: ";
                getline(cin, filename);
                TextProcessor::processFile(filename);
                break;
            }
            case 0:
                cout << "Exit.\n";
                return 0;
            default:
                cout << "No such menu item.\n";
                break;
            }
        }
        catch (const exception& e) {
            cout << "Exception: " << e.what() << "\n";
            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
            }
        }
    }

    return 0;
}