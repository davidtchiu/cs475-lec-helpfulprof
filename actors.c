#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include "actors.h"

void init_semaphores() {
    sem_unlink("/student_outside");
    sem_unlink("/adam_available");
    sem_unlink("/question_asked");
    sem_unlink("/student_got_resp");
    sem_unlink("/student_leaving");
    student_outside = sem_open("/student_outside", O_CREAT, 0600, 0);
    adam_available = sem_open("/adam_available", O_CREAT, 0600, 0);
    question_asked = sem_open("/question_asked", O_CREAT, 0600, 0);
    student_got_resp = sem_open("/student_got_resp", O_CREAT, 0600, 0);
    student_leaving = sem_open("/student_leaving", O_CREAT, 0600, 0);
}

void destroy_semaphores() {
    //close semaphores
	sem_close(student_outside);
	sem_close(adam_available);
	sem_close(question_asked);
	sem_close(student_got_resp);
	sem_close(student_leaving);

	//delete semaphores
	sem_unlink("/student_outside");
	sem_unlink("/adam_available");
	sem_unlink("/question_asked");
	sem_unlink("/student_got_resp");
	sem_unlink("/student_leaving");
}



void* adam_func(void* args) {
    int i = 0;
    while (i < NUM_STUDENTS) {
	   // look busy
        printf("Adam pretends to look busy.\n");

        sem_wait(student_outside);

    	// panic, student has arrived
        printf("Adam is panicking!! \"OMG OMG OMG OMG OMG\"\n");

        sem_post(adam_available);
        sem_wait(question_asked);

    	// yell
        printf("Adam: \"OMG. Get back to work now!!\"\n");

        sem_post(student_got_resp);
        sem_wait(student_leaving);

    	// good bye
        printf("Adam waves goodbye!\n");
	   i++;
    }
    return NULL;
}

void* student_func(void* args) {
    printf("Student %ld arrives at office!\n", pthread_self());
    sem_post(student_outside);

    // ask question
    sem_wait(adam_available);

    // ask question
    printf("Student %ld: \"Hi Adam, do you like tangerines or oranges?\"\n", pthread_self());

    sem_post(question_asked);
    sem_wait(student_got_resp);

    // acknowledge response
    printf("Student %ld: \"Thanks for your help!\"\n", pthread_self());

    sem_post(student_leaving);

    // bye
    printf("Student %ld: \"Goodbye!\"\n", pthread_self());
    return NULL;
}
