#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // isdigit()

#ifdef _WIN32
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif

#define MAX_STUDENTS 10  // 最多學生數
#define MIN_STUDENTS 5   // 最少學生數

// 學生存放姓名、學號、成績和平均
typedef struct {
    char name[50];
    char id[7];
    int math, physics, english;
    float avg;
} Student;

Student students[MAX_STUDENTS]; // 儲存學生
int n = 0; // 實學生人數

// 判斷字串是否全為數字
int is_numeric(const char *str) {
    int i;
    for (i = 0; str[i] != 0; i++) {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }
    return 1;
}

// 暫停
void pause() {
    printf("請按任意鍵繼續...");
    getchar();  
}

// 單一學生平均分數
void calc_avg(Student *s) {
    s->avg = (s->math + s->physics + s->english) / 3.0f;
}

// 輸入指定範圍整數函式，有錯誤會重複要求輸入
int input_int_in_range(int min, int max) {
    int val;
    while(1) {
        if(scanf("%d", &val) == 1 && val >= min && val <= max) {
            while(getchar() != '\n'); 
            return val;
        } else {
            printf("輸入錯誤，請輸入 %d ~ %d 之間的整數：", min, max);
            while(getchar() != '\n'); 
        }
    }
}

// 輸所有學生資料
void input_student_data() {
    CLEAR_SCREEN();
    printf("請輸入學生人數 (%d ~ %d)：", MIN_STUDENTS, MAX_STUDENTS);
    n = input_int_in_range(MIN_STUDENTS, MAX_STUDENTS);

    int i;
    for(i = 0; i < n; i++) {
        printf("第 %d 位學生姓名：", i+1);
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0; 

        // 輸入並檢查學號長度及是否全數字
        while(1) {
            printf("第 %d 位學生學號 (6 位數)：", i+1);
            fgets(students[i].id, sizeof(students[i].id), stdin);
            students[i].id[strcspn(students[i].id, "\n")] = 0;
            if(strlen(students[i].id) == 6 && is_numeric(students[i].id)) break;
            printf("學號格式錯誤，請輸入 6 位數字！\n");
        }

        // 分別輸入三科成績，範圍0~100
        printf("第 %d 位學生數學成績 (0~100)：", i+1);
        students[i].math = input_int_in_range(0, 100);

        printf("第 %d 位學生物理成績 (0~100)：", i+1);
        students[i].physics = input_int_in_range(0, 100);

        printf("第 %d 位學生英文成績 (0~100)：", i+1);
        students[i].english = input_int_in_range(0, 100);

        calc_avg(&students[i]); // 平均
        printf("\n");
    }
    CLEAR_SCREEN();
}

// 所有學生資料
void display_students() {
    CLEAR_SCREEN();
    if(n == 0) {
        printf("目前沒有學生資料！\n");
    } else {
        int i;
        printf("姓名\t學號\t數學\t物理\t英文\t平均\n");
        for(i = 0; i < n; i++) {
            printf("%s\t%s\t%d\t%d\t%d\t%.1f\n",
                students[i].name, students[i].id,
                students[i].math, students[i].physics, students[i].english,
                students[i].avg);
        }
    }
    pause();
    CLEAR_SCREEN();
}

// 輸入姓名，找到顯示資料，找不到顯示提示
void search_student() {
    char search_name[50];
    int found = 0;
    CLEAR_SCREEN();
    printf("請輸入要搜尋的姓名：");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0; 

    int i;
    for(i = 0; i < n; i++) {
        if(strcmp(students[i].name, search_name) == 0) {
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
    if(!found) {
        printf("資料不存在！\n");
    }
    pause();
    CLEAR_SCREEN();
}

// 由高到低排序平均成績
int compare_avg_desc(const void *a, const void *b) {
    Student *s1 = (Student*)a;
    Student *s2 = (Student*)b;
    if(s1->avg < s2->avg) return 1;
    else if(s1->avg > s2->avg) return -1;
    else return 0;
}

// 6. 輸出成績排名，只顯示姓名、學號、平均成績，依平均成績由高到低排列
void grade_ranking() {
    CLEAR_SCREEN();
    if(n == 0) {
        printf("目前沒有學生資料！\n");
        pause();
        CLEAR_SCREEN();
        return;
    }
    
    Student sorted[MAX_STUDENTS];
    memcpy(sorted, students, sizeof(Student)*n);

    qsort(sorted, n, sizeof(Student), compare_avg_desc);

    printf("成績排名（依平均成績由高到低）：\n");
    printf("名次\t姓名\t學號\t平均\n");  
    int i;
    for(i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%.1f\n",
            i+1, sorted[i].name, sorted[i].id, sorted[i].avg);
    }
    pause();
    CLEAR_SCREEN();
}

int main() {
    const char correct_password[] = "2025"; 
    char input_pwd[10];
    int tries = 0;

    while(tries < 3) {
        CLEAR_SCREEN();
        printf("歡迎使用成績系統，請輸入4位數密碼(2025)：");
        fgets(input_pwd, sizeof(input_pwd), stdin);
        input_pwd[strcspn(input_pwd, "\n")] = 0;  

        if(strcmp(input_pwd, correct_password) == 0) {
            break; 
        } else {
            tries++;
            printf("密碼錯誤！剩餘嘗試次數：%d\n", 3 - tries);
            if(tries == 3) {
                printf("連續錯三次，系統結束！\n");
                return 0;
            }
            getchar(); 
        }
    }

    // 主選單迴圈
    while(1) {
        CLEAR_SCREEN();
        printf("------------[Grade System]----------\n");
        printf("| a. Enter student grades          |\n");
        printf("| b. Display student grades        |\n");
        printf("| c. Search for student grades     |\n");
        printf("| d. Grade ranking                 |\n");
        printf("| e. Exit system                   |\n");
        printf("------------------------------------\n");
        printf("請選擇功能：");
        char choice = getchar();
        while(getchar() != '\n'); 

        switch(choice) {
            case 'a': input_student_data(); break;
            case 'b': display_students(); break;
            case 'c': search_student(); break;
            case 'd': grade_ranking(); break;
            case 'e': {
                char confirm;
                while(1) {
                    printf("確定離開？ (y/n)：");
                    confirm = getchar();
                    while(getchar() != '\n');
                    if(confirm == 'y' || confirm == 'Y') {
                        printf("系統結束，再見！\n");
                        return 0;
                    } else if(confirm == 'n' || confirm == 'N') {
                        break;
                    } else {
                        printf("輸入錯誤，請輸入 y 或 n。\n");
                    }
                }
                break;
            }
            default:
                printf("輸入錯誤，請重新輸入！\n");
                pause();
        }
    }
    return 0;
}

