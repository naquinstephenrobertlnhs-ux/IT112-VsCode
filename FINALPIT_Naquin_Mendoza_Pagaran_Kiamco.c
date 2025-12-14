#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROVIDERS 50
#define FILENAME "ProvidersRegisteredLists.txt"

struct ServiceProvider {
    char name[50];
    char serviceType[50];
    char contact[20];
    float rating;
    int ratingCount;
    char review[100];
};

void rewriteFile(struct ServiceProvider providers[], int count) {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) return;
    fprintf(fp, "        Provider Registered List\n");
    fprintf(fp, "------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "Number: %d\n", i + 1);
        fprintf(fp, "Name: %s\n", providers[i].name);
        fprintf(fp, "Service Type: %s\n", providers[i].serviceType);
        fprintf(fp, "Contact: %s\n", providers[i].contact);
        fprintf(fp, "Rating: %.1f (%d ratings)\n", providers[i].rating, providers[i].ratingCount);
        fprintf(fp, "Reviews: %s\n", providers[i].review);
        fprintf(fp, "---\n");
    }
    fclose(fp);
}

int loadProviders(struct ServiceProvider providers[]) {
    FILE *fp = fopen(FILENAME, "r");
    int count = 0;
    char line[200];
    if (!fp) return 0;
    while (fgets(line, sizeof(line), fp)) {
        if (sscanf(line, "Number: %*d") != 1) continue;
        fgets(line, sizeof(line), fp);
        sscanf(line, "Name: %[^\n]", providers[count].name);
        fgets(line, sizeof(line), fp);
        sscanf(line, "Service Type: %[^\n]", providers[count].serviceType);
        fgets(line, sizeof(line), fp);
        sscanf(line, "Contact: %[^\n]", providers[count].contact);
        fgets(line, sizeof(line), fp);
        sscanf(line, "Rating: %f (%d ratings)", &providers[count].rating, &providers[count].ratingCount);
        fgets(line, sizeof(line), fp);
        sscanf(line, "Reviews: %[^\n]", providers[count].review);
        fgets(line, sizeof(line), fp);
        count++;
        if (count >= MAX_PROVIDERS) break;
    }
    fclose(fp);
    return count;
}

int getLastNumber() {
    FILE *fp = fopen(FILENAME, "r");
    if (!fp) return 0;
    char line[200];
    int lastNum = 0;
    while (fgets(line, sizeof(line), fp)) {
        int n;
        if (sscanf(line, "Number: %d", &n) == 1) lastNum = n;
    }
    fclose(fp);
    return lastNum;
}

void appendProvider(struct ServiceProvider *p, int number) {
    FILE *fp = fopen(FILENAME, "a");
    if (!fp) return;
    fprintf(fp, "Number: %d\n", number);
    fprintf(fp, "Name: %s\n", p->name);
    fprintf(fp, "Service Type: %s\n", p->serviceType);
    fprintf(fp, "Contact: %s\n", p->contact);
    fprintf(fp, "Rating: %.1f (%d ratings)\n", p->rating, p->ratingCount);
    fprintf(fp, "Reviews: %s\n", p->review);
    fprintf(fp, "---\n");
    fclose(fp);
}

