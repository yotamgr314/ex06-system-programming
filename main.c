#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "threads_utils.h"

int main() {
    int array_size; // Variable to store the size of the array
    printf("Enter the size of the array: ");
    scanf("%d", &array_size); // Get the size of the array from the user

    // Validate the array size
    if (array_size <= 0) {
        printf("Invalid array size. Exiting.\n");
        return 1; // Exit if the array size is invalid
    }

    int *array = (int *)malloc(array_size * sizeof(int)); // Dynamically allocate memory for the array
    if (array == NULL) {
        printf("Memory allocation failed. Exiting.\n");
        return 1; // Exit if memory allocation fails
    }

    // Populate the array with user input
    printf("Enter %d integers to populate the array:\n", array_size);
    for (int i = 0; i < array_size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &array[i]); // Get the array value from the user
    }

    int num_threads; // Variable to store the number of threads
    printf("Enter the number of threads: ");
    scanf("%d", &num_threads); // Get the number of threads from the user

    // Validate the number of threads
    if (num_threads <= 0 || num_threads > array_size) {
        printf("Invalid number of threads. Exiting.\n");
        free(array); // Free allocated memory before exiting
        return 1; // Exit if the number of threads is invalid
    }

    pthread_t threads[num_threads]; // Array to hold thread identifiers
    ThreadData threadData[num_threads]; // Array to hold data for each thread

    int chunk_size = array_size / num_threads; // Determine the size of the portion for each thread

    // Create threads
    for (int i = 0; i < num_threads; i++) {
        threadData[i].array = array; // Assign the array to the thread's data
        threadData[i].start = i * chunk_size; // Calculate the start index

        // Calculate the end index using simple if-else
        if (i == num_threads - 1) {
            threadData[i].end = array_size; // Last thread gets the remaining elements
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

    free(array); // Free the allocated memory

    return 0; // Exit the program
}
