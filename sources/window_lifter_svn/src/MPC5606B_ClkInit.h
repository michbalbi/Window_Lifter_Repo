/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MCP5606B_ClkInit.h%
* Instance:         1
* %version:         1.1 %
* %created_by:      Michele Balbi %
* %date_created:    2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for clock initialization functions.		      */
/*============================================================================*/
/* FUNCTION COMMENT :   Contains prototypes for clock init functions.         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 25/06/2015  |                               | Michele Balbi    */
/* First Draft 																  */
/*----------------------------------------------------------------------------*/
/*  1.1      | 30/06/2015  |                               | Michele Balbi    */
/* Formatting to pass C code review.                                          */
/*============================================================================*/

#ifndef _CLK_INIT_H_
#define _CLK_INIT_H_

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "MPC5606B_Mapper.h"

/* Exported types and constants */
/* ---------------------------- */

/* Types definition */
/* typedef */


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


/* WORDS */


/* LONGS and STRUCTURES */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Exported functions prototypes and macros */
/* ---------------------------------------- */

/* Functions prototypes */

extern void initModesAndClock(void);

extern void initPeriClkGen(void);

extern void disableWatchdog(void);

/* Functions macros */


/* Exported defines */


#endif