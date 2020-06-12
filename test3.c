#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN sizeof(mywd_t)

typedef struct myword {
    int     num;            /* 出现个数 */
    char    *word;          /* 出现单词 */
    struct  myword  *next;    
}mywd_t, *pmywd;

void main(void)
{   
    void print_link_to_file(pmywd head);   /* 输出链表到文件 */      
    pmywd find_words(FILE *input);         /* 将单词输出到链表 */
    void destory_word(pmywd head);		   /* 销毁链表释放内存 */

    char infile_name[] = {"input.txt"};
    pmywd head;
    FILE *input;
    
    input = fopen(infile_name, "r");                  
    if (input == NULL) {
        printf("打开文件%s失败\n", infile_name);
        exit(0);
    }
    
    head = find_words(input);       /* 找单词 */                 
    fclose(input);                                   
    print_link_to_file(head);       /* 将链表输出到文件 */                  
    destory_word(head);
}

void print_link_to_file(pmywd head)
{
    /* 输入链表，将链表内容输出到input.txt */ 
    printf("NOW,print LINK  to File......\n");
    pmywd p;
    FILE *output;
    char outfile_name[] = {"output.txt"};
    output = fopen(outfile_name, "w");

    if (output == NULL) {
        printf("打开文件%s失败\n", outfile_name);
        exit(0);
    }
    p = head->next;
    do {
        fprintf(output,"%s,%d\n", p->word, p->num);
        p = p->next;
    } while(p != NULL);
    
    fclose(output);
    printf("print to file Done!\n");
}
 
pmywd new_word(char word[]) 
{
    /* 输入一个单词数组，返回一个myword结构体 */
    pmywd tmp;
    char *t_word;
    /* 给一个新的节点申请空间 */
    tmp = (pmywd) malloc(LEN);        
    /* 动态申请一个空间来保存myword->word，因为这本身是个指针，需要指向一个数组来保存 */
    t_word = (char *) malloc(strlen(word));
    strcpy(t_word, strlwr(word));
    tmp->word = t_word;
    tmp->num = 1;
    tmp->next = NULL;

    return tmp;
}

pmywd instert_word(pmywd tmp, pmywd head)
{
    pmywd cur;

    if (head == NULL) {
        head = (pmywd) malloc(LEN);
        head->next = tmp;
    } else {
        cur = head->next;
        while (cur != NULL) {
            if (strcmp(tmp->word, cur->word) < 0) {
                /* 小于第一个值 ,因为链表有序，如果比第一个小，那就是最小的 */
                tmp->next = cur;
                head->next = tmp;
                break;
            } else if (strcmp(tmp->word, cur->word) == 0) {
                /* 等于当前值 */
                cur->num++;
                free(tmp);        
                break;
            } else if (strcmp(tmp->word, cur->word) > 0) {   
                /* 大于当前值 */ 
                if (cur->next != NULL) {
                    /* 后面不为空 */ 
                    if (strcmp(tmp->word, cur->next->word) < 0) {
                        /* 小于下一个值 ,插入当前节点之后 */ 
                        tmp->next = cur->next;
                        cur->next = tmp;
                        break; 
                    }
                    /* 大于等于下一个值 */ 
                    cur = cur->next;
                } else {
                    /* 后面为空 */ 
                    cur->next = tmp; 
                    break; 
                }
            } 
        }
    }

    return head;
}
 
pmywd find_words(FILE *input)
{
    printf("start find Words....\n");
    pmywd head, tmp;
    pmywd instert_word(pmywd tmp, pmywd head); 	 /* 插入节点 */
    pmywd new_word(char word[]);  				 /* 生成一个新的节点，返回指针 */
    char ch;
    char word[25];
    int i = 0;
    head = NULL;
    
    while (!feof(input)) {
        ch = fgetc(input);
        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {
            word[i] = ch;
            i++;
        } else {
            word[i] = '\0';
            if (strlen(word) !=0) {
                tmp = new_word(word);
                head = instert_word(tmp, head);
            }   
            i = 0;
        }
    }
    printf("find Words Done!\n");

    return head;
}

void destory_word(pmywd head)
{
    printf("start free!\n");
    pmywd tmp;
    while (head != NULL) {
        tmp = head;
        head  = head->next;
        free(tmp);
    }
    printf("Free Done!\n");
} 

