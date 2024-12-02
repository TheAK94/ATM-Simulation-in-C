# 🏦 ATM Simulation in C

Welcome to the **ATM Simulation Project**, a console-based application developed in **C** that mimics the core functionalities of an ATM. This project demonstrates the implementation of real-world concepts such as account management, secure PIN handling, and transaction processing in a structured and efficient manner.

---

## 📖 Project Overview

This program is designed to simulate a basic ATM system where users can perform banking operations such as checking balances, withdrawing funds, depositing money, and more. It's a great example of applying **C programming concepts** like **file handling**, **structures**, and **dynamic memory allocation**.

---

## 🌟 Features

- **User Authentication**:
  - Login with a secure PIN.
- **Account Management**:
  - Supports multiple user accounts stored in a file.
- **Core Banking Operations**:
  - Check Profile (includes balance)
  - Withdraw Funds
  - Deposit Money
  - Change Pin
  - Delete Account
- **File-Based Data Storage**:
  - User account data is stored in structured files for persistence.

---

## 🛠️ How It Works

### Functional Flow:
1. **Login**:
   - User enters their account number and PIN to authenticate.
2. **Main Menu**:
   - Once authenticated, the user can choose from various options:
     ```
     1. Show Profile
     2. Withdraw Money
     3. Deposit Money
     4. Change Pin 
     5. Logout
     ```
3. **Perform Transactions**:
   - Based on the user’s selection, the system performs the required operation and updates the data.

4. **Logout**:
   - The session ends when the user selects "Logout" and then "Exit".

---

## 📋 Project Structure

### Code Files:
1. `ATM_Sim.c`: contains full program.
