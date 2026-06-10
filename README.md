# Bank Management System (C++)

A robust, console-based banking application designed for administrative and managerial use. This system handles customer records, financial operations, and account lookups using persistent text file storage.

This project was built as a final semester project to demonstrate core procedural and low-level data tracking principles in C++.

---

## 🚀 Key Features

* **Manager-Focused Bulk Enrollment (`addm`):** Allows administrators to register multiple user profiles simultaneously using **dynamic memory arrays (`new[]`)**, complete with double-pass duplication checking before saving to disk.
* **Persistent File Storage:** Writes data directly to an isolated database flat-file (`accounts.txt`), keeping account records alive even after closing the program.
* **Transactional Integrity Safeguard:** Features a split-state verification pass in the transfer function to prevent account file corruption in the case of insufficient funds.
* **String Parsing & Text Sanitation:** Employs a custom cleanup routine (`cleanStr`) that strips out invisible leading/trailing whitespaces and system carriage returns (`\r`), eliminating conversion errors (`stod`) during runtime parsing.

---

## 🛠️ File Structure & Architecture

The application implements a custom **Two-File Swap Pattern** to modify specific text lines within file streams safely:
[Read Engine]  ──> Open accounts.txt (Extract Fields via Delimiter ',')
│
▼
[Process Logic]──> Calculate Changes / Perform Validations
│
▼
[Write Engine] ──> Write to temp.txt ──> Delete accounts.txt ──> Rename temp.txt

### Why Account IDs are saved as Strings (`std::string`) rather than integers (`int`):
1. **Preserves Leading Zeros:** Prevents C++ from accidentally truncating formatted entries (e.g., preserving `000456` instead of shortening it to `456`).
2. **Crash Prevention:** Storing IDs as string types gracefully handles unexpected user typos without triggering infinite loops or application crashes (`cin.fail()`).
3. **Semantic Correctness:** Avoids violating standard database conventions—since arithmetic operators are never performed on IDs, they are treated strictly as identifiers.

---

## 💻 Available Options

1. **Create New Account:** Register a single customer.
2. **Bulk Account Creation:** Manager-exclusive menu utilizing dynamic allocation.
3. **Deposit Money:** Add currency into an active account profile.
4. **Withdraw Money:** Extract funds with insufficient balance cross-checking.
5. **Transfer Money:** Atomically shift balances across two accounts.
6. **View Account Details:** Query single profiles directly by ID.
7. **View All Accounts:** Display an aligned overview table of the entire file.
8. **Search Account by Name:** Check for full or partial name records.
9. **Search Accounts by Balance:** Returns all records crossing a chosen balance threshold.
10. **Delete Account:** Completely purges a client profile out of storage.

---

## 🔧 Setup & Installation

### Prerequisites
* A C++ compiler supporting at least C++11 (GCC, Clang, or MSVC).

### Compilation (Terminal)
Clone the repository and run the following commands to compile using `g++`:

```bash
git clone (https://github.com/BaByJuNiii/BANK-MANAGEMENT-SYSTEM-C-FILE-HANDLING-SEMESTER-FINAL-PROJECT.git)
cd YOUR_REPOSITORY_NAME
g++ -std=c++11 main.cpp -o BankSystem
