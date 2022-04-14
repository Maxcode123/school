#include <stdio.h>
#include <stdlib.h>
#define FRAMES 4

int is_empty();
int size();
void enqueue(int page);
void dequeue();
int not_in_memory(int page);
int frames_are_full();
void print_queue();
void print_pages(int index, int *page_sequence);

typedef struct Node {
    // Node used for the linked list implementation of the frame queue.
    int value;
    struct Node *next;
} Node;

Node *first = NULL; // Pointer to least recently added node.
Node *last = NULL; // Pointer to most recently added node.
int n = 0; // Current number of nodes in queue.

void main()
{
    int page_sequence[] = {3, 8, 5, 1, 8, 5, 7, 1, 4, 5, 8, 2, 7, 3, 6, 4, 6,
     5, 3, 7};
    int misses = 0; // Page misses counter.

    int length = sizeof(page_sequence) / sizeof(int);

    for (int i=0; i<length; i++)
    {
        if (not_in_memory(page_sequence[i]))
        {
            misses++;
            if (frames_are_full())
            {
                dequeue();
            }
            enqueue(page_sequence[i]);
        }
        print_pages(i, page_sequence);
        printf("\n");
    }
}

int is_empty()
// Return 1 if queue is empty, 0 otherwise.
{
    if (first == NULL)
    {
        return 1;
    }
    return 0;
}

int size()
// Returns the number of element currently in the queue.
{
    return n;
}

void enqueue(int page)
// Adds an element to the queue.
{
    if (size() == FRAMES)
    {
        printf("Frame queue is full, cannot enqueue another page.\n");
        return;
    }
    Node *temp;
    temp = (Node*)malloc(sizeof(Node));
    temp->value = page;
    temp->next = NULL;
    if (is_empty())
    {
        first = temp;
        last = temp;
    }
    else
    {
        last->next = temp;
        last = temp;
    }
    n++;
}

void dequeue()
// Removes an element from the queue.
{
    Node *temp;
    temp = first;
    first = first->next;
    free(temp);
    if (is_empty())
    {
        last = NULL;
    }
    n--;
}

int not_in_memory(int page)
// Returns 1 if page is not in frames, 0 otherwise.
{
    if (is_empty())
    {
        return 1;
    }
    Node *temp;
    temp = first;
    while (temp != last)
    {
        if (temp->value == page)
        {
            return 0;
        }
        temp = temp->next;
    }
    return 1;
}

int frames_are_full()
// Returns 1 if frames are full, 0 otherwise.
{
    if (size() == FRAMES)
    {
        return 1;
    }
    return 0;
}

void print_queue()
// Prints inrow the elements in the queue.
{
    Node *temp;
    temp = first;
    while (temp != NULL)
    {
        printf("%d ", temp->value);
        temp = temp->next;
    }
}

void print_pages(int index, int *page_sequence)
// Prints index, page, pages in frames.
{
    printf("%d  %d  ", index, page_sequence[index]);
    print_queue();
}
