#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#ifdef _WIN32
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif

#define MAX_STUDENTS 10
#define MIN_STUDENTS 5

typedef struct {
    char name[50];
    char id[7];
    int math, physics, english;
    float avg;
} Student;

Student students[MAX_STUDENTS];
int n = 0;

// 暫停畫面
void pause() {
    printf("請按任意鍵繼續...");
    getchar();
}

// 計算平均
void calc_avg(Student *s) {
    s->avg = (s->math + s->physics + s->english) / 3.0f;
}

// 整數輸入防呆
int input_int_in_range(int min, int max) {
    int val;
    char temp[100];
    while (1) {
        if (fgets(temp, sizeof(temp), stdin) != NULL) {
            if (sscanf(temp, "%d", &val) == 1 && val >= min && val <= max) {
                return val;
            }
        }
        printf("輸入錯誤，請輸入 %d ~ %d 的整數：", min, max);
    }
}

// 判斷是否為純數字字串
int is_all_digits(const char *s) {
    int i;
    for (i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

// 輸入學生資料
void input_student_data() {
    int i;
    char buffer[100];
    CLEAR_SCREEN();
    printf("請輸入學生人數 (%d ~ %d)：", MIN_STUDENTS, MAX_STUDENTS);
    n = input_int_in_range(MIN_STUDENTS, MAX_STUDENTS);

    for (i = 0; i < n; i++) {
        printf("第 %d 位學生姓名：", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(students[i].name, buffer, sizeof(students[i].name));

        while (1) {
            printf("第 %d 位學生學號 (6位數)：", i + 1);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 6 && is_all_digits(buffer)) {
                strncpy(students[i].id, buffer, sizeof(students[i].id));
                break;
            }
            printf("格式錯誤，請輸入 6 位數字！\n");
        }

        printf("數學成績 (0~100)：");
        students[i].math = input_int_in_range(0, 100);
        printf("物理成績 (0~100)：");
        students[i].physics = input_int_in_range(0, 100);
        printf("英文成績 (0~100)：");
        students[i].english = input_int_in_range(0, 100);

        calc_avg(&students[i]);
        printf("\n");
    }
    CLEAR_SCREEN();
}

// 顯示學生資料
void display_students() {
    int i;
    CLEAR_SCREEN();
    if (n == 0) {
        printf("目前沒有學生資料！\n");
    } else {
        printf("姓名\t學號\t數學\t物理\t英文\t平均\n");
        for (i = 0; i < n; i++) {
            printf("%s\t%s\t%d\t%d\t%d\t%.1f\n",
                   students[i].name, students[i].id,
                   students[i].math, students[i].physics, students[i].english,
                   students[i].avg);
        }
    }
    pause();
    CLEAR_SCREEN();
}

// 搜尋學生
void search_student() {
    char search_name[50];
    int i, found = 0;
    CLEAR_SCREEN();
    printf("請輸入要搜尋的姓名：");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(students[i].name, search_name) == 0) {
            found = 1;
            printf("姓名：%s\n", students[i].name);
            printf("學號：%s\n", students[i].id);
            printf("數學：%d\n", students[i].math);
            printf("物理：%d\n", students[i].physics);
            printf("英文：%d\n", students[i].english);
            printf("平均：%.1f\n", students[i].avg);
            break;
        }
    }
    if (!found) {
        printf("查無此人！\n");
    }
    pause();
    CLEAR_SCREEN();
}

// 排序比較用
int compare_avg_desc(const void *a, const void *b) {
    float diff = ((Student*)b)->avg - ((Student*)a)->avg;
    return (diff > 0) - (diff < 0);
}

// 排名顯示
void grade_ranking() {
    Student sorted[MAX_STUDENTS];
    int i;
    CLEAR_SCREEN();
    if (n == 0) {
        printf("目前沒有學生資料！\n");
        pause();
        CLEAR_SCREEN();
        return;
    }

    memcpy(sorted, students, sizeof(Student) * n);
    qsort(sorted, n, sizeof(Student), compare_avg_desc);

    printf("成績排名（依平均高低）：\n");
    printf("名次\t姓名\t學號\t平均\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%.1f\n", i + 1, sorted[i].name, sorted[i].id, sorted[i].avg);
    }
    pause();
    CLEAR_SCREEN();
}

