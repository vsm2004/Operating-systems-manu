#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_FRAMES 3 // Maximum number of frames in memory

void fifo(int pages[], int n, int capacity) {
    int frames[MAX_FRAMES];
    bool in_memory[MAX_FRAMES] = { false };
    int page_faults = 0;
    int next_frame_index = 0; // Index to track the next frame to replace

    printf("Page Reference String: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    for (int i = 0; i < n; i++) {
        int page = pages[i];
        bool page_fault = true;

        // Check if page is already in memory
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == page) {
                page_fault = false;
                break;
            }
        }

        // Page fault: page needs to be brought into memory
        if (page_fault) {
            printf("Page %d caused a page fault.\n", page);

            // Replace the oldest page in memory (FIFO)
            frames[next_frame_index] = page;
            next_frame_index = (next_frame_index + 1) % capacity;

            page_faults++;
        } else {
            printf("Page %d is already in memory.\n", page);
        }

        // Print current state of memory frames
        printf("Current state of frames: ");
        for (int j = 0; j < capacity; j++) {
            if (frames[j] == -1) {
                printf("[ ] ");
            } else {
                printf("[%d] ", frames[j]);
            }
        }
        printf("\n\n");
    }

    printf("Total Page Faults: %d\n", page_faults);
}

int main() {
    int pages[] = { 7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2 };
    int n = sizeof(pages) / sizeof(pages[0]);
    int capacity = MAX_FRAMES;

    fifo(pages, n, capacity);

    return 0;
}
