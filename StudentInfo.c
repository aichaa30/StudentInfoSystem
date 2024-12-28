#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define MAX_COURSES 10
#define MAX_NAME_LENGTH 50
#define MAX_COURSE_NAME_LENGTH 50
#define MAX_USERNAME_LENGTH 100
#define MAX_PASSWORD_LENGTH 100


// Structures
typedef struct {
    char firstName[MAX_NAME_LENGTH];
    char lastName[MAX_NAME_LENGTH];
    int rollNumber;
    float CGPA;
    char courses[MAX_COURSES][MAX_COURSE_NAME_LENGTH];
    int totalClasses[MAX_COURSES];
    int attendedClasses[MAX_COURSES];
} Student;

typedef struct {
    char username[MAX_NAME_LENGTH];
    char password[MAX_NAME_LENGTH];
    int role; // 0: Admin, 1: User
} User;

// Global Variables
Student students[MAX_STUDENTS];
User users[MAX_STUDENTS];
User currentUser;
int studentCount = 0;
int userCount = 0;

// Function Prototypes
void saveData();
void loadData();
void saveUsers();
void loadUsers();
void backupData();
void restoreData();
int authenticateUser(char *username, char *password);
void login();
void registerUser();
void addStudent();
void findStudentByRollNumber(int rollNumber);
void findStudentByFirstName(char *firstName);
void findStudentsByCourse(char *course);
void countStudents();
void deleteStudent(int rollNumber);
void updateStudent(int rollNumber);
void logout();
void showAdminMenu();
void showUserMenu();
void performAdminAction(int operation);
void performUserAction(int operation);

// Main Function
// Main Function
int main() {
    loadUsers();   // Load users from file
    restoreData(); // Restore student data from backup

    int choice;
    printf("1. Register\n");
    printf("2. Login\n");
    printf("3. Exit\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
            registerUser(); // Register new user
        } else if (choice == 2) {
            login(); // Authenticate user
        } else if (choice == 3) {
            printf("Exiting the program...\n");
            saveUsers(); // Save user data
            saveData();  // Save student data
            exit(0);     // Exit the program
        } else {
            printf("Invalid choice. Please try again.\n");
        }

    // Check if the currentUser's role is set correctly
    printf("Current User Role: %d\n", currentUser.role); // Debugging line

    if (currentUser.role == 0) {
        while (1) {
            showAdminMenu(); // Display menu for Admin
            int operation;
            scanf("%d", &operation);
            performAdminAction(operation); // Execute admin-selected action
        }
    } else if (currentUser.role == 1) {
        while (1) {
            showUserMenu(); // Display menu for User
            int operation;
            scanf("%d", &operation);
            performUserAction(operation); // Execute user-selected action
        }
    } else {
        printf("Invalid role detected.\n");
    }

    return 0;
}

// Login Function
void login() {
    char username[MAX_USERNAME_LENGTH];
    char password[MAX_PASSWORD_LENGTH];
    int found = 0;

    printf("Enter username: ");
    scanf("%s", username);
    printf("Enter password: ");
    scanf("%s", password);

    // Search for the user in the users list
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            found = 1;
            printf("Login successful!\n");
            currentUser = users[i];  // Set the current user
    break;
            

            // Check user role and redirect accordingly
            if (users[i].role == 0) {
                printf("Current User Role: Regular User\n");
                // Redirect to regular user menu or functionality
                // Optionally, you could call another function here
            } else if (users[i].role == 1) {
                printf("Current User Role: Admin\n");
                // Show admin menu here if needed
                // adminMenu();  // You could call an admin function here
            }
            break;
        }
    }

    if (!found) {
        printf("Invalid username or password.\n");
        // Return to the main menu if login fails
        return; // Exit the login function and go back to the main menu
    }
}


// Function to authenticate user
int authenticateUser(char *username, char *password) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            currentUser = users[i];  // Set currentUser to the logged-in user
            printf("Authenticated User: %s, Role: %d\n", currentUser.username, currentUser.role); // Debugging line
            return 1;  // Authentication successful
        }
    }
    return 0;  // Authentication failed
}



