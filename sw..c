//sw.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//结构体——哈希表节点
typedef struct Node
{
    char *short_code;
    char *long_url;
    struct Node *next;
}node;

//全局自增id
int id = 1 ;

//哈希表
#define HASH_SIZE 100
typedef struct HashMap
{
node *hash_map[HASH_SIZE];
}hashmap;

//初始化哈希表
void init(hashmap *h);
//插入
void map_put(hashmap *h, int id);
//创建节点
node *creat_node(node *next, char *short_code , char *long_url);

//字符集
static const char base62_chars[] = 
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

//哈希函数/id转换为短码
char *id_to_short_code(int id);



int main(int argc, char const *argv[])
{

    return 0;
}

//初始化哈希表
void init(hashmap *h)
{
    for (int i = 0; i < HASH_SIZE; i++)
    {
        h->hash_map[i] = NULL;
    }
}

//创建节点
node *creat_node(node *next, char *short_code , char *long_url)
{
    node *n = malloc(sizeof(node));
    n->short_code = strdup(short_code);
    n->long_url = strdup(long_url);
    n->next = next;
    return n;
}

//插入
void map_put(hashmap *h, int id)
{
    char *short_code = id_to_short_code(id);
}

//哈希函数/id转换为短码
char *id_to_short_code(int id)
{
    if (id == 0)
        return 0;
    char buf[21] = {0};
    int pos = 20;
    buf[pos] = '\0';
    while (id > 0)
    {
        buf[--pos] = base62_chars[id % 62];
        id /= 62;
    }
    return strdup(&buf[pos]);
}