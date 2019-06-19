#include <stdint.h>
#include "reg.h"
#include "blink.h"

# define waitTime 200
void setup_systick(uint32_t ticks);

int main(void)
{
	setup_systick(168e6/8/(waitTime/1000); //200 ms 
	//setup_systick(168e6/8/(5); //200 ms 
	/*
	/8:  除頻器
	/5: 200ms/1000ms(1sec)
	 */
	// 橘色燈PD13 5Hz
	blink(LED_BLUE); //should not return
}


//Enable systick and use external clock source as clock
void setup_systick(uint32_t ticks)
{
	// Set Reload value(多久重數一次)->200 ms
	WRITE_BITS(SYST_BASE + SYST_RVR_OFFSET, SYST_RELOAD_23_BIT,SYST_RELOAD_0_BIT,ticks-1);

	// Uses external reference clock
	/*
	setup_systick: SysTick uses the IMPLEMENTATION DEFINED external reference clock.
	[0]: use external reference clock.
	[1]: use processor clock 
	 */
	CLEAR_BIT(SYST_BASE + SYST_CSR_OFFSET, SYST_CLKSOURCE_BIT) ;

	// Enable systick exception
	/*
	TICKINT:Count to 0 changes the SysTick exception status to pending.
	[1]: Count to 0 change the SysTick exception status to pending.
	*/
	SET_BIT(SYST_BASE + SYST_CSR_OFFSET,SYST_TICKINT_BIT);

	// Enable systick
	/*
	[0]: Enable SysTick
	*/
	SET_BIT(SYST_BASE + SYST_CSR_OFFSET,SYST_ENABLE_BIT); 
}

//
void systick_handler(void)
{
	blink_count(LED_ORANGE, 1);
}
