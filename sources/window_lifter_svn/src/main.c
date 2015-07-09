/*============================================================================*/
/*                        SV C CE SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Source:         %main.c%
* Instance:         1
* %version:         1.5 %
* %created_by:      Michele Balbi %
* %date_created:    25 June 2015 %
*=============================================================================*/
/* DESCRIPTION : C source Window Lifter file                                  */
/*============================================================================*/
/* FUNCTION COMMENT : This file contains the C code for the Window Lifter	  */
/* application.                                                               */
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
/*----------------------------------------------------------------------------*/
/*  1.3      | 01/07/2015  |                               | Michele Balbi    */
/* Correcting wrong includes (was including .c instead of .h).                */
/*----------------------------------------------------------------------------*/
/*  1.4      | 08/07/2015  |                               | Michele Balbi    */
/* Rewrite of code due to an unconsidered use case w/ noise-prone inputs.     */
/*----------------------------------------------------------------------------*/
/*  1.5      | 09/07/2015  |                               | Michele Balbi    */
/* Rewrite of code to integrate new modular libraries.                        */
/*============================================================================*/

/* Includes */
/* -------- */
#include "MPC5606B.h"
#include "conti_typedefs.h"

#include "MPC5606B_GPIO_lib.h"
#include "MPC5606B_ClkInit.h"
#include "MPC5606B_INTERRUPTS_lib.h"
#include "MPC5606B_PIT_lib.h"



/* Private defines */
/* ----------------*/

/* Defines for buttons and pinch signal pins, 				 */
/* and pressed/active states. Correspondence w/ GPIO number. */
#define UP_BUTTON 		6
#define DOWN_BUTTON 	7
#define PRESSED 		0

#define PINCH_SIGNAL 	66 
#define ACTIVE			0

#define DOWN_LED 		46
#define UP_LED 			47

/* Defines for highest and lowest LED. Correspondence w/ PORTC GPIO number. */
#define LED_LEVEL_MAX 	43 	 
#define LED_LEVEL_MIN 	34


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

T_UBYTE rub_led_level = LED_LEVEL_MAX; /* All LEDs are turned on at the start */

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

enum {			/* enum to hold a value depending on the pressed button*/
	NONE,
	BUTTON_UP,
	BUTTON_DOWN
}re_button_pressed;


/* Private functions prototypes */
/* ---------------------------- */
void WindowLifter_StopMovement(void);
void WindowLifter_TurnONLED(void);
void WindowLifter_TurnOFFLED(void);
void Timer10ms_INT_handler(void);
void Timer500ms_INT_handler(void);
void Timer400ms_INT_handler(void);
void Timer5s_INT_handler(void);
void Button_handler(void);
void Pinch_handler(void);


/* Exported functions prototypes */
/* ----------------------------- */

/* Inline functions */
/* ---------------- */

/* Private functions */
/* ----------------- */

