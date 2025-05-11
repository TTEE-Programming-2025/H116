#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define RESERVED 10
#define PASSWORD "2025"

char seats[SIZE][SIZE]; /* The seating layout, with '-' as available, '*' as reserved, and '@' as suggested */

/* Clears the screen depending on the operating system */
void clearScreen(void) {
#ifdef _WIN32
    system("cls"); // Clear screen for Windows
#else
    system("clear"); // Clear screen for Linux/Mac
#endif
}

/* Displays the login screen */
void loginScreen(void) {
    clearScreen();
    printf("==============================================\n");
    printf("=                                            =\n");
    printf("=            Welcome to the Seat Booking      =\n");
    printf("=                                            =\n");
    printf("=      This system requires a 4-digit password =\n");
    printf("=                                            =\n");
    printf("=        Please do not disclose the password  =\n");
    printf("=                                            =\n");
    printf("=        After 3 failed attempts, the system  =\n");
    printf("=            will automatically shut down.    =\n");
    printf("=                                            =\n");
    printf("==============================================\n");
    printf("\nEnter password: ");
}

/* Checks if the entered password is correct */
int checkPassword(void) {
    int attempts = 3;
    char input[10];

    while (attempts > 0) {
        printf("Please enter the 4-digit password: ");
        scanf("%s", input);
        if (strcmp(input, PASSWORD) == 0) {
            printf("Login successful! Welcome to the seat booking system.\n");
            clearScreen();
            return 1;
        } else {
            attempts--;
            printf("Incorrect password! Remaining attempts: %d\n", attempts);
        }
    }

    printf("Too many failed attempts, system will close.\n");
    return 0; // Exit if the password is incorrect after 3 attempts
}

/* Initializes all seats to available */
void initSeats(void) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            seats[i][j] = '-'; // Mark all seats as available initially
        }
    }
}

/* Randomly generates reserved seats */
void generateReservedSeats(void) {
    int count = 0, row, col;
    srand((unsigned int)time(NULL));

    while (count < RESERVED) {
        row = rand() % SIZE;
        col = rand() % SIZE;
        if (seats[row][col] == '-') { // Check if the seat is available
            seats[row][col] = '*'; // Mark the seat as reserved
            count++;
        }
    }
}

/* Displays the seating arrangement */
void showSeats(void) {
    int i, j;

    printf("   ");
    for (i = 0; i < SIZE; i++) {
        printf("%d", i + 1); // Display column numbers
    }
    printf("\n");

    for (i = SIZE - 1; i >= 0; i--) {
        printf("%2d ", i + 1); // Display row numbers
        for (j = 0; j < SIZE; j++) {
            printf("%c", seats[i][j]); // Print the status of each seat
        }
        printf("\n");
    }
}

/* Automatically arranges seats for the user */
void arrangeForYou(void) {
    int n, row, col, i, tryCount, ok;
    char ans;

    printf("Please enter how many seats you want to arrange (1-4): ");
    while (scanf("%d", &n) != 1 || n < 1 || n > 4) {
        printf("Invalid input, please enter a number between 1 and 4: ");
        while (getchar() != '\n'); // Clear the input buffer
    }

    srand((unsigned int)time(NULL));
    tryCount = 500; // Limit the number of attempts to find a suitable arrangement

    while (tryCount--) {
        row = rand() % SIZE;
        col = rand() % (SIZE - n + 1);
        ok = 1;

        for (i = 0; i < n; i++) {
            if (seats[row][col + i] != '-') { // Check if the seats are available
                ok = 0;
                break;
            }
        }

        if (ok) {
            for (i = 0; i < n; i++) {
                seats[row][col + i] = '@'; // Mark suggested seats
            }

            printf("Suggested seats are as follows:\n");
            showSeats();
            printf("Do you accept these suggested seats? (y/n): ");
            scanf(" %c", &ans); // Get user input for acceptance
            while (getchar() != '\n'); // Clear the input buffer

            if (ans == 'y' || ans == 'Y') {
                for (i = 0; i < n; i++) {
                    seats[row][col + i] = '*'; // Confirm and mark seats as reserved
                }
                clearScreen();
                return;
            } else {
                for (i = 0; i < n; i++) {
                    seats[row][col + i] = '-'; // Reject the suggested seats and make them available again
                }
                return;
            }
        }
    }

    printf("Could not find a suitable seat arrangement.\n");
}

/* Allows the user to manually select seats */
void chooseSeats(void) {
    int row, col;
    char input[10];

    while (1) {
        printf("Please enter the seat you want to choose (format 'row-column', e.g. 1-2), or enter 'q' to return to the main menu:\n");
        fgets(input, sizeof(input), stdin); // Get user input

        if (input[0] == 'q' || input[0] == 'Q') {
            return; // Exit if user chooses to return to the menu
        }

        if (sscanf(input, "%d-%d", &row, &col) != 2 || row < 1 || row > SIZE || col < 1 || col > SIZE) {
            printf("Invalid input, please try again.\n");
            continue;
        }

        if (seats[row - 1][col - 1] == '*') {
            printf("This seat is already reserved.\n");
        } else {
            seats[row - 1][col - 1] = '*'; // Reserve the seat if it's available
            printf("Successfully reserved seat %d-%d.\n", row, col);
            showSeats(); // Show updated seating chart
            return;
        }
    }
}

int main(void) {
    char choice;

    loginScreen(); // Display the login screen
    if (!checkPassword()) { // Validate the password
        return 0; // Exit if the password is incorrect
    }

    initSeats(); // Initialize all seats as available
    generateReservedSeats(); // Randomly reserve some seats

    // Main menu loop
    while (1) {
        printf("\n=== Seat Booking System ===\n");
        printf("a. Show all seats\n");
        printf("b. Auto arrange seats\n");
        printf("c. Manually select seats\n");
        printf("d. Exit\n");
        printf("Please select: ");
        scanf(" %c", &choice);
        while (getchar() != '\n'); // Clear the input buffer

        if (choice == 'a') {
            showSeats(); // Display all the seats
        } else if (choice == 'b') {
            arrangeForYou(); // Automatically arrange seats
        } else if (choice == 'c') {
            chooseSeats(); // Let the user manually choose seats
        } else if (choice == 'd') {
            printf("Exiting the system...\n");
            break; // Exit the program
        }
    }

    return 0;
}

