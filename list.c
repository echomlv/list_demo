/**
 * @file list.c
 * @author Kang
 * @brief This File provides the XXX functions.
 * @version 1.0.0
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2019
 *
 */

#define _LIST_C_

#include <stdio.h>


#include "list.h"



/*
********************************************************************************
* ----------------------- Local defines  ---------------------------------------
********************************************************************************
*/






/*
********************************************************************************
* ----------------------- Local Variables  -------------------------------------
********************************************************************************
*/





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
static inline void __list_add(list_head **head, list_head *before, list_head *new);
static inline list_head **find_indirect(list_head **head, list_head *target);




/*
***************************************************************************************************
* ---------------------------------- Source codes  ------------------------------------------------
***************************************************************************************************
*/

//初始化
void list_init(list_head **head)
{
    (*head)->next = NULL;
}


//头插法
void list_add(list_head **head, list_head *new)
{
    __list_add(head, *head, new);
}

//尾插法
void list_add_tail(list_head **head, list_head *new)
{
    __list_add(head, NULL, new);
}

//删除
void list_del(list_head **head, list_head *target)
{
    list_head **p = find_indirect(head, target);
    *p = target->next;
}


/*--------------------------------------static function-------------------------------------------*/
//找到位置
static inline list_head **find_indirect(list_head **head, list_head *target)
{
    list_head **p = head;

    while(*p != target) {
        p = &(*p)->next;
    }
    return p;
}


//插入helper, 当before指向header,头插法，当before指向NULL，尾插法
static inline void __list_add(list_head **head, list_head *before, list_head *new)
{
    list_head **p = find_indirect(head, before);

    if(*head == before) {
        new->next = before->next;
        (*p)->next = new;
    }
    else {
        *p = new;
        new->next = before;
    }

}
