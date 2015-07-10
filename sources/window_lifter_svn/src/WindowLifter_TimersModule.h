/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %WindowLifter_TimersModule.h%
* Instance:         1
* %version:         1 %
* %created_by:      Michele Balbi %
* %date_created:    2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for the timer functions.                         */
/*============================================================================*/
/* FUNCTION COMMENT :  This files contains the prototypes for the implemented */
/* timer functions.                                                           */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 10/07/2015  |                               | Michele Balbi    */
/* First Draft.																  */
/*============================================================================*/

#ifndef _TIMER_MODULE_                           /* To avoid double inclusion */
#define _TIMER_MODULE_

/* Includes */
/* -------- */
#include "conti_typedefs.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */

typedef enum { 			/* enum to hold movement value */
	DISABLED,
	AUTO_UP,
	AUTO_DOWN,
	MANUAL_UP,
	MANUAL_DOWN,
	PINCH
}MovementList;

typedef enum {			/* enum to hold a value depending on the pressed button*/
	NONE,
	BUTTON_UP,
	BUTTON_DOWN
}ButtonList;

/*==================================================*/ 
/* Declaration of exported constants                */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTES */
extern T_UBYTE rub_led_level;

/* WORDS */


/* LONGS and STRUCTURES */
extern MovementList re_move;

extern ButtonList re_button_pressed;

/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */
extern void TimersInit(void);
extern void Timer10ms_INT_handler(void);
extern void Timer500ms_INT_handler(void);
extern void Timer400ms_INT_handler(void);
extern void Timer5s_INT_handler(void);


/* Functions macros */


/* Exported defines */

/* Defines for buttons and pinch signal pins, 				 */
/* and pressed/active states. Correspondence w/ GPIO number. */
#define UP_BUTTON 		6
#define DOWN_BUTTON 	7
#define PRESSED 		0

#define PINCH_SIGNAL 	66 
#define ACTIVE_STATE 	0

#define DOWN_LED 		46
#define UP_LED 			47

/* Defines for highest and lowest LED. Correspondence w/ PORTC GPIO number. */
#define LED_LEVEL_MAX 	43 	 
#define LED_LEVEL_MIN 	34


#endif


