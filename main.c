#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threads_utils.h"

#define ARRAY_SIZE 10 // Size of the array

int main() {
    int num_threads; // Variable to store the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads); // Get the number of threads from the user

    // Validate the number of threads
    if (num_threads <= 0) {
        printf("Invalid number of threads. Exiting.\n");
        return 1; // Exit if the number of threads is invalid
    }

    int array[ARRAY_SIZE]; // Declare the array
    for (int i = 0; i < ARRAY_SIZE; i++) { // Populate the array with values 1 to ARRAY_SIZE
        array[i] = i + 1;
    }

    pthread_t threads[num_threads]; // Array to hold thread identifiers
    ThreadData threadData[num_threads]; // Array to hold data for each thread

    int chunk_size = ARRAY_SIZE / num_threads; // Determine the size of the portion for each thread

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        threadData[i].array = array; // Assign the array to the thread's data
        threadData[i].start = i * chunk_size; // Calculate the start index

        // Calculate the end index using simple if-else
        if (i == num_threads - 1) {
            threadData[i].end = ARRAY_SIZE; // Last thread gets the remaining elements
        } else {
            threadData[i].end = (i + 1) * chunk_size; // Other threads get their chunk size
        }

        pthread_create(&threads[i], NULL, count_even_numbers, &threadData[i]); // Create the thread
    }

    int total_even_numbers = 0; // Initialize the total count to 0

    // Wait for all threads to complete and sum the results
    for (int i = 0; i < num_threads; i++) {
        pthread_join(threads[i], NULL); // Wait for the thread to finish
        total_even_numbers += threadData[i].result; // Add the result to the total count
    }

    // Print the total number of even numbers
    printf("Total even numbers: %d\n", total_even_numbers);

    return 0; // Exit the program
}
