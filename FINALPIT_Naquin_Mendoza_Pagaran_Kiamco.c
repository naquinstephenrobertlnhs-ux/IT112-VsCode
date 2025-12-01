#include <stdio.h>      
#include <string.h>     
#include <ctype.h>      

#define MAX_PROVIDERS 50 

struct ServiceProvider {
    char name[50];        
    char serviceType[50]; 
    char contact[20];     
    float rating;         
    int ratingCount;      
    char review[100];     
};

int main() {
    struct ServiceProvider providers[MAX_PROVIDERS];
    int count = 0;            
    int choice;               
    char searchType[50];      
    char confirmExit;         
    char adminPass[20];       
    int adminChoice;          

    do {
        printf("\n========================================\n");
        printf("   LOCAL SERVICES DIRECTORY SYSTEM\n");
        printf("========================================\n");
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
                    fgets(providers[count].name, sizeof(providers[count].name), stdin);
                    providers[count].name[strcspn(providers[count].name, "\n")] = 0;

                    printf("Enter Service Type (e.g., Plumber, Electrician): ");
                    fgets(providers[count].serviceType, sizeof(providers[count].serviceType), stdin);
                    providers[count].serviceType[strcspn(providers[count].serviceType, "\n")] = 0;

                    printf("Enter Contact Number: ");
                    fgets(providers[count].contact, sizeof(providers[count].contact), stdin);
                    providers[count].contact[strcspn(providers[count].contact, "\n")] = 0;

                    if (strlen(providers[count].name) == 0 ||
                        strlen(providers[count].serviceType) == 0 ||
                        strlen(providers[count].contact) == 0) {
                        printf("\nError: All fields are required. Registration cancelled.\n");
                    } else {
                        providers[count].rating = 0.0;
                        providers[count].ratingCount = 0;
                        strcpy(providers[count].review, "No reviews yet");
                        printf("\n Provider Registered Successfully!\n");
                        count++;
                    }
                } else {
                    printf("\nDirectory is full. Cannot register more providers.\n");
                }
                break;

            case 2:
                printf("\n--- List of Service Providers ---\n");
                if (count == 0) {
                    printf("No providers registered yet.\n");
                } else {
                    for (int i = 0; i < count; i++) {
                        printf("%d. %s - %s - %s\n", i + 1,
                               providers[i].name,
                               providers[i].serviceType,
                               providers[i].contact);
                        printf("    Average Rating: %.1f (%d ratings) | Review: %s\n",
                               providers[i].rating, providers[i].ratingCount, providers[i].review);
                    }
                }
                break;

            case 3: {
                printf("\nEnter Service Type to Search: ");
                fgets(searchType, sizeof(searchType), stdin);
                searchType[strcspn(searchType, "\n")] = 0;

                int found = 0;
                printf("\n--- Search Results ---\n");
                for (int i = 0; i < count; i++) {
                    if (strstr(providers[i].serviceType, searchType) != NULL) {
                        printf("%s - %s - %s\n",
                               providers[i].name,
                               providers[i].serviceType,
                               providers[i].contact);
                        printf("    Average Rating: %.1f (%d ratings) | Review: %s\n",
                               providers[i].rating, providers[i].ratingCount, providers[i].review);
                        found = 1;
                    }
                }
                if (!found) {
                    printf("No providers found for that service type.\n");
                }
                break;
            }

            case 4:
                if (count == 0) {
                    printf("\nNo providers available to rate.\n");
                } else {
                    int num;
                    float newRating;

                    printf("\nEnter Provider Number to Rate (1-%d): ", count);
                    scanf("%d", &num);
                    getchar();

                    if (num > 0 && num <= count) {
                        printf("Enter your rating (1.0-5.0): ");
                        scanf("%f", &newRating);
                        getchar();

                        if (newRating < 1.0 || newRating > 5.0) {
                            printf("\n Invalid rating. Please enter between 1.0 and 5.0.\n");
                        } else {
                            struct ServiceProvider *p = &providers[num - 1];
                            p->rating = ((p->rating * p->ratingCount) + newRating) / (p->ratingCount + 1);
                            p->ratingCount++;

                            printf("Enter short review/feedback: ");
                            fgets(p->review, sizeof(p->review), stdin);
                            p->review[strcspn(p->review, "\n")] = 0;

                            printf("\n Thank you! Rating added successfully.\n");
                        }
                    } else {
                        printf("\nInvalid provider number.\n");
                    }
                }
                break;

            case 5: {
                printf("\nEnter Admin Password: ");
                fgets(adminPass, sizeof(adminPass), stdin);
                adminPass[strcspn(adminPass, "\n")] = 0;

                if (strcmp(adminPass, "admin123") == 0) {
                    printf("\n Access Granted to Admin Panel\n");

                    do {
                        printf("\n===================\n");
                        printf("  ----ADMIN PANEL----  ");
                        printf("\n===================\n");
                        printf("1. View All Providers\n");
                        printf("2. Edit Provider Info\n");
                        printf("3. Delete Provider\n");
                        printf("4. Return to Main Menu\n");
                        printf("Enter your choice: ");
                        scanf("%d", &adminChoice);
                        getchar();

                        switch (adminChoice) {
                            case 1:
                                printf("\n--- Registered Providers ---\n");
                                for (int i = 0; i < count; i++) {
                                    printf("%d. %s - %s - %s\n", i + 1,
                                           providers[i].name,
                                           providers[i].serviceType,
                                           providers[i].contact);
                                    printf("    %.1f (%d ratings) | Review: %s\n",
                                           providers[i].rating, providers[i].ratingCount, providers[i].review);
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

                                    printf("\n Provider updated successfully!\n");
                                } else {
                                    printf("\nInvalid provider number.\n");
                                }
                                break;
                            }

                            case 3: {
                                int delNum;
                                printf("\nEnter Provider Number to Delete (1-%d): ", count);
                                scanf("%d", &delNum);
                                getchar();
                                if (delNum > 0 && delNum <= count) {
                                    for (int i = delNum - 1; i < count - 1; i++) {
                                        providers[i] = providers[i + 1];
                                    }
                                    count--;
                                    printf("\n Provider deleted successfully!\n");
                                } else {
                                    printf("\nInvalid provider number.\n");
                                }
                                break;
                            }

                            case 4:
                                printf("\nAre you sure you want to exit the admin? (Y/N): ");
                                scanf(" %c", &confirmExit);
                                confirmExit = toupper(confirmExit);
                                if (confirmExit == 'Y') {
                                   printf("\nReturning to main menu...!\n");
                               } else {
                                   printf("\nBack to Admin Panel...\n");
                                   adminChoice = 0;
                               }
                               break;

                            default:
                                printf("\nInvalid admin choice.\n");
                                
                        }
                    } while (adminChoice != 4);
                } else {
                    printf("\n Incorrect password. Access denied.\n");
                }
                break;
            }

            case 6:
                printf("\nAre you sure you want to exit? (Y/N): ");
                scanf(" %c", &confirmExit);
                confirmExit = toupper(confirmExit);
                if (confirmExit == 'Y') {
                    printf("\nExiting Program... Goodbye!\n");
                    return 0;
                } else {
                    printf("\nReturning to main menu...\n");
                }
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while (1);

    return 0;
}
