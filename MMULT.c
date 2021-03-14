/*
 * Author: Zijun Hu
 */
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>

#include <sys/shm.h>
#include <sys/time.h>
#include <time.h>
#include <string.h>

#include "MMULT.h"

#define MICRO_SEC_IN_SEC 1000000

/*
 * calculate the result row of the matrix q using matrix m and n from shared memory
 *
 * return an int: Largest number L in the result row
 */
int calculate_matrix(struct shared_use_st *shared_stuff, int i) {
    printf("Child Process: working with row %d\n", i);
    int L = 0;
    for (int k = 0; k < 4; k++) {
        for (int j = 0; j < 4; j++) {
            shared_stuff->q[i][k] += shared_stuff->m[i][j] * shared_stuff->n[j][k];  // Calculate the result row
        }

        if (shared_stuff->q[i][k] > L) {
            L = shared_stuff->q[i][k];  // Storage largest number in L
        }
    }
    return L;
}

/*
 * Print the corresponding matrix from shared memory depend on input char c
 */
void print_matrix(struct shared_use_st *shared_stuff, char c) {
    printf("Matrix %c:\n", c);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (c == 'm') {
                printf("%d     ", shared_stuff->m[i][j]);
            } else if (c == 'n') {
                printf("%d     ", shared_stuff->n[i][j]);
            } else if (c == 'q') {
                printf("%d     ", shared_stuff->q[i][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

/*
 * main process
 */
int main(int argc, char *argv[]) {
    int thread = 4;
    void *shared_memory = NULL;
    struct shared_use_st *shared_stuff;

    srand((unsigned int) getpid());

    // Create shared memory
    int shmid = shmget((key_t) 1234, sizeof(struct shared_use_st), 0666 | IPC_CREAT);
    if (shmid == -1) {
        fprintf(stderr, "shmget failed\n");
        exit(EXIT_FAILURE);
    }

    shared_memory = shmat(shmid, (void *) 0, 0);
    if (shared_memory == (void *) -1) {
        fprintf(stderr, "shmat failed\n");
        exit(EXIT_FAILURE);
    }

    printf("Memory attached at %X\n", (int) shared_memory);
    shared_stuff = (struct shared_use_st *) shared_memory;

    // initialize two input matrix
    matrix m;
    matrix n;
    if (argc == 2) {    // Assign matrix value depend on input argument, more detail please check README.txt
        if (strcmp("test1", argv[1]) == 0) {    // The first test case
            matrix m_1 = {{1, 3, 5,  7},
                          {3, 5, 7,  9},
                          {5, 7, 9,  11},
                          {7, 9, 11, 13}};
            matrix n_1 = {{2, 4,  6,  8},
                          {4, 6,  8,  10},
                          {6, 8,  10, 12},
                          {8, 10, 12, 16}};
            memcpy(m, m_1, sizeof(m_1));
            memcpy(n, n_1, sizeof(n_1));
        } else if (strcmp("test2", argv[1]) == 0) { // the second test case
            matrix m_2 = {{5,  8,  10, 6},
                          {8,  15, 24, 70},
                          {21, 19, 8,  10},
                          {37, 29, 1,  8}};
            matrix n_2 = {{21, 14, 61, 48},
                          {34, 42, 81, 14},
                          {56, 28, 16, 12},
                          {18, 10, 12, 16}};
            memcpy(m, m_2, sizeof(m_2));
            memcpy(n, n_2, sizeof(n_2));
        } else {
            printf("Wrong arguments supplied, please check README.txt.\n");
            exit(EXIT_FAILURE);
        }
    } else if (argc > 2) {
        printf("Too many arguments supplied, please check README.txt.\n");
        exit(EXIT_FAILURE);
    } else {        // Mandatory test case Data
        matrix m_d = {{20, 20, 50, 40},
                      {10, 6,  70, 8},
                      {40, 3,  2,  10},
                      {8,  7,  6,  5}};
        matrix n_d = {{10, 30, 50, 70},
                      {1,  3,  6,  8},
                      {9,  5,  5,  7},
                      {8,  6,  4,  2}};
        memcpy(m, m_d, sizeof(m_d));
        memcpy(n, n_d, sizeof(n_d));
    }

    // Assign matrix and largest int from Matrix into shared memory
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            shared_stuff->m[i][j] = m[i][j];
            shared_stuff->n[i][j] = n[i][j];
        }
    }
    shared_stuff->L = 0;

    struct timeval start, end;
    gettimeofday(&start, NULL);     // time counter start
    for (int i = 0; i < thread; i++) {
        pid_t new_pid = fork();
        switch (new_pid) {
            case -1:
                perror("fork failed");
                exit(1);
            case 0: {
                int L = calculate_matrix(shared_stuff, i);
                if (L > shared_stuff->L) {      // Assign the largest number into shared memory
                    shared_stuff->L = L;
                }
                exit(0);    // Child thread exit after finished the calculation
            }
            default:
                break;
        }
    }

    while (thread > 0) {    // Wait for all thread finish
        wait();
        thread--;
    }
    gettimeofday(&end, NULL);   // time counter stop

    // Print out matrices
    print_matrix(shared_stuff, 'm');
    print_matrix(shared_stuff, 'n');
    print_matrix(shared_stuff, 'q');
    printf("The largest integer in Q is %d\n", shared_stuff->L);

    // Print out time used
    printf("Start Time: %lf sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))\n",
           start.tv_sec + (double) start.tv_usec / MICRO_SEC_IN_SEC);
    printf("End Time: %lf sec from Epoch (1970‐01‐01 00:00:00 +0000 (UTC))\n",
           end.tv_sec + (double) end.tv_usec / MICRO_SEC_IN_SEC);
    printf("\nElapsed Time: %ld micro sec\n",
           ((end.tv_sec * MICRO_SEC_IN_SEC + end.tv_usec) - (start.tv_sec * MICRO_SEC_IN_SEC + start.tv_usec)));

    // Clear used memory
    if (shmdt(shared_memory) == -1) {
        fprintf(stderr, "shmdt failed\n");
        exit(EXIT_FAILURE);
    }
    if (shmctl(shmid, IPC_RMID, 0) == -1) {
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS); // Process ends safely
}