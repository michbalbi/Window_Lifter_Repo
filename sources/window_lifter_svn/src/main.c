/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %main.c%
* Instance:         1
* %version:         1.2 %
* %created_by:      Michele Balbi %
* %date_created:    29 June 2015 %
*=============================================================================*/
/* DESCRIPTION : C source Window Lifter file                                  */
/*============================================================================*/
/* FUNCTION COMMENT : This file contains the C code for the Window Lifter	  */
/* application.                                                              */
/*                                                                            */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 25/06/2015  |                               | Michele Balbi    */
/* First Draft 																  */
/*----------------------------------------------------------------------------*/
/*  1.1      | 29/06/2015  |                               | Michele Balbi    */
/* Reorganizing of functions order and renaming according to conventions.     */
/*----------------------------------------------------------------------------*/
/*  1.2      | 30/06/2015  |                               | Michele Balbi    */
/* Changes to pass C Code Review Template. 									  */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "MPC5606B_Mapper.h"
#include "conti_typedefs.h"

#include "MPC5606B_ClkInit.h"
#include "MPC5606B_Wait.h"

#define UP_BUTTON 		6
#define DOWN_BUTTON 	7
#define PRESSED 		0
#define PINCH_SIGNAL 	66 
#define ACTIVE			0

#define DOWN_LED 46
#define UP_LED 47


/* Defines for highest and lowest LED. Correspondence w/ PORTC GPIO number */
#define LED_LEVEL_MAX 43 	 
#define LED_LEVEL_MIN 34

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

/* All LEDs are turned on at the start */
T_UBYTE rub_led_level = LED_LEVEL_MAX; 

/* WORD RAM variables */


/* LONG and STRUCTURE RAM variables */

enum { 			/* enum to hold movement value */
	DISABLED,
	AUTO_UP,
	AUTO_DOWN,
	MANUAL_UP,
	MANUAL_DOWN,
	PINCH
}re_move;

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
 *  Name                 :	Button_handler
 *  Description          :
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  This is the External Interrupt handler
 							 for up and down buttons
 **************************************************************/
void Button_handler(void){
	/* Check if the UP button was the one that generated the External Interrupt */
	if (EXTINT_GET_FLAG(1) && (re_move==DISABLED)){
		
		/* 10ms wait to avoid invalid inputs */
		waitms(10);
		
		/* If button is still pressed, auto mode is selected */
		if(INPUT_STATE(UP_BUTTON)==PRESSED){
			re_move = AUTO_UP;
		}
		
		/* 500ms wait to enable manual mode */
		waitms(500);
		
		/* If button is still pressed, manual mode is selected */
		if(INPUT_STATE(UP_BUTTON)==PRESSED){
			re_move = MANUAL_UP;
		}
		
		/* while loop to turn on LEDs with 400ms wait interval in auto mode.
		   We check if the highest LED has been turned on, if auto mode is still
		   enabled and if the up button is still pressed						*/		
		while((rub_led_level<LED_LEVEL_MAX) && (re_move==AUTO_UP)){
			waitms(400);
			OUTPUT_HIGH(UP_LED);
			if(re_move==AUTO_UP){
				rub_led_level++;
				OUTPUT_HIGH(rub_led_level);
			}
		}
		
		/* while loop to turn on LEDs with 400ms wait interval in manual mode.
		   We check if the highest LED has been turned on, if manual mode is still
		   enabled and if the up button is still pressed						*/	
		while((rub_led_level<LED_LEVEL_MAX) && (INPUT_STATE(UP_BUTTON)==PRESSED) && (re_move==MANUAL_UP)){
			waitms(400);
			OUTPUT_HIGH(UP_LED);
			if(re_move==MANUAL_UP){
				rub_led_level++;
				OUTPUT_HIGH(rub_led_level);
			}
		}
		
		re_move = DISABLED;
		OUTPUT_LOW(UP_LED);
		
		/* Interrupt flag clear to enable next interrupts */
		EXTINT_CLEAR_INT_FLAG(1);
	}
	
	/* Check if the DOWN button was the one that generated the External Interrupt */
	if (EXTINT_GET_FLAG(2) && (re_move==DISABLED)){
		
		/* 10ms wait to avoid invalid inputs */
		waitms(10); 					
		
		/* If button is still pressed, auto mode is selected*/
		if(INPUT_STATE(DOWN_BUTTON)==PRESSED){		
			re_move = AUTO_DOWN;		
		}
		
		/* 500ms wait to enable manual mode */
		waitms(500);
		
		/* If button is still pressed, manual mode is selected */
		if(INPUT_STATE(DOWN_BUTTON)==PRESSED){		
			re_move = MANUAL_DOWN;
		}
		
		/* while loop to turn off LEDs with 400ms wait interval in auto mode.
		   We check if the lowest LED has been turned off and if auto mode is still
		   enabled																*/
		while(rub_led_level>=LED_LEVEL_MIN && re_move==AUTO_DOWN){
			waitms(400);
			OUTPUT_HIGH(DOWN_LED);
			OUTPUT_LOW(rub_led_level);
			rub_led_level--;
		}
		
		/* while loop to turn off LEDs with 400ms wait interval in manual mode.
		   We check if the lowest LED has been turned off, if manual mode is still
		   enabled and if the down button is still pressed						*/			
		while((rub_led_level>=LED_LEVEL_MIN) && (INPUT_STATE(DOWN_BUTTON)==PRESSED) && (re_move==MANUAL_DOWN)){
			waitms(400);
			OUTPUT_HIGH(DOWN_LED);
			OUTPUT_LOW(rub_led_level);
			rub_led_level--;
		}
		
		OUTPUT_LOW(DOWN_LED);
		re_move = DISABLED;
		
		/* Interrupt flag clear to enable next interrupts */
		EXTINT_CLEAR_INT_FLAG(2);
	}
	
}

