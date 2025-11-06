#include <stdio.h>
#include <string.h>

int main(){
    
FILE *file = fopen("students.txt", "w");
char name [100];
char section [30];

printf("Complete Name: ");
fgets(name, sizeof(name), stdin);

printf("Section: ");
fgets(section, sizeof(section), stdin);

file = fopen("students.txt", "w");
if (file == NULL){
    printf("Error opening file!\n");
    return 1;
}

fprintf(file, "Complete Name: %s", name);
fprintf(file, "Section: %s", section);
fclose(file);

printf("Information succesfully saved to students.txt\n");


file = fopen("students.txt", "r");
if (file == NULL){
    printf("Error reading file!\n");
    return 1;
}

char fname [100];
char fsection [30];

fgets(fname, sizeof(fname), file);
fgets(fsection, sizeof(fsection), file);

printf("\n%s", fname);
printf("%s", fsection);
fclose(file);

return 0;

}

