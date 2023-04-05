/**
 * @file list.h
 * @author Kang
 * @brief This File provides the prototype of xxx.
 * @version 1.0.0
 * @date 2023-04-05
 *
 * @copyright Copyright (c) 2019
 *
 */

#ifndef _LIST_H_
#define _LIST_H_

#ifndef _LIST_C_
#define _EXTERN
#endif

#ifdef __cplusplus
extern "C" {
#endif



/*
********************************************************************************
* ----------------------- Globe defines  --------------------------------------
********************************************************************************
*/


typedef struct list_head {
    struct list_head *next;
}list_head;







//遍历
/**
 * list_for_each    -   iterate over a list
 * @pos:    the &struct list_head to use as a loop counter.
 * @head:   the head for your list.
 */
#define list_for_each(pos, head)    \
    for(pos = (head)->next; pos != NULL; pos = pos->next)


/**
 * list_for_each_safe - iterate over a list safe against removal of list entry
 * @pos:	the &struct list_head to use as a loop cursor.
 * @n:		another &struct list_head to use as temporary storage
 * @head:	the head for your list.
 */
#define list_for_each_safe(pos, n, head) \
    for(pos = (head)->next, n = pos->next; pos != NULL; pos = n, n = pos->next)


//计算偏移量，编译期间: 该宏得到的是TYPE（结构体）类型中成员MEMBER相对于结构体的偏移地址
#define my_offsetof(TYPE, MEMBER)   ((size_t) &((TYPE *)0)->MEMBER)

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:    the pointer to the member.
 * @type:   the type of the container struct this is embedded in.
 * @member: the name of the member within the struct.
 */
//第一句，其实第一句话没有也完全不影响该宏的功能，但是内核链表设计者们为什么要增加这个一个赋值的步骤呢？
//因为宏没有参数检查的功能,增加这个之后，如果类型不匹配，会有警告
#define container_of(ptr, type, member)     ( {             \
    const typeof( ((type *)0)->member) *__mptr = (ptr);     \
    (type *)((char *)__mptr - my_offsetof(type, member));   \
})


/**
 * list_entry - get the struct for this entry
 * @ptr:    the &struct list_head pointer.
 * @type:   the type of the struct this is embedded in.
 * @member: the name of the list_struct within the struct.
 */
#define list_entry(ptr, type, member) \
    container_of(ptr, type, member)

/**
 * list_for_each_entry  -   iterate over list of given type
 * @pos:    the type * to use as a loop cursor.
 * @head:   the head for your list.
 * @member: the name of the list_struct within the struct.
 */
#define list_for_each_entry(pos, head, member)  \
    for(pos = list_entry((head)->next, typeof(*pos), member);   \
        &pos->member != NULL; pos = list_entry(pos->member.next, typeof(*pos), member))


/**
 * list_for_each_entry_safe - iterate over list of given type safe against removal of list entry
 * @pos:	the type * to use as a loop cursor.
 * @n:		another type * to use as temporary storage
 * @head:	the head for your list.
 * @member:	the name of the list_struct within the struct.
 */
#define list_for_each_safe_entry(pos, n, head, member)  \
    for(pos = list_entry((head)->next, typeof(*pos), member),   \
        n = list_entry(pos->member.next, typeof(*pos), member);   \
        &pos->member != NULL; pos = n, n = list_entry(pos->member.next, typeof(*pos), member))




/*
********************************************************************************
* ----------------------- Globe variables  ------------------------------------
********************************************************************************
*/

#ifdef _EXTERN



#undef _EXTERN
#endif

/*
********************************************************************************
* ----------------------- Globe functions  ------------------------------------
********************************************************************************
*/
//初始化
void list_init(list_head **head);

//头插法
void list_add(list_head **head, list_head *new);
//尾插法
void list_add_tail(list_head **head, list_head *new);
//删除
void list_del(list_head **head, list_head *target);



#ifdef __cplusplus
}
#endif


#endif
/*-------------------------End of the file------------------------------------*/
