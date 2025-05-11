#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
char seats[SIZE][SIZE]; // '-'=�Ŧ�A'*'=�w�w���A'@'=��ĳ�y��

// ��l�Ʈy��
void initSeats() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            seats[i][j] = '-';
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

// �۰ʦw�Ʈy��
void arrangeForYou() {
    int n;
    printf("�п�J�n�w�ƴX�Ӯy��]1~4�^�G");
    scanf("%d", &n);

    if (n < 1 || n > 4) {
        printf("��J���~�A�п�J1~4�������Ʀr�C\n");
        return;
    }

    srand(time(NULL));
    int tryCount = 500;
    while (tryCount--) {
        int row = rand() % SIZE;
        int col = rand() % (SIZE - n + 1);
        int i, ok = 1;

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

            char ans;
            printf("�O�_�����o�ǫ�ĳ�y��H(y/n)�G");
            scanf(" %c", &ans);

            if (ans == 'y' || ans == 'Y') {
                for (i = 0; i < n; i++) {
                    seats[row][col + i] = '*';
                }
            } else {
                for (i = 0; i < n; i++) {
                    seats[row][col + i] = '-';
                }
            }
            return;
        }
    }

    printf("�䤣��X�A���y��C\n");
}

int main() {
    char choice;
    initSeats();

    do {
        printf("\n=== �y��w���t�� ===\n");
        printf("a. ��ܩҦ��y��\n");
        printf("b. �۰ʦw�Ʈy��\n");
        printf("d. ���}\n");
        printf("�п�ܡG");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                showSeats();
                break;
            case 'b':
                arrangeForYou();
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