/*****************************************************************
*  Name                 :	WindowLifter_StopMovement
*  Description          :	Routine to stop the LED switching.
*  Parameters           :	void
*  Return               :	void
*  Critical/explanation :   Change re_move to stop movement.
							Turn OFF LED indicators.
******************************************************************/
void WindowLifter_StopMovement(void){
	TIMER_STOP(4); /* Disable 400ms automatic recount. */
	OUTPUT_LOW(UP_LED);
	OUTPUT_LOW(DOWN_LED);
	re_move=DISABLED;
}

 /*****************************************************************
 *  Name                 :	WindowLifter_TurnONLED
 *  Description          :	Routine to turn ON next LED.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Turn ON next LED and keep OFF the UP
 							movement LED indicator.
 ******************************************************************/
 void WindowLifter_TurnONLED(void){
 	OUTPUT_HIGH(UP_LED);
	OUTPUT_LOW(DOWN_LED);
	rub_led_level++;
	OUTPUT_HIGH(rub_led_level);
 }
 
 /*****************************************************************
 *  Name                 :	WindowLifter_TurnOFFLED
 *  Description          :	Routine to turn OFF next LED.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Turn OFF next LED and keep ON the DOWN
 							movement LED indicator.
 ******************************************************************/
 void WindowLifter_TurnOFFLED(void){
	OUTPUT_LOW(UP_LED);
	OUTPUT_HIGH(DOWN_LED);
	OUTPUT_LOW(rub_led_level);
	rub_led_level--;
 }
 
 /*****************************************************************
 *  Name                 :	Timer10ms_INT_handler
 *  Description          :	Timer Interrupt handler for the 10ms.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Check if input signals are still active
 							after 10ms, to filter glitches.
 							If the signals are valid, set AUTO modes
 							and start timersfor 500ms to check for 
 							MANUAL modes.
 ******************************************************************/
 void Timer10ms_INT_handler(void){
 	TIMER_STOP(0); /* Disable 10ms automatic recount. */
 	if(INPUT_STATE(DOWN_BUTTON)==PRESSED && re_button_pressed==BUTTON_DOWN &&  rub_led_level>=LED_LEVEL_MIN){
 		re_move = AUTO_DOWN;
 	/*	OUTPUT_LOW(UP_LED);
		OUTPUT_HIGH(DOWN_LED); */
		TIMER_STOP(4);
		TIMER_START(4);
 	} 	
 	
 	if(INPUT_STATE(UP_BUTTON)==PRESSED && re_button_pressed==BUTTON_UP && rub_led_level<LED_LEVEL_MAX){
 		re_move = AUTO_UP;
 	/*	OUTPUT_HIGH(UP_LED);
		OUTPUT_LOW(DOWN_LED); */
		TIMER_STOP(4);
		TIMER_START(4);
 	}
 	
 	if(INPUT_STATE(PINCH_SIGNAL)==ACTIVE && (re_move==AUTO_UP || re_move==MANUAL_UP)){
		re_move=PINCH;
	} 
 	
 	TIMER_CLEAR_INT_FLAG(0);
 }
 
 /*****************************************************************
 *  Name                 :	Timer500ms_INT_handler
 *  Description          :	Timer Interrupt handler for the 500ms.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  If buttons are still pressed after 500ms
 							MANUAL modes are activated.
 ******************************************************************/
 void Timer500ms_INT_handler(void){
 	TIMER_STOP(1); /* Disable 500ms automatic recount. */
 	if(INPUT_STATE(DOWN_BUTTON)==PRESSED && re_button_pressed==BUTTON_DOWN && rub_led_level>=LED_LEVEL_MIN){
 		re_move = MANUAL_DOWN;
 	} 	
 	
 	if(INPUT_STATE(UP_BUTTON)==PRESSED && re_button_pressed==BUTTON_UP && rub_led_level<LED_LEVEL_MAX){
 		re_move = MANUAL_UP;
 	} 
 	
 	re_button_pressed = NONE;
 	TIMER_CLEAR_INT_FLAG(1);
 }
 
 /*****************************************************************
 *  Name                 :	Timer400ms_INT_handler
 *  Description          :	Timer Interrupt handler for the 400ms
 							count between LEDs' change of state.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Checks movement state through re_move,
 							if button is pressed (in case of manual
 							modes) and calls routines to turn ON/OFF
 							the next LED. Also calls the routine to
 							end the LED switching, if necessary.
 ******************************************************************/
 void Timer400ms_INT_handler(void){
 	
 	if(re_move==PINCH){						
		if(rub_led_level>=LED_LEVEL_MIN){  /* Any LEDs still ON?      */
			WindowLifter_TurnOFFLED();	   /* Yes. Turn OFF next LED. */
		}else{							   
			WindowLifter_StopMovement();   /* No. Stop movement and   */
			re_move=PINCH;				   /* start 5s blocking count.*/
			TIMER_STOP(5);
			TIMER_START(5); 			
		}
 	}
 
 	/* Decisions for UP movements. */
 	if((INPUT_STATE(UP_BUTTON)==PRESSED && re_move==MANUAL_UP) || re_move==AUTO_UP){
 		if(rub_led_level<LED_LEVEL_MAX){   /* Check LED limits */
 			WindowLifter_TurnONLED();
 		}else{
 			WindowLifter_StopMovement();   /* If limit was reached, stop movement.	 */
 		}
 	}else{
 		if(re_move==MANUAL_UP){				/* If manual UP is active but its button */
 			WindowLifter_StopMovement();    /* isn't pressed anymore, stop movement. */
 		}
 	}
 	
 	/* Decisions for DOWN movements. */
 	if((INPUT_STATE(DOWN_BUTTON)==PRESSED && re_move==MANUAL_DOWN) || re_move==AUTO_DOWN){
		if(rub_led_level>=LED_LEVEL_MIN){
			WindowLifter_TurnOFFLED();		/* If limit was reached, stop movement.	 */
		}else{
 			WindowLifter_StopMovement();
 		}
 	}else{
 		if(re_move==MANUAL_DOWN){			/* If manual DOWN is active but its button */
 			WindowLifter_StopMovement();    /* isn't pressed anymore, stop movement. */
 		}
 	}
 	
 	TIMER_CLEAR_INT_FLAG(4);
 }
 
 /**************************************************************
 *  Name                 :	Timer5s_INT_handler
 *  Description          :	This is the Timer Interrupt handler
 							for the 5s count to block the module.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Disables the 5s timer and resets
 							re_move so signals can be read again.
 **************************************************************/
 void Timer5s_INT_handler(void){
 	
 	TIMER_STOP(5);
 	re_move=DISABLED;
 	
 	TIMER_CLEAR_INT_FLAG(5);
 }

