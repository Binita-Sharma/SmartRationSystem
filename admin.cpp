#include <iostream>
#include <fstream> // For file operations
#include <sstream> // For string stream operations
#include <ctime> // For time-related functions
#include <string>
#include "admin.h" // Assuming adminMenu and userMenu are declared in admin.h
#include "ration.h" // Include the header file for ration functions 
using namespace std;


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
// ------------------------------

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

    cout << "\n List of Registered Beneficiaries:\n";
    cout << "---------------------------------------------------------\n";
    cout << "ID\tName\t\tFamily\tIncome\tLast Month\n";
    cout << "---------------------------------------------------------\n";

    string id, name;
    int familySize, income;
    string lastMonth;

string line; // Read each line from the file
    // Loop through each line in the file
    while (getline(inFile, line)) {
        stringstream ss(line);  // Create a string stream for parsing
        string id, name, family, income, lastMonth;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, family, ',');
        getline(ss, income, ',');
        getline(ss, lastMonth, ',');

        cout << id << "\t" << name << "\t" << family << "\t" << income << "\t" << lastMonth << "\n";
    }

    inFile.close();
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

    cout << "\n Allocating Ration for " << currentMonth << ":\n";

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
            tempFile << id << "," << name << "," << family<< "," << income << "," << lastMonth << endl;
            continue; // Skip to the next beneficiary
        }

        Ration r = calculateRation(income, family);
        cout << id << " gets " << r.rice << "kg rice & " << r.wheat << "kg wheat &" << 
        r.sugar<<"kg sugar &" << r.oil<< "kg oil\n";
        tempFile << id << "," << name << "," << family << "," << income << "," << currentMonth << "\n";
        logFile << "[" << currentMonth << "] " << id << " received " << r.rice << "kg rice and " << r.wheat << "kg wheat\n";    }

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

    cout << "\n Ration Allocation History:\n";
    cout << "---------------------------------\n";

    string line;
    while (getline(logFile, line))
    {
        cout << line << endl; // Print each line from the log file
    }
    cout << "---------------------------------\n";

    logFile.close(); // Close the log file
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
        addBeneficiary(); // Call the function to add a beneficiary
        break;
    case 2:
        // placeholder for viewing ration stock functionality

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
