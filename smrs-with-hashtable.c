#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NAME_LEN 50
#define MAX_ROLL_LEN 10

typedef struct student {
    char name[MAX_NAME_LEN];
    char roll[MAX_ROLL_LEN];
    float cgpa;
    struct student *next;
} Student;

int hash(char *str) {
    int hash = 0;
    while (*str) {
        hash += *str++;
    }
    return hash % 10000;
}

void insert(Student **head, char *name, char *roll, float cgpa) {
    Student *new_node = (Student *) malloc(sizeof(Student));
    strcpy(new_node->name, name);
    strcpy(new_node->roll, roll);
    new_node->cgpa = cgpa;
    new_node->next = *head;
    *head = new_node;
}

void delete(Student **head, char *roll) {
    Student *prev = NULL;
    Student *curr = *head;
    while (curr) {
        if (strcmp(curr->roll, roll) == 0) {
            if (prev == NULL) {
                *head = curr->next;
            } else {
                prev->next = curr->next;
            }
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void search(Student *head, char *key) {
    int index = hash(key);
    int found = 0;
    while (head) {
        if (hash(head->roll) == index && strcmp(head->roll, key) == 0) {
            printf("%-50s %-10s %5.2f\n", head->name, head->roll, head->cgpa);
            found = 1;
        }
        head = head->next;
    }
    if (!found) {
        printf("Record not found.\n");
    }
}

void update(Student *head, char *roll) {
    while (head) {
        if (strcmp(head->roll, roll) == 0) {
            printf("Enter new name: ");
            scanf("%s", head->name);
            printf("Enter new CGPA: ");
            scanf("%f", &head->cgpa);
            return;
        }
        head = head->next;
    }
    printf("Record not found.\n");
}

void read_file(Student **head) {
    FILE *fp = fopen("students.bin", "rb");
    if (fp == NULL) {
        return;
    }
    while (!feof(fp)) {
        char name[MAX_NAME_LEN];
        char roll[MAX_ROLL_LEN];
        float cgpa;
        fread(name, sizeof(char), MAX_NAME_LEN, fp);
        fread(roll, sizeof(char), MAX_ROLL_LEN, fp);
        fread(&cgpa, sizeof(float), 1, fp);
        insert(head, name, roll, cgpa);
    }
    fclose(fp);
}

void write_file(Student *head) {
    FILE *fp = fopen("students.bin", "wb");
    if (fp == NULL) {
        return;
    }
    while (head) {
        fwrite(head->name, sizeof(char), MAX_NAME_LEN, fp);
        fwrite(head->roll, sizeof(char), MAX_ROLL_LEN, fp);
        fwrite(&head->cgpa, sizeof(float), 1, fp);
        head = head->next;
    }
    fclose(fp);
}

void print_menu() {
    printf("1. Add student\n");
    printf("2. Search student\n");
    printf("3. Update student\n");
    printf("4. Delete student\n");
    printf("5. Exit\n");
}

int main() {
    Student *head = NULL;
    read_file(&head);
    int choice;
    do {
        print_menu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: {
                char name[MAX_NAME_LEN];
                char roll[MAX_ROLL_LEN];
                float cgpa;
                printf("Enter name: ");
                scanf("%s", name);
                printf("Enter roll: ");
                scanf("%s", roll);
                printf("Enter CGPA: ");
                scanf("%f", &cgpa);
                insert(&head, name, roll, cgpa);
                write_file(head);
                break;
            }
            case 2: {
                char key[MAX_ROLL_LEN];
                printf("Enter roll or name: ");
                scanf("%s", key);
                printf("%-50s %-10s %5s\n", "Name", "Roll", "CGPA");
                search(head, key);
                break;
            }
            case 3: {
                char roll[MAX_ROLL_LEN];
                printf("Enter roll: ");
                scanf("%s", roll);
                update(head, roll);
                write_file(head);
                break;
            }
            case 4: {
                char roll[MAX_ROLL_LEN];
                printf("Enter roll: ");
                scanf("%s", roll);
                delete(&head, roll);
                write_file(head);
                break;
            }
            case 5: {
                break;
            }
            default: {
                printf("Invalid choice.\n");
                break;
            }
        }
    } while (choice != 5);
    return 0;
}
