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

//哈希表
#define HASH_SIZE 100
typedef struct HashMap
{
node *hash_map[HASH_SIZE];
}hashmap;

//哈希函数
int hash_function(char *short_code);

//初始化哈希表函数
void init(hashmap *h);
//创建节点
node *create_node(char *short_code , char *long_url);
//插入
void map_put(hashmap *h, char *short_code , char *long_url);
//查询
char *map_get(hashmap *h, char *short_code);

//字符集
static const char base62_chars[] = 
    "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

//哈希函数/id转换为短码
char *id_to_short_code(long id);

//全局自增id
static long id =1;
//定义两个哈希表：一个用于短码到长URL的映射，另一个用于长URL到短码的映射
hashmap short_to_long;
hashmap long_to_short;
//初始化哈希表
void init_hash();
//生成短码
char *shorten_url(char *long_url);
//根据短码获取长URL
char *get_long_url(char *short_code);


int main(int argc, char const *argv[])
{
    init_hash();
    char *long_url = "https://www.example.com/some/very/long/ur";
    char *short_code = shorten_url(long_url);
    printf(" %s 的短码是 %s\n", long_url, short_code);
    char *retrieved_long_url = get_long_url(short_code);
    printf(" %s 的长URL是 %s\n", short_code, retrieved_long_url);
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

//哈希函数
int hash_function(char *short_code)
{
    int hash = 0;
    for (int i = 0; short_code[i] != '\0'; i++)
    {
        hash = (hash * 31 + short_code[i]) % HASH_SIZE;
    }
    return hash;
}

//创建节点
node *create_node(char *short_code , char *long_url)
{
    node *n = malloc(sizeof(node));
    n->short_code = strdup(short_code);
    n->long_url = strdup(long_url);
    n->next = NULL;
    return n;
}

//插入
void map_put(hashmap *h, char *short_code , char *long_url)
{
    int index = hash_function(short_code);
    node *new_node = create_node(short_code , long_url);
    new_node->next = h->hash_map[index];
    h->hash_map[index] = new_node;
}

//查询
char *map_get(hashmap *h, char *short_code)
{
    int index = hash_function(short_code);
    node *c = h->hash_map[index];
    while (c != NULL)
    {
        if (strcmp(c->short_code, short_code) == 0)//比较短码是否相同
        {
            return c->long_url;
        }
        c = c->next;
    }
    return NULL;
}

//哈希函数/id转换为短码
char *id_to_short_code(long id)
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

//初始化哈希表
void init_hash()
{
    init(&short_to_long);
    init(&long_to_short);
}
//生成短码
char *shorten_url(char *long_url)
{
    //检查长URL是否已经存在
    char *existing_short_code = map_get(&long_to_short, long_url);
    if (existing_short_code != NULL)
    {
        return existing_short_code;
    }
    //生成新的短码
    char *short_code = id_to_short_code(id++);
    //存储映射关系
    map_put(&short_to_long, short_code, long_url);
    map_put(&long_to_short, long_url, short_code);
    return short_code;  
}
//根据短码获取长URL
char *get_long_url(char *short_code)
{
    return map_get(&short_to_long, short_code);
}