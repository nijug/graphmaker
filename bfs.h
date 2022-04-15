struct box
{
    // numer wezla
    int nb;
    // wskaznik na nastepny wezel
    struct box *next;
};

void enqueue_curr(int number);
void dequeue();
void dequeue_curr();
int in_queue(int number);
int queue_size();
void clear_queue();
int bfs(int a, int b, int x, int y);