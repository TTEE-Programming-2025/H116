#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define RESERVED 10
#define MAX_SEATS 4
#define PASSWORD "2025"

char seats[SIZE][SIZE]; // '-'=�Ŧ�A'*'=�w�w���A'@'=��ĳ�y��

// �M���ù��]�ھڧ@�~�t�ο�ܩR�O�^
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux/Mac
    #endif
}

// ��ܵn�J�e���]����ơ^
void loginScreen() {
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

// �K�X����
int checkPassword() {
    int attempts = 3;
    char input[10];
    while (attempts > 0) {
        printf("�п�J4��ƱK�X�G");
        scanf("%s", input);
        if (strcmp(input, PASSWORD) == 0) {
            printf("�n�J���\�I�w��ϥήy��w���t�ΡC\n");
            clearScreen(); // �K�X���T��M���ù�
            return 1;
        } else {
            attempts--;
            printf("�K�X���~�I�Ѿl���ơG%d\n", attempts);
        }
    }
    printf("���~���ƹL�h�A�t�ε����C\n");
    return 0;
}

// ��l�Ʈy��
void initSeats() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            seats[i][j] = '-';
}

// �H���ͦ��w�w�q�y��
void generateReservedSeats() {
    int count = 0;
    srand(time(NULL));

    while (count < RESERVED) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (seats[row][col] == '-') {
            seats[row][col] = '*'; // �w�w�y��
            count++;
        }
    }
}

// ��ܮy���
void showSeats() {
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

// �H���w�Ʈy��]�̦h�|�Ӯy��^
void arrangeForYou() {
    int n;
    int row, col, i;
    char ans;
    
    printf("�п�J�n�w�ƴX�Ӯy��]1~4�^�G");
    scanf("%d", &n);

    if (n < 1 || n > 4) {
        printf("��J���~�A�п�J1~4�������Ʀr�C\n");
        return;
    }

    srand(time(NULL));

    if (n == 1 || n == 2 || n == 3) {
        // �H���w�Ƴs�򪺮y��
        int tryCount = 500;
        while (tryCount--) {
            row = rand() % SIZE;
            col = rand() % (SIZE - n + 1);
            int ok = 1;

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

                if (ans == 'y' || ans == 'Y') {
                    for (i = 0; i < n; i++) {
                        seats[row][col + i] = '*';
                    }
                    clearScreen(); // ��ܧ�����M���ù��æ^��D���
                    return;
                } else {
                    for (i = 0; i < n; i++) {
                        seats[row][col + i] = '-';
                    }
                    return;
                }
            }
        }
    } else if (n == 4) {
        // �w��4�Ӯy��A��C�ΦP�C
        int tryCount = 500;
        while (tryCount--) {
            // ���զw�Ʀb�P�@�C
            row = rand() % SIZE;
            col = rand() % (SIZE - 4 + 1);
            int ok = 1;

            for (i = 0; i < 4; i++) {
                if (seats[row][col + i] != '-') {
                    ok = 0;
                    break;
                }
            }

            if (ok) {
                for (i = 0; i < 4; i++) {
                    seats[row][col + i] = '@';
                }

                printf("��ĳ�y��p�U�G\n");
                showSeats();

                printf("�O�_�����o�ǫ�ĳ�y��H(y/n)�G");
                scanf(" %c", &ans);

                if (ans == 'y' || ans == 'Y') {
                    for (i = 0; i < 4; i++) {
                        seats[row][col + i] = '*';
                    }
                    clearScreen(); // ��ܧ�����M���ù��æ^��D���
                    return;
                } else {
                    for (i = 0; i < 4; i++) {
                        seats[row][col + i] = '-';
                    }
                    return;
                }
            }

            // ���զw�Ʀb�۾F��C
            row = rand() % (SIZE - 1);
            col = rand() % SIZE;
            if (seats[row][col] == '-' && seats[row + 1][col] == '-') {
                seats[row][col] = '@';
                seats[row + 1][col] = '@';
                printf("��ĳ�y��p�U�G\n");
                showSeats();

                printf("�O�_�����o�ǫ�ĳ�y��H(y/n)�G");
                scanf(" %c", &ans);

                if (ans == 'y' || ans == 'Y') {
                    seats[row][col] = '*';
                    seats[row + 1][col] = '*';
                    clearScreen(); // ��ܧ�����M���ù��æ^��D���
                    return;
                } else {
                    seats[row][col] = '-';
                    seats[row + 1][col] = '-';
                    return;
                }
            }
        }
    }

    printf("�L�k���X�A���y��w�ơC\n");
}

int main() {
    char choice;

    loginScreen(); // ��ܬ��ƪ��n�J�e��
    if (!checkPassword()) {
        return 0;
    }

    initSeats();  // ��l�Ʈy��
    generateReservedSeats();  // �H���ͦ��w�w�y��

    do {
        printf("\n=== �y��w���t�� ===\n");
        printf("a. ��ܩҦ��y��\n");
        printf("b. �۰ʦw�Ʈy��\n");
        printf("d. ���}\n");
        printf("�п�ܡG");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                showSeats(); // ��ܮy���
                break;
            case 'b':
                arrangeForYou(); // �w�Ʈy��
                break;
            case 'd':
                printf("�t�ε����A�A���C\n");
                return 0;
            default:
                printf("��J���~�A�Э��s��ܡC\n");
        }
    } while (1);

    return 0;
}

