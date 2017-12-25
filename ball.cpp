//Ball
//Joo Yun (Rosa) Kim
//Purpose: Animation of a circle moving around the screen at a constant velocity.
//If the user clicks on the screen, move the circle to the location of the click with new random velocity

#include "gfx.h"
#include <iomanip>
#include <cmath>
#include <unistd.h>  //usleep
#include <cstdlib>

#define PI 3.14

int get_random_velocity();

int main () 
{
	srand (time(NULL));
	int wd = 500;
	int ht = 400;
	int xm = 250, ym = 200, n = 25;
	double deltat = 2;
	int pausetime = 20000;
	int x_vel = 5;
	int y_vel = 5;
	char c;
	bool loop = true;

	gfx_open(wd, ht, "Bounce");		//open new window

	gfx_color(102, 255, 204);

	while(loop) {
		gfx_clear();
		xm = xm + x_vel*deltat;
		ym = ym + y_vel*deltat;

		gfx_circle(xm, ym, n);
		gfx_flush();
		usleep(pausetime);

		if ((xm - n) < 0) {
			x_vel *= -1;
			xm = n;
		} else if ((xm + n) >= wd) {
			x_vel *= -1;
			xm = wd - n;
		} else if ((ym - n) < 0) {
			y_vel *= -1;
			ym = n;
		} else if ((ym + n) >= ht) {
			y_vel *= -1;
			ym = ht - n;
		} 

		if(gfx_event_waiting()) {
			c = gfx_wait();
			switch (c) {
				case 1: 
					xm = gfx_xpos();
					ym = gfx_ypos();
					x_vel = get_random_velocity();
					y_vel = get_random_velocity();
			}
			if (c == 'q')
				break;
		}
	}
	return 0;
}

int get_random_velocity() {
	int v = 0;
	while (v == 0) {
		v = 5 - (rand () % 11);
	}
	return v;
}
