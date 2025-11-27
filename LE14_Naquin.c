#include <stdio.h>

int main() {
    
    FILE *fptr;
    fptr = fopen("student_records.txt", "a");
    int studentNumber;
    char name[50];
    char section[50];
    
    while (1) {
        printf("Enter Student Number: ");
        scanf("%d", &studentNumber);
        getchar();
        
        printf("Enter Complete Name: ");
        fgets(name, sizeof(name), stdin);
        
    
        printf("Enter Section: ");
        fgets(section, sizeof(section), stdin);
    
        fprintf(fptr, "ID Number: %d\n", studentNumber);
        fprintf(fptr, "Complete Name: %s", name);
        fprintf(fptr, "Section: %s\n", section);

        printf("\n\nRecord added and saved successfully");
    
        int input;
        printf("Add another student? [Enter 1 for Yes, 0 for No]\n");
        scanf("%d", &input);
        getchar();
        if (input == 0) {
            printf("All student records have been saved");
            break;
        }
    }
    
    return 0;
}
