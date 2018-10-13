#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <errno.h>

typedef struct NODE
{
    int data;
    struct NODE *prev;
    struct NODE *next;
} node;

typedef struct LIST
{
    struct NODE *head;
} list;

void add_client(list *clients, int pipe);
void print_list(list *clients);
void add_node(list *clients, int pid);
list *create_list(void);
bool find(list *clients, int value);
void delete_list(list *clients);
void delete_node(node *n);
