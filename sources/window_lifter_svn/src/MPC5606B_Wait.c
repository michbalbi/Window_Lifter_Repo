/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_Wait.c%
* Instance:         1
* %version:         1.3 %
* %created_by:      Michele Balbi %
* %date_created:    26 June 2015 %
*=============================================================================*/
/* DESCRIPTION : C source to implement waitms function.                       */
/*============================================================================*/
/* FUNCTION COMMENT : This file contains the C code to implement the waitms   */
/* function prototyped in MPC5606B_Wait.h                                     */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 26/06/2015  |                               | Michele Balbi    */
/* First Draft 																  */
/*----------------------------------------------------------------------------*/
/*  1.1      | 28/06/2015  |                               | Michele Balbi    */
/* Tweaked the for cycle to make it more accurate.               			  */
/*----------------------------------------------------------------------------*/
/*  1.2      | 30/06/2015  |                               | Michele Balbi    */
/* Changes to pass C Code Review Template. 									  */
/*----------------------------------------------------------------------------*/
/*  1.3      | 01/07/2015  |                               | Michele Balbi    */
/* Now using Continental's own typedefs.       			  */
/* TO-DO: See why the counter does not correspond to what it is supposed to.  */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B_Wait.h"

/* Functions macros, constants, types and datas         */
/* ---------------------------------------------------- */
/* Functions macros */

/*==================================================*/ 
/* Definition of constants                          */
/*==================================================*/ 
/* BYTE constants */


/* WORD constants */


/* LONG and STRUCTURE constants */



/*======================================================*/ 
/* Definition of RAM variables                          */
/*======================================================*/ 
/* BYTE RAM variables */


/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */


/*======================================================*/ 
/* close variable declaration sections                  */
/*======================================================*/ 

/* Private defines */


/* Private functions prototypes */
/* ---------------------------- */



/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */
/**************************************************************
 *  Name                 : inline_func	2
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Private functions */
/* ----------------- */
/**************************************************************
 *  Name                 : private_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/


/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	waitms
 *  Description          :	Cycles the MCU in a for loop for 
 							the specified miliseconds
 *  Parameters           :  uint16_t ms
 *  Return               :	void
 *  Critical/explanation :  No
 **************************************************************/
void waitms(T_UWORD ms) {
	T_ULONG i;
	T_UBYTE dummy_counter=0;
	for(i=((T_ULONG)8000*ms);i>0;i--){
		dummy_counter++;
	}
}