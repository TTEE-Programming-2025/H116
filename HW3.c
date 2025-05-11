#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define RESERVED 10
#define PASSWORD "2025"

char seats[SIZE][SIZE]; /* '-'=�Ŧ�A'*'=�w�w���A'@'=��ĳ�y�� */

void clearScreen(void) {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void loginScreen(void) {
    clearScreen();
    printf("==============================================\n");
    printf("=                                            =\n");
    printf("=     ???? �w��Ө�y��w���t�� ????       =\n");
    printf("=                                            =\n");
    printf("=      ���t�λݿ�J4��ƱK�X�~��i�J       =\n");
    printf("=                                            =\n");
    printf("=        �ФŬ��|�K�X�A�O�@�z����T        =\n");
    printf("=                                            =\n");
    printf("=        ���~�W�L�T���N�۰������t��        =\n");
    printf("=                                            =\n");
    printf("==============================================\n");
    printf("\n�п�J�K�X�G");
}

int checkPassword(void) {
    int attempts = 3;
    char input[10];

    while (attempts > 0) {
        printf("�п�J4��ƱK�X�G");
        scanf("%s", input);
        if (strcmp(input, PASSWORD) == 0) {
            printf("�n�J���\�I�w��ϥήy��w���t�ΡC\n");
            clearScreen();
            return 1;
        } else {
            attempts--;
            printf("�K�X���~�I�Ѿl���ơG%d\n", attempts);
        }
    }

    printf("���~���ƹL�h�A�t�ε����C\n");
    return 0;
}

void initSeats(void) {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            seats[i][j] = '-';
        }
    }
}

void generateReservedSeats(void) {
    int count, row, col;
    count = 0;
    srand((unsigned int)time(NULL));

    while (count < RESERVED) {
        row = rand() % SIZE;
        col = rand() % SIZE;
        if (seats[row][col] == '-') {
            seats[row][col] = '*';
            count++;
        }
    }
}

void showSeats(void) {
    int i, j;

    printf("   ");
    for (i = 0; i < SIZE; i++) {
        printf("%d", i + 1);
    }
    printf("\n");

    for (i = SIZE - 1; i >= 0; i--) {
        printf("%2d ", i + 1);
        for (j = 0; j < SIZE; j++) {
            printf("%c", seats[i][j]);
        }
        printf("\n");
    }
}

void arrangeForYou(void) {
    int n, row, col, i, tryCount, ok;
    char ans;

    printf("�п�J�n�w�ƴX�Ӯy��]1~4�^�G");
    while (scanf("%d", &n) != 1 || n < 1 || n > 4) {
        printf("��J���~�A�п�J1~4�������Ʀr�G");
        while (getchar() != '\n');
    }

    srand((unsigned int)time(NULL));
    tryCount = 500;

    while (tryCount--) {
        row = rand() % SIZE;
        col = rand() % (SIZE - n + 1);
        ok = 1;

        for (i = 0; i < n; i++) {
            if (seats[row][col + i] != '-') {
                ok = 0;
                break;
            }
        }

        if (ok) {
            for (i = 0; i < n; i++) {
                seats[row][col + i] = '@';
            }

            printf("��ĳ�y��p�U�G\n");
            showSeats();
            printf("�O�_�����o�ǫ�ĳ�y��H(y/n)�G");
            scanf(" %c", &ans);
            while (getchar() != '\n');

            if (ans == 'y' || ans == 'Y') {
                for (i = 0; i < n; i++) {
                    seats[row][col + i] = '*';
                }
                clearScreen();
                return;
            } else {
                for (i = 0; i < n; i++) {
                    seats[row][col + i] = '-';
                }
                return;
            }
        }
    }

    printf("�L�k���X�A���y��w�ơC\n");
}

void chooseSeats(void) {
    int row, col;
    char input[10];

    while (1) {
        printf("�п�J�z�Q��ܪ��y��(�榡�� '�C-��', �Ҧp 1-2)�A�ο�J 'q' ��^�D���G\n");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'q' || input[0] == 'Q') {
            return;
        }

        if (sscanf(input, "%d-%d", &row, &col) != 2 || row < 1 || row > SIZE || col < 1 || col > SIZE) {
            printf("�榡���~�A�Э��s��J�C\n");
            continue;
        }

        if (seats[row - 1][col - 1] == '*') {
            printf("�Ӯy��w�Q�w���C\n");
        } else {
            seats[row - 1][col - 1] = '*';
            printf("���\�w���y�� %d-%d�C\n", row, col);
            showSeats();
            return;
        }
    }
}

int main(void) {
    char choice;

    loginScreen();
    if (!checkPassword()) {
        return 0;
    }

    initSeats();
    generateReservedSeats();

    while (1) {
        printf("\n=== �y��w���t�� ===\n");
        printf("a. ��ܩҦ��y��\n");
        printf("b. �۰ʦw�Ʈy��\n");
        printf("c. ��ʿ�ܮy��\n");
        printf("d. ���}\n");
        printf("�п�ܡG");
        scanf(" %c", &choice);
        while (getchar() != '\n');

        if (choice == 'a') {
            showSeats();
        } else if (choice == 'b') {
            arrangeForYou();
        } else if (choice == 'c') {
            chooseSeats();
        } else if (choice == 'd') {
            char confirm;
            while (1) {
                printf("Continue? (y/n)�G");
                scanf(" %c", &confirm);
                while (getchar() != '\n');
                if (confirm == 'y' || confirm == 'Y') {
                    break;
                } else if (confirm == 'n' || confirm == 'N') {
                    printf("�P�¨ϥΡA�A���I\n");
                    return 0;
                } else {
                    printf("��J���~�A�п�J 'y' �� 'n'�C\n");
                }
            }
        } else {
            printf("��J���~�A�Э��s��ܡC\n");
        }
    }

    return 0;
}

