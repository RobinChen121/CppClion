/*
 * Created by Zhen Chen on 2025/3/12.
 * Email: chen.zhen5526@gmail.com
 * Description: 
 *
 *
 */
#include<stdlib.h>
#include<stdio.h>

typedef struct Node {
  int data;
  struct Node *next;
} Node;

// 因为是动态链表，所以返回一个指针
Node *create_Node(const int data) {
  Node *newNode = (Node *) malloc(sizeof(Node *));
  if (newNode == NULL) {
    printf("there is no available memory.");
  }
  newNode->data = data;
  newNode->next = NULL;
  return newNode;
}

void print_list(const Node *head) {
  int num = 1;
  while (head != NULL) {
    printf("Node %d data is %d\n", num, head->data);
    head = head->next;
    num++;
  }
}

void free_list(Node *head) {
  while (head != NULL) {
    Node *temp = head;
    head = head->next;
    free(temp);
  }
}

int main() {
  Node *first = create_Node(1);
  Node *second = create_Node(2);
  Node *third = create_Node(3);

  first->next = second; // link the nodes
  second->next = third;

  print_list(first);
  free_list(first);

  return 0;
}
