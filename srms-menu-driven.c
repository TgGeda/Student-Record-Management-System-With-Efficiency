# Implementation of the menu driven Student Record Management System using C:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILENAME "students.dat"

struct student {
    int roll;
    char name[50];
    float marks;
    struct student *next;
};

void read_students(struct student **head) {
    FILE *fp = fopen(FILENAME, "rb");
    if (fp == NULL) {
        return;
    }
    struct student *p = NULL;
    while (!feof(fp)) {
        struct student *s = malloc(sizeof(struct student));
        fread(s, sizeof(struct student), 1, fp);
        if (s->roll == 0) {
            free(s);
            break;
        }
        if (*head == NULL) {
            *head = s;
        } else {
            p->next = s;
        }
        p = s;
    }
    fclose(fp);
}

void write_students(struct student *head) {
    FILE *fp = fopen(FILENAME, "wb");
    if (fp == NULL) {
        return;
    }
    struct student *p = head;
    while (p != NULL) {
        fwrite(p, sizeof(struct student), 1, fp);
        p = p->next;
    }
    struct student end = {0};
    fwrite(&end, sizeof(struct student), 1, fp);
    fclose(fp);
}

void add_student(struct student **head) {
    struct student *s = malloc(sizeof(struct student));
    printf("Enter roll number: ");
    scanf("%d", &s->roll);
    printf("Enter name: ");
    scanf("%s", s->name);
    printf("Enter marks: ");
    scanf("%f", &s->marks);
    s->next = NULL;
    if (*head == NULL) {
        *head = s;
    } else {
        struct student *p = *head;
        while (p->next != NULL) {
            p = p->next;
        }
        p->next = s;
    }
    write_students(*head);
}

void search_student(struct student *head) {
    int roll;
    printf("Enter roll number: ");
    scanf("%d", &roll);
    struct student *p = head;
    while (p != NULL) {
        if (p->roll == roll) {
            printf("Roll number: %d\n", p->roll);
            printf("Name: %s\n", p->name);
            printf("Marks: %.2f\n", p->marks);
            return;
        }
        p = p->next;
    }
    printf("Student not found\n");
}

void update_student(struct student **head) {
    int roll;
    printf("Enter roll number: ");
    scanf("%d", &roll);
    struct student *p = *head;
    while (p != NULL) {
        if (p->roll == roll) {
            printf("Enter new name: ");
            scanf("%s", p->name);
            printf("Enter new marks: ");
            scanf("%f", &p->marks);
            write_students(*head);
            return;
        }
        p = p->next;
    }
    printf("Student not found\n");
}

void delete_student(struct student **head) {
    int roll;
    printf("Enter roll number: ");
    scanf("%d", &roll);
    struct student *p = *head;
    struct student *prev = NULL;
    while (p != NULL) {
        if (p->roll == roll) {
            if (prev == NULL) {
                *head = p->next;
            } else {
                prev->next = p->next;
            }
            free(p);
            write_students(*head);
            return;
        }
        prev = p;
        p = p->next;
    }
    printf("Student not found\n");
}

void print_menu() {
    printf("1. Add student\n");
    printf("2. Search student\n");
    printf("3. Update student\n");
    printf("4. Delete student\n");
    printf("5. Exit\n");
}

int main() {
    struct student *head = NULL;
    read_students(&head);
    int choice;
    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: add_student(&head); break;
            case 2: search_student(head); break;
            case 3: update_student(&head); break;
            case 4: delete_student(&head); break;
            case 5: break;
            default: printf("Invalid choice\n"); break;
        }
    } while (choice != 5);
    struct student *p = head;
    while (p != NULL) {
        struct student *tmp = p;
        p = p->next;
        free(tmp);
    }
    return 0;
}
