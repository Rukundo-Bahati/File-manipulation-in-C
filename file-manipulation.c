#include <stdio.h>
#include <stdlib.h>

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

void create() {
    student *s;
    FILE *fp;
    int n;
    printf("\nHow many students do you want?: ");
    scanf("%d", &n);
    
    s = (student *)calloc(n, sizeof(student));
    if (s == NULL) {
        perror("\nError allocating memory");
        return;
    }

    fp = fopen("mystudents.txt", "w");
    if (fp == NULL) {
        perror("\nError opening file");
        free(s);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        s[i].total = 0;
        s[i].per = 0.0;
        
        printf("\nEnter Student ID: ");
        scanf("%d", &s[i].id);
        while (getchar() != '\n'); // clear the input buffer
        printf("\nEnter Name: ");
        scanf(" %[^\n]", s[i].name);
        for (int j = 0; j < 3; j++) {
            printf("\nEnter marks of subject %d: ", j + 1);
            scanf("%d", &s[i].sub[j].mark);
            s[i].total += s[i].sub[j].mark;
        }
        s[i].per = s[i].total / 3.0;
        if (fwrite(&s[i], sizeof(student), 1, fp) != 1) {
            perror("\nError writing to file");
        }
    }
    fclose(fp);
    free(s);
}

void display() {
    student s1;
    FILE *fp;
    fp = fopen("mystudents.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    
    while (fread(&s1, sizeof(student), 1, fp)) {
        printf("\n%-5d%-20s", s1.id, s1.name);
        for (int j = 0; j < 3; j++) {
            printf("%4d", s1.sub[j].mark);
        }
        printf("%5d%7.2f", s1.total, s1.per);
    }
    fclose(fp);
}

void append() {
    student *s;
    FILE *fp;
    int n;
    printf("\nHow many students do you want to append?: ");
    scanf("%d", &n);
    
    s = (student *)calloc(n, sizeof(student));
    if (s == NULL) {
        perror("Error allocating memory");
        return;
    }

    fp = fopen("mystudents.txt", "a");
    if (fp == NULL) {
        perror("Error opening file");
        free(s);
        return;
    }
    
    for (int i = 0; i < n; i++) {
        s[i].total = 0;
        s[i].per = 0.0;
        
        printf("\nEnter Student ID: ");
        scanf("%d", &s[i].id);
        while (getchar() != '\n'); // clear the input buffer
        printf("\nEnter Name: ");
        scanf(" %[^\n]", s[i].name);
        for (int j = 0; j < 3; j++) {
            printf("\nEnter marks of subject %d: ", j + 1);
            scanf("%d", &s[i].sub[j].mark);
            s[i].total += s[i].sub[j].mark;
        }
        s[i].per = s[i].total / 3.0;
        if (fwrite(&s[i], sizeof(student), 1, fp) != 1) {
            perror("Error writing to file");
        }
    }
    fclose(fp);
    free(s);
}

void totalrecords() {
    FILE *fp;
    fp = fopen("mystudents.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }
    fseek(fp, 0, SEEK_END);
    int n = ftell(fp) / sizeof(student);
    printf("\nNumber of Records = %d", n);
    fclose(fp);
}

void search() {
    int id;
    int found = 0;
    student s1;
    FILE *fp;
    fp = fopen("mystudents.txt", "r");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    printf("\nEnter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&s1, sizeof(student), 1, fp)) {
        if (s1.id == id) {
            found = 1;
            printf("\n%-5d%-20s", s1.id, s1.name);
            for (int j = 0; j < 3; j++) {
                printf("%4d", s1.sub[j].mark);
            }
            printf("%5d%7.2f", s1.total, s1.per);
            break;  // Exit the loop as we found the record
        }
    }

    if (!found) {
        printf("\nRecord Not Found!");
    }

    fclose(fp);
}

void update() {
    int id;
    int found = 0;
    student s1;
    FILE *fp, *fp1;
    fp = fopen("mystudents.txt", "r");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL || fp1 == NULL) {
        perror("Error opening file");
        if (fp) fclose(fp);
        if (fp1) fclose(fp1);
        return;
    }

    printf("\nEnter Student ID to Update: ");
    scanf("%d", &id);

    while (fread(&s1, sizeof(student), 1, fp)) {
        if (s1.id == id) {
            found = 1;
            while (getchar() != '\n'); // clear the input buffer
            printf("\nEnter New Name: ");
            scanf(" %[^\n]", s1.name);
            s1.total = 0; // Reset total before updating marks
            s1.per =0;
            for (int j = 0; j < 3; j++) {
                printf("\nEnter New marks of subject %d: ", j + 1);
                scanf("%d", &s1.sub[j].mark);
                s1.total += s1.sub[j].mark;
            }
            s1.per = s1.total / 3.0;
        }
        fwrite(&s1, sizeof(student), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);

    if (found) {
        fp1 = fopen("temp.txt", "r");
        fp = fopen("mystudents.txt", "w"); // Open in write mode to overwrite
        if (fp == NULL || fp1 == NULL) {
            perror("Error reopening file");
            if (fp) fclose(fp);
            if (fp1) fclose(fp1);
            return;
        }

        while (fread(&s1, sizeof(student), 1, fp1)) {
            fwrite(&s1, sizeof(student), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
    } else {
        printf("\nRecord Not Found!");
    }

    remove("temp.txt"); // Clean up the temporary file
}

void delete() {
    int id;
    int found = 0;
    student s1;
    FILE *fp, *fp1;
    fp = fopen("mystudents.txt", "r");
    fp1 = fopen("temp.txt", "w");
    if (fp == NULL || fp1 == NULL) {
        perror("Error opening file");
        if (fp) fclose(fp);
        if (fp1) fclose(fp1);
        return;
    }

    printf("\nEnter Student ID to Delete: ");
    scanf("%d", &id);

    while (fread(&s1, sizeof(student), 1, fp)) {
        if (s1.id == id) {
            found = 1;
        }
        else
            fwrite(&s1, sizeof(student), 1, fp1);
    }
    fclose(fp);
    fclose(fp1);

    if (found) {
        fp1 = fopen("temp.txt", "r");
        fp = fopen("mystudents.txt", "w"); // Open in write mode to overwrite
        if (fp == NULL || fp1 == NULL) {
            perror("Error reopening file");
            if (fp) fclose(fp);
            if (fp1) fclose(fp1);
            return;
        }

        while (fread(&s1, sizeof(student), 1, fp1)) {
            fwrite(&s1, sizeof(student), 1, fp);
        }

        fclose(fp);
        fclose(fp1);
    } else {
        printf("\nRecord Not Found!");
    }

    remove("temp.txt"); // Clean up the temporary file
}



int main() {
    int ch;
    do {
        printf("\n\n1. Create a Record");
        printf("\n2. Display all Records");
        printf("\n3. Append new Record");
        printf("\n4. Total Records");
        printf("\n5. Search a Record");
        printf("\n6. Update A record");
        printf("\n7. Delete A record");
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
            case 4: totalrecords();
                break;
            case 5: search();
                break;
            case 6: update();
                break;
            case 7: delete();    
                break;
            case 0: break;
            default: printf("\nInvalid Option Chosen.");
        }
    } while (ch != 0);
    
    return 0;
}
