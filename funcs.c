//
// Created by qfwfq on 2024/3/31.
//

#include "funcs.h"

STU_NODE* initStuNode(STU stu) {
    STU_NODE* newNode = (STU_NODE*)malloc(sizeof(STU_NODE));
    if (!newNode) return NULL;
    newNode->stu = stu;
    newNode->next = NULL;
    return newNode;
}

void AppendRecord(STU_NODE ** head, STU stu) {
    STU_NODE* newNode = initStuNode(stu);
    if (!*head) {
        *head = newNode;
    } else {
        STU_NODE* current = *head;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = newNode;
    }
}

void DeleteRecord(STU_NODE ** head, long number) {
    STU_NODE *temp = *head, *prev = NULL;
    if (temp != NULL && temp->stu.num == number) {
        *head = temp->next;
        free(temp);
        return;
    }
    while (temp != NULL && temp->stu.num != number) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) return;
    prev->next = temp->next;
    free(temp);
}

STU_NODE * SearchByNumber(STU_NODE * head, long number) {
    STU_NODE* current = head;
    while (current != NULL) {
        if (current->stu.num == number)
            return current;
        current = current->next;
    }
    return NULL;
}

void InputRecord(STU_NODE **head) {
    STU newStu;
    printf("请输入学生学号: ");
    scanf("%ld", &newStu.num);
    printf("请输入学生姓名: ");
    scanf("%s", newStu.name);
    newStu.sum = 0;
    for (int i = 0; i < COURSE_NUM; i++) {
        printf("请输入课程%d成绩: ", i + 1);
        scanf("%f", &newStu.score[i]);
        newStu.sum += newStu.score[i];
    }
    newStu.aver = newStu.sum / COURSE_NUM;
    AppendRecord(head, newStu);
}

void ModifyRecord(STU_NODE **head, long number) {
    STU_NODE *node = SearchByNumber(*head, number);
    if (node) {
        printf("修改学生信息 (学号: %ld)\n", number);

        // 更新姓名
        printf("请输入新的姓名: ");
        scanf("%s", node->stu.name); // 假设姓名不超过之前定义的NAME_LEN

        // 更新各科成绩并重新计算总分和平均分
        node->stu.sum = 0;
        for (int i = 0; i < COURSE_NUM; i++) {
            printf("请输入课程 %d 的新成绩: ", i + 1);
            scanf("%f", &node->stu.score[i]);
            node->stu.sum += node->stu.score[i];
        }

        node->stu.aver = node->stu.sum / COURSE_NUM;

        printf("学生信息更新成功。\n");
    } else {
        printf("未找到学号为 %ld 的学生.\n", number);
    }
}


void CalculateScoreOfStudent(STU_NODE *node) {
    node->stu.sum = 0;
    for (int i = 0; i < COURSE_NUM; i++) {
        node->stu.sum += node->stu.score[i];
    }
    node->stu.aver = node->stu.sum / COURSE_NUM;
}

