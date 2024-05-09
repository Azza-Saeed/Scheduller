/*
 * Scheduler_interface.h
 *
 * Created: 24/01/2024 03:39:03 م
 *  Author: Azza Saeed
 */ 


#ifndef SCHEDULER_INTERFACE_H_
#define SCHEDULER_INTERFACE_H_

#include "Std_Types.h"

void Start_voidSchaduler(void);

u8 Create_u8task(u8 task_u8priority, u16 task_u16periodicity,u16 task_u16FirstDelay, void (*CopyTaskfunc)(void));

void Resume_voidTask(u8 task_u8priority);

void Suspend_voidTask(u8 task_u8priority);

void Delete_voidTask(u8 task_u8priority);


#endif /* SCHEDULER_INTERFACE_H_ */