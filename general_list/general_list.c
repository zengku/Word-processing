/*
 * Copyright(C) 2020 Dragonsoft. All rights reserved.
 */ 
/*
 * word.c         
 * Original Author:  zengjh@dragonsoft.com.cn, 2020-6-8  
 * 
 * 对读入的某个文本文件input.txt中，拆出英文单词，输出一个按字典顺序排列的单词表，
 * 并统计出现的个数，两字符用逗号分隔开，输出在文本文件output.txt里，相同单词只输
 * 出一个，大小写不区分。
 * 
 * History   
 *   v1.5     zengjh@dragonsoft.com.cn        2020-6-19
 *            改用通用链表实现 
 *   v1.4     zengjh@dragonsoft.com.cn        2020-6-15
 *            处理函数命名，内存泄漏  
 *   v1.3     zengjh@dragonsoft.com.cn        2020-6-15 
 *            比较后再生成结点插入到链表
 *   v1.2     zengjh@dragonsoft.com.cn        2020-6-6 
 *            改用链表进行处理单词，按位读取，方便去重和统计个数
 *   v1.1     zengjh@dragonsoft.com.cn        2020-6-4 
 *            通过数组存放单词，按行读取，在通过库函数处理单词排序
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "list.h"

struct word_s {
    int  num;                /* 出现次数 */
    char *word;              /* 出现单词 */
    struct list_head list;   /* 链接因子 */
};

#define LEN sizeof(struct word_s)     

static struct list_head *mwd_collect_words(FILE *input);     /* 将单词输出到链表 */
static void mwd_print_file(struct list_head *head);          /* 输出链表到文件 */
static void mwd_destory_list(struct list_head *head);	      /* 销毁链表 */

int main(void)
{
    FILE *input;       
    struct list_head *head;                 /* 首结点 */
    
    /* 打开该路径下的文件 input.txt */
    char rfile[] = {"input.txt"};

    /* 只读的形式打开文件 */
    input = fopen(rfile, "r");
    if (input == NULL) {
        printf("打开文件%s失败\n", rfile);
        exit(0);
    }

    head = mwd_collect_words(input);    /* 找单词 */
    fclose(input);                      /* 关闭文件 */
    mwd_print_file(head);               /* 将链表输出到文件 */
    mwd_destory_list(head);             /* 销毁链表 */

    return 0;
}

/*
 * mwd_new_word — 生成新的节点
 * @word: 字符串数组
 *
 * 通过使用strcpy（）函数将单词存在临时变量里
 *
 * 返回值：指向对应的结构体的指针
 */
static struct word_s *mwd_new_word(char word[])
{
    struct word_s *tmp;
    char *words;
        
	/* 给一个新的节点申请空间 */
    tmp = (struct word_s *)malloc(LEN);       
    if (tmp == NULL) {
        (void)printf("malloc memory fail!\n");
        return NULL;
    }

    /* 动态申请一个空间来保存 t_word */
    words = (char *)malloc(strlen(word));
    if (words == NULL) {
        (void)printf("malloc memory fail!\n");
        return NULL;
    }

    /* 将字符串赋给words */
    strcpy(words, word);
    tmp->word = words;
    tmp->num = 1; 

    return tmp;
}

/*
 * mwd_sort_word — 将新的结点插入到链表里
 * @word:字符串
 * @head:头结点
 *
 * 使用strcmp（）函数进行字符串的比较，分为三类情况，等于则保留一个且个数加一，
 * 小于则存入链表，大于的话又分为两大类，下一节点是否为头结点，不是的话交换位置插入，
 * 是的话直接插入到头结点前面。
 *
 * 返回值：排完序的链表头结点
 */
static struct list_head * mwd_sort_word(char *word, struct list_head *head)
{
    struct list_head *cur, *cur_next;       /* 指向当前节点的连接因子，下一节点的连接因子 */
    struct word_s *tmp, *tmp_next;          /* 获取数据结点的临时指针，获取数据结点的下一临时指针 */
    struct word_s *tmp_node;                /* 临时结点 */

    cur = head->next;                /* 第一个结点（头结点的下一个结点） */
    
