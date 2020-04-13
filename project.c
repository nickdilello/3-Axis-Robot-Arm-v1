#include <msp430.h>

//External Push Buttons
#define 	BUTTON1			BIT0					//button on P2.0
#define		BUTTON2			BIT1					//button on P2.1
#define		BUTTON3			BIT3					//button on P2.3

//RGB LED
#define		LED_R			BIT4					//Red LED pin on P1.4
#define		LED_B			BIT5					//Blue LED pin on P1.5
#define		LED_G			BIT7					//Green LED pin on P1.7

//Servos
#define		servo1			BIT6					//SERVO P1.6 using TA0.1
#define		servo2			BIT2					//SERVO P2.2 using TA1.1
#define		servo3			BIT4					//SERVO P2.4 using TA1.2

void main(void)
{
	WDTCTL = WDTPW + WDTHOLD;						//stop WDT

	//LED setup
	P1DIR |= LED_R + LED_B + LED_G;						//LEDs set as outputs

	//Push button setup
	P2DIR &= ~BUTTON1 + ~BUTTON2 + ~BUTTON3;				//P2.0, P2.1, P2.3 set as inputs

	//Servo setup
	P1DIR |= servo1;
	P2DIR |= (servo2|servo3);
	P1OUT = 0;
	P2OUT = 0;	
	P1SEL |= servo1;
	P2SEL |= (servo2|servo3);	

	TA0CCR0 = 20000-1;							//PWM Period for TA0
	TA1CCR0 = 20000-1;							//PWM Period for TA1

	//Move to home position
	motionhome();								//perform home motion path

	TA0CCTL1 = OUTMOD_7;							//CCR1 reset for TA0.1
	TA0CTL = TASSEL_2 + MC_1;						//SMCLK, up mode
	TA1CCTL1 = OUTMOD_7;							//CCR1 reset for TA1.1
	TA1CCTL2 = OUTMOD_7;							//CCR1 reset for TA1.2
	TA1CTL = TASSEL_2 + MC_1;						//SMCLK, up mode

	//loop to check what push button is pressed
	while(1)
	{
		if((P2IN&BUTTON1) == 0x01)					//if P2.0 reads high, then...
		{			
				P1OUT |= LED_G;					//Green LED on
				delay();					//delay
				motionpath1();					//perform motion path 1
				delay();					//delay
				motionhome();					//perform home motion path					
				P1OUT &= ~LED_G;				//Green LED off
		}
		if((P2IN&BUTTON2) == 0x02)					//if P2.1 reads high, then...
		{	
				P1OUT |= LED_B;					//Blue LED on
				delay();					//delay
				motionpath2();					//perform motion path 2
				delay();
				motionhome();					//perform home motion path
				P1OUT &= ~LED_B;				//Blue LED off
		}
		if((P2IN&BUTTON3) == 0x08)					//if P2.3 reads high, then...
		{
				P1OUT |= LED_R;					//Red LED on
				delay();					//delay
				motionpath3();					//perform motion path 3
				delay();
				motionhome();					//perform home motion path
				P1OUT &= ~LED_R;				//Red LED off
		}
	}
}

//Delay loop
void delay() 
{ 
	volatile unsigned long i;
	i = 25000; 								//number of counts in delay
	do (i--);								//decrement by 1
	while (i != 0);								//decrement while i is not zero
}

//Robot Arm Home Position
void motionhome()
{
	TA0CCR1 = 1500;								//servo1 (base) at 90deg
	delay();
	TA1CCR1 = 1500;								//servo2 (arm) at 90deg
	delay();	
	TA1CCR2 = 1500;								//servo3 (gripper) at 90deg
	delay();
}

//Robot Arm Motion Path 1 - GRAB AND SUPLEX OBJECT
void motionpath1()
{
	TA1CCR2 = 2200;								//servo3 (gripper)
	delay();	
	TA1CCR1 = 2425;								//servo2 (arm)
	delay();
	TA1CCR2 = 1325;								//servo3 (gripper)
	delay();
	TA1CCR1 = 600;								//servo2 (arm)
	delay();
	TA1CCR2 = 2000;								//servo3 (gripper)
	delay();
}

//Robot Arm Motion Path 2 - GRAB AND DROP OBJECT
void motionpath2()
{
	TA1CCR2 = 2200;								//servo3 (gripper)
	delay();	
	TA1CCR1 = 2425;								//servo2 (arm)
	delay();
	TA1CCR2 = 1325;								//servo3 (gripper)
	delay();
	TA1CCR1 = 1850;								//servo2 (arm)
	delay();
	TA0CCR1 = 800;								//servo1 (base)	
	delay();
	TA1CCR2 = 2000;								//servo3 (gripper)
	delay();	
}

//Robot Arm Motion Path 3 - GRAB AND THROW OBJECT
void motionpath3()
{	
	TA1CCR2 = 2200;								//servo3 (gripper)
	delay();	
	TA1CCR1 = 2425;								//servo2 (arm)
	delay();
	TA1CCR2 = 1325;								//servo3 (gripper)
	delay();
	TA1CCR1 = 2000;								//servo2 (arm)
	TA0CCR1 = 650;								//servo1 (base)
	TA1CCR2 = 2000;								//servo3 (gripper)
	delay();
}
