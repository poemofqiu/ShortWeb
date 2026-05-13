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

void init(hashmap *h);
void map_put(hashmap *h, int id);

int main(int argc, char const *argv[])
{
    int id = 1;

    return 0;
}
