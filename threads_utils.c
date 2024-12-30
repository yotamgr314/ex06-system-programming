#include <pthread.h>
#include <stdio.h>
#include "threads_utils.h"

// Function executed by each thread to count even numbers
void* count_even_numbers(void* arg){
    ThreadData *data = (ThreadData*)arg; // Cast argument to ThreadData structure
    data->result = 0; // Initialize the result to 0

    // Loop through the assigned portion of the array
    for (int i = data->start; i < data->end; i++) {
        if (data->array[i] % 2 == 0) { // Check if the number is even
            data->result++; // Increment the count if even
        }
    }

    pthread_exit(NULL); // Exit the thread
}
