/*============================================================================*/
/*                        SV C BC SOFTWARE GROUP                              */
/*============================================================================*/
/*                        OBJECT SPECIFICATION                                */
/*============================================================================*
* C Include:        %MPC5606B_Mapper.h%
* Instance:         1
* %version:         1.3 %
* %created_by:      Michele Balbi %
* %date_created:    08 June 2015 %
*=============================================================================*/
/* DESCRIPTION : Header file for mappings and macros of MPC5606B Freescale MCU*/
/*============================================================================*/
/* FUNCTION COMMENT : This header tags different pins and module functions    */
/*                    to make it easier to use them.                          */
/*============================================================================*/
/*                               OBJECT HISTORY                               */
/*============================================================================*/
/*  REVISION |   DATE      |                               |      AUTHOR      */
/*----------------------------------------------------------------------------*/
/*  1.0      | 08/06/2015  |                               | Michele Balbi    */
/* First Draft of file. Inclusion of GPIO pin mappings            			  */
/*----------------------------------------------------------------------------*/
/*  1.1      | 20/06/2015  |                               | Michele Balbi    */
/* Added mappings for interruptions and timers.                  			  */
/*----------------------------------------------------------------------------*/
/*  1.2      | 28/06/2015  |                               | Michele Balbi    */
/* Added macros for modules (timers, interruptions).              			  */
/*----------------------------------------------------------------------------*/
/*  1.3      | 30/06/2015  |                               | Michele Balbi    */
/* Implementation of templates for C code review compliance.                  */
/*============================================================================*/

#ifndef _MPC5606B_Mapper_
#define _MPC5606B_Mapper_

/* Exported defines */

#define CLK_FREQ 64000000

/* Mappping pin number to GPIO[n] */
#define PA0 0
#define PA1 1
#define PA2 2
#define PA3 3
#define PA4 4
#define PA5 5
#define PA6 6
#define PA7 7
#define PA8 8
#define PA9 9
#define PA10 10
#define PA11 11
#define PA12 12
#define PA13 13
#define PA14 14
#define PA15 15

#define PB0 16
#define PB1 17
#define PB2 18
#define PB3 19
#define PB4 20
#define PB5 21
#define PB6 22
#define PB7 23
#define PB8 24
#define PB9 25
#define PB10 26
#define PB11 27
#define PB12 28
#define PB13 29
#define PB14 30
#define PB15 31

#define PC0 32
#define PC1 33
#define PC2 34
#define PC3 35
#define PC4 36
#define PC5 37
#define PC6 38
#define PC7 39
#define PC8 40
#define PC9 41
#define PC10 42
#define PC11 43
#define PC12 44
#define PC13 45
#define PC14 46
#define PC15 47

#define PD0 48
#define PD1 49
#define PD2 50
#define PD3 51
#define PD4 52
#define PD5 53
#define PD6 54
#define PD7 55
#define PD8 56
#define PD9 57
#define PD10 58
#define PD11 59
#define PD12 60
#define PD13 61
#define PD14 62
#define PD15 63

#define PE0 64
#define PE1 65
#define PE2 66
#define PE3 67
#define PE4 68
#define PE5 69
#define PE6 70
#define PE7 71
#define PE8 72
#define PE9 73
#define PE10 74
#define PE11 75
#define PE12 76
#define PE13 77
#define PE14 78
#define PE15 79

#define PF0 80
#define PF1 81
#define PF2 82
#define PF3 83
#define PF4 84
#define PF5 85
#define PF6 86
#define PF7 87
#define PF8 88
#define PF9 89
#define PF10 90
#define PF11 91
#define PF12 92
#define PF13 93
#define PF14 94
#define PF15 95

#define PG0 96
#define PG1 97
#define PG2 98
#define PG3 99
#define PG4 100
#define PG5 101
#define PG6 102
#define PG7 103
#define PG8 104
#define PG9 105
#define PG10 106
#define PG11 107
#define PG12 108
#define PG13 109
#define PG14 110
#define PG15 111

#define PH0 112
#define PH1 113
#define PH2 114
#define PH3 115
#define PH4 116
#define PH5 117
#define PH6 118
#define PH7 119
#define PH8 120
#define PH9 121
#define PH10 122
#define PH11 123

/* Map peripherals */

#define PUSH1 64
#define PUSH2 65
#define PUSH3 66
#define PUSH4 67

#define LED1 68
#define LED2 69
#define LED3 70
#define LED4 71

#define DIP1 102
#define DIP2 103
#define DIP3 104
#define DIP4 105


/* Register gating addresses offsets for PCTL registers */

