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
    printf("���U Enter �~��...");
    while(getchar() != '\n'); 
    getchar();
}

int login() {
    char input[10];
    int tries = 3;
    while (tries > 0) {
        clearScreen();
        printf("====================================\n");
        printf("        �п�J 4 ��ƱK�X (�w�] 2025)     \n");
        printf("�Ѿl���զ���: %d\n", tries);
        printf("�K�X: ");
        scanf("%s", input);
        while(getchar() != '\n'); 
        if (strcmp(input, PASSWORD) == 0) {
            printf("�n�J���\�I�w��ϥΨt�ΡI\n");
            pauseScreen();
            return 1;
        } else {
            printf("�K�X���~�I\n");
            tries--;
            pauseScreen();
        }
    }
    printf("�s����~�T���A�t����w�C\n");
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
    printf("�п�J�ﶵ (a~e): ");
}

void inputGrades() {
    clearScreen();
    int n;
    printf("�п�J�ǥͤH�� (5~10): ");
    scanf("%d", &n);
    while(getchar() != '\n'); 

    if (n < MIN_STUDENTS || n > MAX_STUDENTS) {
        printf("���~�G�ǥͤH�ƥ������� 5 �� 10�C\n");
        pauseScreen();
        return;
    }

    student_count = n;

    for (int i = 0; i < n; i++) {
        printf("\n��J�� %d ��ǥ͸�ơG\n", i + 1);

        printf("�m�W�G");
        fgets(students[i].name, sizeof(students[i].name), stdin);
        size_t len = strlen(students[i].name);
        if (len > 0 && students[i].name[len-1] == '\n') {
            students[i].name[len-1] = '\0';
        }

        do {
            printf("�Ǹ�(6����)�G");
            if (scanf("%d", &students[i].id) != 1) {
                printf("�п�J�Ʀr�C\n");
                while(getchar() != '\n');
                continue;
            }
            if (students[i].id < 100000 || students[i].id > 999999) {
                printf("�Ǹ������O6���ơC\n");
            }
        } while (students[i].id < 100000 || students[i].id > 999999);
        while(getchar() != '\n');

        int score;
        do {
            printf("�ƾǦ��Z (0~100): ");
            if (scanf("%d", &score) != 1) {
                printf("�п�J�Ʀr�C\n");
                while(getchar() != '\n');
                continue;
            }
            if (score < 0 || score > 100) {
                printf("���Z��������0��100�C\n");
            }
        } while (score < 0 || score > 100);
        students[i].math = score;
        while(getchar() != '\n');

        do {
            printf("���z���Z (0~100): ");
            if (scanf("%d", &score) != 1) {
                printf("�п�J�Ʀr�C\n");
                while(getchar() != '\n');
                continue;
            }
            if (score < 0 || score > 100) {
                printf("���Z��������0��100�C\n");
            }
        } while (score < 0 || score > 100);
        students[i].physics = score;
        while(getchar() != '\n');

        do {
            printf("�^�妨�Z (0~100): ");
            if (scanf("%d", &score) != 1) {
                printf("�п�J�Ʀr�C\n");
                while(getchar() != '\n');
                continue;
            }
            if (score < 0 || score > 100) {
                printf("���Z��������0��100�C\n");
            }
        } while (score < 0 || score > 100);
        students[i].english = score;
        while(getchar() != '\n');

        students[i].average = (students[i].math + students[i].physics + students[i].english) / 3.0f;
    }
    printf("\n��J�����I\n");
    pauseScreen();
}

void displayGrades() {
    clearScreen();
    if (student_count == 0) {
        printf("�|����J����ǥ͸�ơC\n");
        pauseScreen();
        return;
    }
    printf("%-10s %-10s %-8s %-8s %-8s %-8s\n", "�m�W", "�Ǹ�", "�ƾ�", "���z", "�^��", "����");
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
                printf("�j�M�\��|����@�C\n");
                pauseScreen();
                break;
            case 'd':
                printf("�ƦW�\��|����@�C\n");
                pauseScreen();
                break;
            case 'e':
                printf("�t�ε����A���¨ϥΡI\n");
                break;
            default:
                printf("��J���~�A�Э��s��J�C\n");
                pauseScreen();
                break;
        }
    } while (choice != 'e');
    return 0;
}