// Function Implementations
void addStudent() {
    if (studentCount >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    Student newStudent;
    printf("Enter first name: ");
    scanf("%s", newStudent.firstName);
    printf("Enter last name: ");
    scanf("%s", newStudent.lastName);
    printf("Enter roll number: ");
    scanf("%d", &newStudent.rollNumber);
    printf("Enter CGPA: ");
    scanf("%f", &newStudent.CGPA);

    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == newStudent.rollNumber) {
            printf("Student with roll number %d already exists.\n", newStudent.rollNumber);
            return;
        }
    }

    int numCourses;
    printf("Enter number of courses: ");
    scanf("%d", &numCourses);

    for (int i = 0; i < numCourses; i++) {
        printf("Enter course %d name: ", i + 1);
        scanf("%s", newStudent.courses[i]);
        printf("Enter total classes for course %d: ", i + 1);
        scanf("%d", &newStudent.totalClasses[i]);
        printf("Enter attended classes for course %d: ", i + 1);
        scanf("%d", &newStudent.attendedClasses[i]);
    }

    students[studentCount++] = newStudent;
    printf("Student added successfully.\n");
}

void findStudentByRollNumber(int rollNumber) {
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            printf("Student found:\n");
            printf("First Name: %s\n", students[i].firstName);
            printf("Last Name: %s\n", students[i].lastName);
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("CGPA: %.2f\n", students[i].CGPA);
            for (int j = 0; j < MAX_COURSES && students[i].courses[j][0] != '\0'; j++) {
                printf("Course %d: %s\n", j + 1, students[i].courses[j]);
                printf("Total Classes: %d\n", students[i].totalClasses[j]);
                printf("Attended Classes: %d\n", students[i].attendedClasses[j]);
            }
            return;
        }
    }
    printf("Student with roll number %d not found.\n", rollNumber);
}

void findStudentByFirstName(char *firstName) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        if (strcmp(students[i].firstName, firstName) == 0) {
            printf("Student found:\n");
            printf("First Name: %s\n", students[i].firstName);
            printf("Last Name: %s\n", students[i].lastName);
            printf("Roll Number: %d\n", students[i].rollNumber);
            printf("CGPA: %.2f\n", students[i].CGPA);
            for (int j = 0; j < MAX_COURSES && students[i].courses[j][0] != '\0'; j++) {
                printf("Course %d: %s\n", j + 1, students[i].courses[j]);
                printf("Total Classes: %d\n", students[i].totalClasses[j]);
                printf("Attended Classes: %d\n", students[i].attendedClasses[j]);
            }
            found = 1;
        }
    }
    if (!found) {
        printf("No students with first name %s found.\n", firstName);
    }
}

void findStudentsByCourse(char *course) {
    int found = 0;
    for (int i = 0; i < studentCount; i++) {
        for (int j = 0; j < MAX_COURSES && students[i].courses[j][0] != '\0'; j++) {
            if (strcmp(students[i].courses[j], course) == 0) {
                printf("Student found:\n");
                printf("First Name: %s\n", students[i].firstName);
                printf("Last Name: %s\n", students[i].lastName);
                printf("Roll Number: %d\n", students[i].rollNumber);
                printf("CGPA: %.2f\n", students[i].CGPA);
                printf("Total Classes for course %s: %d\n", course, students[i].totalClasses[j]);
                printf("Attended Classes for course %s: %d\n", course, students[i].attendedClasses[j]);
                found = 1;
                break;
            }
        }
    }
    if (!found) {
        printf("No students registered in course %s found.\n", course);
    }
}

// Admin Menu
void showAdminMenu() {
    printf("\nAdmin Menu:\n");
    printf("1. Add Student\n");
    printf("2. Find Student by Roll Number\n");
    printf("3. Find Student by First Name\n");
    printf("4. Find Students by Course\n");
    printf("5. Count Students\n");
    printf("6. Delete Student\n");
    printf("7. Update Student\n");
    printf("8. Logout\n");
    printf("9. Exit\n");
    printf("Enter your choice: ");
}

