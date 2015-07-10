/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MPC5606B_PIT_lib.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    08 July 2015 %
*=============================================================================*/
/* DESCRIPTION : Provides needed defines and macros to manage timers modules. */
/*============================================================================*/
/* FUNCTION COMMENT : The PIT library makes it easier to configure and use    */
/*					  the timers.                                             */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 08/07/2015  |                               | Michele Balbi    */
/* First Draft of file.                                          			  */
/*============================================================================*/

#ifndef _MPC5606B_PIT_LIB_
#define _MPC5606B_PIT_LIB_

#include "MPC5606B.h"
#include "MPC5606B_ClkInit.h"

/* Timer Macros */

#define TIMER_INIT()						(PIT.PITMCR.R = 0)
#define TIMER_LOAD_VALUE_TICKS(ticks,timer)	(PIT.CH[timer].LDVAL.R = ticks)
#define TIMER_LOAD_VALUE_MS(ms,timer)		(PIT.CH[timer].LDVAL.R = (ms*(CLK_FREQ/1000U))-1U)
#define TIMER_LOAD_VALUE_US(us,timer)		(PIT.CH[timer].LDVAL.R = (us*(CLK_FREQ/1000000U))-1U)
#define TIMER_GET_VALUE_TICKS(timer)		(PIT.CH[timer].CVAL.R)
#define TIMER_GET_VALUE_MS(timer)			((PIT.CH[timer].LDVAL.R - PIT.CH[timer].CVAL.R)/(CLK_FREQ/1000U))

#define TIMER_ENABLE_INT(timer)				(PIT.CH[timer].TCTRL.B.TIE = 1)
#define TIMER_DISABLE_INT(timer)			(PIT.CH[timer].TCTRL.B.TIE = 0)
#define TIMER_START(timer)					(PIT.CH[timer].TCTRL.B.TEN = 1)
#define TIMER_STOP(timer)					(PIT.CH[timer].TCTRL.B.TEN = 0)
#define TIMER_IS_RUNNING(timer)				(PIT.CH[timer].TCTRL.B.TEN)
#define TIMER_CLEAR_INT_FLAG(timer)			(PIT.CH[timer].TFLG.B.TIF = 1)




#endif