#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <time.h>

// Global variable for N
int N;

// Function to check if a number is prime
bool is_prime(int num) {
    if (num < 2)
        return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0)
            return false;
    }
    return true;
}

// Thread A: Calculate sum of first N prime numbers
void* thread_A_function(void* arg) {
    int count = 0, num = 2, sum = 0;
    while (count < N) {
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }
    printf("Thread A: Sum of first %d prime numbers is %d\n", N, sum);
    pthread_exit(NULL);
}

// Thread B: Print message every 2 seconds
void* thread_B_function(void* arg) {
    int duration = 100;
    for (int i = 0; i < duration; i += 2) {
        printf("Thread 1 running (every 2 seconds)\n");
        sleep(2);
    }
    pthread_exit(NULL);
}

// Thread C: Print message every 3 seconds
void* thread_C_function(void* arg) {
    int duration = 100;
    for (int i = 0; i < duration; i += 3) {
        printf("Thread 2 running (every 3 seconds)\n");
        sleep(3);
    }
    pthread_exit(NULL);
}

int main() {
    pthread_t threadA, threadB, threadC;

    printf("Enter the value of N: ");
    scanf("%d", &N);

    // Create threads
    pthread_create(&threadA, NULL, thread_A_function, NULL);
    pthread_create(&threadB, NULL, thread_B_function, NULL);
    pthread_create(&threadC, NULL, thread_C_function, NULL);

    // Wait for threads to finish
    pthread_join(threadA, NULL);
    pthread_join(threadB, NULL);
    pthread_join(threadC, NULL);

    printf("All threads finished execution.\n");

    return 0;
}
