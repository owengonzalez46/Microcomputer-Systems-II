#include "derivative.h" /* include peripheral declarations */
//#include "common.h"

#define SLOW_BLINK      (10000000)
#define FAST_BLINK      (100000)
#define BLINK_DELAY     FAST_BLINK

#define RED				(18) 
#define RED_SHIFT		(1 << 18)
#define GREEN			(19)
#define GREEN_SHIFT		(1 << 19)
#define BLUE			(1)
#define BLUE_SHIFT		(1 << 1)
#define LED				(10)
#define LED_SHIFT		(1 << 10)

#define LED_ON			(GPIOB_PSOR = LED_SHIFT)
#define LED_OFF			(GPIOB_PCOR = LED_SHIFT)
#define LED_TOGGLE		(GPIOB_PTOR = LED_SHIFT)

#define RED_OFF			(GPIOB_PSOR = RED_SHIFT)
#define RED_ON			(GPIOB_PCOR = RED_SHIFT)
#define RED_TOGGLE		(GPIOB_PTOR = RED_SHIFT)

#define GREEN_OFF		(GPIOB_PSOR = GREEN_SHIFT)
#define GREEN_ON		(GPIOB_PCOR = GREEN_SHIFT)
#define GREEN_TOGGLE	(GPIOB_PTOR = GREEN_SHIFT)

#define BLUE_OFF		(GPIOD_PSOR = BLUE_SHIFT)
#define BLUE_ON			(GPIOD_PCOR = BLUE_SHIFT)
#define BLUE_TOGGLE		(GPIOD_PTOR = BLUE_SHIFT)

void delay_time(int);
void init_leds();
void red_on();
void red_off();
void green_on();
void green_off();
void blue_on();
void blue_off();
void led_on();
void led_off();
/********************************************************************/
int main (void)
{
	
	int i=0;

	init_leds();

	while(1)
    {
		i++;						// just a count variable. 
		
		red_on();
		delay_time(BLINK_DELAY);	// Red 
		red_off();
		
		green_on();
		delay_time(BLINK_DELAY);	// Green 
		green_off();
		
		blue_on();
		delay_time(BLINK_DELAY);	// Blue
		
		red_on();
		delay_time(BLINK_DELAY);	// Blue + Red 
		blue_off();
		
		delay_time(BLINK_DELAY);	// Red + Green
		green_on();
		delay_time(BLINK_DELAY);	 
		red_off();
		
		blue_on();
		delay_time(BLINK_DELAY);	// Green + Blue 

		red_on();
		delay_time(BLINK_DELAY);	// Green + Blue + Red 
		green_off();
		blue_off();
		delay_time(BLINK_DELAY);
		
		led_on();
		delay_time(BLINK_DELAY);	// LED on PTB10
		led_off();
		delay_time(BLINK_DELAY);
	}
}

void led_on(){
	LED_ON;
}

void led_off(){
	LED_OFF;
}

void red_on(){
	RED_ON;
}

void red_off(){
	RED_OFF;
}

void green_on(){
	GREEN_ON;
}

void green_off(){
	GREEN_OFF;
}

void blue_on(){
	BLUE_ON;
}

void blue_off(){
	BLUE_OFF;
}

/********************************************************************/

void delay_time(int number){
  int cnt;
  for(cnt=0;cnt<number;cnt++);
}
/********************************************************************/

/********************************************************************/
/*	init_leds()
 * initialize the ports for LEDs
 * ******************************************************************/
 

 void init_leds()
 	 {
	 
    /* 
	 * Initialize the Red LED (PTB18)
	 */

		/* Turn on clock to PortB module */
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

		/* Set the PTB18 pin multiplexer to GPIO mode */
		PORTB_PCR18 = PORT_PCR_MUX(1);

		/* Set the initial output state to high */
		GPIOB_PSOR |= RED_SHIFT;

		/* Set the pins direction to output */
		GPIOB_PDDR |= RED_SHIFT;


	/*
	 * Initialize the Green LED (PTB19)
	 */

		/* Turn on clock to PortA module */
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

		/* Set the PTB19 pin multiplexer to GPIO mode */
		PORTB_PCR19 = PORT_PCR_MUX(1);

		/* Set the initial output state to high */
		GPIOB_PSOR |= GREEN_SHIFT;

		/* Set the pins direction to output */
		GPIOB_PDDR |= GREEN_SHIFT;



	/*
	 * Initialize the Blue LED (PTD1)
	 */

		/* Turn on clock to PortD module */
		SIM_SCGC5 |= SIM_SCGC5_PORTD_MASK;

		/* Set the PTD1 pin multiplexer to GPIO mode */
		PORTD_PCR1 = PORT_PCR_MUX(1);

		/* Set the initial output state to high */
		GPIOD_PSOR = BLUE_SHIFT;

		/* Set the pins direction to output */
		GPIOD_PDDR |= BLUE_SHIFT;
		
		
	/* 
	 * Initialize the LED (PTB10)
	 */

		/* Turn on clock to PortB module */
		SIM_SCGC5 |= SIM_SCGC5_PORTB_MASK;

		/* Set the PTB10 pin multiplexer to GPIO mode */
		PORTB_PCR10 = PORT_PCR_MUX(1);
					
		/* Set the initial output state to high */
		GPIOB_PSOR |= LED_SHIFT;

		/* Set the pins direction to output */
		GPIOB_PDDR |= LED_SHIFT;
	}
