# Bank Management System (C++)

A console-based **Bank Management System** developed in C++ that simulates core banking operations using **file-based persistence**.  
The project focuses on **account handling, secure PIN authentication, transaction processing, and transaction history management**, without using databases or networking.

---

## 📌 Features

### 👤 Account Management
- Create new bank accounts
- Auto-generated unique account numbers
- Secure 4-digit PIN-based login
- Account lock after multiple incorrect PIN attempts
- Manual account unlock request
- Account deletion support

### 💰 Banking Operations
- Deposit money
- Withdraw money
- Transfer money between accounts
- Real-time balance updates
- Persistent account data stored in files

### 🔐 Security
- PIN-based authentication
- Account lock mechanism after repeated wrong PIN attempts
- Manual unlock request feature

### 📜 Transaction History
- Records every transaction (Deposit, Withdraw, Transfer)
- Timestamped transaction entries
- Separate transaction history file
- View transaction history for any account

### 🗂 File Persistence
- User data, account number transaction hsitory are stored using text files
- Data remains intact across multiple program runs
- Use of temporary files for updating and deleting data
- If you are running this program for first time then you must create a file named "User.txt" and store create first Account Number according to your choice. Otherwise it would create by its own and would start from 0. In future i would try to solve this problem.

---

## 🛠 Technologies Used
- Object-Oriented Programming (Classes,Objects)
- File handling (ifstream,ofstream,fstream)
- Functions and Control structures
- Basic data security using PIN and account locking

---

## ▶️ How to Compile and Run
   ```bash
   g++ main.cpp -o bank
   ./bank

