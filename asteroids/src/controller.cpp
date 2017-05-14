/* Asteroids Controller 
    Semester 2 Small Embedded Systems(CM0506)
    William Malkin		ID: 15040083
		14/05/2017
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

/* Hardware platform libraries */
#include <mbed.h>

/* Asteroids */
#include "model.h"
#include "asteroids.h"

/* Joystick 5-way switch */
enum position { right,down,left,up,centre };
DigitalIn joystick[] = {P5_0, P5_1, P5_4, P5_2, P5_3};
static bool jsPrsd(position);

/* Main conrol method */
void controls(void)
{
	//If the game is not Pause joystick inputs
	if (!Pause) {
		//If the user presses left turn the ship left
		if (jsPrsd(left)) {
			player.heading -= 5;
		}
		//If the user presses right turn the ship right
		else if (jsPrsd(right)) {
			player.heading += 5;
		}
		//If the user presses up go up
		else if (jsPrsd(up)) {
			player.engines = 1;
		}
		//If the user presses down go down
		else if (jsPrsd(down)) {
			player.engines = -1;
		}
		//If the user presses the joystick is pressed fire a missile
		else if (jsPrsd(centre)) {
			player.fire = true;
		}
		//If the user is neither pressing up or down deactivate the ships engine and brakes
		if (!jsPrsd(down) && !jsPrsd(up)) {
			player.engines = 0;
		}
	}
}

/* Returns true if the button given has been pressed */
bool jsPrsd(position p) {
	bool result = false;
	static uint32_t state;
	state = joystick[p].read();
  if (state == 0) {
		result = true;
	}
	return result;
}
