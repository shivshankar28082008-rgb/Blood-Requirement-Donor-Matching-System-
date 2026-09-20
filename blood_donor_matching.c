#include <stdio.h>
#include <string.h>

#define MAX_DONORS 100
#define MAX_REQUESTS 100

struct Donor {
    int id;
    char name[80];
    char bloodGroup[5];
    char location[60];
    char phone[20];
    int availableUnits;
};

struct Request {
    int id;
    char requester[80];
    char bloodGroup[5];
    char location[60];
    int unitsRequired;
};

struct Donor donors[MAX_DONORS] = {
    {1, "Aman Kumar", "O+", "Phagwara", "9876500011", 2},
    {2, "Priya Sharma", "A+", "Phagwara", "9876500012", 1},
    {3, "Rohit Verma", "B+", "Jalandhar", "9876500013", 2},
    {4, "Neha Singh", "AB+", "Phagwara", "9876500014", 1},
    {5, "Arjun Das", "O-", "Ludhiana", "9876500015", 3},
    {6, "Simran Kaur", "B-", "Jalandhar", "9876500016", 1},
    {7, "Vikas Yadav", "A-", "Phagwara", "9876500017", 2},
    {8, "Kiran Devi", "AB-", "Ludhiana", "9876500018", 1}
};

int donorCount = 8;
struct Request requests[MAX_REQUESTS];
int requestCount = 0;

void clearInputBuffer(void) {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

void readLine(char *text, int size) {
    fgets(text, size, stdin);
    text[strcspn(text, "\n")] = '\0';
}

void showInstructions(void) {
    printf("\n==============================================\n");
    printf("     BLOOD DONOR MATCHING - INSTRUCTIONS\n");
    printf("==============================================\n");
    printf("1. Add a blood requirement request.\n");
    printf("2. Select required blood group and location.\n");
    printf("3. System searches matching donor records.\n");
    printf("4. Matching donors must have the same blood\n");
    printf("   group and enough available units.\n");
    printf("5. View all sample donor records.\n");
    printf("==============================================\n");
}

void showDonors(void) {
    printf("\n==============================================\n");
    printf("                 DONOR LIST\n");
    printf("==============================================\n");

    for (int i = 0; i < donorCount; i++) {
        printf("\nID: %d\n", donors[i].id);
        printf("Name          : %s\n", donors[i].name);
        printf("Blood Group   : %s\n", donors[i].bloodGroup);
        printf("Location      : %s\n", donors[i].location);
        printf("Phone         : %s\n", donors[i].phone);
        printf("Available Unit: %d\n", donors[i].availableUnits);
    }
}

void findMatchingDonors(void) {
    struct Request r;
    int matches = 0;

    if (requestCount >= MAX_REQUESTS) {
        printf("\nRequest limit reached.\n");
        return;
    }

    clearInputBuffer();

    r.id = requestCount + 1;

    printf("\nRequester Name: ");
    readLine(r.requester, sizeof(r.requester));

    printf("Blood Group Required: ");
    readLine(r.bloodGroup, sizeof(r.bloodGroup));

    printf("Location: ");
    readLine(r.location, sizeof(r.location));

    printf("Units Required: ");
    if (scanf("%d", &r.unitsRequired) != 1 || r.unitsRequired <= 0) {
        clearInputBuffer();
        printf("\nInvalid units required.\n");
        return;
    }

    requests[requestCount++] = r;

    printf("\n==============================================\n");
    printf("              MATCHING DONORS\n");
    printf("==============================================\n");

    for (int i = 0; i < donorCount; i++) {
        if (strcmp(donors[i].bloodGroup, r.bloodGroup) == 0 &&
            donors[i].availableUnits >= r.unitsRequired &&
            (strlen(r.location) == 0 ||
             strstr(donors[i].location, r.location) != NULL)) {

            printf("\n✅ Match Found\n");
            printf("Donor Name    : %s\n", donors[i].name);
            printf("Blood Group   : %s\n", donors[i].bloodGroup);
            printf("Location      : %s\n", donors[i].location);
            printf("Available Unit: %d\n", donors[i].availableUnits);
            printf("Phone         : %s\n", donors[i].phone);
            matches++;
        }
    }

    if (matches == 0)
        printf("\n⚠️ No matching sample donor found.\n");
    else
        printf("\nTotal Matches: %d\n", matches);
}

void showRequests(void) {
    printf("\n==============================================\n");
    printf("              BLOOD REQUIREMENTS\n");
    printf("==============================================\n");

    if (requestCount == 0) {
        printf("No requests created yet.\n");
        return;
    }

    for (int i = 0; i < requestCount; i++) {
        printf("\nRequest %d\n", requests[i].id);
        printf("----------------------------------------------\n");
        printf("Requester     : %s\n", requests[i].requester);
        printf("Blood Group   : %s\n", requests[i].bloodGroup);
        printf("Location      : %s\n", requests[i].location);
        printf("Units Required: %d\n", requests[i].unitsRequired);
    }
}

int main(void) {
    int choice;

    while (1) {
        printf("\n\n==============================================\n");
        printf("       BLOOD REQUIREMENT & DONOR MATCHING\n");
        printf("==============================================\n");
        printf("1. Find Matching Donors\n");
        printf("2. View Donor List\n");
        printf("3. View Blood Requirements\n");
        printf("4. Instructions\n");
        printf("5. Exit\n");
        printf("==============================================\n");
        printf("Enter your choice: ");

        if (scanf("%d", &choice) != 1) {
            clearInputBuffer();
            printf("\nInvalid input. Please enter a number.\n");
            continue;
        }

        switch (choice) {
            case 1:
                findMatchingDonors();
                break;
            case 2:
                showDonors();
                break;
            case 3:
                showRequests();
                break;
            case 4:
                showInstructions();
                break;
            case 5:
                printf("\nThank you for using the system!\n");
                return 0;
            default:
                printf("\nInvalid choice! Please select 1-5.\n");
        }
    }
}
