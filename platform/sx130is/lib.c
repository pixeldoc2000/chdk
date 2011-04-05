/*
*********************
SX20
********************** 
*/

/*
SX130
LED address:
same as sx210
orange 0xC0220010
green  0xC0220014
AF      0xC022000C
*/
#define LED_AF		0xC022000C
#define LED_ORANGE	0xC0220010
#define LED_GREEN	0xC0220014

#define DELAY 300000

#define LED_ON 		*((long*) LED_GREEN) = 0x46
#define LED_OFF		*((long*) LED_GREEN) = 0x44

#define LED_ON_RED 		*((long*) LED_ORANGE) = 0x46
#define LED_OFF_RED		*((long*) LED_ORANGE) = 0x44

#define LED_ON_AF 		*((long*) LED_AF) = 0x46
#define LED_OFF_AF		*((long*) LED_AF) = 0x44

void debug_led(int state)
{
    if (state)
		LED_ON;
    else
		LED_OFF;
} 

void debug_wait()
{
	int counter;

	counter = DELAY; 
	while (counter--) { asm("nop\n nop\n"); };
}


void debug_blink()
{
	//led on
	LED_ON;
	debug_wait();

	//led off
	LED_OFF;
	debug_wait();
}

void debug_blink_red()
{
	//led on
	LED_ON_RED;
	debug_wait();

	//led off
	LED_OFF_RED;
	debug_wait();
}


/*	
void debug_my_blink()
{
	volatile long *p = (void*)LED_GREEN;       		// turned off later, so assumed to be power
	volatile long *p2 = (void*)LED_AF;       		// turned off later, so assumed to be power
	int counter;

	// DEBUG: blink led
	//led on
	counter = DELAY; 
	*p = 0x46; 
	while (counter--) { asm("nop\n nop\n"); };
	*p2 = 0x46;
	//led off
	counter = DELAY; 
	*p = 0x44; 
	while (counter--) { asm("nop\n nop\n"); };
	*p2= 0x44;
	
}
*/ 

#include "platform.h"
#include "lolevel.h"


/*
void vid_bitmap_refresh()
{
	 extern int enabled_refresh_physical_screen; // screen lock counter
	 extern void _ScreenUnlock();

//     _LockAndRefresh();
	 _ScreenLock();
	enabled_refresh_physical_screen=1;
//	full_screen_refresh=3; //found in ScreenUnlock underneath a CameraLog.c call sub_FFA02598	//sx210
	_ScreenUnlock();
//	_UnlockAndRefresh();	
}
*/

// Testing another refresh method
void vid_bitmap_refresh()
{
	extern int enabled_refresh_physical_screen;
	extern int full_screen_refresh;

	// i've tried refreshphysical screen (screen unlock) and that caused the canon and
	// function menu to not display at all. This seems to work and is called in a similar
	// way in other places where original OSD should be refreshed.
	extern void _LockAndRefresh(); // wrapper function for screen lock
	extern void _UnlockAndRefresh(); // wrapper function for screen unlock

	_LockAndRefresh();

	enabled_refresh_physical_screen=1;
	full_screen_refresh |= 3; 

	_UnlockAndRefresh();
}

void shutdown()
{
	volatile long *p = (void*)0xC022001C;    
	
	asm(
		"MRS     R1, CPSR\n"
		"AND     R0, R1, #0x80\n"
		"ORR     R1, R1, #0x80\n"
		"MSR     CPSR_cf, R1\n"
		:::"r1","r0");
	
	*p = 0x44;  // power off.
	
	while(1);
}


void camera_set_led(int led, int state, int bright) {
 static char led_table[3]={0,1,9};
 _LEDDrive(led_table[led%sizeof(led_table)], state<=1 ? !state : state);
}

int get_flash_params_count(void){
 return 132; 
}

void JogDial_CW(void){
 _PostLogicalEventForNotPowerType(0x874, 2);  // RotateJogDialRight
}

void JogDial_CCW(void){
 _PostLogicalEventForNotPowerType(0x875, 2);  // RotateJogDialLeft
}