#define PCTL_ADC_0 		32
#define PCTL_ADC_1	 	33
#define PCTL_SIUL 		68
#define PCTL_PIT 		92
#define PCTL_EMIOS_0 	72
#define PCTL_EMIOS_1 	73


/* Interrupt Vectors */

#define EXT0_Vector 41
#define EXT1_Vector 42
#define EXT2_Vector 43

#define PIT0_Vector 59
#define PIT1_Vector 60
#define PIT2_Vector 61
#define PIT3_Vector 127
#define PIT4_Vector 128
#define PIT5_Vector 129
#define PIT6_Vector 130
#define PIT7_Vector 131

#define ADC0_EOC_Vector 	62
#define ADC0_WD_Vector 		64
#define ADC1_EOC_Vector 	82
#define ADC1_WD_Vector 		84


/* Interrupt Macros and Defines */

#define	EXTINT0		0
#define	EXTINT1		1
#define	EXTINT2		2
#define	EXTINT3		3
#define	EXTINT4		4
#define	EXTINT5		5
#define	EXTINT6		6
#define	EXTINT7		7
#define	EXTINT8		8
#define	EXTINT9		9
#define	EXTINT10	10
#define	EXTINT11	11
#define	EXTINT12	12
#define	EXTINT13	13
#define	EXTINT14	14
#define	EXTINT15	15
#define	EXTINT16	16
#define	EXTINT17	17
#define	EXTINT18	18
#define	EXTINT19	19
#define	EXTINT20	20
#define	EXTINT21	21
#define	EXTINT22	22
#define	EXTINT23	23

#define	PRIORITY0	0
#define	PRIORITY1	1
#define	PRIORITY2	2
#define	PRIORITY3	3
#define	PRIORITY4	4
#define	PRIORITY5	5
#define	PRIORITY6	6
#define	PRIORITY7	7
#define	PRIORITY8	8
#define	PRIORITY9	9
#define	PRIORITY10	10
#define	PRIORITY11	11
#define	PRIORITY12	12
#define	PRIORITY13	13
#define	PRIORITY14	14
#define	PRIORITY15	15

#define INT_SW_VECTOR_MODE()			(INTC.MCR.R = 0x00000000)
#define INT_LOWER_CPR(priority)			(INTC.CPR.R = priority)
#define EXTINT_ENABLE(int_num)			(SIU.IRER.B.IRE##int_num = 1)
#define EXTINT_FALLING_EDGE(int_num)	(SIU.IFEER.B.IFEE##int_num = 1)
#define EXTINT_CLEAR_INT_FLAG(int_num)	(SIU.ISR.B.EIF##int_num = 1)
#define EXTINT_GET_FLAG(int_num)		(SIU.ISR.B.EIF##int_num)


/* Timer Macros */

#define TIMER_INIT()					(PIT.PITMCR.R = 0)
#define TIMER_LOAD_VALUE(ms,timer)		(PIT.CH[timer].LDVAL.R = (ms*64000)-1)
#define TIMER_GET_VALUE(timer)			(PIT.CH[timer].CVAL.R)
#define TIMER_ENABLE_INT(timer)			(PIT.CH[timer].TCTRL.B.TIE = 1)
#define TIMER_DISABLE_INT(timer)		(PIT.CH[timer].TCTRL.B.TIE = 0)
#define TIMER_START(timer)				(PIT.CH[timer].TCTRL.B.TEN = 1)
#define TIMER_STOP(timer)				(PIT.CH[timer].TCTRL.B.TEN = 0)
#define TIMER_IS_RUNNING(timer)			(PIT.CH[timer].TCTRL.B.TEN)
#define TIMER_CLEAR_INT_FLAG(timer)		(PIT.CH[timer].TFLG.B.TIF = 1)


/* Macros for GPIO config */

#define GPIO_AS_OUTPUT(port)		(SIU.PCR[port].R = 0x0200)
#define GPIO_AS_INPUT(port)			(SIU.PCR[port].R = 0x0103)

#define OUTPUT_HIGH(port)			(SIU.GPDO[port].B.PDO = 1)
#define OUTPUT_LOW(port)			(SIU.GPDO[port].B.PDO = 0)

#define INPUT_STATE(port)			(SIU.GPDI[port].B.PDI)

/* LED Macros */

#define LED_ON(channel)				(SIU.GPDO[channel].B.PDO = 0)
#define LED_OFF(channel)            (SIU.GPDO[channel].B.PDO = 1)
#define LED_TOGGLE(channel)         (SIU.GPDO[channel].B.PDO ^= 1) 



#endif



