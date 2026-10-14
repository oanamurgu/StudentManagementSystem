
#include <stdio.h>
#include <string.h>

struct Student {
    char name[50];
    int grade;
};

void loadStudents(struct Student students[], int *n) {
    FILE *file = fopen("students.txt", "r");

    if (file == NULL) {
        return;
    }

    while (*n < 100 &&
           fgets(students[*n].name, 50, file) != NULL) {

        students[*n].name[
            strcspn(students[*n].name, "\n")
        ] = '\0';

        if (fscanf(file, "%d", &students[*n].grade) != 1) {
            break;
        }

        int c;
        while ((c = fgetc(file)) != '\n' && c != EOF) {
        }

        if (students[*n].grade >= 1 &&
            students[*n].grade <= 10) {
            (*n)++;
        }
    }

    fclose(file);
}

void saveStudents(struct Student students[], int n) {
    FILE *file = fopen("students.txt", "w");

    if (file == NULL) {
        printf("Error saving students!\n");
        return;
    }

    for (int i = 0; i < n; i++) {
        fprintf(file, "%s\n%d\n",
                students[i].name,
                students[i].grade);
    }

    fclose(file);
}

int main() {
    struct Student students[100];
    int n = 0;
    int option;

    loadStudents(students, &n);

    do {
        printf("\n=== STUDENT MANAGEMENT SYSTEM ===\n");
        printf("1. Add student\n");
        printf("2. Display students\n");
        printf("3. Calculate average grade\n");
        printf("0. Exit\n");
        printf("Choose an option: ");

        if (scanf("%d", &option) != 1) {
            printf("Invalid input!\n");
            return 1;
        }
        getchar();

        if (option == 1) {
            if (n < 100) {
                printf("Enter student name: ");
                if (fgets(students[n].name, 50, stdin) == NULL) {
                    printf("Error reading name!\n");
                    continue;
                }

                students[n].name[
                    strcspn(students[n].name, "\n")
                ] = '\0';

                printf("Enter grade (1-10): ");

                if (scanf("%d", &students[n].grade) != 1) {
                    printf("Invalid grade input!\n");
                    return 1;
                }
                getchar();

                if (students[n].grade >= 1 &&
                    students[n].grade <= 10 &&
                    strlen(students[n].name) > 0) {
                    n++;
                    saveStudents(students, n);
                    printf("Student added and saved!\n");
                } else {
                    printf("Invalid name or grade!\n");
                }
            } else {
                printf("Student list is full!\n");
            }

        } else if (option == 2) {
            if (n == 0) {
                printf("No students available.\n");
            }

            for (int i = 0; i < n; i++) {
                printf("%d. %s - Grade: %d\n",
                       i + 1,
                       students[i].name,
                       students[i].grade);
            }

        } else if (option == 3) {
            if (n == 0) {
                printf("No grades available.\n");
            } else {
                float sum = 0;

                for (int i = 0; i < n; i++) {
                    sum += students[i].grade;
                }

                printf("Average grade: %.2f\n", sum / n);
            }

        } else if (option != 0) {
            printf("Invalid option!\n");
        }

    } while (option != 0);

    printf("Goodbye!\n");
    return 0;
}

