#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

void pause() {
    printf("�Ы����N���~��...");
    getchar();
}

void calc_avg(Student *s) {
    s->avg = (s->math + s->physics + s->english) / 3.0f;
}

int input_int_in_range(int min, int max) {
    int val;
    while(1) {
        if(scanf("%d", &val) == 1 && val >= min && val <= max) {
            while(getchar() != '\n'); // �M�������
            return val;
        } else {
            printf("��J���~�A�п�J %d ~ %d ��������ơG", min, max);
            while(getchar() != '\n'); // �M�����~��J
        }
    }
}

void input_student_data() {
    CLEAR_SCREEN();
    printf("�п�J�ǥͤH�� (%d ~ %d)�G", MIN_STUDENTS, MAX_STUDENTS);
    n = input_int_in_range(MIN_STUDENTS, MAX_STUDENTS);

    for(int i = 0; i < n; i++) {
        printf("�� %d ��ǥͩm�W�G", i+1);
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0;

        while(1) {
            printf("�� %d ��ǥ;Ǹ� (6 ���)�G", i+1);
            fgets(students[i].id, sizeof(students[i].id), stdin);
            students[i].id[strcspn(students[i].id, "\n")] = 0;
            if(strlen(students[i].id) == 6) break;
            printf("�Ǹ��榡���~�A�п�J 6 ��ơI\n");
        }

        printf("�� %d ��ǥͼƾǦ��Z (0~100)�G", i+1);
        students[i].math = input_int_in_range(0, 100);

        printf("�� %d ��ǥͪ��z���Z (0~100)�G", i+1);
        students[i].physics = input_int_in_range(0, 100);

        printf("�� %d ��ǥͭ^�妨�Z (0~100)�G", i+1);
        students[i].english = input_int_in_range(0, 100);

        calc_avg(&students[i]);
        printf("\n");
    }
    CLEAR_SCREEN();
}

void display_students() {
    CLEAR_SCREEN();
    if(n == 0) {
        printf("�ثe�S���ǥ͸�ơI\n");
    } else {
        printf("�m�W\t�Ǹ�\t�ƾ�\t���z\t�^��\t����\n");
        for(int i = 0; i < n; i++) {
            printf("%s\t%s\t%d\t%d\t%d\t%.1f\n",
                students[i].name, students[i].id,
                students[i].math, students[i].physics, students[i].english,
                students[i].avg);
        }
    }
    pause();
    CLEAR_SCREEN();
}

void search_student() {
    char search_name[50];
    int found = 0;
    CLEAR_SCREEN();
    printf("�п�J�n�j�M���m�W�G");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    for(int i = 0; i < n; i++) {
        if(strcmp(students[i].name, search_name) == 0) {
            found = 1;
            printf("�m�W�G%s\n", students[i].name);
            printf("�Ǹ��G%s\n", students[i].id);
            printf("�ƾǡG%d\n", students[i].math);
            printf("���z�G%d\n", students[i].physics);
            printf("�^��G%d\n", students[i].english);
            printf("�����G%.1f\n", students[i].avg);
            break;
        }
    }
    if(!found) {
        printf("��Ƥ��s�b�I\n");
    }
    pause();
    CLEAR_SCREEN();
}

int compare_avg_desc(const void *a, const void *b) {
    Student *s1 = (Student*)a;
    Student *s2 = (Student*)b;
    if(s1->avg < s2->avg) return 1;
    else if(s1->avg > s2->avg) return -1;
    else return 0;
}

void grade_ranking() {
    CLEAR_SCREEN();
    if(n == 0) {
        printf("�ثe�S���ǥ͸�ơI\n");
        pause();
        CLEAR_SCREEN();
        return;
    }
    // �ƻs�}�C�ƧǡA�����ܭ쥻����
    Student sorted[MAX_STUDENTS];
    memcpy(sorted, students, sizeof(Student)*n);
    qsort(sorted, n, sizeof(Student), compare_avg_desc);

    printf("���Z�ƦW�]�̥������Z�Ѱ���C�^�G\n");
    printf("�W��\t�m�W\t�Ǹ�\t�ƾ�\t���z\t�^��\t����\n");
    for(int i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%d\t%d\t%d\t%.1f\n",
            i+1, sorted[i].name, sorted[i].id,
            sorted[i].math, sorted[i].physics, sorted[i].english,
            sorted[i].avg);
    }
    pause();
    CLEAR_SCREEN();
}

int main() {
    const char correct_password[] = "2025";
    char input_pwd[10];
    int tries = 0;

    // �n�J����
    while(tries < 3) {
        CLEAR_SCREEN();
        printf("�w��ϥΦ��Z�t�ΡA�п�J4��ƱK�X�G");
        fgets(input_pwd, sizeof(input_pwd), stdin);
        input_pwd[strcspn(input_pwd, "\n")] = 0;

        if(strcmp(input_pwd, correct_password) == 0) {
            break;
        } else {
            tries++;
            printf("�K�X���~�I�Ѿl���զ��ơG%d\n", 3 - tries);
            if(tries == 3) {
                printf("�s����T���A�t�ε����I\n");
                return 0;
            }
            getchar();
        }
    }

    while(1) {
        CLEAR_SCREEN();
        printf("------------[Grade System]----------\n");
        printf("| a. Enter student grades          |\n");
        printf("| b. Display student grades        |\n");
        printf("| c. Search for student grades     |\n");
        printf("| d. Grade ranking                 |\n");
        printf("| e. Exit system                   |\n");
        printf("------------------------------------\n");
        printf("�п�ܥ\��G");
        char choice = getchar();
        while(getchar() != '\n'); // �M���Ѿl��J

        switch(choice) {
            case 'a': input_student_data(); break;
            case 'b': display_students(); break;
            case 'c': search_student(); break;
            case 'd': grade_ranking(); break;
            case 'e': 
                printf("���¨ϥΡA�A���I\n");
                return 0;
            default:
                printf("�L�Ŀﶵ�A�Э��s��J�C\n");
                pause();
                break;
        }
    }

    return 0;
}