// 歡迎畫面
void welcome_screen() {
    CLEAR_SCREEN();
    printf("====================================\n");
    printf("||                                ||\n");
    printf("||     歡迎使用成績管理系統      ||\n");
    printf("||                                ||\n");
    printf("||     請輸入四位數密碼登入      ||\n");
    printf("||     預設密碼為：2025          ||\n");
    printf("||                                ||\n");
    printf("||     功能選單預覽如下：        ||\n");
    printf("||     a. 輸入成績               ||\n");
    printf("||     b. 顯示成績               ||\n");
    printf("||     c. 搜尋學生               ||\n");
    printf("||     d. 成績排名               ||\n");
    printf("||     e. 離開系統               ||\n");
    printf("||                                ||\n");
    printf("||     請按任意鍵繼續…           ||\n");
    printf("||                                ||\n");
    printf("====================================\n");
    getchar(); // 等待使用者按下任意鍵
}


// 主程式
int main() {
    char input_pwd[10];
    const char correct_pwd[] = "2025";
    int tries = 0;
    char choice[10];

    welcome_screen();

    while (tries < 3) {
        printf("請輸入密碼：");
        fgets(input_pwd, sizeof(input_pwd), stdin);
        input_pwd[strcspn(input_pwd, "\n")] = 0;

        if (strcmp(input_pwd, correct_pwd) == 0) {
            break;
        } else {
            tries++;
            printf("密碼錯誤！剩餘次數：%d\n", 3 - tries);
            if (tries == 3) {
                printf("已錯誤三次，系統結束。\n");
                return 0;
            }
        }
    }

    while (1) {
        CLEAR_SCREEN();
        printf("------------[Grade System]----------\n");
        printf("| a. 輸入學生資料                  |\n");
        printf("| b. 顯示所有學生資料              |\n");
        printf("| c. 搜尋學生                      |\n");
        printf("| d. 顯示平均成績排名              |\n");
        printf("| e. 離開系統                      |\n");
        printf("------------------------------------\n");
        printf("請選擇功能：");
        fgets(choice, sizeof(choice), stdin);

        switch (choice[0]) {
            case 'a': input_student_data(); break;
            case 'b': display_students(); break;
            case 'c': search_student(); break;
            case 'd': grade_ranking(); break;
            case 'e':
                while (1) {
                    char confirm[10];
                    printf("確定離開？(y/n)：");
                    fgets(confirm, sizeof(confirm), stdin);
                    if (confirm[0] == 'y' || confirm[0] == 'Y') {
                        printf("系統結束，再見！\n");
                        return 0;
                    } else if (confirm[0] == 'n' || confirm[0] == 'N') {
                        break;
                    } else {
                        printf("請輸入 y 或 n。\n");
                    }
                }
                break;
            default:
                printf("選項錯誤，請重新輸入。\n");
                pause();
        }
    }

    return 0;
}
/*
討論與心得：

本程式是一個簡單的學生成績管理系統，有輸入、顯示、搜尋與排序等功能。
有結構陣列的設計，讓資料統一管理，方便存取與維護。

學習如何將程式功能拆成多個函式，讓主選單更加清晰，也更容易理解與除錯。
也加強輸入防呆，例如學號必須為六位數且全為數字，避免誤輸造成資料錯亂。

為了提升體驗，加入了清除螢幕與暫停提示，在操作時有明確的引導與反饋。
在密碼驗證部分，也加入了三次嘗試限制

過程中遇到的挑戰，如何實現字串輸入與清理緩衝區等細節問題，每次測試都要輸入學生資料輸入很久 

總結而言，這次作業讓我實際體會到結構化程式設計的重要性，也提升了我對C語言輸入輸出、字串操作及程式流程控制的熟悉度。
未來會持續加強錯誤處理與使用者介面設計，使程式更穩定且易用。
*/

