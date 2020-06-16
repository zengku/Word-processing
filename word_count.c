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
 *   v1.4     zengjh@dragonsoft.com.cn        2020-6-15
 *            处理函数命名，内存泄漏  
 *   v1.3     zengjh@dragonsoft.com.cn        2020-6-15 
 *            比较后再生成结点插入到链表
 *   v1.2     zengjh@dragonsoft.com.cn        2020-6-6 
 *            改用链表进行处理单词，按位读取，方便去重和统计个数。
 *   v1.1     zengjh@dragonsoft.com.cn        2020-6-4 
 *            通过数组存放单词，按行读取，在通过库函数处理单词排序。   
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

struct word_s {
    int  num;                /* 出现次数 */
    char *word;              /* 出现单词 */
    struct  word_s *next;    /* 指向下一结点 */
};

#define LEN sizeof(struct word_s)

static struct word_s *mwd_collect_words(FILE *input);     /* 将单词输出到链表 */
static void mwd_print_file(struct word_s *head);       /* 输出链表到文件 */
static void mwd_destory_list(struct word_s *head);	   /* 销毁链表 */

int main(void)
{
    FILE *input;
    struct word_s *head;
    /* 打开该路径下的文件 input.txt */
    char rfile[] = { "input.txt" };

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

    /* 将字符串赋给t_word */
    strcpy(words, word);
    tmp->word = words;
    tmp->num = 1;
    tmp->next = NULL;

    return tmp;
}

/*
 * mwd_first_word — 将首结点插入到链表里
 * @word:字符串
 * @head:头结点
 *
 * 判断首结点存放单词
 *
 * 返回值：链表头结点
 */
static struct word_s *mwd_first_word(char *word, struct word_s *head)
{
    struct word_s *temp;

    if (head == NULL) {         
        head = (struct word_s *)malloc(LEN);
        if (head == NULL) {
            (void)printf("malloc memory fail!\n");
            return NULL;
        } else {
            head->num = 0;
            head->word = NULL;
            temp = mwd_new_word(word);      /* 存放在第一个结点 */
            head->next = temp;
        }
    }

    return head;  
}

/*
 * mwd_sort_and_cound — 将新的结点插入到链表里
 * @word:字符串
 * @head:头结点
 *
 * 使用strcmp（）函数进行字符串的比较，分为三类情况，等于则保留一个且个数加一，
 * 小于则存入链表，大于则交换位置。
 *
 * 返回值：排完序的链表头结点
 */
static struct word_s *mwd_sort_and_cound(char *word, struct word_s *head)
{
    struct word_s *cur;
    struct word_s *temp;
    
    cur = head->next;
    while (cur != NULL) {
        /* 小于情况，单词顺序不变 */
        if (stricmp(word, cur->word) < 0) {
            temp = mwd_new_word(word);	/* 生成新结点 */
            temp->next = cur;
            head->next = temp;
            break;
            /* 等于情况，单词保留一个，个数加一 */
        } else if (stricmp(word, cur->word) == 0) {
            cur->num++;
            break;
        } else if (stricmp(word, cur->word) > 0) {  /* 大于情况，插cur后面 */
            if (cur->next != NULL) {    			/* 后面不为空情况 */
                /* 小于下一个值 ,插入当前节点之后 */
                if (stricmp(word, cur->next->word) < 0) {
                    temp = mwd_new_word(word);	
                    temp->next = cur->next;
                    cur->next = temp;
                    break;
                }
                cur = cur->next;        /* 大于等于下一个值 */
            } else {
                temp = mwd_new_word(word);
                cur->next = temp;        /* 后面为空情况 */
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
 * 通过字符按位比较，在ASCII字母范围内则保留下来，传参到mwd_new_word（）
 * 和mwd_instert_word（）函数，将输入的字符串排序好且去除相同单词，最后会被存入链表。
 *
 * 返回值：头结点
 */
static struct word_s *mwd_collect_words(FILE* input)
{
    char ch;            /* 读取字符的长度 */
    int i;              /* 数组元素个数 */
    char word[25];      /* 存放字符 */
    struct word_s *head, *temp;       /* 头结点和临时结点 */

    i = 0;
    head = NULL;                /* 头结点为空 */

    while (!feof(input)) {      /* 判断文件是否读完 */
        ch = fgetc(input);      /* 按个读取 */
        if (isalpha(ch)) {      /* 判断字符是否是字母 */
            word[i] = ch;
            i++;
        } else {
            word[i] = '\0';              /* 区分单词是否结束 */
            if (strlen(word) != 0) {     /* 将单词插入链表 */
                head = mwd_first_word(word, head);
                head = mwd_sort_and_cound(word, head);
            }
            i = 0;              /* 将单词重新从数组首位存放 */
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
static void mwd_print_file(struct word_s* head)
{
    FILE *output;
    struct word_s *p;

    /* 生成 output.txt 并保存在该路径 */
    char  wfile[] = { "output.txt" };

    output = fopen(wfile, "w");
    if (output == NULL) {
        printf("打开文件%s失败\n", wfile);
        exit(0);
    }

    p = head->next;
    /* 将链表内容写到output.txt */
    while (p != NULL) {
        printf("%s,%d\n", p->word, p->num);
        fprintf(output, "%s,%d\n", p->word, p->num);
        p = p->next;
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
static void mwd_destory_list(struct word_s *head)
{
    struct word_s *tmp;
    char *nword;

    if (!head) {    
        return;
    }
    if (head->next) { 
        while (head) {
            if (head->next != NULL) {
                if (head->next->word) {
                    nword = head->next->word;
                    free(nword);
                }
            }
            tmp = head->next;
            free(head);
            head = tmp;
        }
    }
    (void)printf("List free Done!\n");
}