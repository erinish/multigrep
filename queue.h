typedef struct node {
    char *line;
    struct node *next;
} node;

extern node *first; 
extern node *end; 
extern int queuelen;

void printnode(node *n);
void enque(char *s);
void printque(node *n);
char* deque();
void reset_queue();

