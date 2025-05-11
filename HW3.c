#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define RESERVED 10
#define PASSWORD "2025"

char seats[SIZE][SIZE]; /* '-'=空位，'*'=已預約，'@'=建議座位 */

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
    printf("=     ???? 歡迎來到座位預約系統 ????       =\n");
    printf("=                                            =\n");
    printf("=      本系統需輸入4位數密碼才能進入       =\n");
    printf("=                                            =\n");
    printf("=        請勿洩漏密碼，保護您的資訊        =\n");
    printf("=                                            =\n");
    printf("=        錯誤超過三次將自動關閉系統        =\n");
    printf("=                                            =\n");
    printf("==============================================\n");
    printf("\n請輸入密碼：");
}

int checkPassword(void) {
    int attempts = 3;
    char input[10];

    while (attempts > 0) {
        printf("請輸入4位數密碼：");
        scanf("%s", input);
        if (strcmp(input, PASSWORD) == 0) {
            printf("登入成功！歡迎使用座位預約系統。\n");
            clearScreen();
            return 1;
        } else {
            attempts--;
            printf("密碼錯誤！剩餘次數：%d\n", attempts);
        }
    }

    printf("錯誤次數過多，系統結束。\n");
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

    printf("請輸入要安排幾個座位（1~4）：");
    while (scanf("%d", &n) != 1 || n < 1 || n > 4) {
        printf("輸入錯誤，請輸入1~4之間的數字：");
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

            printf("建議座位如下：\n");
            showSeats();
            printf("是否接受這些建議座位？(y/n)：");
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

    printf("無法找到合適的座位安排。\n");
}

void chooseSeats(void) {
    int row, col;
    char input[10];

    while (1) {
        printf("請輸入您想選擇的座位(格式為 '列-行', 例如 1-2)，或輸入 'q' 返回主選單：\n");
        fgets(input, sizeof(input), stdin);
        if (input[0] == 'q' || input[0] == 'Q') {
            return;
        }

        if (sscanf(input, "%d-%d", &row, &col) != 2 || row < 1 || row > SIZE || col < 1 || col > SIZE) {
            printf("格式錯誤，請重新輸入。\n");
            continue;
        }

        if (seats[row - 1][col - 1] == '*') {
            printf("該座位已被預約。\n");
        } else {
            seats[row - 1][col - 1] = '*';
            printf("成功預約座位 %d-%d。\n", row, col);
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
        printf("\n=== 座位預約系統 ===\n");
        printf("a. 顯示所有座位\n");
        printf("b. 自動安排座位\n");
        printf("c. 手動選擇座位\n");
        printf("d. 離開\n");
        printf("請選擇：");
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
                printf("Continue? (y/n)：");
                scanf(" %c", &confirm);
                while (getchar() != '\n');
                if (confirm == 'y' || confirm == 'Y') {
                    break;
                } else if (confirm == 'n' || confirm == 'N') {
                    printf("感謝使用，再見！\n");
                    return 0;
                } else {
                    printf("輸入錯誤，請輸入 'y' 或 'n'。\n");
                }
            }
        } else {
            printf("輸入錯誤，請重新選擇。\n");
        }
    }

    return 0;
}

