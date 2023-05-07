Code Implementation:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student {
    int rollNo;
    char name[50];
    float marks;
    struct student *next;
} Student;

Student *head = NULL;

void readFromFile() {
    FILE *fp;
    fp = fopen("students.dat", "rb");
    if(fp == NULL) {
        printf("Error opening file!");
        return;
    }
    Student *temp;
    while(!feof(fp)) {
        temp = (Student *) malloc(sizeof(Student));
        if(fread(temp, sizeof(Student), 1, fp)) {
            temp->next = NULL;
            if(head == NULL) {
                head = temp;
            } else {
                Student *current = head;
                while(current->next != NULL) {
                    current = current->next;
                }
                current->next = temp;
            }
        }
    }
    fclose(fp);
}

void writeToFile() {
    FILE *fp;
    fp = fopen("students.dat", "wb");
    if(fp == NULL) {
        printf("Error opening file!");
        return;
    }
    Student *current = head;
    while(current != NULL) {
        fwrite(current, sizeof(Student), 1, fp);
        current = current->next;
    }
    fclose(fp);
}

void addStudent() {
    Student *temp = (Student *) malloc(sizeof(Student));
    printf("Enter roll number: ");
    scanf("%d", &temp->rollNo);
    printf("Enter name: ");
    scanf("%s", temp->name);
    printf("Enter marks: ");
    scanf("%f", &temp->marks);
    temp->next = NULL;
    if(head == NULL) {
        head = temp;
    } else {
        Student *current = head;
        while(current->next != NULL) {
            current = current->next;
        }
        current->next = temp;
    }
    writeToFile();
}

void searchStudent() {
    int rollNo;
    char name[50];
    printf("Enter roll number or name: ");
    scanf("%s", name);
    rollNo = atoi(name);
    Student *current = head;
    while(current != NULL) {
        if(current->rollNo == rollNo || strcmp(current->name, name) == 0) {
            printf("Roll Number: %d\n", current->rollNo);
            printf("Name: %s\n", current->name);
            printf("Marks: %.2f\n", current->marks);
            return;
        }
        current = current->next;
    }
    printf("Student not found!\n");
}

void updateStudent() {
    int rollNo;
    printf("Enter roll number of student to update: ");
    scanf("%d", &rollNo);
    Student *current = head;
    while(current != NULL) {
        if(current->rollNo == rollNo) {
            printf("Enter updated details:\n");
            printf("Enter name: ");
            scanf("%s", current->name);
            printf("Enter marks: ");
            scanf("%f", &current->marks);
            writeToFile();
            printf("Student details updated!\n");
            return;
        }
        current = current->next;
    }
    printf("Student not found!\n");
}

void deleteStudent() {
    int rollNo;
    printf("Enter roll number of student to delete: ");
    scanf("%d", &rollNo);
    Student *current = head;
    Student *prev = NULL;
    while(current != NULL) {
        if(current->rollNo == rollNo) {
            if(prev == NULL) {
                head = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            writeToFile();
            printf("Student deleted!\n");
            return;
        }
        prev = current;
        current = current->next;
    }
    printf("Student not found!\n");
}

void displayMenu() {
    printf("Menu: \n");
    printf("1. Add student\n");
    printf("2. Search student\n");
    printf("3. Update student\n");
    printf("4. Delete student\n");
    printf("5. Exit\n");
    printf("Enter your choice: ");
}

int main() {
    readFromFile();
    int choice;
    do {
        displayMenu();
        scanf("%d", &choice);
        switch(choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                updateStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                printf("Exiting program...\n");
                break;
            default:
                printf("Invalid choice!\n");
        }
    } while(choice != 5);
    return 0;
}
