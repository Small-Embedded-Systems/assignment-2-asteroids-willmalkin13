/* Asteroids
    Sample solution for assignment
    Semester 2 -- Small Embedded Systems
    Dr Alun Moon
*/

/* C libraries */
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>

/* hardware platform libraries */
#include <display.h>
#include <mbed.h>

/* Main game elements */
#include "model.h"
#include "view.h"
#include "controller.h"

/* Game state */
float elapsed_time; 
int   score;
int   lives;
struct ship player;

float Dt = 0.01f;

Ticker model, view, controller;

bool paused = true;
/* The single user button needs to have the PullUp resistor enabled */
DigitalIn userbutton(P2_10,PullUp);
int main()
{

    init_DBuffer();
    

    view.attach( draw, 0.025);
    model.attach( physics, Dt);
    controller.attach( controls, 0.1);
    
    lives = 5;
    
    /* Pause to start */
    while( userbutton.read() ){ /* remember 1 is not pressed */
        paused=true;
        wait_ms(100);
    }
    paused = false;
    
    while(true) {
        /* do one of */
        /* Wait until all lives have been used
        while(lives>0){
            // possibly do something game related here
            wait_ms(200);
        }
        */
        /* Wait until each life is lost
        while( inPlay ){
            // possibly do something game related here
            wait_ms(200);
        }
        */
    }
}
