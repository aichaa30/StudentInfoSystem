# Student Information Management System

A C-based application for managing student information, course registrations, and attendance records with enhanced features for data security and backup.

## Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Installation](#installation)
- [Usage](#usage)
- [Project Structure](#project-structure)
- [Contributing](#contributing)
- [License](#license)
- [Acknowledgements](#acknowledgements)

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

### Clone the Repository:
```bash
git clone https://github.com/yourusername/StudentInfoSystem.git
cd StudentInfoSystem 

### Compile the Program:
```bash
gcc StudentInfo.c -o StudentInfoSystem

Run the Program:
./StudentInfoSystem


