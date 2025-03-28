#ifndef ACTORS_H_INCL
#define ACTORS_H_INCL

// defined in an external file
extern sem_t* student_outside;
extern sem_t* prof_available;
extern sem_t* question_asked;
extern sem_t* student_got_resp;
extern sem_t* student_leaving;

// function declarations
void init_semaphores();
void destroy_semaphores();
void* prof_func(void* args);
void* student_func(void* args);

extern int NUM_STUDENTS;

#endif