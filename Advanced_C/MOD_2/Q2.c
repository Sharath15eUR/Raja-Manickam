#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <stdbool.h>
#include <signal.h>
#include <time.h>

// Global variables
int N;
volatile sig_atomic_t keep_running = 1;

// Signal handler
void handle_sigint(int sig) {
    printf("\nSIGINT received. Ignoring Ctrl+C and continuing execution...\n");
}

// Function to check if a number is prime
bool is_prime(int num) {
    if (num < 2) return false;
    for (int i = 2; i * i <= num; i++) {
        if (num % i == 0) return false;
    }
    return true;
}

// Thread A function: calculate sum of first N primes
void* thread_A_function(void* arg) {
    time_t start = time(NULL);

    int count = 0, num = 2, sum = 0;
    while (count < N) {
        if (!keep_running) break;
        if (is_prime(num)) {
            sum += num;
            count++;
        }
        num++;
    }

    time_t end = time(NULL);
    double time_taken = difftime(end, start);

    printf("Thread A: Sum of first %d prime numbers is %d\n", N, sum);
    printf("Thread A execution time: %.2f seconds\n", time_taken);

    pthread_exit(NULL);
}

// Thread B: prints message every 2 seconds
void* thread_B_function(void* arg) {
    time_t start = time(NULL);
    int duration = 100;
    for (int i = 0; i < duration && keep_running; i += 2) {
        printf("Thread 1 running (every 2 seconds)\n");
        sleep(2);
    }
    time_t end = time(NULL);
    printf("Thread B execution time: %.2f seconds\n", difftime(end, start));
    pthread_exit(NULL);
}

// Thread C: prints message every 3 seconds
void* thread_C_function(void* arg) {
    time_t start = time(NULL);
    int duration = 100;
    for (int i = 0; i < duration && keep_running; i += 3) {
        printf("Thread 2 running (every 3 seconds)\n");
        sleep(3);
    }
    time_t end = time(NULL);
    printf("Thread C execution time: %.2f seconds\n", difftime(end, start));
    pthread_exit(NULL);
}

int main() {
    // Set signal handler
    signal(SIGINT, handle_sigint);

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

    printf("All threads completed execution.\n");

    return 0;
}
