#include <stdio.h>

int main() {
    FILE *fp;
    int n, i;
    char name[50], course[50];
    int age;


    fp = fopen("student_records.txt", "w");
    if (fp == NULL) {
        printf("Error opening file for writing.\n");
        return 1;
    }

    printf("Writing Student Database:\n");
    printf("How many students do you want to record? ");
    scanf("%d", &n);
    getchar(); 

    for (i = 1; i <= n; i++) {
        printf("\nStudent %d\n", i);

        printf("Enter Name: ");
        fgets(name, sizeof(name), stdin);

        printf("Enter Age: ");
        scanf("%d", &age);
        getchar();

        printf("Enter Course: ");
        fgets(course, sizeof(course), stdin);

       
        fprintf(fp, "Student %d\n", i);
        fprintf(fp, "Name: %s", name);
        fprintf(fp, "Age: %d\n", age);
        fprintf(fp, "Course: %s", course);
        fprintf(fp, "--------------------------\n");
    }

    fclose(fp);
    printf("\nStudent database successfully saved to file.\n");

    
    fp = fopen("student_records.txt", "r");
    if (fp == NULL) {
        printf("Error opening file for reading.\n");
        return 1;
    }

    printf("\nReading Student Database:\n\n");

    char line[200];
    while (fgets(line, sizeof(line), fp)) {
        printf("%s", line);
    }

    fclose(fp);
    return 0;
}
