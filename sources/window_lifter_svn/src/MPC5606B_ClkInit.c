/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %MPC5606B_ClkInit.c%
* Instance:         1
* %version:         1.3 %
* %created_by:      Michele Balbi %
* %date_created:    20 June 2015 %
*=============================================================================*/
/* DESCRIPTION : C file for clocks initialization                             */
/*============================================================================*/
/* FUNCTION COMMENT : This file configures running modes and clock            */
/*                    initialization for the MCU and its peripherals.         */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 20/06/2015  |                               | Michele Balbi    */
/* 	First Draft.                                                              */
/*----------------------------------------------------------------------------*/
/*  1.1      | 21/06/2015  |                               | Michele Balbi    */
/* 	Corrected invalid write to a read-only register.                          */
/*----------------------------------------------------------------------------*/
/*  1.2      | 26/06/2015  |                               | Michele Balbi    */
/* 	Now using defines from MPC5606_Mapper.h                                   */
/*----------------------------------------------------------------------------*/
/*  1.3      | 30/06/2015  |                               | Michele Balbi    */
/* 	Corrections and formatting for C Code Review template compliance.         */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "MPC5606B_ClkInit.h"

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
 *  Name                 :	initModesAndClock
 *  Description          :	Initializes running mode and clock of the MCU.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  yes
 **************************************************************/
void initModesAndClock(void) {
  ME.MER.R = 0x0000001D;          /* Enable DRUN, RUN0, SAFE, RESET modes */
                                  /* Initialize PLL before turning it on: */
  CGM.FMPLL_CR.R = 0x02400100;    /* 8 MHz xtal: Set PLL0 to 64 MHz */
  								  //  Divide by 64, 8 in ODF, 1 in IDF
  ME.RUN[0].R = 0x001F0074;       /* RUN0 cfg: 16MHzIRCON,OSC0ON,PLL0ON,syclk=PLL0 */
  ME.RUNPC[1].R = 0x00000010; 	  /* Peri. Cfg. 1 settings: only run in RUN0 mode */
  
  ME.PCTL[PCTL_SIUL].R = 0x01; 	  /* MPC56xxB/S SIU: select ME.RUNPC[1] */	  
  ME.PCTL[PCTL_PIT].R = 0x01;
  ME.PCTL[PCTL_EMIOS_0].R = 0x01;
                                  
  /* Mode Transition to enter RUN0 mode: */
  ME.MCTL.R = 0x40005AF0;         /* Enter RUN0 Mode & Key */
  ME.MCTL.R = 0x4000A50F;         /* Enter RUN0 Mode & Inverted Key */  
  while (ME.GS.B.S_MTRANS) {}     /* Wait for mode transition to complete */    
                                  /* Note: could wait here using timer and/or I_TC IRQ */
  while(ME.GS.B.S_CURRENTMODE != 4) {} /* Verify RUN0 is the current mode */
}


/**************************************************************
 *  Name                 :	initPeriClkGen
 *  Description          :	Initializes clock of peripheral sets which will
 							be needed in the project.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  yes
 **************************************************************/
 void initPeriClkGen(void) {
/* Use the following code as required for MPC56xxB or MPC56xxS:*/
  CGM.SC_DC[2].R = 0x80;   /* MPC56xxB/S: Enable peri s	et 3 sysclk divided by 1 */
}


/**************************************************************
 *  Name                 :	disableWatchdog
 *  Description          :	Disables the MCU's watchdog.
 *  Parameters           :  void
 *  Return               :	void
 *  Critical/explanation :  yes
 **************************************************************/
void disableWatchdog(void) {
  SWT.SR.R = 0x0000c520;     /* Write keys to clear soft lock bit */
  SWT.SR.R = 0x0000d928; 
  SWT.CR.R = 0x8000010A;     /* Clear watchdog enable (WEN) */
} 