/**************************************************************
 *  Name                 :	Pinch_handler
 *  Description          :	This is the External Interrupt handler
 *							for up/down buttons.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Starts 10ms and 500 ms timers to check for a
 							valid signal. 							
 **************************************************************/
void Button_handler(void){
	/* Check if the UP button was the one that generated the External Interrupt */
	if (EXTINT_GET_FLAG(1) && (re_move==DISABLED)){
		
		re_button_pressed = BUTTON_UP;
		TIMER_STOP(0);
		TIMER_STOP(1);
		TIMER_START(0);
		TIMER_START(1);		
	}
	
	/* Check if the DOWN button was the one that generated the External Interrupt */
	if (EXTINT_GET_FLAG(2) && (re_move==DISABLED)){
		
		re_button_pressed = BUTTON_DOWN;
		TIMER_STOP(0);
		TIMER_STOP(1);
		TIMER_START(0);
		TIMER_START(1);
	}
	
	EXTINT_CLEAR_INT_FLAG(1);
	EXTINT_CLEAR_INT_FLAG(2);
}

/**************************************************************
 *  Name                 :	Pinch_handler
 *  Description          :	This is the External Interrupt handler
 *							for the pinch signal input.
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  Starts 10ms timer to check for a
 							valid signal. 							
 **************************************************************/
void Pinch_handler(void){

	/* Check that the pinch signal pin was effectively the one that */
	/* generated the interrupt. 									*/
	if (EXTINT_GET_FLAG(21)){
		
		TIMER_STOP(0);
		TIMER_START(0);
		
		/* Clear interrupt flag to allow next interrupts */
		EXTINT_CLEAR_INT_FLAG(21);
	}
}

/* Exported functions */
/* ------------------ */


/* ---------------- MAIN FUNCTION -------------------------- */
/**************************************************************
 *  Name                 :	main
 *  Description          :
 *  Parameters           :	void
 *  Return               :	void
 *  Critical/explanation :  The main routine initializes GPIO
 							pins, interrupts, clocks and timers.
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
    
    /* Button pins and pinch-detecttion init as inputs w/ buffer and pull-ups */
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
    
    /* Interrupts init, SW Mode */
    INT_SW_VECTOR_MODE();
    
    /* Timer init, loading times values, enable Timer INTs */
    TIMER_INIT();
    TIMER_LOAD_VALUE_MS(10,0);
    TIMER_LOAD_VALUE_MS(500,1);
    TIMER_LOAD_VALUE_MS(400,4);
    TIMER_LOAD_VALUE_MS(5000,5);
    TIMER_ENABLE_INT(0);		
    TIMER_ENABLE_INT(1);
    TIMER_ENABLE_INT(4);
    TIMER_ENABLE_INT(5);
    
    /* External Interrupts enabling for falling-edge */
    EXTINT_FALLING_EDGE(1);
    EXTINT_FALLING_EDGE(2);
    EXTINT_FALLING_EDGE(21);
    EXTINT_ENABLE(1);
    EXTINT_ENABLE(2);
    EXTINT_ENABLE(21);
    
    INTC_InstallINTCInterruptHandler(Button_handler, EXT0_Vector, PRIORITY7);
    INTC_InstallINTCInterruptHandler(Pinch_handler, EXT2_Vector, PRIORITY10);
    INTC_InstallINTCInterruptHandler(Timer10ms_INT_handler, PIT0_Vector, PRIORITY8);
    INTC_InstallINTCInterruptHandler(Timer500ms_INT_handler, PIT1_Vector, PRIORITY8);
    INTC_InstallINTCInterruptHandler(Timer400ms_INT_handler, PIT4_Vector, PRIORITY8);
    INTC_InstallINTCInterruptHandler(Timer5s_INT_handler, PIT5_Vector, PRIORITY8);
    
    INT_LOWER_CPR(PRIORITY0);
    INTC_InitINTCInterrupts();  
    
    /* No movement at the beggining */
    re_move = DISABLED;
    re_button_pressed = NONE;
    
    /* Infinite for loop */
	for(;;){ 
		
	}
  
}



