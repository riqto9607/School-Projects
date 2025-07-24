# 🔐 Cybersecurity Group Assignment (UCCN1223)

**Universiti Tunku Abdul Rahman (UTAR)**  
**Faculty of Information Communication Technology**  
**October 2022 Trimester**

This repository documents the Cybersecurity Group Assignment completed as part of the UCCN1223 course. The project consists of hands-on tasks involving brute-force attacks, service exploitation, and password cracking, all aimed at deepening our understanding of offensive security tools and techniques.

---

## 👥 Group Members

| Student Name    | Student ID   | Practical Group | Programme |
|------------------|---------------|------------------|-----------|
| Foo Kar Yeng     | 2300422       | P3               | CN        |
| **Liew Ren Yi**     | 2300434       | P4               | CN        |
| **Tan Yi Fei**      | 2200842       | P3               | CN        |
| **Wong Pei Kei**    | 2207466       | P4               | CN        |

---

## 🧩 Project Overview

The assignment consists of three main parts:

- **Part A:** Brute-forcing DVWA login with Hydra.
- **Part B:** Exploiting a hidden Telnet server and retrieving a secret flag.
- **Part C:** Cracking encrypted Word documents using `office2john.py` and `Hashcat`.

---

## ✨ My Contribution – Wong Pei Kei (Part C)

### 🔓 Part C: Password Cracking with Hashcat (10%)

This section focuses on cracking 5 encrypted Microsoft Word documents using advanced password cracking techniques. Each document varies in password complexity and character composition. I was responsible for performing all cracking procedures and compiling the final results.

---

### 🛠 Tools & Techniques Used

- **John the Ripper**: `office2john.py` to extract password hashes.
- **Hashcat**: Brute-force mode using GPU acceleration.
- **Command Line Tools**: Used in Windows CMD and Kali Linux environments.

---

### ⚙️ General Workflow

1. **Hash Extraction**  
   Used `office2john.py` to convert each Word document into a hash format.

2. **Password Cracking**  
   Deployed `Hashcat` with brute-force (`-a 3`) using custom mask patterns based on given hints.

3. **Validation**  
   Successfully decrypted all 5 files and recorded the cracked passwords, document contents, and time taken.

---
