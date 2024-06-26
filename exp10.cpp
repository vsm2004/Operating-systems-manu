#include <stdio.h>
#include <stdlib.h>

#define MAX_CYLINDERS 200 // Maximum number of cylinders on the disk

// Function to sort the disk request array in ascending order
void sort_requests(int requests[], int n) {
    // Using bubble sort for simplicity
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (requests[j] > requests[j + 1]) {
                // Swap requests[j] and requests[j+1]
                int temp = requests[j];
                requests[j] = requests[j + 1];
                requests[j + 1] = temp;
            }
        }
    }
}

// Function to simulate the SCAN disk scheduling algorithm
void scan(int requests[], int n, int start, char direction) {
    int total_cylinders = MAX_CYLINDERS;
    int head_movement = 0;
    int current_position = start;

    // Sort requests in ascending order
    sort_requests(requests, n);

    // Determine the boundary of SCAN based on direction
    int boundary;
    if (direction == 'left') {
        boundary = 0;
    } else { // direction == 'right'
        boundary = total_cylinders - 1;
    }

    // Scan to the right (ascending order)
    if (direction == 'right') {
        // Go right until the last request <= boundary
        for (int i = 0; i < n; i++) {
            if (requests[i] >= current_position) {
                head_movement += abs(requests[i] - current_position);
                current_position = requests[i];
                printf("Servicing cylinder %d\n", current_position);
            }
        }
        // Go left to the boundary
        head_movement += abs(boundary - current_position);
        current_position = boundary;
        printf("Servicing cylinder %d\n", current_position);
    }
    // Scan to the left (descending order)
    else { // direction == 'left'
        // Go left until the first request >= boundary
        for (int i = n - 1; i >= 0; i--) {
            if (requests[i] <= current_position) {
                head_movement += abs(requests[i] - current_position);
                current_position = requests[i];
                printf("Servicing cylinder %d\n", current_position);
            }
        }
        // Go right to the boundary
        head_movement += abs(current_position - boundary);
        current_position = boundary;
        printf("Servicing cylinder %d\n", current_position);
    }

    printf("Total head movement: %d cylinders\n", head_movement);
}

int main() {
    int requests[] = { 98, 183, 37, 122, 14, 124, 65, 67 };
    int n = sizeof(requests) / sizeof(requests[0]);
    int start = 53; // Starting position of disk arm
    char direction = 'right'; // Direction of disk arm movement ('left' or 'right')

    printf("Disk Scheduling Algorithm: SCAN (Elevator)\n");
    printf("Initial position of disk arm: %d\n", start);
    printf("Direction of movement: %s\n\n", (direction == 'right') ? "right" : "left");

    scan(requests, n, start, direction);

    return 0;
}
