#include <stdio.h>
#include <string.h>

#define MAX_BOOKS 50
#define MAX_STUDENTS 50

/* ---------- STRUCTURES ---------- */

typedef struct {
    int id;
    char name[50];
    int password;
} Student;

typedef struct {
    int id;
    char title[50];
    char author[50];
    int copies;
    int issuedTo; // student id, 0 if not issued
} Book;

/* ---------- GLOBAL DATA ---------- */

Book books[MAX_BOOKS];
Student students[MAX_STUDENTS];

int bookCount = 0;
int studentCount = 0;

const int ADMIN_ID = 11;
const int ADMIN_PASS = 121;

/* ---------- ADMIN FUNCTIONS ---------- */

void addBook() {
    int n;
    printf("Number of books to add: ");
    scanf("%d", &n);

    for (int i = 0; i < n && bookCount < MAX_BOOKS; i++) {
        printf("Book Name: ");
        scanf("%49s", books[bookCount].title);

        printf("Author Name: ");
        scanf("%49s", books[bookCount].author);

        printf("Book ID: ");
        scanf("%d", &books[bookCount].id);

        printf("Number of copies: ");
        scanf("%d", &books[bookCount].copies);

        books[bookCount].issuedTo = 0;
        bookCount++;

        printf("Book added successfully\n\n");
    }
}

void addStudent() {
    int n;
    printf("Number of students to add: ");
    scanf("%d", &n);

    for (int i = 0; i < n && studentCount < MAX_STUDENTS; i++) {
        printf("Student ID: ");
        scanf("%d", &students[studentCount].id);

        printf("Student Name: ");
        scanf("%49s", students[studentCount].name);

        printf("Password: ");
        scanf("%d", &students[studentCount].password);

        studentCount++;
        printf("Student added successfully\n\n");
    }
}

void report() {
    int found = 0;
    printf("\nIssued Books Report:\n");

    for (int i = 0; i < bookCount; i++) {
        if (books[i].issuedTo != 0) {
            printf("Book: %s | Issued To Student ID: %d\n",
                   books[i].title, books[i].issuedTo);
            found = 1;
        }
    }

    if (!found)
        printf("No books are currently issued.\n");
}

void adminMenu() {
    int choice;
    do {
        printf("\n1. Add Book\n2. Add Student\n3. Report\n4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) addBook();
        else if (choice == 2) addStudent();
        else if (choice == 3) report();
    } while (choice != 4);
}

/* ---------- STUDENT FUNCTIONS ---------- */

void viewBooks() {
    printf("\nAvailable Books:\n");
    for (int i = 0; i < bookCount; i++) {
        printf("%s by %s | ID: %d | Copies: %d\n",
               books[i].title, books[i].author,
               books[i].id, books[i].copies);
    }
}

void issueBook(int studentId) {
    int id;
    printf("Enter Book ID: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id && books[i].copies > 0) {
            books[i].copies--;
            books[i].issuedTo = studentId;
            printf("Book issued successfully\n");
            return;
        }
    }
    printf("Book not available\n");
}

void returnBook(int studentId) {
    int id;
    printf("Enter Book ID: ");
    scanf("%d", &id);

    for (int i = 0; i < bookCount; i++) {
        if (books[i].id == id && books[i].issuedTo == studentId) {
            books[i].copies++;
            books[i].issuedTo = 0;
            printf("Book returned successfully\n");
            return;
        }
    }
    printf("Invalid return request\n");
}

void studentMenu(int studentId) {
    int choice;
    do {
        printf("\n1. View Books\n2. Issue Book\n3. Return Book\n4. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) viewBooks();
        else if (choice == 2) issueBook(studentId);
        else if (choice == 3) returnBook(studentId);
    } while (choice != 4);
}

/* ---------- MAIN ---------- */

int main() {
    int choice;

    printf("WELCOME TO T4TEQ LIBRARY\n");

    while (1) {
        printf("\n1. Admin\n2. Student\n3. Exit\n");
        scanf("%d", &choice);

        if (choice == 1) {
            int id, pass;
            printf("Admin ID: ");
            scanf("%d", &id);
            printf("Password: ");
            scanf("%d", &pass);

            if (id == ADMIN_ID && pass == ADMIN_PASS) {
                adminMenu();
            } else {
                printf("Invalid admin credentials\n");
            }
        }

        else if (choice == 2) {
            int id, pass;
            printf("Student ID: ");
            scanf("%d", &id);
            printf("Password: ");
            scanf("%d", &pass);

            for (int i = 0; i < studentCount; i++) {
                if (students[i].id == id && students[i].password == pass) {
                    studentMenu(id);
                    break;
                }
                if (i == studentCount - 1)
                    printf("Invalid student credentials\n");
            }
        }

        else if (choice == 3) {
            printf("Thank you\n");
            break;
        }

        else {
            printf("Invalid option\n");
        }
    }

    return 0;
}
