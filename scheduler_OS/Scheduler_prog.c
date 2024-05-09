/*
 * Scheduler.c
 *
 * Created: 24/01/2024 03:38:23 م
 *  Author: Azza Saeed
 */ 

#include "Std_Types.h"
#include "bit_math.h"

#include "TIMR0_int.h"
#include "TIMR0_config.h"
#include "GIE.h"

#include "Scheduler_interface.h"
#include "Scheduler_config.h"
#include "Scheduler_private.h"


Task_Parameters_t System_Tasks[MAXIMUM_NUMBER_TASKS]={{0}};
	
void Start_voidSchaduler(void)
{
	/* Function to run when the interrupt comes*/
	TIMER0_void_Init();
	TIMER0_void_SetCompareVal(COMPARE_MATCH_VALUE);
	GIE_voidGlobalInterruptEnable();
	TIMER0_void_SetCTCCallBack(&voidScheduler);
	TIMER0_void_EnableCTCInt();
}

u8 Create_u8task(u8 task_u8priority, u16 task_u16periodicity,u16 task_u16FirstDelay, void (*CopyTaskfunc)(void))
{
	u8 Local_u8ErrorState = STD_OK;
	
	/* Check if there is another task in the index or not */
		if( System_Tasks[task_u8priority].Taskfunc == 0 )
		{
			System_Tasks[task_u8priority].task_u16periodicity= task_u16periodicity;
			System_Tasks[task_u8priority].task_u16FirstDelay= task_u16FirstDelay;
			System_Tasks[task_u8priority].Taskfunc= CopyTaskfunc;
			System_Tasks[task_u8priority].task_u8state = TASK_RESUMED;
		}else{
			Local_u8ErrorState = STD_NOK;
		}
		
		return Local_u8ErrorState;
}

void Resume_voidTask(u8 task_u8priority)
{
	System_Tasks[task_u8priority].task_u8state = TASK_RESUMED;
}

void Suspend_voidTask(u8 task_u8priority)
{
	System_Tasks[task_u8priority].task_u8state = TASK_SUSPEND;
}

void Delete_voidTask(u8 task_u8priority)
{
	System_Tasks[task_u8priority].Taskfunc = 0;
}
static void voidScheduler(void)
{
	u8 Local_u8TaskCounter;
	
	 /* Loop on all tasks to check thier periodicity */
	for(Local_u8TaskCounter=0;Local_u8TaskCounter<MAXIMUM_NUMBER_TASKS;Local_u8TaskCounter++)
	{
		if( System_Tasks[Local_u8TaskCounter].task_u8state == TASK_RESUMED )
		{
			if( System_Tasks[Local_u8TaskCounter].task_u16FirstDelay == 0 )
			{
				/* Invoke this function in */
				if( System_Tasks[Local_u8TaskCounter].Taskfunc != 0 )
				{
					System_Tasks[Local_u8TaskCounter].Taskfunc();
					/* Assign the periodicity in the first delay */
					System_Tasks[Local_u8TaskCounter].task_u16FirstDelay = System_Tasks[Local_u8TaskCounter].task_u16periodicity -1;
				}
			}else{
				/* Decreament the first delay */
				System_Tasks[Local_u8TaskCounter].task_u16FirstDelay --;
			}
		}else{
			// Do Nothing
		}
	}
	
}