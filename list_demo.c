/**
 * @file list_demo.c
 * @author Kang
 * @brief This File provides the XXX functions.
 * @version 1.0.0
 * @date 2019-10-30
 *
 * @copyright Copyright (c) 2019
 *
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "list.h"





/*
********************************************************************************
* ----------------------- Local defines  ---------------------------------------
********************************************************************************
*/

typedef struct {
    char *name;
    int num;
    int age;
}StudentInfo_t;


typedef struct {
    StudentInfo_t info;
    list_head list_node;
}StudentInfo_List_t;


#define DEMO_LOG(...)       printf(__VA_ARGS__)

#define FREE_MEMORY(X)      if( NULL != X) {free(X); X = NULL;}

/*
********************************************************************************
* ----------------------- Local Variables  -------------------------------------
********************************************************************************
*/

list_head demo_head;
list_head *p_demo_head = &demo_head;




/*
********************************************************************************
* ----------------------- Globe variables  -------------------------------------
********************************************************************************
*/




/*
********************************************************************************
* ----------------------- Function Declaration  --------------------------------
********************************************************************************
*/

static StudentInfo_List_t *create_student_node(StudentInfo_t *info);
static void update_student_list(StudentInfo_t *info);
static void update_student_list_tail(StudentInfo_t *info);
static void delete_student_node_by_num(int num);
static list_head *find_node_by_num(int num);
static void print_list(void);


/*
***************************************************************************************************
* ---------------------------------- Source codes  ------------------------------------------------
***************************************************************************************************
*/

int main(void)
{
    int i = 0;
    StudentInfo_t info;

    list_init(&p_demo_head);

    //更新student信息，头插法
    DEMO_LOG("-----update student info: add\n");
    for(i=0; i<6; i++) {
        info.num = i;
        info.name = "Jon";
        info.age = i + 10;

        update_student_list(&info);
    }
    print_list();


    //更新student信息，尾插法
    DEMO_LOG("-----update student info: add_tail\n");
    info.num = 10;
    info.age = 18;
    info.name = "Lily";
    update_student_list_tail(&info);
    print_list();


    //删除一个student信息
    DEMO_LOG("-----delete student info: end\n");
    delete_student_node_by_num(10);
    print_list();

    DEMO_LOG("-----delete student info: head\n");
    delete_student_node_by_num(5);
    print_list();


    DEMO_LOG("-----delete student info: midle\n");
    delete_student_node_by_num(3);
    print_list();

    return 0;
}






/*--------------------------------------static function-------------------------------------------*/

static StudentInfo_List_t *create_student_node(StudentInfo_t *info)
{
    StudentInfo_List_t *new_node = NULL;

    new_node = (StudentInfo_List_t *)calloc(1, sizeof(StudentInfo_List_t));
    if(NULL == new_node)    return NULL;

    new_node->info.age = info->age;
    new_node->info.num = info->num;
    new_node->info.name = strdup(info->name);

    return new_node;
}

static void update_student_list(StudentInfo_t *info)
{
    list_head *head = NULL;
    StudentInfo_List_t *new = NULL;

    //判断是否已存在
    head = find_node_by_num(info->num);
    if(NULL == head) {  //不存在
        DEMO_LOG("New node...\n");

        new = create_student_node(info);

        list_add(&p_demo_head, &new->list_node);

    }
    else {
        DEMO_LOG("Update node...\n");
    }
}

static void update_student_list_tail(StudentInfo_t *info)
{
    list_head *head = NULL;
    StudentInfo_List_t *new = NULL;

    //判断是否已存在
    head = find_node_by_num(info->num);
    if(NULL == head) {  //不存在
        DEMO_LOG("New node...\n");

        new = create_student_node(info);

        list_add_tail(&p_demo_head, &new->list_node);

    }
    else {
        DEMO_LOG("Update node...\n");
    }
}



static list_head *find_node_by_num(int num)
{
    StudentInfo_List_t *pos = NULL;
    list_head *head = NULL;

    list_for_each_entry(pos, p_demo_head, list_node) {
        if(num == pos->info.num) {
            head = &pos->list_node;
            break;
        }
    }
    return head;
}



static void delete_student_node_by_num(int num)
{
    StudentInfo_List_t *pos = NULL, *temp = NULL;

    list_for_each_safe_entry(pos, temp, p_demo_head, list_node) {
        if(num == pos->info.num) {
            list_del(&p_demo_head, &pos->list_node);

            //释放空间
            if(NULL != pos) {
                FREE_MEMORY(pos->info.name);
                FREE_MEMORY(pos);
            }
            break;
        }
    }
}



static void print_list(void)
{
    StudentInfo_List_t *pos = NULL;

    list_for_each_entry(pos, p_demo_head, list_node) {
        DEMO_LOG("num=%d, age=%d, name=%s\n", pos->info.num, pos->info.age, pos->info.name);
    }
}
