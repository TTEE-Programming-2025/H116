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

// �Ȱ��e��
void pause() {
    printf("�Ы����N���~��...");
    getchar();
}

// �p�⥭��
void calc_avg(Student *s) {
    s->avg = (s->math + s->physics + s->english) / 3.0f;
}

// ��ƿ�J���b
int input_int_in_range(int min, int max) {
    int val;
    char temp[100];
    while (1) {
        if (fgets(temp, sizeof(temp), stdin) != NULL) {
            if (sscanf(temp, "%d", &val) == 1 && val >= min && val <= max) {
                return val;
            }
        }
        printf("��J���~�A�п�J %d ~ %d ����ơG", min, max);
    }
}

// �P�_�O�_���¼Ʀr�r��
int is_all_digits(const char *s) {
    int i;
    for (i = 0; s[i]; i++) {
        if (!isdigit(s[i])) return 0;
    }
    return 1;
}

// ��J�ǥ͸��
void input_student_data() {
    int i;
    char buffer[100];
    CLEAR_SCREEN();
    printf("�п�J�ǥͤH�� (%d ~ %d)�G", MIN_STUDENTS, MAX_STUDENTS);
    n = input_int_in_range(MIN_STUDENTS, MAX_STUDENTS);

    for (i = 0; i < n; i++) {
        printf("�� %d ��ǥͩm�W�G", i + 1);
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = 0;
        strncpy(students[i].name, buffer, sizeof(students[i].name));

        while (1) {
            printf("�� %d ��ǥ;Ǹ� (6���)�G", i + 1);
            fgets(buffer, sizeof(buffer), stdin);
            buffer[strcspn(buffer, "\n")] = 0;
            if (strlen(buffer) == 6 && is_all_digits(buffer)) {
                strncpy(students[i].id, buffer, sizeof(students[i].id));
                break;
            }
            printf("�榡���~�A�п�J 6 ��Ʀr�I\n");
        }

        printf("�ƾǦ��Z (0~100)�G");
        students[i].math = input_int_in_range(0, 100);
        printf("���z���Z (0~100)�G");
        students[i].physics = input_int_in_range(0, 100);
        printf("�^�妨�Z (0~100)�G");
        students[i].english = input_int_in_range(0, 100);

        calc_avg(&students[i]);
        printf("\n");
    }
    CLEAR_SCREEN();
}

