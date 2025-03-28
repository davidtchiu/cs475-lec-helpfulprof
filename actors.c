#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <fcntl.h>
#include "actors.h"

void init_semaphores() {
    destroy_semaphores();
    student_outside = sem_open("/student_outside", O_CREAT, 0600, 0);
    prof_available = sem_open("/prof_available", O_CREAT, 0600, 0);
    question_asked = sem_open("/question_asked", O_CREAT, 0600, 0);
    student_got_resp = sem_open("/student_got_resp", O_CREAT, 0600, 0);
    student_leaving = sem_open("/student_leaving", O_CREAT, 0600, 0);
}

void destroy_semaphores() {
    //close semaphores
	sem_close(student_outside);
	sem_close(prof_available);
	sem_close(question_asked);
	sem_close(student_got_resp);
	sem_close(student_leaving);

	//delete semaphores
	sem_unlink("/student_outside");
	sem_unlink("/prof_available");
	sem_unlink("/question_asked");
	sem_unlink("/student_got_resp");
	sem_unlink("/student_leaving");
}



void* prof_func(void* args) {
    int i = 0;
    while (i < NUM_STUDENTS) {
	   // look busy
        printf("Prof pretends to look busy.\n");

        sem_wait(student_outside);

    	// panic, student has arrived
        printf("Prof is panicking!! \"OMG OMG OMG OMG OMG\"\n");

        sem_post(prof_available);

        sem_wait(question_asked);

    	// yell
        printf("Prof: \"You've got to be kidding. Get back to work .. NOW!!\"\n");

        sem_post(student_got_resp);
        sem_wait(student_leaving);

    	// good bye
        printf("Prof waves goodbye!\n");
	   i++;
    }
    return NULL;
}

void* student_func(void* args) {
    printf("Student %ld arrives at office!\n", pthread_self());
    sem_post(student_outside);

    // ask question
    sem_wait(prof_available);

    // ask question
    printf("Student %ld: \"Hey Prof, do you like tangerines or oranges?\"\n", pthread_self());

    sem_post(question_asked);
    sem_wait(student_got_resp);

    // acknowledge response
    printf("Student %ld: \"Thanks for your help!\"\n", pthread_self());

    sem_post(student_leaving);

    // bye
    printf("Student %ld: \"Goodbye!\"\n", pthread_self());
    return NULL;
}
