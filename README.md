# Bank Management System (C++)

## Description
A console-based Bank Management System implemented in C++.  
The project simulates basic banking operations such as account creation, login, deposits, withdrawals, and balance display using file handling and object-oriented programming.

## Features
- Create new bank accounts
- Secure PIN-based account access
- Account locking after three consecutive incorrect PIN attempts
- Deposit and withdraw money
- Display account balance
- Display transaction history
- Persistent data storage using files

## Concepts Used
- Object-Oriented Programming (Classes, Objects)
- File Handling (ifstream, ofstream, fstream)
- Functions and control structures
- Basic data security using PIN

## How to Run
1. Compile the program:
   ```bash
   g++ main.cpp -o bank
2. Run the executable:
   ./bank

## Data Files
- The program uses text files for persistent storage:
- user.txt- Stores the account number to be used. Already uploaded.
- Bank.txt- Stores account details. Automatically created at runtime. 

- TransactionHistory.txt- Stores transaction records. Automatically created at runtime.