    while (cur != head) {          /* cur不是头结点 */
        tmp = list_entry(cur, struct word_s, list);        
        if (stricmp(word, tmp->word) < 0) {                 /* 小于情况，单词顺序不变插入 */
            tmp_node = mwd_new_word(word);	                
            list_add_tail(&tmp_node->list, &(tmp->list));
            break;
        } else if (stricmp(word, tmp->word) == 0) {         /* 等于情况，单词个数加一 */
            tmp->num++;
            break;
        } else if (stricmp(word, tmp->word) > 0) {          /* 大于情况，分后面是否为头结点 */
            cur_next = cur->next;
            if (cur_next != head) {    			            /* 后面不为头结点，接着和后面的比较 */
                tmp_next = list_entry(cur_next, struct word_s, list);
                if (stricmp(word, tmp_next->word) < 0) {    /* 小于下一个值 ,插入下一个值的前面 */
                    tmp_node = mwd_new_word(word);
                    list_add(&tmp_node->list, cur);
                    break;
                } else {                                    /* 大于等于下一个值,接着遍历 */
                    cur = cur_next;                         
                }
            } else {                                        /* 后面为头结点，直接插入 */
                tmp_node = mwd_new_word(word);
                list_add(&tmp_node->list, cur);
                break;
            }
        }
    }

    return head;
}

/*
 * mwd_collect_words — 将单词有序且统计好输出到链表，
 * @input:文本文件
 *
 * 对字符串进行区分，在ASCII字母范围内则保留下来构成单词，对单词进行排列并统计个数，最后会贝存入链表
 *
 * 返回值：头结点
 */
static struct list_head *mwd_collect_words(FILE *input)
{
    int i;                  /* 数组元素个数 */
    char ch;                /* 读取字符的缓存 */
    char word[25];          /* 存放字符 */

    struct list_head *head;    /* 头结点 */
    struct word_s *tmp;

    head = (struct list_head *)malloc(LEN);
    if (head == NULL) {
        (void)printf("malloc memory fail!\n");
        exit(-1);
    }
    INIT_LIST_HEAD(head);  /* 初始化头节点 */ 

    i = 0;
    while (!feof(input)) {      /* 判断文件是否读完 */
        ch = fgetc(input);      /* 按个读取 */
        if (isalpha(ch)) {      /* 判断字符是否是字母 */
            word[i] = ch;
            i++;
        } else {
            word[i] = '\0';              /* 区分单词是否结束 */
            if (strlen(word) != 0) {     /* 将单词插入到链表 */
                if (list_empty(head)) {            /* 链表为空，将第一个直接单词插入 */
                    tmp = mwd_new_word(word);    
                    list_add(&(tmp->list), head);  
                } else {
                    head = mwd_sort_word(word, head);  /* 不为空，将单词排序 */
                }
            }
            i = 0;      /* 将单词重新从数组首位存放 */
        }
    }

    return head;
}

/*
 * mwd_print_file — 将单词写到文件
 * @head: 链表头
 *
 * 遍历链表后输出将单词及出现的次数输出到目标文件
 *
 * 返回值：无
 */
static void mwd_print_file(struct list_head *head)
{
    FILE *output;
    struct list_head *pos;
    struct word_s *tmp, *tmp_next;

    /* 生成 output.txt 并保存在该路径 */
    char wfile[] = {"output.txt"};

    output = fopen(wfile, "w");
    if (output == NULL) {
        printf("打开文件%s失败\n", wfile);
        exit(0);
    }

    pos = head->next;
    list_for_next_each(pos, head) {            /* 从头结点开始遍历，打印并且写到文件 */
        tmp = list_entry(pos, struct word_s, list);
        printf("%s,%d \n", tmp->word, tmp->num);
        fprintf(output, "%s,%d\n", tmp->word, tmp->num);
    }

    fclose(output);
    (void)printf("print to file Done!\n");
}

/*
 * mwd_destory_list — 销毁链表
 * @head: 首结点
 *
 * 先遍历整个链表，将每个结点的空间释放掉
 *
 * 返回值：无
 */
static void mwd_destory_list(struct list_head *head)
{
    struct list_head *cur, *next;		/*当前结点， 下一结点 */
    struct word_s *tmp;

    if (list_empty(head)) {    
        return;
    }
    
    cur = head->next;
    while(cur != head) {                       /* 遍历头结点，先删除单词的内存，在释放结点 */
        tmp = list_entry(cur, struct word_s, list);
        if (tmp->word) {
            free(tmp->word);
        }
        next = cur->next;
        free(cur);
        cur = next;
    }
    free(head);

    (void)printf("List free Done!\n");
} 