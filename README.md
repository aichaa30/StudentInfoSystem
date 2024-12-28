# 🌟 Student Information Management System

A C-based application for managing student information, course registrations, and attendance records with enhanced features for data security and backup.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Demo](#demo)

---
## Overview

The **Student Information Management System** is a console application written in C. It provides functionalities for:
- Adding, updating, deleting, and retrieving student information.
- Tracking course registrations and attendance.
- Managing backups and restores.
- Enhancing security with user authentication.

This project is designed to streamline the management of student-related data with a focus on simplicity, reliability, and efficiency.

---

## Features
### Core Functionalities:
- **User Authentication:**
  - Role-based login system (Admin/User).
  - Registration for new users.

- **Student Management (Admin-only):**
  - Add, update, delete, and view student records.
  - Search students by roll number, name, or course.
  - Count total students in the database.

- **Course and Attendance Management:**
  - Track courses for each student.
  - Maintain attendance records for individual courses.

- **Data Backup and Restoration:**
  - Automatic backup of student records.
  - Restore data from backup files.

- **Menu-based Navigation:**
  - Separate menus for Admin and User roles for streamlined access to features.
---
 ## Installation
 
 ### Prerequisites:
- A C compiler (e.g., GCC).
- Basic understanding of terminal/command-line operations.
  
1. **Clone the repository**:
    ```bash
    git clone https://github.com/yourusername/StudentInfoSystem.git
    cd StudentInfoSystem 
    ```

2. **Compile the program**:
    ```bash
    gcc StudentInfo.c -o StudentInfoSystem
    ```

3. **Run the program**:
    ```bash
    ./StudentInfoSystem
    ```
--- 

## Usage

### Register a User:
- Start the program and choose the Register option.
- Enter the desired username, password, and role (Admin/User).

### Login:
- Use your credentials to log in.
- Admins can access the full set of functionalities, while Users have limited access.

### Admin Menu:
- Add students and manage their records.
- View, search, update, or delete student information.
- Manage course and attendance data.

### User Menu:
- View student records.
- Search for students by roll number, first name, or course.

--- 
### Project Structure

main.c                   # Main source file  

README.md                # Project documentation

data/                    # Data folder for backups and saved records

users/                   # Folder for user credentials

--- 
### Demo


[example.pdf](https://github.com/user-attachments/files/18265397/example.pdf)
