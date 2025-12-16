#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_PROVIDERS 50
#define MAX_REVIEWS 30
#define FILENAME "ProvidersRegisteredLists.txt"

struct ServiceProvider {
    char name[50];
    char serviceType[50];
    char contact[20];
    float rating;
    int ratingCount;
    char reviews[MAX_REVIEWS][100];
    int reviewCount;
};

void rewriteFile(struct ServiceProvider providers[], int count) {
    FILE *fp = fopen(FILENAME, "w");
    if (!fp) return;
    fprintf(fp, "\n------------------------------------------\n");
    fprintf(fp, "        Provider Registered List\n");
    fprintf(fp, "------------------------------------------\n");
    for (int i = 0; i < count; i++) {
        fprintf(fp, "ID Number: %d\n", i + 1);
        fprintf(fp, "Name: %s\n", providers[i].name);
        fprintf(fp, "Service Type: %s\n", providers[i].serviceType);
        fprintf(fp, "Contact: %s\n", providers[i].contact);
        fprintf(fp, "Rating: %.1f (%d ratings)\n", providers[i].rating, providers[i].ratingCount);
        fprintf(fp, "Reviews:\n");
        if (providers[i].reviewCount == 0) {
            fprintf(fp, "- No reviews yet\n");
        } else {
            for (int j = 0; j < providers[i].reviewCount; j++) {
                fprintf(fp, "- %s\n", providers[i].reviews[j]);
            }
        }
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
        if (strncmp(line, "ID Number:", 10) != 0) continue;
        fgets(line, sizeof(line), fp);
        sscanf(line, "Name: %[^\n]", providers[count].name);
        fgets(line, sizeof(line), fp);
        sscanf(line, "Service Type: %[^\n]", providers[count].serviceType);
        fgets(line, sizeof(line), fp);
        sscanf(line, "Contact: %[^\n]", providers[count].contact);
        fgets(line, sizeof(line), fp);
        sscanf(line, "Rating: %f (%d ratings)", &providers[count].rating, &providers[count].ratingCount);
        providers[count].reviewCount = 0;
        fgets(line, sizeof(line), fp);
        while (fgets(line, sizeof(line), fp)) {
            if (strncmp(line, "---", 3) == 0) break;
            if (strncmp(line, "- ", 2) == 0) {
                line[strcspn(line, "\n")] = 0;
                if (strcmp(line + 2, "No reviews yet") != 0) { 
                    strcpy(providers[count].reviews[providers[count].reviewCount], line + 2);
                    providers[count].reviewCount++;
                }
            }
        }
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
        if (sscanf(line, "ID Number: %d", &n) == 1) lastNum = n;
    }
    fclose(fp);
    return lastNum;
}

void appendProvider(struct ServiceProvider *p, int number) {
    FILE *fp = fopen(FILENAME, "a");
    if (!fp) return;
    fprintf(fp, "ID Number: %d\n", number);
    fprintf(fp, "Name: %s\n", p->name);
    fprintf(fp, "Service Type: %s\n", p->serviceType);
    fprintf(fp, "Contact: %s\n", p->contact);
    fprintf(fp, "Rating: %.1f (%d ratings)\n", p->rating, p->ratingCount);
    fprintf(fp, "Reviews:\n");
    if (p->reviewCount == 0) {
        fprintf(fp, "- No reviews yet\n");
    } else {
        for (int i = 0; i < p->reviewCount; i++) {
            fprintf(fp, "- %s\n", p->reviews[i]);
        }
    }
    fprintf(fp, "---\n");
    fclose(fp);
}

