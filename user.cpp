#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "user.h"
#include "ration.h" // Include the header file for ration functions
#include "admin.h" // Include the header file for admin functions
using namespace std;

// ------------------------------
// USER MENU FUNCTION
// ------------------------------
void userMenu()
{
string userId;
    cout << "\nWelcome User!\n";
    cout << "Enter your User ID to continue (e.g., U001): ";
    cin >> userId;

    int choice;
    do {
        cout << "\nUser Menu:\n";
        cout << "1. View My Ration History\n";
        cout << "2. Check My Latest Ration Status\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

  switch (choice) {
            case 1: {
                ifstream logFile("database/log.txt");
                string line;
                bool found = false;
                while (getline(logFile, line)) {
                    if (line.find(userId) != string::npos) {
                        cout << line << endl;
                        found = true;
                    }
                }
                if (!found) cout << " No history found.\n";
                break;
            }
            case 2: {
                ifstream userFile("database/user.txt");
                string line;
                while (getline(userFile, line)) {
                    if (line.find(userId) != string::npos) {
                        stringstream ss(line);
                        string id, name, fam, income, month;
                        getline(ss, id, ',');
                        getline(ss, name, ',');
                        getline(ss, fam, ',');
                        getline(ss, income, ',');
                        getline(ss, month, ',');
                        cout << "Name: " << name << "\nFamily: " << fam << "\nIncome: ₹" << income << "\nLast Month: " << month << endl;
                        break;
                    }
                }
                break;
            }
            case 3: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 3);
}