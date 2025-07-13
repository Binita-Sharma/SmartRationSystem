#include <iostream>
#include <string>
#include <fstream> // For file operations
#include "admin.h" // Include the header file for admin functions
#include "user.h" // Include the header file for user functions
#include "ration.h" // Include the header file for ration functions
using namespace std;

// Main function
// This is the entry point of the program
int main()
{

    string username, password, role;

    // displaying project title
    cout << " smart ration distribution system\n";
    cout << "-------------------------------\n";

    // asking username for their role
    cout << "login as (admin/user): ";
    cin >> role;

    // take user name and and password
    cout << "enter username: ";
    cin >> username;
    cout << "enter password: ";
    cin >> password;

    // check call respective menu and credentials

    if (role == "admin" && username == "admin" && password == "admin123")
    {
        adminMenu(); // Admin menu
    }
    else if (role == "user" && username == "user" && password == "user123")
    {
        userMenu(); // User menu
    }
    else
    {
        // invalid login message
        cout << "Invalid credentials or role. Please try again.\n";
    }
    return 0; // end of main function
}
