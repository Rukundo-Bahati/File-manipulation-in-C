<h1>File Manipulation in C: CRUD Operations</h1>


This project demonstrates how to perform CRUD (Create, Read, Update, Delete) operations on a file in C.
The program manages student records, including their ID, name, 
and marks for three subjects. The records are stored in a file and manipulated through various functions.

Features
Create a Record: Add new student records to the file.
Display All Records: Read and display all student records from the file.
Append a Record: Append new student records to the existing file.
Update a Record: Modify an existing student record.
Count Records: Display the total number of student records.
Search a Record: Find and display a student record by ID.
Getting Started
Prerequisites
A C compiler (e.g., GCC)
Basic knowledge of C programming
Installing
Clone the repository to your local machine:

sh
Copy code
git clonehttps://github.com/Rukundo-Bahati/File-manipulation-in-C
cd file-manipulation-c
Building
Compile the program using a C compiler:

sh
Copy code
gcc main.c -o file_manipulation
Running
Run the compiled program:

sh
Copy code
./file_manipulation
Program Structure
student Structure
Defines the student record structure:

c
Copy code
typedef struct student {
    int id;
    char name[20];
    struct subject {
        int scode;
        char subjectName[20];
        int mark;
    } sub[3];
    int total;
    float per;
} student;
Functions
Create Records

c
Copy code
void create();
Prompts the user for the number of students.
Reads student details and writes them to mystudents.txt.
Display All Records

c
Copy code
void display();
Reads and displays all records from mystudents.txt.
Append Records

c
Copy code
void append();
Prompts the user for additional student records.
Appends new records to mystudents.txt.
Update a Record

c
Copy code
void update();
Prompts the user for a student ID to update.
Modifies the existing record in mystudents.txt.
Count Records

c
Copy code
void noofrec();
Displays the total number of student records in mystudents.txt.
Search a Record

c
Copy code
void search();
Prompts the user for a student ID.
Searches and displays the student record if found.
Main Function
The main function provides a menu for the user to select various operations:

c
Copy code
int main() {
    int ch;
    do {
        printf("\n1. Create a Record");
        printf("\n2. Display all Records");
        printf("\n3. Append new Record");
        printf("\n4. Total Records");
        printf("\n5. Search a Record");
        printf("\n0. EXIT");

        printf("\nEnter your Choice: ");
        scanf("%d", &ch);

        switch (ch) {
            case 1: create();
                break;
            case 2: display();
                break;
            case 3: append();
                break;
            case 4: noofrec();
                break;
            case 5: search();
                break;
            case 0: break;
            default: printf("\nInvalid Option Chosen.");
        }
    } while (ch != 0);

    return 0;
}
License
This project is licensed under the MIT License - see the LICENSE file for details.

Acknowledgments
Inspired by basic file manipulation tasks in C programming.
Special thanks to the C programming community for various tips and tricks.
