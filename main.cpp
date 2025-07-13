#include <iostream>
#include <string>
#include <fstream> // For file operations

#include <sstream> // For string stream operations
#include <ctime>   // For time-related functions
using namespace std;

// function declaration (defined later in the code)
void adminMenu();
void userMenu();

// ------------------------------
string getCurrentDate()
{
    time_t now = time(0);      // Get current time
    tm *ltm = localtime(&now); // Convert to local time structure
    string months[] = {"January", "February", "March", "April", "May", "June",
                       "July", "August", "September", "October", "November", "December"};

    return months[ltm->tm_mon]; //+ " " + to_string(ltm->tm_mday) + ", " + to_string(1900 + ltm->tm_year);
}

// ------------------------------

// Function to add a beneficiary
// This function will prompt the user for beneficiary details and save them to a file
void addBeneficiary()
{

    ofstream outFile("database/user.txt", ios::app); // Open file in append mode
    if (!outFile)
    {
        cout << "Error opening file for writing.\n";
        return;
    }
    string id, name;
    int familySize, income;

    cout << "Enter Beneficiary ID (e.g., U001): ";
    cin >> id;

    cout << "Enter Beneficiary Name: ";
    cin.ignore();       // Clear the newline character from the input buffer
    getline(cin, name); // Use getline to allow spaces in the name

    cout << "Enter Family Size: ";
    cin >> familySize;

    cout << "Enter Monthly Income: ";
    cin >> income;

    outFile << id << "," << name << "," << familySize << "," << income << endl; // Write data to file
    outFile.close();                                                            // Close the file
    cout << "Beneficiary added successfully!\n";
}

// Function to view beneficiaries
// This function will read the beneficiaries from the file and display them
// It assumes the file is structured with each line containing ID, Name, Family Size, Income, and Last Month's Entitlement
// separated by commas.
void viewBeneficiaries()
{
    ifstream inFile("database/user.txt"); // Open file for reading
    if (!inFile)
    {
        cout << "Error opening file for reading.\n";
        return;
    }

    cout << "\n📋 List of Registered Beneficiaries:\n";
    cout << "---------------------------------------------------------\n";
    cout << "ID\tName\t\tFamily\tIncome\tLast Month\n";
    cout << "---------------------------------------------------------\n";

    string id, name, line;
    int familySize, income;
    string lastMonth;

    while (getline(inFile, line))
    {
        // Split the line by comma
        size_t pos = 0;
        int field = 0;
        string temp = "";
        string fields[5]; // Array to hold the fields , ID, Name, Family Size, Income, Last Month

        for (char c : line)
        {
            if (c == ',')
            {
                fields[field++] = temp; // Store the field in the array
                temp = "";              // Reset temp for the next field
            }
            else
            {
                temp += c; // Append character to temp
            }
        }

        fields[field] = temp; // Store the last field

        // output the fields
        cout << fields[0] << "\t"
             << fields[1] << "\t"
             << fields[2] << "\t"
             << fields[3] << "\t"
             << fields[4] << endl;
    }

    cout << "---------------------------------\n";
    cout << "Beneficiaries listed successfully!\n";
    inFile.close(); // Close the file
}

void allocateRation()
{
    ifstream inFile("database/user.txt");           // Open file for reading
    ofstream tempFile("database/temp.txt");         // Temporary file for writing
    ofstream logFile("database/log.txt", ios::app); // Log file for ration allocation

    if (!inFile || !tempFile || !logFile)
    {
        cout << "Error opening file for reading or writing.\n";
        return;
    }

    string currentMonth = getCurrentDate(); // Get the current month
    string line;

    cout << "\n📦 Allocating Ration for " << currentMonth << ":\n";

    while (getline(inFile, line))
    {
        stringstream ss(line);
        string id, name, familySizeStr, incomeStr, lastMonth;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, familySizeStr, ',');
        getline(ss, incomeStr, ',');
        getline(ss, lastMonth, ',');

        int family = stoi(familySizeStr);
        int income = stoi(incomeStr);

        // Check if the ration is already allocated for the current month
        if (lastMonth == currentMonth)
        {
            cout << "Ration already allocated for" << id << "(" << name << ").\n";
            tempFile << id << "," << name << "," << familySizeStr << "," << incomeStr << "," << lastMonth << endl;
            continue; // Skip to the next beneficiary
        }

        // calculate ration based on family size and income
        int rice = (income < 10000) ? family * 5 : family * 3;  // 5 kg per person if income < 10,000, else 3 kg
        int wheat = (income < 10000) ? family * 2 : family * 1; // 2 kg per person if income < 10,000, else 1 kg
        int sugar = (income < 10000) ? family * 1 : family * 0; // 1 kg per person if income < 10,000, else no sugar
        int oil = (income < 10000) ? family * 1 : family * 0;   // 1 liter per person if income < 10,000, else no oil

        cout << "Allocating for " << id << " (" << name << ") gets " << "Rice: " << rice << " kg, Wheat: " << wheat << " kg, Sugar: " << sugar << " kg, Oil: " << oil << " liters\n";

        // write the updated lastmonth and ration details to the temporary file
        tempFile << id << "," << name << "," << family << "," << income << "," << currentMonth << endl;

        // log the transaction
        logFile << "[" << currentMonth << "] " << id << " (" << name << "): " << "received ration - "
                << "Rice: " << rice << " kg, Wheat: " << wheat << " kg, Sugar: " << sugar << " kg, Oil: " << oil << " liters\n";
    }

    // Close all files
    inFile.close();
    tempFile.close();
    logFile.close();

    // Replace the original file with the temporary file
    remove("database/user.txt");
    rename("database/temp.txt", "database/user.txt");

    cout << "Ration allocation completed for " << currentMonth << ".\n";
}

void viewRationHistory()
{
    ifstream logFile("database/log.txt"); // Open the log file for reading
    if (!logFile)
    {
        cout << "Error opening log file for reading.\n";
        return;
    }

    cout << "\n📜 Ration Allocation History:\n";
    cout << "---------------------------------\n";

    string line;
    while (getline(logFile, line))
    {
        cout << line << endl; // Print each line from the log file
    }
    cout << "---------------------------------\n";

    logFile.close(); // Close the log file
}

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

// ------------------------------
// ADMIN MENU FUNCTION
// ------------------------------
void adminMenu()
{
    cout << "Welcome to the Admin Menu!\n";

    // Display admin options
    cout << "1. Add Beneficiary\n";
    cout << "2. View Beneficiaries\n";
    cout << "3. Allocate Ration\n";
    cout << "4. View Ration Logs\n";
    cout << "5. Exit\n";

    int choice;
    cout << "Enter your choice: ";
    cin >> choice;

    // Handle admin choices
    switch (choice)
    {
    case 1:

        // placeholder for adding beneficiary functionality
        // cout << "Adding Beneficiary will be implemented next\n";
        addBeneficiary(); // Call the function to add a beneficiary
        break;
    case 2:
        // placeholder for viewing ration stock functionality
        // cout << "Viewing Ration stock wiil be implemented later\n";

        viewBeneficiaries(); // Call the function to view beneficiaries
        break;
    case 3:
        allocateRation(); // Call the function to allocate ration
        break;
    case 4:
        viewRationHistory(); // Call the function to view ration history
        break;
    case 5:
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
void userMenu()
{
    cout << "Welcome to the User Menu!\n";

    // Display user options
    cout << "1. View Ration History (coming soon)\n";
    cout << "2. View Entitlement (coming soon)\n";
}