/**************************************************************
 *  Name                 :	Pinch_handler
 *  Description          :
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  This is the External Interrupt handler
 							 for the pinch signal input
 **************************************************************/
void Pinch_handler(void){

	/* Check that the pinch signal pin was effectively the one that generated the interrupt */
	if (EXTINT_GET_FLAG(21)){
		
		/* 10ms wait to filter invalid inputs */
		waitms(10);
		
		/* If the pinch input is still present and there is any up movement
		   we stop it and turn LEDs off									 */
		if((INPUT_STATE(PINCH_SIGNAL)==ACTIVE) && ((re_move==AUTO_UP) || (re_move==MANUAL_UP))){
			re_move = PINCH;
			OUTPUT_LOW(UP_LED);
			OUTPUT_HIGH(DOWN_LED);
			
			/* while loop to turn off LEDs in 400ms intervals with check for lowest LED*/
			while(rub_led_level>=LED_LEVEL_MIN){
				waitms(400);
				OUTPUT_LOW(rub_led_level);
				rub_led_level--;
			}
			
			OUTPUT_LOW(DOWN_LED);
			
			/* 5s wait after turning off all LEDs, by requirement */
			waitms(5000);
			re_move = DISABLED;
		}
		
		/* Clear interrupt flag to allow next interrupts */
		EXTINT_CLEAR_INT_FLAG(21);
	}
}

/* Exported functions */
/* ------------------ */
/**************************************************************
 *  Name                 :	export_func
 *  Description          :
 *  Parameters           :  [Input, Output, Input / output]
 *  Return               :
 *  Critical/explanation :    [yes / No]
 **************************************************************/

/**************************************************************
 *  Name                 :	main
 *  Description          :
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  The main routine initializes GPIO
 							pins, interrupts, clocks.
 **************************************************************/
void main(void) {

	initModesAndClock();    /* Initialize mode entries and system clock */
	disableWatchdog();      /* Disable watchdog */
	initPeriClkGen();       /* Initialize peripheral clock generation for DSPIs */
    
    /* LED pins as outputs */
    GPIO_AS_OUTPUT(PC2);
    GPIO_AS_OUTPUT(PC3);
    GPIO_AS_OUTPUT(PC4);
    GPIO_AS_OUTPUT(PC5);
    GPIO_AS_OUTPUT(PC6);
    GPIO_AS_OUTPUT(PC7);
    GPIO_AS_OUTPUT(PC8);
    GPIO_AS_OUTPUT(PC9);
    GPIO_AS_OUTPUT(PC10);
    GPIO_AS_OUTPUT(PC11);
    GPIO_AS_OUTPUT(DOWN_LED);
    GPIO_AS_OUTPUT(UP_LED);  
    
    /* Button pins and pinch-detecttion init as inputs w/ buffer and pull-up */
    GPIO_AS_INPUT(UP_BUTTON);
    GPIO_AS_INPUT(DOWN_BUTTON);
    GPIO_AS_INPUT(PINCH_SIGNAL);
    
    /* All LEDs are on at the start (window is completely closed) */
    OUTPUT_HIGH(PC2);
    OUTPUT_HIGH(PC3);
    OUTPUT_HIGH(PC4);
    OUTPUT_HIGH(PC5);
    OUTPUT_HIGH(PC6);
    OUTPUT_HIGH(PC7);
    OUTPUT_HIGH(PC8);
    OUTPUT_HIGH(PC9);
    OUTPUT_HIGH(PC10);
    OUTPUT_HIGH(PC11);
    OUTPUT_LOW(DOWN_LED);
    OUTPUT_LOW(UP_LED);
    
    /* INT init, interupt handlers installation */
    INT_SW_VECTOR_MODE();
    INTC_InstallINTCInterruptHandler(Button_handler, EXT0_Vector, PRIORITY8);
    INTC_InstallINTCInterruptHandler(Pinch_handler, EXT2_Vector, PRIORITY10);
    
    /* External Interrupts enabling for falling-edge */
    EXTINT_ENABLE(1);
    EXTINT_ENABLE(2);
    EXTINT_ENABLE(21);
    EXTINT_FALLING_EDGE(1);
    EXTINT_FALLING_EDGE(2);
    EXTINT_FALLING_EDGE(21);
    
    INT_LOWER_CPR(PRIORITY0);
    INTC_InitINTCInterrupts();  
    
    /* No movement at the beggining */
    re_move = DISABLED;	
    
    /* Infinite for loop */
	for(;;){
		
	}
  
}



