#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define SIZE 9
#define RESERVED 10
#define MAX_SEATS 4
#define PASSWORD "2025"

char seats[SIZE][SIZE]; // '-'=空位，'*'=已預約，'@'=建議座位

// 清除螢幕（根據作業系統選擇命令）
void clearScreen() {
    #ifdef _WIN32
        system("cls"); // Windows
    #else
        system("clear"); // Linux/Mac
    #endif
}

// 顯示登入畫面（風格化）
void loginScreen() {
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

// 密碼驗證
int checkPassword() {
    int attempts = 3;
    char input[10];
    while (attempts > 0) {
        printf("請輸入4位數密碼：");
        scanf("%s", input);
        if (strcmp(input, PASSWORD) == 0) {
            printf("登入成功！歡迎使用座位預約系統。\n");
            clearScreen(); // 密碼正確後清除螢幕
            return 1;
        } else {
            attempts--;
            printf("密碼錯誤！剩餘次數：%d\n", attempts);
        }
    }
    printf("錯誤次數過多，系統結束。\n");
    return 0;
}

// 初始化座位
void initSeats() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            seats[i][j] = '-';
}

// 隨機生成已預訂座位
void generateReservedSeats() {
    int count = 0;
    srand(time(NULL));

    while (count < RESERVED) {
        int row = rand() % SIZE;
        int col = rand() % SIZE;
        if (seats[row][col] == '-') {
            seats[row][col] = '*'; // 預定座位
            count++;
        }
    }
}

// 顯示座位表
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

// 隨機安排座位（最多四個座位）
void arrangeForYou() {
    int n;
    int row, col, i;
    char ans;
    
    printf("請輸入要安排幾個座位（1~4）：");
    scanf("%d", &n);

    if (n < 1 || n > 4) {
        printf("輸入錯誤，請輸入1~4之間的數字。\n");
        return;
    }

    srand(time(NULL));

    if (n == 1 || n == 2 || n == 3) {
        // 隨機安排連續的座位
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

                printf("建議座位如下：\n");
                showSeats();

                printf("是否接受這些建議座位？(y/n)：");
                scanf(" %c", &ans);

                if (ans == 'y' || ans == 'Y') {
                    for (i = 0; i < n; i++) {
                        seats[row][col + i] = '*';
                    }
                    clearScreen(); // 顯示完畢後清除螢幕並回到主選單
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
        // 安排4個座位，兩列或同列
        int tryCount = 500;
        while (tryCount--) {
            // 嘗試安排在同一列
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

                printf("建議座位如下：\n");
                showSeats();

                printf("是否接受這些建議座位？(y/n)：");
                scanf(" %c", &ans);

                if (ans == 'y' || ans == 'Y') {
                    for (i = 0; i < 4; i++) {
                        seats[row][col + i] = '*';
                    }
                    clearScreen(); // 顯示完畢後清除螢幕並回到主選單
                    return;
                } else {
                    for (i = 0; i < 4; i++) {
                        seats[row][col + i] = '-';
                    }
                    return;
                }
            }

            // 嘗試安排在相鄰兩列
            row = rand() % (SIZE - 1);
            col = rand() % SIZE;
            if (seats[row][col] == '-' && seats[row + 1][col] == '-') {
                seats[row][col] = '@';
                seats[row + 1][col] = '@';
                printf("建議座位如下：\n");
                showSeats();

                printf("是否接受這些建議座位？(y/n)：");
                scanf(" %c", &ans);

                if (ans == 'y' || ans == 'Y') {
                    seats[row][col] = '*';
                    seats[row + 1][col] = '*';
                    clearScreen(); // 顯示完畢後清除螢幕並回到主選單
                    return;
                } else {
                    seats[row][col] = '-';
                    seats[row + 1][col] = '-';
                    return;
                }
            }
        }
    }

    printf("無法找到合適的座位安排。\n");
}

int main() {
    char choice;

    loginScreen(); // 顯示美化的登入畫面
    if (!checkPassword()) {
        return 0;
    }

    initSeats();  // 初始化座位
    generateReservedSeats();  // 隨機生成預定座位

    do {
        printf("\n=== 座位預約系統 ===\n");
        printf("a. 顯示所有座位\n");
        printf("b. 自動安排座位\n");
        printf("d. 離開\n");
        printf("請選擇：");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                showSeats(); // 顯示座位表
                break;
            case 'b':
                arrangeForYou(); // 安排座位
                break;
            case 'd':
                printf("系統結束，再見。\n");
                return 0;
            default:
                printf("輸入錯誤，請重新選擇。\n");
        }
    } while (1);

    return 0;
}

