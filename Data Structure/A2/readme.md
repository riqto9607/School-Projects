# 📘 Data Structures Group Assignment – Binary Search Tree System (C++)

## 🎯 Objective
This group project was developed as part of our **Data Structures** coursework. It reinforces the concept and implementation of **Binary Search Trees (BST)** using C++. The objectives include:

- Strengthening understanding of **tree-based data structures**
- Applying **recursion techniques** effectively
- Practicing **tree traversal methods**:
  - Pre-order
  - In-order
  - Post-order
  - Level-order

---

## ⚙️ Environment
- **Language:** C++
- **Platform:** Microsoft Visual Studio 2022 (as per coursework requirement)

---

## 📂 Project Overview

This program simulates a **student record management system** using a **Binary Search Tree (BST)** where each node represents a student. The project includes the following functionalities:

### ✅ Core Functionalities

| Function         | Description |
|------------------|-------------|
| `readFile()`     | Reads student records from a `.txt` file and inserts them into the BST based on `student ID` |
| `deepestNodes()` | Identifies and prints all student IDs located at the **deepest level** of the tree |
| `display(order, source)` | Prints all student records either in **ascending** or **descending** order by ID; output to **screen** or **file** |
| `CloneSubtree(t1, item)` | Clones a **subtree** from tree `t1` starting at the node with the given `student ID` and stores it into another BST |
| `printLevelNodes()` | Displays student IDs **level-by-level** (breadth-first traversal) |
| `printPath()`    | Prints all **external paths** (root-to-leaf paths) in the BST |
| `menu()`         | Presents a user-friendly CLI menu for selecting all the above functionalities interactively |

---

## 🧠 Key Data Structures & Concepts Used

- **Binary Search Tree (BST)** with insert, delete, and search operations
- **Queue (Custom Linked List implementation)** for level-order traversal
- **Recursion** for traversals and path printing
- **File I/O** using `ifstream` and `ofstream` for input/output
- **Struct-based Student Record** system

---

## 📁 Sample Input Format (`student.txt`)
ID: 123
Name: John Doe
Address: ...
DOB: ...
Phone No: ...
Course: ...
CGPA: ...

---

## 👨‍💻 My Contributions

- Implemented key BST functions like `deepestNodes()`, `printPath()`, and `CloneSubtree()`
- Built file reading logic with validation for duplicate student IDs
- Designed modular code for BST traversal and output formatting
- Collaborated in debugging and testing across multiple test cases

---

## 🔍 How to Run

1. Open the project in **Visual Studio 2022**
2. Compile and run `main.cpp`
3. Follow the on-screen menu to interact with the BST features

---

## 🧾 Notes

- Duplicate student IDs are ignored with a message.
- All tree traversals use **recursive** implementations.
- This was a **group project** developed collaboratively.
