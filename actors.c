#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include "actors.h"

void init_semaphores() {
    sem_unlink("/student_outside");
    sem_unlink("/david_available");
    sem_unlink("/question_asked");
    sem_unlink("/student_got_resp");
    sem_unlink("/student_leaving");
    student_outside = sem_open("/student_outside", O_CREAT, 0600, 0);
    david_available = sem_open("/david_available", O_CREAT, 0600, 0);
    question_asked = sem_open("/question_asked", O_CREAT, 0600, 0);
    student_got_resp = sem_open("/student_got_resp", O_CREAT, 0600, 0);
    student_leaving = sem_open("/student_leaving", O_CREAT, 0600, 0);
}

void* david_func(void* args) {
    int i = 0;
    while (i < NUM_STUDENTS) {
	   // look busy
        printf("David: looks busy before students arrive.\n");

        sem_wait(student_outside);

    	// panic, student has arrived
        printf("David is panicking!!\n");

        sem_post(david_available);
        sem_wait(question_asked);

    	// yell
        printf("David: \"OMG. Get back to work now!!\"\n");

        sem_post(student_got_resp);
        sem_wait(student_leaving);

    	// good bye
        printf("David: waves goodbye!\n");
	   i++;
    }
    return NULL;
}

void* student_func(void* args) {
    sem_post(student_outside);
    sem_wait(david_available);

    // ask question
    printf("Student: \"Hey David, do you like bananas or oranges?\"\n");

    sem_post(question_asked);
    sem_wait(student_got_resp);

    // acknowledge response
    printf("Student: \"Got it! Thanks for your help!\"\n");

    sem_post(student_leaving);

    // bye
    printf("Student: \"Goodbye!\"\n");
    return NULL;
}
