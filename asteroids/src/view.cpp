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
#include "asteroids.h"
#include "model.h"
#include "utils.h"

Display *graphics = Display::theDisplay();

const colour_t background = rgb(150,150,150); /* GREY */ 

/* Local Method Declarations*/
static void drawStart();
static void drawResume();
static void drawGameOver();
static void drawBanner();
//static void drawDebug();
static void drawShip();
static void drawShield();
static void drawAsteroids(struct asteroid *a);
static void drawMissiles(struct missile *m);
static coordinate_t getPoint(coordinate_t origin, int basex, int basey, float heading);

/* double buffering functions */
void init_DBuffer(void)
{   /* initialise the LCD driver to use second frame in buffer */
  uint16_t *bufferbase = graphics->getFb();
  uint16_t *nextbuffer = bufferbase+ (480*272);
  LPC_LCD->UPBASE = (uint32_t)nextbuffer;
}

void swap_DBuffer(void)
{   /* swaps frames used by the LCD driver and the graphics object */
  uint16_t *buffer = graphics->getFb();
  graphics->setFb( (uint16_t*) LPC_LCD->UPBASE);
  LPC_LCD->UPBASE = (uint32_t)buffer;
}

/* Main Draw Method */
void draw(void) {
  //Draw background
	graphics->fillScreen(background);
	//If the game has not started draw the start screen
	if (Pause && Lives == 5) {
		drawStart();
	}
	//If the player has died and has remaining Lives draw the respawn screen
	else if (Pause && Lives < 5 && Lives >= 0) {
		drawResume();
	}	
	//If the player is out of Lives draw the game over screen
	else if (Pause && Lives < 0) {
		drawGameOver();
	}	
	//If the game is in play draw the game elements
	else {
		drawAsteroids(asteroidCurrent);
		drawMissiles(missileCurrent);
		drawBanner();
		//drawDebug();
		drawShip();
	}
	//Display the elements drawn on the LCD
  swap_DBuffer();
}

/* Draws title screen complete with controls and credits */
static void drawStart() {
	graphics->setTextSize(3);
	graphics->setCursor(20, 20);
	graphics->printf("Will Malkin"); 
	graphics->setCursor(20, 70);
	graphics->setTextColor(WHITE);
	graphics->setTextSize(5);
	graphics->printf("ASTEROIDS");
	graphics->setTextSize(2);
	graphics->setCursor(20, 140);
	graphics->printf("Press the joystick to start");
	graphics->setTextSize(1);
	graphics->setCursor(180, 180);

}

/* Draws death screen */
static void drawResume() {
	graphics->setCursor(20, 40);
	graphics->setTextColor(RED); 
	graphics->setTextSize(5);
	graphics->printf("SHIP CRASHED");
	graphics->setCursor(20, 100);
	graphics->setTextSize(2);
	graphics->printf("Press Joystick to keep going");
	graphics->setTextSize(3);
	graphics->setCursor(20,150);
	graphics->printf("Current Score: %d", Score);
	graphics->setCursor(20,210);
	graphics->printf("Lives Remaining: %d", Lives);
}

/* Draws game over screen*/
static void drawGameOver() {
	graphics->setCursor(20, 40);
	graphics->setTextColor(WHITE); 
	graphics->setTextSize(6);
	graphics->printf("GAME OVER");
	graphics->setCursor(20, 150);
	graphics->setTextSize(2);
	graphics->printf("Press the joystick to Restart"); 
	graphics->setTextSize(2);
	graphics->setCursor(145,200);
	graphics->printf("Final Score: %d", Score);
}

/* Draw banner information containing the players Lives Score and Shield status */
static void drawBanner() {
	graphics->setCursor(5,4);
	graphics->setTextSize(1);
	graphics->setTextColor(WHITE);
	graphics->printf("Lives Left: %d", Lives);
	graphics->setCursor(180,4);
	graphics->drawRect(229, 2, 62, 10, WHITE);
	graphics->setCursor(400,4);
	graphics->printf("Score: %d", Score);
}

/*
static void drawDebug() {
	float heading = radians(player.heading);
	graphics->drawRect(400, 200, 482, 240, WHITE);
	graphics->setCursor(402,210);
	graphics->setTextSize(1);
	graphics->setTextColor(WHITE);
}
*/

/* Draw the players ship */
static void drawShip() {
	float heading = radians(player.heading);
	coordinate_t front, backR, backL;
	//Calculate the three points of the triangle based on the players heading
	front = getPoint(player.position, 0, -8, heading);
	backL = getPoint(player.position, 5, 5, heading);
	backR = getPoint(player.position, -5, 5, heading);
	graphics->drawTriangle(front.x, front.y, backL.x, backL.y, backR.x, backR.y, BLUE); 
	//Draw the ships Shields
	drawShield();
}

/* Draw Shields around the ship and in the information banner */
static void drawShield() {
	//As the Shield is damaged it turns red and the Shield bar in the info banner reduces
	if (Shield == 2) {        
		graphics->drawCircle(player.position.x, player.position.y, 12, BLUE);   
		graphics->fillRect(230, 2, 60, 8, BLUE); 
	}
	else {
		graphics->drawCircle(player.position.x, player.position.y, 12, RED);
		graphics->fillRect(230, 2, 30, 8, RED); 
	}
}

/* Calculate a point based on its origin and displacement*/
static coordinate_t getPoint(coordinate_t origin, int basex, int basey, float heading) {
	coordinate_t result;
	result.x = (basex * cos(heading)) - (basey * sin(heading));
	result.y = (basex * sin(heading)) + (basey * cos(heading));
	result.x += origin.x;
	result.y += origin.y;
	return result;
}

/* Iterate through the list of asteroids and draw each one if it is still alive */
void drawAsteroids(struct asteroid *a) {
	while (a) {
		if (a->live) {
			graphics->drawCircle(a->position.x, a->position.y, a->size, BLACK); 
		}
		a = a->next;
	}
}

/* Iterate through the list of missiles and draw each one if it is still alive */
void drawMissiles(struct missile *m) {
	while (m) {
		if(m->live) {
			graphics->fillCircle(m->position.x, m->position.y, 3, RED); 
		}
		m = m->next;
	}
}
