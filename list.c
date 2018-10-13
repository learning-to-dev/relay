#include "list.h"

node *create_node(int data)
{
    node *n = malloc(sizeof(node));
    n->data = data;
    n->prev = NULL;
    n->next = NULL;
    return n;
}

list *create_list(void)
{
    list *l = malloc(sizeof(list));
    l->head = NULL;
    return l;
}

void add_client(list *clients, int pid)
{
    if(!find(clients, pid))
    {
        add_node(clients, pid);
    }
}

void add_node(list *clients, int pid)
{
    node *new = create_node(pid);
    node *current = clients->head;
    if(current)
    {
        while(current->next != NULL)
        {
            current = current->next;
        }
        current->next = new;
	new->prev = current;
    } else {
        clients->head = new;
    }
}

void print_list(list *clients)
{
    node *current = clients->head;
    printf("The following clients are connected:\n");
    while(current)
    {
	if(kill(current->data, 0) != ESRCH)
	{
            printf("%d ", current->data);
	}
        current = current->next;
    }
    printf("\n");
}

bool find(list *clients, int value)
{
    node *current = clients->head;
    while(current != NULL)
    {
        if(current->data == value)
        {
            return true;
        }
        current = current->next;
    }
    return false;
}

void delete_list(list *clients)
{
    node *current = clients->head;
    while(current != NULL)
    {
        clients->head = current->next;
        kill(current->data, SIGKILL);
        free(current);
        current = clients->head;
    }
}

void delete_node(node *current)
{
    node *tmp = current->prev;
    tmp->next = current->next;
    free(current);
}