// User Menu
void showUserMenu() {
    printf("\nUser Menu:\n");
    printf("1. Find Student by Roll Number\n");
    printf("2. Find Student by First Name\n");
    printf("3. Find Students by Course\n");
    printf("4. Logout\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}
void exitProgram() {
    printf("Exiting the program...\n");
    saveUsers(); // Save user data
    saveData();  // Save student data
    exit(0);     // Terminate the program
}
// Perform Admin Actions
void performAdminAction(int operation) {
    int rollNumber;
    char firstName[MAX_NAME_LENGTH], course[MAX_COURSE_NAME_LENGTH];

    switch (operation) {
        case 1:
            addStudent();
            break;
        case 2:
            printf("Enter roll number: ");
            scanf("%d", &rollNumber);
            findStudentByRollNumber(rollNumber);
            break;
        case 3:
            printf("Enter first name: ");
            scanf("%s", firstName);
            findStudentByFirstName(firstName);
            break;
        case 4:
            printf("Enter course name: ");
            scanf("%s", course);
            findStudentsByCourse(course);
            break;
        case 5:
            countStudents();
            break;
        case 6:
            printf("Enter roll number to delete: ");
            scanf("%d", &rollNumber);
            deleteStudent(rollNumber);
            break;
        case 7:
            printf("Enter roll number to update: ");
            scanf("%d", &rollNumber);
            updateStudent(rollNumber);
            break;
        case 8:
            logout();
            break;
        case 9:
            exitProgram();  // Handle exit for admin
            break;
        default:
            printf("Invalid choice.\n");
    }
}

// Perform User Actions
void performUserAction(int operation) {
    int rollNumber;
    char firstName[MAX_NAME_LENGTH], course[MAX_COURSE_NAME_LENGTH];

    switch (operation) {
        case 1:
            printf("Enter roll number: ");
            scanf("%d", &rollNumber);
            findStudentByRollNumber(rollNumber);
            break;
        case 2:
            printf("Enter first name: ");
            scanf("%s", firstName);
            findStudentByFirstName(firstName);
            break;
        case 3:
            printf("Enter course name: ");
            scanf("%s", course);
            findStudentsByCourse(course);
            break;
        case 4:
            logout();
            break;
        case 5:
            exitProgram();  // Handle exit for user
            break;
        default:
            printf("Invalid choice.\n");
    }
}



// Register User
void registerUser() {
    printf("Enter username: ");
    scanf("%s", users[userCount].username);
    printf("Enter password: ");
    scanf("%s", users[userCount].password);

    printf("Enter role (0 for Admin, 1 for User): ");
    scanf("%d", &users[userCount].role);

    userCount++;
    printf("User registered successfully.\n");
}

// Logout Function
void logout() {
    printf("Logged out successfully.\n");
    saveUsers(); // Save user data
    saveData();  // Save student data
    main();      // Return to main for re-login or register
    exit(0);
}

// Save Data (students and users)
void saveData() {
    FILE *file = fopen("students.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving student data.\n");
        return;
    }
    fwrite(students, sizeof(Student), studentCount, file);
    fclose(file);
}

void saveUsers() {
    FILE *file = fopen("users.dat", "wb");
    if (file == NULL) {
        printf("Error opening file for saving user data.\n");
        return;
    }
    fwrite(users, sizeof(User), userCount, file);
    fclose(file);
}

void loadData() {
    FILE *file = fopen("students.dat", "rb");
    if (file == NULL) {
        printf("No student data found. Starting fresh.\n");
        return;
    }
    studentCount = fread(students, sizeof(Student), MAX_STUDENTS, file);
    fclose(file);
}

void loadUsers() {
    FILE *file = fopen("users.dat", "rb");
    if (file == NULL) {
        printf("No user data found. Starting fresh.\n");
        return;
    }
    userCount = fread(users, sizeof(User), MAX_STUDENTS, file);
    fclose(file);
}

void backupData() {
    saveData(); // Save student data
    saveUsers(); // Save user data
    printf("Data backed up successfully.\n");
}

void restoreData() {
    loadData(); // Load student data
    loadUsers(); // Load user data
    printf("Data restored successfully.\n");
}

void countStudents() {
    printf("Total number of students: %d\n", studentCount);
}

void deleteStudent(int rollNumber) {
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Student with roll number %d not found.\n", rollNumber);
        return;
    }

    // Shift students to fill the gap
    for (int i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }
    studentCount--;  // Decrease the student count
    printf("Student with roll number %d deleted successfully.\n", rollNumber);
}


void updateStudent(int rollNumber) {
    int index = -1;
    for (int i = 0; i < studentCount; i++) {
        if (students[i].rollNumber == rollNumber) {
            index = i;
            break;
        }
    }
    if (index == -1) {
        printf("Student with roll number %d not found.\n", rollNumber);
        return;
    }

    printf("Update student information for roll number %d:\n", rollNumber);
    printf("Enter CGPA: ");
    scanf("%f", &students[index].CGPA);

    int numCourses;
    printf("Enter number of courses: ");
    scanf("%d", &numCourses);

    for (int i = 0; i < numCourses; i++) {
        printf("Enter course %d name: ", i + 1);
        scanf("%s", students[index].courses[i]);
        printf("Enter total classes for course %d: ", i + 1);
        scanf("%d", &students[index].totalClasses[i]);
        printf("Enter attended classes for course %d: ", i + 1);
        scanf("%d", &students[index].attendedClasses[i]);
    }

    printf("Student updated successfully.\n");
}