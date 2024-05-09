/*
 * Scheduler_private.h
 *
 * Created: 24/01/2024 03:39:56 م
 *  Author: Azza Saeed
 */ 


#ifndef SCHEDULER_PRIVATE_H_
#define SCHEDULER_PRIVATE_H_

typedef struct {
	u16 task_u16periodicity;
	u16 task_u16FirstDelay;
	void (*Taskfunc)(void);
	u8 task_u8state;
}Task_Parameters_t; 

#define TASK_RESUMED 0
#define TASK_SUSPEND 1

#define STD_OK 1
#define STD_NOK 0

static void voidScheduler(void);

#endif /* SCHEDULER_PRIVATE_H_ */