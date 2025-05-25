#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

#define MAX_STUDENTS 10
#define MIN_STUDENTS 5
#define PASSWORD "2025"

typedef struct {
    char name[50];
    int id;
    int math;
    int physics;
    int english;
    float average;
} Student;

Student students[MAX_STUDENTS];
int student_count = 0;

void clearScreen() {
    system(CLEAR);
}

void pauseScreen() {
    printf("按下 Enter 繼續...");
    while(getchar() != '\n'); 
    getchar();
}

int login() {
    char input[10];
    int tries = 3;
    while (tries > 0) {
        clearScreen();
        printf("====================================\n");
        printf("        請輸入 4 位數密碼 (預設 2025)     \n");
        printf("剩餘嘗試次數: %d\n", tries);
        printf("密碼: ");
        scanf("%s", input);
        while(getchar() != '\n'); 
        if (strcmp(input, PASSWORD) == 0) {
            printf("登入成功！歡迎使用系統！\n");
            pauseScreen();
            return 1;
        } else {
            printf("密碼錯誤！\n");
            tries--;
            pauseScreen();
        }
    }
    printf("連續錯誤三次，系統鎖定。\n");
    return 0;
}

void showMenu() {
    clearScreen();
    printf("------------[Grade System]----------\n");
    printf("| a. Enter student grades          |\n");
    printf("| b. Display student grades        |\n");
    printf("| c. Search for student grades     |\n");
    printf("| d. Grade ranking                 |\n");
    printf("| e. Exit system                   |\n");
    printf("------------------------------------\n");
    printf("請輸入選項 (a~e): ");
}

void inputGrades() {
    clearScreen();
    int n;
    printf("請輸入學生人數 (5~10): ");
    scanf("%d", &n);
    while(getchar() != '\n'); 

    if (n < MIN_STUDENTS || n > MAX_STUDENTS) {
        printf("錯誤：學生人數必須介於 5 到 10。\n");
        pauseScreen();
        return;
    }

    student_count = n;

    for (int i = 0; i < n; i++) {
        printf("\n輸入第 %d 位學生資料：\n", i + 1);

        printf("姓名：");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        size_t len = strlen(students[i].name);
        if (len > 0 && students[i].name[len-1] == '\n') {
            students[i].name[len-1] = '\0';
        }

        do {
            printf("學號(6位整數)：");
            if (scanf("%d", &students[i].id) != 1) {
                printf("請輸入數字。\n");
                while(getchar() != '\n');
                continue;
            }
            if (students[i].id < 100000 || students[i].id > 999999) {
                printf("學號必須是6位整數。\n");
            }
        } while (students[i].id < 100000 || students[i].id > 999999);
        while(getchar() != '\n');

        int score;
        do {
            printf("數學成績 (0~100): ");
            if (scanf("%d", &score) != 1) {
                printf("請輸入數字。\n");
                while(getchar() != '\n');
                continue;
            }
            if (score < 0 || score > 100) {
                printf("成績必須介於0到100。\n");
            }
        } while (score < 0 || score > 100);
        students[i].math = score;
        while(getchar() != '\n');

        do {
            printf("物理成績 (0~100): ");
            if (scanf("%d", &score) != 1) {
                printf("請輸入數字。\n");
                while(getchar() != '\n');
                continue;
            }
            if (score < 0 || score > 100) {
                printf("成績必須介於0到100。\n");
            }
        } while (score < 0 || score > 100);
        students[i].physics = score;
        while(getchar() != '\n');

        do {
            printf("英文成績 (0~100): ");
            if (scanf("%d", &score) != 1) {
                printf("請輸入數字。\n");
                while(getchar() != '\n');
                continue;
            }
            if (score < 0 || score > 100) {
                printf("成績必須介於0到100。\n");
            }
        } while (score < 0 || score > 100);
        students[i].english = score;
        while(getchar() != '\n');

        students[i].average = (students[i].math + students[i].physics + students[i].english) / 3.0f;
    }
    printf("\n輸入完成！\n");
    pauseScreen();
}

void displayGrades() {
    clearScreen();
    if (student_count == 0) {
        printf("尚未輸入任何學生資料。\n");
        pauseScreen();
        return;
    }
    printf("%-10s %-10s %-8s %-8s %-8s %-8s\n", "姓名", "學號", "數學", "物理", "英文", "平均");
    for (int i = 0; i < student_count; i++) {
        printf("%-10s %-10d %-8d %-8d %-8d %-8.1f\n",
            students[i].name,
            students[i].id,
            students[i].math,
            students[i].physics,
            students[i].english,
            students[i].average
        );
    }
    pauseScreen();
}

int main() {
    if (!login()) {
        return 0;
    }
    char choice;
    do {
        showMenu();
        scanf(" %c", &choice);
        while(getchar() != '\n');
        switch (choice) {
            case 'a':
                inputGrades();
                break;
            case 'b':
                displayGrades();
                break;
            case 'c':
                printf("搜尋功能尚未實作。\n");
                pauseScreen();
                break;
            case 'd':
                printf("排名功能尚未實作。\n");
                pauseScreen();
                break;
            case 'e':
                printf("系統結束，謝謝使用！\n");
                break;
            default:
                printf("輸入錯誤，請重新輸入。\n");
                pauseScreen();
                break;
        }
    } while (choice != 'e');
    return 0;
}

