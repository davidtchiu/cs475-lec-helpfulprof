#ifndef ACTORS_H_INCL
#define ACTORS_H_INCL

#define NUM_STUDENTS 4

// defined in an external file
extern sem_t* student_outside;
extern sem_t* david_available;
extern sem_t* question_asked;
extern sem_t* student_got_resp;
extern sem_t* student_leaving;

// function declarations
void init_semaphores();
void* david_func(void* args);
void* student_func(void* args);

#endif