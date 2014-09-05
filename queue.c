#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <unistd.h>
#include <regex.h>
#include "queue.h"

void printnode(node *n)
{
//    puts("-------------------");
//    printf("Address: %p\n", n);
    printf("%s", n->line);
//    printf("Next: %p\n", n->next);
}

node *first = NULL; 
node *end = NULL; 
int queuelen = 0;

void enque(char *s)
{
    queuelen += 1;
    node *tmp; // temp node pointer 
    tmp = (struct node *)malloc(sizeof(struct node));
    tmp->line = strdup(s);
    tmp->next = NULL;
    if (first == NULL) {
        first = tmp;
    }
    if (end == NULL) {
        end = tmp;
    } else {
        end->next = tmp; // current end node's next pointer to new node
    }
    end = tmp; // end pointer changed to the new node
}


void printque(node *n)
{
    printnode(n);
    while (n->next != NULL) // loop while the next node isn't null
    {
        n = n->next;
        printnode(n);
    }
}

char* deque()
{
    if ( queuelen > 0) {
        node *tmp = first;
        node *next = first->next;
        char *line = strdup(first->line);
        free(first->line);
        first = next;
        free(tmp);
        queuelen -= 1;
        return line; 
    } else {
        return "END OF QUEUE";
    }
}

void reset_queue()
{
    while ( queuelen > 0 )
    {
        deque();
    }
}