void SortbyNum(STU_NODE **head) {
    int swapped;
    STU_NODE *ptr1;
    STU_NODE *lptr = NULL;

    if (*head == NULL)
        return;

    do {
        swapped = 0;
        ptr1 = *head;

        while (ptr1->next != lptr) {
            if (ptr1->stu.num > ptr1->next->stu.num) {
                STU temp = ptr1->stu;
                ptr1->stu = ptr1->next->stu;
                ptr1->next->stu = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}

void SortbyName(STU_NODE **head) {
    if (!head || !*head) return;
    int swapped;
    STU_NODE *current;
    STU_NODE *prev = NULL;
    STU_NODE *temp = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != temp) {
            if (strcmp(current->stu.name, current->next->stu.name) > 0) {
                swapped = 1;
                if (current == *head) {
                    *head = current->next;
                    current->next = current->next->next;
                    (*head)->next = current;
                    current = *head;
                } else {
                    prev->next = current->next;
                    current->next = current->next->next;
                    prev->next->next = current;
                    current = prev->next;
                }
            }
            prev = current;
            current = current->next;
        }
        temp = current;
    } while (swapped);
}

void SortbyScore(STU_NODE **head, int (*compare)(float a, float b)) {
    if (!head || !*head) return;
    int swapped;
    STU_NODE *current;
    STU_NODE *prev = NULL;
    STU_NODE *temp = NULL;

    do {
        swapped = 0;
        current = *head;

        while (current->next != temp) {
            if (compare(current->stu.aver, current->next->stu.aver) > 0) {
                swapped = 1;
                if (current == *head) {
                    *head = current->next;
                    current->next = current->next->next;
                    (*head)->next = current;
                    current = *head;
                } else {
                    prev->next = current->next;
                    current->next = current->next->next;
                    prev->next->next = current;
                    current = prev->next;
                }
            }
            prev = current;
            current = current->next;
        }
        temp = current;
    } while (swapped);
}

int Ascending(float a, float b) {
    return a > b ? 1 : (a < b ? -1 : 0);
}


void PrintRecord(STU_NODE *head) {
    STU_NODE *current = head;
    while (current != NULL) {
        printf("学号: %ld, 姓名: %s, 总分: %.2f, 平均分: %.2f\n",
               current->stu.num, current->stu.name, current->stu.sum, current->stu.aver);
        current = current->next;
    }
}
void WritetoFile(STU_NODE *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return;
    }
    STU_NODE *current = head;
    while (current != NULL) {
        fprintf(file, "%ld %s", current->stu.num, current->stu.name);
        for (int i = 0; i < COURSE_NUM; i++) {
            fprintf(file, " %.2f", current->stu.score[i]);
        }
        fprintf(file, "\n");
        current = current->next;
    }
    fclose(file);
}

int ReadfromFile(STU_NODE **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("无法打开文件。\n");
        return -1;
    }
    STU newStu;
    while (fscanf(file, "%ld %s", &newStu.num, newStu.name) == 2) {
        newStu.sum = 0;
        for (int i = 0; i < COURSE_NUM; i++) {
            fscanf(file, "%f", &newStu.score[i]);
            newStu.sum += newStu.score[i];
        }
        newStu.aver = newStu.sum / COURSE_NUM;
        AppendRecord(head, newStu);
    }
    fclose(file);
    return 0;
}

uint32_t key[4] = {0x01234567, 0x89ABCDEF, 0xFEDCBA98, 0x76543210};
void encrypt(uint32_t* v, uint32_t* k) {
    uint32_t v0 = v[0], v1 = v[1], sum = 0;
    uint32_t delta = 0x9e3779b9;
    for (uint32_t i = 0; i < 32; i++) {
        sum += delta;
        v0 += ((v1 << 4) + k[0]) ^ (v1 + sum) ^ ((v1 >> 5) + k[1]);
        v1 += ((v0 << 4) + k[2]) ^ (v0 + sum) ^ ((v0 >> 5) + k[3]);
    }
    v[0] = v0; v[1] = v1;
}

UserRole login() {
    char username[50];
    char password[50];
    printf("Username: ");
    scanf("%49s", username);
    printf("Password: ");
    scanf("%49s", password);

    // 将密码进行简单处理以适应加密（实际应用中应更安全地处理密码）
    uint32_t v[2] = {0, 0};
    strncpy((char*)v, password, sizeof(v)); // 注意，这里的处理方式很简单，实际情况应更复杂
    encrypt(v, key);

    // 假设教师账户为"teacher"，密码为TEACHER_PASSWORD加密后的值
    uint32_t teacherPwd[2] = {0, 0};
    strncpy((char*)teacherPwd, TEACHER_PASSWORD, sizeof(teacherPwd));
    encrypt(teacherPwd, key);

    if (strcmp(username, "teacher") == 0 && v[0] == teacherPwd[0] && v[1] == teacherPwd[1]) {
        return ROLE_TEACHER;
    } else {
        // 假设学生不需要密码或有其他验证方式
        return ROLE_STUDENT;
    }
}
