# Bank Management System (C++)

A console-based Bank Client Management System built in C++. The program manages client records stored in a local text file, with a full menu-driven interface for common banking operations.

## Features

- **Show Client List**: displays all clients in a formatted table
- **Add New Client**: creates a new client record, with a duplicate account-ID check to prevent overwriting existing clients
- **Delete Client**: finds a client by account number, confirms before deleting, and safely rewrites the data file
- **Update Client**: finds a client by account number, confirms before updating, and rewrites the data file with the new data
- **Find Client**: looks up and displays a single client's full details
- **Exit**: closes the program

## How It Works

Client data is stored as delimited text lines (`#//#` as the field separator) in `Clients.txt`, in the same directory as the executable. On each menu action, the file is read, parsed into structured records, modified as needed, and written back.

Each client record includes:
- Account Number
- Pin Code
- Name
- Phone
- Account Balance

## Built From Scratch

All core logic — file reading/writing, manual string splitting, struct-based record parsing, and search/update/delete operations was written and debugged independently as part of this roadmap project.

## Testing

Manually tested 15+ times across all menu options (add, delete, update, find, list), including repeated add/delete cycles in the same session, duplicate account-ID entries, and non-numeric/out-of-range menu input. All cases behaved as expected.

## Possible Improvements

- Input validation on individual client fields (e.g. rejecting an empty account number, non-numeric account balance)
- Case-insensitive search when finding a client
- Sorting or filtering the client list (by name, balance, etc.)
- Separating the menu/UI logic from the data logic into different files for better organization
- Replacing the plain-text file format with a more robust storage format (e.g. CSV or a lightweight database) to avoid issues if a field ever contains the delimiter itself

## Tech Stack

- C++ (single-file console application)
- Standard Library only: `<iostream>`, `<fstream>`, `<string>`, `<vector>`, `<iomanip>`

## How to Run

1. Compile with any standard C++ compiler, e.g.:
   ```
   g++ -o BankSystem main.cpp
   ```
2. Run the executable in a directory where it has permission to read/write `Clients.txt` (the file is created automatically on first write if it doesn't exist).
3. Follow the on-screen menu prompts.
