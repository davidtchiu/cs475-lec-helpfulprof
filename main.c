#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <fcntl.h>
#include <pthread.h>
#include "actors.h"

/* globals */
sem_t* student_outside;
sem_t* prof_available;
sem_t* question_asked;
sem_t* student_got_resp;
sem_t* student_leaving;

int NUM_STUDENTS;

int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("usage: %s <num students>\n", argv[0]);
		exit(0);
	}
	NUM_STUDENTS = atoi(argv[1]);

	init_semaphores();

	//create professor and student threads
	pthread_t *prof = malloc(sizeof(pthread_t));
	pthread_t *students = malloc(NUM_STUDENTS * sizeof(pthread_t));

	pthread_create(prof, NULL, prof_func, NULL);
	for (int i = 0; i < NUM_STUDENTS; i++) {
		pthread_create(&students[i], NULL, student_func, NULL);
	}

	for (int i = 0; i < NUM_STUDENTS; i++) {
		pthread_join(students[i], NULL);
	}
	pthread_join(*prof, NULL);

	free(prof);
	prof = NULL;

	free(students);
	students = NULL;

	return 0;
}
