/*
 * Created by Zhen Chen on 2025/3/5.
 * Email: chen.zhen5526@gmail.com
 * Description: A hashmap by c.
 *
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// 键值对结构体
typedef struct Entry {
    char* key;         // 键（字符串）
    int value;         // 值（整数）
    struct Entry* next; // 链表解决冲突
} Entry;

// HashMap 结构体
typedef struct HashMap {
    Entry** buckets;   // 哈希桶数组
    int size;          // 桶数量
} HashMap;

// 哈希函数（简单示例）
unsigned int hash(const char* key, int size) {
    unsigned int hashVal = 0;
    while (*key) {
        hashVal = (hashVal << 5) + *key++;
    }
    return hashVal % size;
}

// 创建 HashMap
HashMap* createHashMap(int size) {
    HashMap* map = (HashMap*)malloc(sizeof(HashMap));
    map->size = size;
    map->buckets = (Entry**)calloc(size, sizeof(Entry*));
    return map;
}

// 插入键值对
void put(HashMap* map, const char* key, int value) {
    unsigned int index = hash(key, map->size);
    Entry* entry = map->buckets[index];

    // 检查是否已存在
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value; // 更新值
            return;
        }
        entry = entry->next;
    }

    // 新建节点
    Entry* newEntry = (Entry*)malloc(sizeof(Entry));
    newEntry->key = strdup(key); // 复制键
    newEntry->value = value;
    newEntry->next = map->buckets[index];
    map->buckets[index] = newEntry;
}

// 查找值
int get(HashMap* map, const char* key) {
    unsigned int index = hash(key, map->size);
    Entry* entry = map->buckets[index];

    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return -1; // 未找到
}

// 释放 HashMap
void freeHashMap(HashMap* map) {
    for (int i = 0; i < map->size; i++) {
        Entry* entry = map->buckets[i];
        while (entry != NULL) {
            Entry* next = entry->next;
            free(entry->key);
            free(entry);
            entry = next;
        }
    }
    free(map->buckets);
    free(map);
}

int main() {
    HashMap* map = createHashMap(10);
    put(map, "apple", 5);
    put(map, "banana", 8);
    printf("apple: %d\n", get(map, "apple"));  // 输出 5
    printf("banana: %d\n", get(map, "banana")); // 输出 8
    printf("orange: %d\n", get(map, "orange")); // 输出 -1
    freeHashMap(map);
    return 0;
}