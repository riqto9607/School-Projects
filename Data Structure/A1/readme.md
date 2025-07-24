# 📚 Data Structure Group Assignment 1 – Library Management System

This project is part of a group assignment for the Data Structure course. It demonstrates the use of **linked lists**, **structures**, and **file handling** in C++ to implement a simple **Library Management System** that tracks students and the books they borrow.

---

## 🧩 Project Overview

The system manages student borrowing records using the following data structures:

- `Date` struct: Stores day, month, and year, with a function to print the date.
- `LibBook` struct: Represents a book with attributes like title, author(s), publisher, ISBN, call number, and fine calculation.
- `LibStudent` struct: Represents a student and the list of books they've borrowed.
- `List` class: A singly linked list to store and manage `LibStudent` records.
- `Node` struct: Basic node used in the linked list implementation.

---

## 🔧 Features Implemented

### 1. Reading Student Records
- Load student records from a text file into a linked list with no duplicate entries.

### 2. Deleting Records
- Delete a student record based on student ID.

### 3. Searching Student
- Search and display student details by ID.

### 4. Inserting Borrowed Books
- Read book borrow records from a file and add them to the correct student, computing fines where necessary.

### 5. Display Output
- Display student and book information either to the console or a file (supports basic and detailed views).

### 6. Compute Statistics
- Compute and display per-course statistics such as total students, books borrowed, overdue books, and fines.

### 7. Find Students with Same Book
- Search for all students who borrowed a specific book (based on call number).

### 8. Warn Students
- Identify students who either:
  - Have more than 2 books overdue by 10+ days
  - Have fines over RM50.00 and all borrowed books are overdue

### 9. Menu System
- A console-based menu that allows the user to interact with the above features.

---

## 💾 File Structure

- `Date.h` / `Date.cpp` – Implements date struct and print functionality.
- `LibBook.h` – Defines a book's attributes and comparison/print methods.
- `LibStudent.h` / `LibStudent.cpp` – Defines the student struct and related functions.
- `List.h` / `List.cpp` – Implements a singly linked list for storing students.
- `Node.h` / `Node.cpp` – Basic node structure.
- `main.cpp` – Contains the menu and calls all main functionalities.

---

## 📌 Key Concepts Used

- Singly Linked List  
- Structs with member functions  
- File Input/Output  
- Pointer Arrays (for authors)  
- Basic searching and sorting logic  
- Operator-style comparisons (`>=`, `==`)  
- Julian day calculation for fine logic  

---

## 💻 Sample Executable

You can download and run the project from the executable file here:  
🔗 [Group52.exe](https://github.com/riqto9607/School-Projects/blob/main/Programming/Group52.exe)

---

## 📎 Sample Files

- `student.txt` – Contains student data  
- `book.txt` – Contains borrowed book data  
- `student_info.txt` / `student_booklist.txt` – Sample output files  

---

## 👥 Group Members

- Wong Pei Kei
- Lim Wei Haw
- Foo Kar Yeng
- Tan Yi Fei
- Tharini A/P Sandran

---

> *This project is educational and demonstrates the use of data structures for basic library management logic in C++.*

