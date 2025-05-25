#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>  // isdigit()

#ifdef _WIN32
#define CLEAR_SCREEN() system("cls")
#else
#define CLEAR_SCREEN() system("clear")
#endif

#define MAX_STUDENTS 10  // �̦h�ǥͼ�
#define MIN_STUDENTS 5   // �̤־ǥͼ�

// �ǥͦs��m�W�B�Ǹ��B���Z�M����
typedef struct {
    char name[50];
    char id[7];
    int math, physics, english;
    float avg;
} Student;

Student students[MAX_STUDENTS]; // �x�s�ǥ�
int n = 0; // ��ǥͤH��

// �P�_�r��O�_�����Ʀr
int is_numeric(const char *str) {
    int i;
    for (i = 0; str[i] != 0; i++) {
        if (!isdigit((unsigned char)str[i]))
            return 0;
    }
    return 1;
}

// �Ȱ�
void pause() {
    printf("�Ы����N���~��...");
    getchar();  
}

// ��@�ǥͥ�������
void calc_avg(Student *s) {
    s->avg = (s->math + s->physics + s->english) / 3.0f;
}

// ��J���w�d���ƨ禡�A�����~�|���ƭn�D��J
int input_int_in_range(int min, int max) {
    int val;
    while(1) {
        if(scanf("%d", &val) == 1 && val >= min && val <= max) {
            while(getchar() != '\n'); 
            return val;
        } else {
            printf("��J���~�A�п�J %d ~ %d ��������ơG", min, max);
            while(getchar() != '\n'); 
        }
    }
}

// ��Ҧ��ǥ͸��
void input_student_data() {
    CLEAR_SCREEN();
    printf("�п�J�ǥͤH�� (%d ~ %d)�G", MIN_STUDENTS, MAX_STUDENTS);
    n = input_int_in_range(MIN_STUDENTS, MAX_STUDENTS);

    int i;
    for(i = 0; i < n; i++) {
        printf("�� %d ��ǥͩm�W�G", i+1);
        fgets(students[i].name, sizeof(students[i].name), stdin);
        students[i].name[strcspn(students[i].name, "\n")] = 0; 

        // ��J���ˬd�Ǹ����פάO�_���Ʀr
        while(1) {
            printf("�� %d ��ǥ;Ǹ� (6 ���)�G", i+1);
            fgets(students[i].id, sizeof(students[i].id), stdin);
            students[i].id[strcspn(students[i].id, "\n")] = 0;
            if(strlen(students[i].id) == 6 && is_numeric(students[i].id)) break;
            printf("�Ǹ��榡���~�A�п�J 6 ��Ʀr�I\n");
        }

        // ���O��J�T�즨�Z�A�d��0~100
        printf("�� %d ��ǥͼƾǦ��Z (0~100)�G", i+1);
        students[i].math = input_int_in_range(0, 100);

        printf("�� %d ��ǥͪ��z���Z (0~100)�G", i+1);
        students[i].physics = input_int_in_range(0, 100);

        printf("�� %d ��ǥͭ^�妨�Z (0~100)�G", i+1);
        students[i].english = input_int_in_range(0, 100);

        calc_avg(&students[i]); // ����
        printf("\n");
    }
    CLEAR_SCREEN();
}

// �Ҧ��ǥ͸��
void display_students() {
    CLEAR_SCREEN();
    if(n == 0) {
        printf("�ثe�S���ǥ͸�ơI\n");
    } else {
        int i;
        printf("�m�W\t�Ǹ�\t�ƾ�\t���z\t�^��\t����\n");
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

// ��J�m�W�A�����ܸ�ơA�䤣����ܴ���
void search_student() {
    char search_name[50];
    int found = 0;
    CLEAR_SCREEN();
    printf("�п�J�n�j�M���m�W�G");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0; 

    int i;
    for(i = 0; i < n; i++) {
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

// �Ѱ���C�Ƨǥ������Z
int compare_avg_desc(const void *a, const void *b) {
    Student *s1 = (Student*)a;
    Student *s2 = (Student*)b;
    if(s1->avg < s2->avg) return 1;
    else if(s1->avg > s2->avg) return -1;
    else return 0;
}

// 6. ��X���Z�ƦW�A�u��ܩm�W�B�Ǹ��B�������Z�A�̥������Z�Ѱ���C�ƦC
void grade_ranking() {
    CLEAR_SCREEN();
    if(n == 0) {
        printf("�ثe�S���ǥ͸�ơI\n");
        pause();
        CLEAR_SCREEN();
        return;
    }
    
    Student sorted[MAX_STUDENTS];
    memcpy(sorted, students, sizeof(Student)*n);

    qsort(sorted, n, sizeof(Student), compare_avg_desc);

    printf("���Z�ƦW�]�̥������Z�Ѱ���C�^�G\n");
    printf("�W��\t�m�W\t�Ǹ�\t����\n");  
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
        printf("�w��ϥΦ��Z�t�ΡA�п�J4��ƱK�X(2025)�G");
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

    // �D���j��
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
        while(getchar() != '\n'); 

        switch(choice) {
            case 'a': input_student_data(); break;
            case 'b': display_students(); break;
            case 'c': search_student(); break;
            case 'd': grade_ranking(); break;
            case 'e': {
                char confirm;
                while(1) {
                    printf("�T�w���}�H (y/n)�G");
                    confirm = getchar();
                    while(getchar() != '\n');
                    if(confirm == 'y' || confirm == 'Y') {
                        printf("�t�ε����A�A���I\n");
                        return 0;
                    } else if(confirm == 'n' || confirm == 'N') {
                        break;
                    } else {
                        printf("��J���~�A�п�J y �� n�C\n");
                    }
                }
                break;
            }
            default:
                printf("��J���~�A�Э��s��J�I\n");
                pause();
        }
    }
    return 0;
}

