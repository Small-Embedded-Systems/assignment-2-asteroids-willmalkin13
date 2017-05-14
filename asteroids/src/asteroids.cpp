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
#include <string.h>

/* Hardware platform libraries */
#include <display.h>
#include <mbed.h>

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"

/* Game state */
float Elapsed_time; 
int   Score = 0;
int   Lives = 5;
int Shield = 2;
struct ship player;
bool Pause = true;

/* Game speed */
float Dt = 0.01f;

/* Ticker objects to manage physics, graphics and input */
Ticker model, view, controller;

/* Local Method Declarations*/
static void death();

/* Button used to begin play from Pause state */
DigitalIn userbutton(P5_3,PullUp); 

/* Main Method */
int main()
{
    init_DBuffer();
    
	
    view.attach( draw, 0.025);
    model.attach( physics, Dt);
    controller.attach( controls, 0.025);
    
    /* Pause to start */
    while( userbutton.read() ){
        Pause=true;
    }
		Pause = false;
		
		/* Main Loop */
    while(true) {
			//If the Shields are broken end current life
			if(Shield < 1) {
				death();
			}
			//If the player runs out of Lives reset the game when play is resumed
			if(Lives < 0) {
				Lives = 5;
				Score = 0;
				Elapsed_time = 0;
			}
    }
}

/* Called when the player crashes the ship. 
	 Pauses the game, resets Shields and takes away a life.  */
static void death() {
	Lives --;
	while( userbutton.read() ){
        Pause=true;
    }
	Shield = 2; 
	Pause = false;
}
