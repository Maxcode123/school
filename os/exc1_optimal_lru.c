#include <stdio.h>
#define FRAMES 4

int not_in_memory(int *frames, int page);
int frames_not_full(int *frames);
void print_pages(int *frames, int index, int *page_sequence);
void optimal_replacement(int *frames, int length, int index, int *page_sequence);
void lru_replacement(int *frames, int length, int index, int *page_sequence);
int index_max(int *distances);

void main()
{
    int page_sequence[] = {3, 8, 5, 1, 8, 5, 7, 1, 4, 5, 8, 2, 7, 3, 6, 4, 6,
     5, 3, 7};
    int frames[] = {0, 0, 0, 0}; // array of page numbers in frames
    int misses = 0; // page misses counter

    int length = sizeof(page_sequence) / sizeof(int);

    for (int i=0; i<length; i++)
    {
        if (not_in_memory(frames, page_sequence[i]))
        {
            misses++;
            if (frames_not_full(frames))
            {
                frames[i] = page_sequence[i];
            }
            else
            {
                lru_replacement(frames, length, i, page_sequence);
            }
        }
        print_pages(frames, i, page_sequence);
        printf("\n");
    }
    printf("Page misses: %d\n", misses);
}

int not_in_memory(int *frames, int page)
// Returns 1 if page is not in frames, 0 otherwise.
{
    for (int i=0; i<FRAMES; i++)
    {
        if (page == frames[i])
        {
            return 0;
        }
    }
    return 1;
}

int frames_not_full(int *frames)
// Returns 1 if frames are not full, 0 otherwise.
{
    for (int i=0; i<FRAMES; i++)
    {
        if (frames[i] == 0)
        {
            return 1;
        }
    }
    return 0;
}

void print_pages(int *frames, int index, int *page_sequence)
// Prints index, page, pages in frames.
{
    printf("%d  %d  %d %d %d %d", index, page_sequence[index], frames[0], frames[1], frames[2], frames[3]);
}

void optimal_replacement(int *frames, int length, int index, int *page_sequence)
// Implements the optimal page replacement strategy.
{
    int distances[FRAMES];
    for (int i =0; i<FRAMES; i++)
    {
        distances[i] = length + 1;
    }

    for (int i=0; i<FRAMES; i++)
    {
        for (int j=index+1; j<length; j++)
        {
            if (frames[i] == page_sequence[j])
            {
                distances[i] = j;
                break;
            }
        }
    }
    frames[index_max(distances)] = page_sequence[index];
}

void lru_replacement(int *frames, int length, int index, int *page_sequence)
// Implement the Least Recently Used page replacement strategy.
{
    int distances[FRAMES];
    for (int i =0; i<FRAMES; i++)
    {
        distances[i] = length + 1;
    }

    for (int i=0; i<FRAMES; i++)
    {
        for (int j=index-1; j>=0; j--)
        {
            if (frames[i] == page_sequence[j])
            {
                distances[i] = index - j;
                break;
            }
        }
    }
    frames[index_max(distances)] = page_sequence[index];
}

int index_max(int *distances)
// Returns the index of the item with the maximum value in the array.
{
    int index = 0;
    int max = distances[0];

    for (int i=0; i<FRAMES; i++)
    {
        if (distances[i] > max)
        {
            max = distances[i];
            index = i;
        }
    }
    return index;
}