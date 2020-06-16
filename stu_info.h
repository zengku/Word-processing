#ifndef _LIST_HEAD_H_
#define _LIST_HEAD_H_

/* 通用链表结点，双向链表 */
struct list_head {
    struct list_head *prev;
    struct list_head *next;
};

void list_init(struct list_head *list);
void list_add(struct list_head *node, struct list_head *head);
void list_add_tail(struct list_head *node, struct list_head *head);
void list_del(struct list_head *node);

/*遍历链表  依次为：从头节点的下一个节点开始遍历   
*                 从头节点的上一个节点开始遍历
*（以list_for_next_each为例理解：首先节点指针pos指向头节点的下一个节点，
* 判断 pos是否指向头节点，不是的话就向后继续遍历）
*/
//#define list_for_next_each(pos, head)\
for(pos=(head)->next; pos!=(head); pos=pos->next) \
#define list_for_prev_each(pos, head)\
for(pos=(head)->prev; pos!=(head); pos=pos->prev)

#define list_for_next_each(pos, head) do {  \
    (pos) = (head)->next;   \
    (pos) = (pos)->prev;    \
} while ((pos) != (head))

#define list_for_prev_each(pos, head) do {  \
    (pos) = (head)->prev;   \
    (pos) = pos->prev;      \
} while ((pos) != (head))


/* 提取数据结构   
 * ptr 是链接因子的指针  
 * type是包含了链接因子的数据类型  
 * member是链接因子成员名
 */ 
#define container_of(ptr,type,member)   \
    (type *)( (int)ptr - (int)(&((type *)0)->member) )


#endif /* _LIST_HEAD_H_ */