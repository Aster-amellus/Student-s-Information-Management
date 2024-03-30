//
// Created by qfwfq on 2024/3/31.
//

#ifndef STUDENT_SINFOMANAGE_FUNS_H
#define STUDENT_SINFOMANAGE_FUNS_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define NAME_LEN 20
#define COURSE_NUM 10
#define TEACHER_PASSWORD "teacher123"
typedef struct student
{
    long num;                       //学号
    char name[NAME_LEN];            //姓名
    float score[COURSE_NUM];        //每门课程成绩
    float sum;                      //总分
    float aver;                     //平均分
} STU;

// 定义链表结构体
typedef struct node
{
    STU stu;
    struct node *next;
} STU_NODE;

typedef enum {
    ROLE_TEACHER,
    ROLE_STUDENT
} UserRole;

// 初始化
STU_NODE* initStuNode(STU stu);
void InputRecord(STU_NODE ** head);
// 增加学生信息
void AppendRecord(STU_NODE ** head, STU stu);
// 删除学生信息
void DeleteRecord(STU_NODE ** head, long number);
// 按学号查询学生信息
STU_NODE * SearchByNumber(STU_NODE * head, long number);
// 按姓名查询学生信息
STU_NODE * SearchByName(STU_NODE * head, const char* name);
// 修改学生信息
void ModifyRecord(STU_NODE ** head, long number);
// 计算学生的总分和平均分
void CalculateScoreOfStudent(STU_NODE * node);
// 计算某门课程的总分和平均分
void CalculateScoreOfCourse(STU_NODE * head, int courseIndex);
// 按学号排序
void SortbyNum(STU_NODE ** head);
// 按姓名排序
void SortbyName(STU_NODE ** head);
// 按平均分排序（使用比较函数）
void SortbyScore(STU_NODE ** head, int (*compare)(float a, float b));
// 升序排序辅助函数
int Ascending(float a, float b);
// 降序排序辅助函数
int Descending(float a, float b);
// 统计并输出各个分数段学生人数及占比（假设链表已排序）
void StatisticAnalysis(STU_NODE * head);
// 打印学生成绩
void PrintRecord(STU_NODE * head);
// 将学生信息保存至文件
void WritetoFile(STU_NODE * head, const char* filename);
// 从文件读取学生信息
int ReadfromFile(STU_NODE ** head, const char* filename);
// 返回角色
UserRole login();
// TEA加密
void encrypt(uint32_t* v, uint32_t* k);
#endif //STUDENT_SINFOMANAGE_FUNS_H