// ��ܾǥ͸��
void display_students() {
    int i;
    CLEAR_SCREEN();
    if (n == 0) {
        printf("�ثe�S���ǥ͸�ơI\n");
    } else {
        printf("�m�W\t�Ǹ�\t�ƾ�\t���z\t�^��\t����\n");
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

// �j�M�ǥ�
void search_student() {
    char search_name[50];
    int i, found = 0;
    CLEAR_SCREEN();
    printf("�п�J�n�j�M���m�W�G");
    fgets(search_name, sizeof(search_name), stdin);
    search_name[strcspn(search_name, "\n")] = 0;

    for (i = 0; i < n; i++) {
        if (strcmp(students[i].name, search_name) == 0) {
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
    if (!found) {
        printf("�d�L���H�I\n");
    }
    pause();
    CLEAR_SCREEN();
}

// �ƧǤ����
int compare_avg_desc(const void *a, const void *b) {
    float diff = ((Student*)b)->avg - ((Student*)a)->avg;
    return (diff > 0) - (diff < 0);
}

// �ƦW���
void grade_ranking() {
    Student sorted[MAX_STUDENTS];
    int i;
    CLEAR_SCREEN();
    if (n == 0) {
        printf("�ثe�S���ǥ͸�ơI\n");
        pause();
        CLEAR_SCREEN();
        return;
    }

    memcpy(sorted, students, sizeof(Student) * n);
    qsort(sorted, n, sizeof(Student), compare_avg_desc);

    printf("���Z�ƦW�]�̥������C�^�G\n");
    printf("�W��\t�m�W\t�Ǹ�\t����\n");
    for (i = 0; i < n; i++) {
        printf("%d\t%s\t%s\t%.1f\n", i + 1, sorted[i].name, sorted[i].id, sorted[i].avg);
    }
    pause();
    CLEAR_SCREEN();
}

// �w��e��
void welcome_screen() {
    CLEAR_SCREEN();
    printf("====================================\n");
    printf("||                                ||\n");
    printf("||     �w��ϥΦ��Z�޲z�t��      ||\n");
    printf("||                                ||\n");
    printf("||     �п�J�|��ƱK�X�n�J      ||\n");
    printf("||     �w�]�K�X���G2025          ||\n");
    printf("||                                ||\n");
    printf("||     �\����w���p�U�G        ||\n");
    printf("||     a. ��J���Z               ||\n");
    printf("||     b. ��ܦ��Z               ||\n");
    printf("||     c. �j�M�ǥ�               ||\n");
    printf("||     d. ���Z�ƦW               ||\n");
    printf("||     e. ���}�t��               ||\n");
    printf("||                                ||\n");
    printf("||     �Ы����N���~��K           ||\n");
    printf("||                                ||\n");
    printf("====================================\n");
    getchar(); // ���ݨϥΪ̫��U���N��
}


// �D�{��
int main() {
    char input_pwd[10];
    const char correct_pwd[] = "2025";
    int tries = 0;
    char choice[10];

    welcome_screen();

    while (tries < 3) {
        printf("�п�J�K�X�G");
        fgets(input_pwd, sizeof(input_pwd), stdin);
        input_pwd[strcspn(input_pwd, "\n")] = 0;

        if (strcmp(input_pwd, correct_pwd) == 0) {
            break;
        } else {
            tries++;
            printf("�K�X���~�I�Ѿl���ơG%d\n", 3 - tries);
            if (tries == 3) {
                printf("�w���~�T���A�t�ε����C\n");
                return 0;
            }
        }
    }

    while (1) {
        CLEAR_SCREEN();
        printf("------------[Grade System]----------\n");
        printf("| a. ��J�ǥ͸��                  |\n");
        printf("| b. ��ܩҦ��ǥ͸��              |\n");
        printf("| c. �j�M�ǥ�                      |\n");
        printf("| d. ��ܥ������Z�ƦW              |\n");
        printf("| e. ���}�t��                      |\n");
        printf("------------------------------------\n");
        printf("�п�ܥ\��G");
        fgets(choice, sizeof(choice), stdin);

        switch (choice[0]) {
            case 'a': input_student_data(); break;
            case 'b': display_students(); break;
            case 'c': search_student(); break;
            case 'd': grade_ranking(); break;
            case 'e':
                while (1) {
                    char confirm[10];
                    printf("�T�w���}�H(y/n)�G");
                    fgets(confirm, sizeof(confirm), stdin);
                    if (confirm[0] == 'y' || confirm[0] == 'Y') {
                        printf("�t�ε����A�A���I\n");
                        return 0;
                    } else if (confirm[0] == 'n' || confirm[0] == 'N') {
                        break;
                    } else {
                        printf("�п�J y �� n�C\n");
                    }
                }
                break;
            default:
                printf("�ﶵ���~�A�Э��s��J�C\n");
                pause();
        }
    }

    return 0;
}
/*
�Q�׻P�߱o�G

���{���O�@��²�檺�ǥͦ��Z�޲z�t�ΡA����J�B��ܡB�j�M�P�Ƨǵ��\��C
�����c�}�C���]�p�A����ƲΤ@�޲z�A��K�s���P���@�C

�ǲߦp��N�{���\���h�Ө禡�A���D����[�M���A�]��e���z�ѻP�����C
�]�[�j��J���b�A�Ҧp�Ǹ�����������ƥB�����Ʀr�A�קK�~��y����ƿ��áC

���F��������A�[�J�F�M���ù��P�Ȱ����ܡA�b�ާ@�ɦ����T���޾ɻP���X�C
�b�K�X���ҳ����A�]�[�J�F�T�����խ���

�L�{���J�쪺�D�ԡA�p���{�r���J�P�M�z�w�İϵ��Ӹ`���D�A�C�����ճ��n��J�ǥ͸�ƿ�J�ܤ[ 

�`���Ө��A�o���@�~���ڹ����|�쵲�c�Ƶ{���]�p�����n�ʡA�]���ɤF�ڹ�C�y����J��X�B�r��ާ@�ε{���y�{������x�סC
���ӷ|����[�j���~�B�z�P�ϥΪ̤����]�p�A�ϵ{����í�w�B���ΡC
*/

