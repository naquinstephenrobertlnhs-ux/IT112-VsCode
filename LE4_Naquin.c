#include <stdio.h>

int main() {
    char name[50], section[20];
    float g1, g2, g3, g4, average;
    
    printf("Enter Complete Name: ");
    fgets(name, sizeof(name), stdin);

    printf("Enter Section: ");
    fgets(section, sizeof(section), stdin);
    
    printf("Enter 1st Quarter Grade: ");
    scanf("%f", &g1);
    printf("Enter 2nd Quarter Grade: ");
    scanf("%f", &g2);
    printf("Enter 3rd Quarter Grade: ");
    scanf("%f", &g3);
    printf("Enter 4th Quarter Grade: ");
    scanf("%f", &g4);

    average = (g1 + g2 + g3 + g4) / 4;

    printf("\nStudent: %s", name);
    printf("Section: %s", section);
    printf("General Average: %.2f\n", average);

    if (average >= 90 && average <= 100) {
        printf("Remarks: Outstanding\n");
    } else if (average >= 85 && average <= 89) {
        printf("Remarks: Very Satisfactory\n");
    } else if (average >= 80 && average <= 84) {
        printf("Remarks: Satisfactory\n");
    } else if (average >= 75 && average <= 79) {
        printf("Remarks: Fair\n");
    } else {
        printf("Remarks: Failed\n");
    }
    return 0;
}