#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 9
char seats[SIZE][SIZE]; // '-'=空位，'*'=已預約，'@'=建議座位

// 初始化座位
void initSeats() {
    int i, j;
    for (i = 0; i < SIZE; i++)
        for (j = 0; j < SIZE; j++)
            seats[i][j] = '-';
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

// 自動安排座位
void arrangeForYou() {
    int n;
    printf("請輸入要安排幾個座位（1~4）：");
    scanf("%d", &n);

    if (n < 1 || n > 4) {
        printf("輸入錯誤，請輸入1~4之間的數字。\n");
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

            printf("建議座位如下：\n");
            showSeats();

            char ans;
            printf("是否接受這些建議座位？(y/n)：");
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

    printf("找不到合適的座位。\n");
}

int main() {
    char choice;
    initSeats();

    do {
        printf("\n=== 座位預約系統 ===\n");
        printf("a. 顯示所有座位\n");
        printf("b. 自動安排座位\n");
        printf("d. 離開\n");
        printf("請選擇：");
        scanf(" %c", &choice);

        switch (choice) {
            case 'a':
                showSeats();
                break;
            case 'b':
                arrangeForYou();
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

