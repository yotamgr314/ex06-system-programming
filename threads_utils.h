#ifndef THREADS_UTILS_H
#define THREADS_UTILS_H

// Structure to hold data for each thread
typedef struct {
    int *array;    // Pointer to the array
    int start;     // Start index for the thread
    int end;       // End index for the thread
    int result;    // Number of even numbers found by the thread
} ThreadData;

// Function executed by each thread
void* count_even_numbers(void* arg);

#endif
