#include <iostream>
#include <string>
using namespace std;

//function declaration (defined later in the code)
void adminMenu();
void userMenu();

int main(){
    string username, password, role;

    //displaying project title
    cout<< " smart ration distribution system\n";
    cout<< "-------------------------------\n";

    //asking username for their role
    cout << "login as (admin/user): ";
    cin >> role;

    // take user name and and password
    cout << "enter username: ";
    cin >> username;
    cout << "enter password: ";
    cin >> password;

    // check call respective menu and credentials 

    if(role == "admin" && username == "admin" && password == "admin123") {
        adminMenu(); // Admin menu
    } else if(role == "user" && username == "user" && password == "user123") {
        userMenu(); // User menu
    } else {
        //invalid login message
        cout << "Invalid credentials or role. Please try again.\n";
    }
    return 0; // end of main function
}


// ------------------------------
// ADMIN MENU FUNCTION
// ------------------------------
void adminMenu() {
    cout << "Welcome to the Admin Menu!\n";

    //Display admin options
    cout << "1. Add Beneficiary\n";
    cout << "2. view Ration stock(coming soon)\n";
    cout << "4. Exit\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    // Handle admin choices
    switch(choice) {
        case 1:

        //placeholder for adding beneficiary functionality
            cout << "Adding Beneficiary will be implemented next\n";
            break;
        case 2:
            //placeholder for viewing ration stock functionality
            cout << "Viewing Ration stock wiil be implemented later\n";
            break;
        case 4:

        // Exit the admin menu
            cout << "Exiting Admin Menu.\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
    }
}

// ------------------------------
// USER MENU FUNCTION
// ------------------------------
void userMenu(){
    cout << "Welcome to the User Menu!\n";

    //Display user options
    cout << "1. View Ration History (coming soon)\n";
    cout << "2. View Entitlement (coming soon)\n";

}