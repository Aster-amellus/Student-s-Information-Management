#include "funcs.h"


#include <stdio.h>
#include <stdlib.h>

// 假设前面定义的所有结构体和函数声明都已经包含在这里

int Menu_For_Teacher(void) {
    int choice;
    printf("\n学生信息管理系统\n");
    printf("1. 添加学生信息\n");
    printf("2. 删除学生信息\n");
    printf("3. 查找学生信息\n");
    printf("4. 修改学生信息\n");
    printf("5. 打印所有学生信息\n");
    printf("6. 按学号排序并打印\n");
    printf("7. 按姓名排序并打印\n");
    printf("8. 按平均分排序并打印\n");
    printf("9. 保存信息到文件\n");
    printf("10. 从文件加载信息\n");
    printf("0. 退出\n");
    printf("请输入选项: ");
    scanf("%d", &choice);
    return choice;
}

int Menu_For_Student(void) {
    int choice;
    printf("\n学生信息管理系统\n");
    printf("1. 添加学生信息\n");
    printf("2. 按平均分排序并打印\n");
    printf("0. 退出\n");
    printf("请输入选项: ");
    scanf("%d", &choice);
    return choice;
}

int main() {
    system("chcp 65001"); // 设置字符集为 UTF-8
    STU_NODE *head = NULL;
    int running = 1;
    long num;
    STU stu;
    UserRole userRole = login();

    if (userRole == ROLE_TEACHER) {
        printf("欢迎老师登录！\n");
        while (running) {
            switch (Menu_For_Teacher()) {
                case 1:
                    printf("添加学生信息:\n");
                    InputRecord(&head);
                    break;
                case 2:
                    printf("请输入要删除的学生学号: ");
                    scanf("%ld", &num);
                    DeleteRecord(&head, num);
                    break;
                case 3:
                    printf("请输入学生学号: ");
                    scanf("%ld", &num);
                    STU_NODE *found = SearchByNumber(head, num);
                    if (found) {
                        PrintRecord(found);
                    } else {
                        printf("未找到学号为 %ld 的学生。\n", num);
                    }
                    break;
                case 4:
                    // 请添加修改学生信息的具体实现
                    printf("请输入学生学号: ");
                    scanf("%ld", &num);
                    ModifyRecord(&head, num);
                    break;
                case 5:
                    printf("所有学生信息:\n");
                    PrintRecord(head);
                    break;
                case 6:
                    SortbyNum(&head);
                    PrintRecord(head);
                    break;
                case 7:
                    SortbyName(&head);
                    PrintRecord(head);
                    break;
                case 8:
                    SortbyScore(&head, Ascending);
                    PrintRecord(head);
                    break;
                case 9:
                    WritetoFile(head, "students.txt");
                    break;
                case 10:
                    ReadfromFile(&head, "students.txt");
                    break;
                case 0:
                    running = 0;
                    break;
                default:
                    printf("无效的选项，请重新输入。\n");
            }
        }
    } else if (userRole == ROLE_STUDENT) {
        printf("欢迎学生登录！\n");
        while (running) {
            switch (Menu_For_Student()) {
                case 1:
                    printf("添加学生信息:\n");
                    InputRecord(&head);
                    break;
                case 2:
                    SortbyScore(&head, Ascending);
                    PrintRecord(head);
                    break;
                case 0:
                    running = 0;
                    break;
                default:
                    printf("无效的选项，请重新输入。\n");
            }
        }
    } else {
        printf("登录失败！\n");
        return 1;
    }


    // 释放链表内存
    while (head != NULL) {
        STU_NODE *temp = head;
        head = head->next;
        free(temp);
    }

    printf("系统退出。\n");
    return 0;
}