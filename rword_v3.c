#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN sizeof(mywd_t)

typedef struct myword {
    int     num;            /* 出现个数 */
    char    *word;          /* 出现单词 */
    struct  myword  *next;  /* 指向下一结点 */
} mywd_t, * pmywd;

void print_link_to_file(pmywd head);   /* 输出链表到文件 */      
pmywd find_words(FILE *input);         /* 将单词输出到链表 */
void destory_word(pmywd head);		   /* 销毁链表 */

void main(void)
{   
    FILE *input;
    pmywd head;
    /* 打开该路径下的文件 input.txt */
    char infile_id[] = {"C:\\Users\\hp\\Desktop\\words\\word-processing\\input.txt"};

    /* 只读的形式打开文件 */    
    input = fopen(infile_id, "r");                  
    if (input == NULL) {
        printf("打开文件%s失败\n", infile_id);
        exit(0);
    }
    
    head = find_words(input);       /* 找单词 */                 
    fclose(input);                  /* 关闭文件 */                 
    print_link_to_file(head);       /* 将链表输出到文件 */                  
    destory_word(head);
}
 
void print_link_to_file(pmywd head)
{
    pmywd p;
    FILE *output;
    /* 生成 output.txt 并保存在该路径 */
    char  outfile_id[] = {"C:\\Users\\hp\\Desktop\\words\\word-processing\\output.txt"};
    
    (void)printf("NOW,print LINK  to File......\n");
    output = fopen(outfile_id, "w");
    if (output == NULL) {
        printf("打开文件%s失败\n", outfile_id);
        exit(0);
    }

    p = head->next;
    /* 将链表内容写到output.txt */
    while (p != NULL) {
        fprintf(output, "%s,%d\n", p->word, p->num);
        p = p->next;
    } 

    fclose(output);     
    (void)printf("print to file Done!\n");
}

pmywd new_word(char word[]) 
{
    pmywd tmp;
    char *t_word;

    tmp = (pmywd)malloc(LEN);       /* 给一个新的节点申请空间 */
    /* 动态申请一个空间来保存 myword->word，因为这本身是个指针，需要指向一个数组来保存 */
    t_word = (char *)malloc(strlen(word));

    strcpy(t_word, strlwr(word));   /* 先将单词转为小写，再赋给t_word，方便排序 */
    tmp->word = t_word;
    tmp->num = 1;
    tmp->next = NULL;

    return tmp;
}

pmywd instert_word(pmywd tmp, pmywd head)
{
    pmywd cur;

    if (head == NULL) {         /* 存放在第一个结点 */    
        head = (pmywd)malloc(LEN);
        head->next = tmp;
    } else {
        cur = head->next;
        while (cur != NULL) {
            if (strcmp(tmp->word, cur->word) < 0) {               /* 小于情况，单词顺序不变 */
                tmp->next = cur;
                head->next = tmp;
                break;
            } else if (strcmp(tmp->word, cur->word) == 0) {       /* 等于情况，单词保留一个，个数加一 */
                cur->num++;
                free(tmp);        
                break;
            } else if (strcmp(tmp->word, cur->word) > 0) {         /* 大于情况， */ 
                if (cur->next != NULL) {    /* 后面不为空情况 */
                    if (strcmp(tmp->word, cur->next->word) < 0) {  /* 小于下一个值 ,插入当前节点之后 */ 
                        tmp->next = cur->next;
                        cur->next = tmp;
                        break; 
                    }
                    cur = cur->next;        /* 大于等于下一个值 */ 
                } else {
                    cur->next = tmp;        /* 后面为空情况 */                                     
                    break; 
                }
            } 
        }
    }

    return head;
}

pmywd find_words(FILE *input)
{
    pmywd head, tmp;
    pmywd instert_word(pmywd tmp, pmywd head); 	 /* 插入节点 */
    pmywd new_word(char word[]);  				 /* 生成一个新的节点，返回指针 */
    char ch;
    char word[25];
    int i;

    i = 0;
    head = NULL;
    
    printf("start find Words....\n");
    while (!feof(input)) {      /* 判断文件是否读完 */
        ch = fgetc(input);      /* 按个读取 */
        if ((ch >= 65 && ch <= 90) || (ch >= 97 && ch <= 122)) {    /* 将在 'a'-'z'和'A'-'Z'范围内的字母保存 */
            word[i] = ch;
            i++;
        } else {
            word[i] = '\0';              /* 区分单词是否结束 */
            if (strlen(word) != 0) {     /* 将单词插入链表 */
                tmp = new_word(word);   
                head = instert_word(tmp, head);
            }   
            i = 0;      /* 将单词重新从数组首位存放 */
        }
    }
    (void)printf("find Words Done!\n");

    return head;
}

void destory_word(pmywd head)
{
    pmywd tmp;
    
    (void)printf("start free!\n");
    while (head != NULL) {      /* 将链表所占用的内存释放 */
        tmp = head;
        head  = head->next;
        free(tmp);
    }
    (void)printf("Free Done!\n");
} 