void displayProvider(struct ServiceProvider *p, int id) {
    printf("\nID Number: %d\n", id);
    printf("Name: %s\n", p->name);
    printf("Service Type: %s\n", p->serviceType);
    printf("Contact: %s\n", p->contact);
    printf("Rating: %.1f (%d ratings)\n", p->rating, p->ratingCount);
    printf("Reviews:\n");
    if (p->reviewCount == 0) {
        printf("- No reviews yet\n");
    } else {
        for (int j = 0; j < p->reviewCount; j++) {
            printf("- %s\n", p->reviews[j]);
        }
    }
    printf("---\n");
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
        fprintf(fp, "\n------------------------------------------\n");
        fprintf(fp, "        Provider Registered List\n");
        fprintf(fp, "------------------------------------------\n");
        fclose(fp);
    } else fclose(fp_check);

    count = loadProviders(providers);

    do {
        printf("\n------------------------------------------\n");
        printf("     LOCAL SERVICES DIRECTORY SYSTEM\n");
        printf("------------------------------------------\n");
        printf("Please choose an option.\n");
        printf("1. Register Service Provider\n");
        printf("2. View All Providers\n");
        printf("3. Search by Service Type\n");
        printf("4. Add Rating and Review\n");
        printf("5. Admin Panel\n");
        printf("6. Exit\n\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            printf("\nInvalid choice. Try again.\nReturning to Main Menu...\n");
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
                    if (strlen(providers[count].name) == 0) {
                        printf("\nName cannot be empty. Registration cancelled.\nReturning to Main Menu...\n");
                        break;
                    }

                    printf("Enter Service Type: ");
                    fgets(providers[count].serviceType, 50, stdin);
                    providers[count].serviceType[strcspn(providers[count].serviceType, "\n")] = 0;
                    if (strlen(providers[count].serviceType) == 0) {
                        printf("\nService type cannot be empty. Registration cancelled.\nReturning to Main Menu...\n");
                        break;
                    }

                    printf("Enter Contact Number: ");
                    fgets(providers[count].contact, 20, stdin);
                    providers[count].contact[strcspn(providers[count].contact, "\n")] = 0;
                    if (strlen(providers[count].contact) == 0) {
                        printf("\nContact number cannot be empty. Registration cancelled.\nReturning to Main Menu...\n");
                        break;
                    }

                    int valid = 1;
                    for (int i = 0; providers[count].contact[i] != '\0'; i++) {
                        if (!isdigit(providers[count].contact[i])) {
                            valid = 0;
                            break;
                        }
                    }

                    if (!valid) {
                        printf("\nInvalid contact number. Numbers only.\nReturning to Main Menu...\n");
                        break;
                    }

                    providers[count].rating = 0.0;
                    providers[count].ratingCount = 0;
                    providers[count].reviewCount = 0;

                    int newNumber = getLastNumber() + 1;
                    appendProvider(&providers[count], newNumber);
                    count++;

                    printf("\nProvider Registered Successfully!\nReturning to Main Menu...\n");
                } else {
                    printf("\nDirectory is full. Cannot register more providers.\nReturning to Main Menu...\n");
                }
                break;

            case 2:
                if (count == 0) {
                    printf("\nNo providers registered yet.\nReturning to Main Menu...\n");
                } else {
                    printf("\n       All providers registered:\n");
                    printf("------------------------------------------\n");
                    for (int i = 0; i < count; i++) {
                        displayProvider(&providers[i], i + 1);
                    }
                    printf("\nReturning to Main Menu...\n");
                }
                break;

            case 3:
                printf("\nEnter Service Type to Search: ");
                fgets(searchType, 50, stdin);
                searchType[strcspn(searchType, "\n")] = 0;
                int found = 0;

                printf("\n            Search Result:\n");
                printf("------------------------------------------\n");
                for (int i = 0; i < count; i++) {
                    if (strstr(providers[i].serviceType, searchType)) {
                        displayProvider(&providers[i], i + 1);
                        found = 1;
                    }
                }
                if (!found) printf("\nNo providers found for that service type.\n");
                printf("\nReturning to Main Menu...\n");
                break;

            case 4:
                if (count == 0) {
                    printf("\nNo providers available to rate.\nReturning to Main Menu...\n");
                    break;
                }
                int num;
                float newRating;

                printf("\nEnter Provider ID Number to Rate (1-%d): ", count);
                if (scanf("%d", &num) != 1) {
                    while (getchar() != '\n');
                    printf("\nInvalid provider ID Number. Numbers only.\nReturning to Main Menu...\n");
                    break;
                }
                getchar();

                if (num > 0 && num <= count) {
                    struct ServiceProvider *p = &providers[num - 1];

                    printf("Enter your rating (1.0-5.0): ");
                    if (scanf("%f", &newRating) != 1) {
                        while (getchar() != '\n');
                        printf("\nInvalid rating input. Numbers only.\nReturning to Main Menu...\n");
                        break;
                    }
                    getchar();

                    if (newRating < 1.0 || newRating > 5.0) {
                        printf("\nInvalid rating. Please enter between 1.0 and 5.0.\nReturning to Main Menu...\n");
                    } else {
                        p->rating = ((p->rating * p->ratingCount) + newRating) / (p->ratingCount + 1);
                        p->ratingCount++;

                        printf("Enter short review/feedback: ");
                        char newReview[100];
                        fgets(newReview, 100, stdin);
                        newReview[strcspn(newReview, "\n")] = 0;

                        if (p->reviewCount < MAX_REVIEWS) {
                            strcpy(p->reviews[p->reviewCount], newReview);
                            p->reviewCount++;
                        } else {
                            printf("\nMaximum reviews reached. Cannot add more.\n");
                        }

                        rewriteFile(providers, count);
                        printf("\nThank you! Rating added successfully.\nReturning to Main Menu...\n");
                    }
                } else {
                    printf("\nInvalid provider number.\nReturning to Main Menu...\n");
                }
                break;

            case 5:
                printf("\nEnter Admin Password: ");
                fgets(adminPass, 20, stdin);
                adminPass[strcspn(adminPass, "\n")] = 0;

                if (strcmp(adminPass, "admin123") == 0) {
                    printf("\nAccess granted!\nProceed to Admin Panel...\n");

                    do {
                        printf("\n------------------------------------------\n");
                        printf("              ADMIN PANEL\n");
                        printf("------------------------------------------\n");
                        printf("Please choose an admin option.\n");
                        printf("1. View All Providers\n");
                        printf("2. Edit Provider Info\n");
                        printf("3. Delete Provider\n");
                        printf("4. Return to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &adminChoice);
                        getchar();

                        switch (adminChoice) {
                            case 1:
                                if (count == 0) {
                                    printf("\nNo providers registered yet.\nReturning to Admin Menu...\n");
                                } else {
                                    printf("\n       All providers registered:\n");
                                    printf("------------------------------------------\n");
                                    for (int i = 0; i < count; i++) {
                                        displayProvider(&providers[i], i + 1);
                                    }
                                    printf("Returning to Admin Menu...\n");
                                }
                                break;

                            case 2: {
                                int editNum;
                                printf("\nEnter Provider ID Number to Edit (1-%d): ", count);
                                scanf("%d", &editNum);
                                getchar();

                                if (editNum > 0 && editNum <= count) {
                                    char temp[50];

                                    printf("Enter new name: ");
                                    fgets(providers[editNum - 1].name, 50, stdin);
                                    providers[editNum - 1].name[strcspn(providers[editNum - 1].name, "\n")] = 0;
                                    if (strlen(providers[editNum - 1].name) == 0) {
                                        printf("\nName cannot be empty. Edit cancelled.\nReturning to Admin Menu...\n");
                                        break;
                                    }

                                    printf("Enter new service type: ");
                                    fgets(providers[editNum - 1].serviceType, 50, stdin);
                                    providers[editNum - 1].serviceType[strcspn(providers[editNum - 1].serviceType, "\n")] = 0;
                                    if (strlen(providers[editNum - 1].serviceType) == 0) {
                                        printf("\nService type cannot be empty. Edit cancelled.\nReturning to Admin Menu...\n");
                                        break;
                                    }

                                    printf("Enter Contact Number: ");
                                    fgets(providers[editNum - 1].contact, 20, stdin);
                                    providers[editNum - 1].contact[strcspn(providers[editNum - 1].contact, "\n")] = 0;
                                    if (strlen(providers[editNum - 1].contact) == 0) {
                                        printf("\nContact number cannot be empty. Edit cancelled.\nReturning to Admin Menu...\n");
                                        break;
                                    }

                                    int valid = 1;
                                    for (int i = 0; providers[editNum - 1].contact[i] != '\0'; i++) {
                                        if (!isdigit(providers[editNum - 1].contact[i])) {
                                            valid = 0;
                                            break;
                                        }
                                    }

                                    if (!valid) {
                                        printf("\nInvalid contact number. Numbers only.\nReturning to Admin Menu...\n");
                                        break;
                                    }

                                    rewriteFile(providers, count);
                                    printf("\nProvider updated successfully!\nReturning to Admin Menu...\n");
                                } else {
                                    printf("\nInvalid provider ID number.\nReturning to Admin Menu...\n");
                                }
                                break;
                            }

                            case 3: {
                                int delNum;
                                printf("\nEnter Provider ID Number to Delete (1-%d): ", count);
                                scanf("%d", &delNum);
                                getchar();
                                if (delNum > 0 && delNum <= count) {
                                    for (int i = delNum - 1; i < count - 1; i++) providers[i] = providers[i + 1];
                                    count--;
                                    rewriteFile(providers, count);
                                    printf("\nProvider deleted successfully!\nReturning to Admin Menu...\n");

                                } else printf("\nInvalid provider ID number.\nReturning to Admin Menu...\n");
                                break;
                            }

                            case 4:
                            printf("\nReturning to Main Menu...\n");
                                break;
                            default:
                                printf("\nInvalid admin choice.\nReturning to Admin Menu...\n");
                        }
                    } while (adminChoice != 4);
                } else printf("\nIncorrect password. Access denied.\nReturning to Main Menu...\n");
                break;

            case 6:
                printf("\nAre you sure you want to exit? (Y/N): ");
                scanf(" %c", &confirmExit);
                confirmExit = toupper(confirmExit);

                if (confirmExit == 'Y') {
                    printf("\nGood Bye! Come back again...\n\n");
                    return 0;
                } else {
                    printf("\nReturning to Main Menu...\n");
                }
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }
    } while (1);

    return 0;
}
