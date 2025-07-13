# 🌾 Smart Ration Distribution Management System

A C++ console-based application aimed at improving transparency and fairness in the public distribution system (PDS) of essential commodities like rice, wheat, sugar, and oil.
This project enables administrators to manage ration distribution efficiently while allowing users to track their own ration history and entitlements.

In rural or low-income areas, managing ration distribution is often prone to corruption and data mismanagement. This system provides:

-Fair allocation based on income level

-Traceability of records

-Accountability in monthly rationing


---

## 🚀 Features

### 👩‍💼 Admin Panel
- **Add Beneficiaries** with details like ID, name, income, and family size
- **View Beneficiaries** in a structured format
- **Allocate Ration** based on family size and income
- **Maintain Logs** of each month's distribution
- **View Ration History** for audit and transparency

### 🙋‍♂️ User Panel
- Login using **user credentials**
- **View Personal Ration History**
- **Check Latest Ration Status** (last month received, entitlements)

---

## 📁 Project Structure

SmartRationSystem/
├── main.cpp # Entry point (login + role-based access)
├── admin.cpp / admin.h # Admin functionalities
├── user.cpp / user.h # User functionalities
├── ration.cpp / ration.h # Logic to calculate ration based on income & family
├── database/
│ ├── user.txt # Stores user/beneficiary records
│ └── log.txt # Stores ration distribution logs

---

## 🛠️ Tech Stack

- **Language**: C++
- **I/O**: File handling using `fstream`
- **Structure**: Modular with header/source separation

---

## ⚙️ How to Compile

```bash
g++ main.cpp admin.cpp user.cpp ration.cpp -o rationSystem.exe
Then run:
./rationSystem.exe     # For Git Bash / Linux / Mac
.\rationSystem.exe     # For Windows PowerShell
rationSystem.exe       # For Windows CMD

Sample Credentials
Role	Username	Password
Admin	admin	admin123
User	user	user123

👤 Binita Sharma
💻 Final Year BCA Student
📍 Lovely Professional University
🌐 GitHub: Binita-Sharma