int main() {
    struct ServiceProvider providers[MAX_PROVIDERS];
    int count = 0;
    int choice;
    char searchType[50];
    char confirmExit;
    char adminPass[20];
    int adminChoice;

    FILE *fp_check = fopen(FILENAME, "r");
    if (!fp_check) {
        FILE *fp = fopen(FILENAME, "w");
        fprintf(fp, "        Provider Registered List\n");
        fprintf(fp, "------------------------------------------\n");
        fclose(fp);
    } else fclose(fp_check);

    count = loadProviders(providers);

    do {
        printf("\n------------------------------------------\n");
        printf("    LOCAL SERVICES DIRECTORY SYSTEM\n");
        printf("------------------------------------------\n");
        printf("1. Register Service Provider\n");
        printf("2. View All Providers\n");
        printf("3. Search by Service Type\n");
        printf("4. Add Rating and Review\n");
        printf("5. Admin Panel\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid choice. Try again.\n");
            while (getchar() != '\n');
            continue;
        }
        getchar();

        switch (choice) {
            case 1:
                if (count < MAX_PROVIDERS) {
                    printf("\nEnter Provider Name: ");
                    fgets(providers[count].name, 50, stdin);
                    providers[count].name[strcspn(providers[count].name, "\n")] = 0;
                    printf("Enter Service Type: ");
                    fgets(providers[count].serviceType, 50, stdin);
                    providers[count].serviceType[strcspn(providers[count].serviceType, "\n")] = 0;
                    printf("Enter Contact Number: ");
                    fgets(providers[count].contact, 20, stdin);
                    providers[count].contact[strcspn(providers[count].contact, "\n")] = 0;
                    providers[count].rating = 0.0;
                    providers[count].ratingCount = 0;
                    strcpy(providers[count].review, "No reviews yet");

                    int newNumber = getLastNumber() + 1;
                    appendProvider(&providers[count], newNumber);
                    count++;

                    printf("\nProvider Registered Successfully!\n");
                } else {
                    printf("\nDirectory is full. Cannot register more providers.\n");
                }
                break;

            case 2:
                if (count == 0) {
                    printf("\nNo providers registered yet.\n");
                } else {
                    for (int i = 0; i < count; i++) {
                        printf("\nNumber: %d\n", i + 1);
                        printf("Name: %s\n", providers[i].name);
                        printf("Service Type: %s\n", providers[i].serviceType);
                        printf("Contact: %s\n", providers[i].contact);
                        printf("Rating: %.1f (%d ratings)\n", providers[i].rating, providers[i].ratingCount);
                        printf("Reviews: %s\n", providers[i].review);
                        printf("---\n");
                    }
                }
                break;

            case 3:
                printf("\nEnter Service Type to Search: ");
                fgets(searchType, 50, stdin);
                searchType[strcspn(searchType, "\n")] = 0;
                int found = 0;
                for (int i = 0; i < count; i++) {
                    if (strstr(providers[i].serviceType, searchType)) {
                        printf("\nNumber: %d\n", i + 1);
                        printf("Name: %s\n", providers[i].name);
                        printf("Service Type: %s\n", providers[i].serviceType);
                        printf("Contact: %s\n", providers[i].contact);
                        printf("Rating: %.1f (%d ratings)\n", providers[i].rating, providers[i].ratingCount);
                        printf("Reviews: %s\n", providers[i].review);
                        printf("---\n");
                        found = 1;
                    }
                }
                if (!found) printf("\nNo providers found for that service type.\n");
                break;

            case 4:
                if (count == 0) {
                    printf("\nNo providers available to rate.\n");
                    break;
                }
                int num;
                float newRating;
                printf("\nEnter Provider Number to Rate (1-%d): ", count);
                scanf("%d", &num);
                getchar();
                if (num > 0 && num <= count) {
                    struct ServiceProvider *p = &providers[num - 1];
                    printf("Enter Rating (1.0-5.0): ");
                    scanf("%f", &newRating);
                    getchar();
                    if (newRating < 1.0 || newRating > 5.0) {
                        printf("\nInvalid rating. Please enter 1.0-5.0\n");
                    } else {
                        p->rating = ((p->rating * p->ratingCount) + newRating) / (p->ratingCount + 1);
                        p->ratingCount++;
                        printf("Enter Review: ");
                        fgets(p->review, 100, stdin);
                        p->review[strcspn(p->review, "\n")] = 0;
                        rewriteFile(providers, count);
                        printf("\nThank you! Rating added successfully.\n");
                    }
                } else printf("\nInvalid provider number.\n");
                break;

            case 5:
                printf("\nEnter Admin Password: ");
                fgets(adminPass, 20, stdin);
                adminPass[strcspn(adminPass, "\n")] = 0;
                if (strcmp(adminPass, "admin123") == 0) {
                    do {
                        printf("\n-------------------------\n");
                        printf("      ADMIN PANEL\n");
                        printf("-------------------------\n");
                        printf("1. View All Providers\n");
                        printf("2. Edit Provider Info\n");
                        printf("3. Delete Provider\n");
                        printf("4. Return to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &adminChoice);
                        getchar();
                        switch (adminChoice) {
                            case 1:
                                if (count == 0) printf("\nNo providers registered yet.\n");
                                else for (int i = 0; i < count; i++) {
                                    printf("\nNumber: %d\n", i + 1);
                                    printf("Name: %s\n", providers[i].name);
                                    printf("Service Type: %s\n", providers[i].serviceType);
                                    printf("Contact: %s\n", providers[i].contact);
                                    printf("Rating: %.1f (%d ratings)\n", providers[i].rating, providers[i].ratingCount);
                                    printf("Reviews: %s\n", providers[i].review);
                                    printf("---\n");
                                }
                                break;
                            case 2: {
                                int editNum;
                                printf("\nEnter Provider Number to Edit (1-%d): ", count);
                                scanf("%d", &editNum);
                                getchar();
                                if (editNum > 0 && editNum <= count) {
                                    printf("Enter new name: ");
                                    fgets(providers[editNum - 1].name, 50, stdin);
                                    providers[editNum - 1].name[strcspn(providers[editNum - 1].name, "\n")] = 0;
                                    printf("Enter new service type: ");
                                    fgets(providers[editNum - 1].serviceType, 50, stdin);
                                    providers[editNum - 1].serviceType[strcspn(providers[editNum - 1].serviceType, "\n")] = 0;
                                    printf("Enter new contact number: ");
                                    fgets(providers[editNum - 1].contact, 20, stdin);
                                    providers[editNum - 1].contact[strcspn(providers[editNum - 1].contact, "\n")] = 0;
                                    rewriteFile(providers, count);
                                    printf("\nProvider updated successfully!\n");
                                } else printf("\nInvalid provider number.\n");
                                break;
                            }
                            case 3: {
                                int delNum;
                                printf("\nEnter Provider Number to Delete (1-%d): ", count);
                                scanf("%d", &delNum);
                                getchar();
                                if (delNum > 0 && delNum <= count) {
                                    for (int i = delNum - 1; i < count - 1; i++) providers[i] = providers[i + 1];
                                    count--;
                                    rewriteFile(providers, count);
                                    printf("\nProvider deleted successfully!\n");
                                } else printf("\nInvalid provider number.\n");
                                break;
                            }
                            case 4:
                                break;
                            default:
                                printf("\nInvalid admin choice.\n");
                        }
                    } while (adminChoice != 4);
                } else printf("\nIncorrect password. Access denied.\n");
                break;

            case 6:
                printf("\nAre you sure you want to exit? (Y/N): ");
                scanf(" %c", &confirmExit);
                confirmExit = toupper(confirmExit);
                if (confirmExit == 'Y') return 0;
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } while (1);
    return 0;
}
