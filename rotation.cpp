//Rotation
//Joo Yun (Rosa) Kim

#include "gfx.h"
#include <iomanip>
#include <cmath>
#include <unistd.h>  //usleep
#include <cstdlib>

#define PI 3.14

int get_random_velocity();
void drawStar(int, int, int, int);
void drawTriangle(int, int, int);
void movingCircle(int, int, int, int, int, double, int, int);
void movingTriangle(int, int, int, int, int, double, int, int);

int main () 
{
	srand (time(NULL));
	int wd = 500;
	int ht = 400;
	int xc = 250, yc = 200, n = 25, m = 12;
	int xm = 0, ym = 0;
	int xt = 0, yt = 0;
	int cir = 80, tri = 150;
	double dt = 0;
	int pausetime = dt*10000;
	int circ_vel = get_random_velocity();
	int tri_vel = circ_vel * -1;
	char c;
	bool loop = true;

	gfx_open(wd, ht, "Animate");

	while(loop) {
		gfx_clear();

		gfx_color(255, 255, 255);
		gfx_text(50, 30, "Click to change direction of moving objects.");

		drawStar(xc, yc, n, m);

		movingCircle(xm, ym, xc, yc, circ_vel, dt, cir, n);

		movingTriangle(xt, yt, xc, yc, tri_vel, dt, tri, n);

		dt += 0.01;

		if (dt > 2*PI) 
			dt = 0;

		gfx_flush();
		usleep(pausetime);

		if(gfx_event_waiting()) {
			c = gfx_wait();
			switch (c) {
				case 1: 
					
					circ_vel *= -1;
					tri_vel *= -1;
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

void drawStar(int xm, int ym, int n, int m) {
	gfx_color(255, 215, 0);
	gfx_line(xm-n, ym+m, xm+n, ym+m);
	gfx_line(xm+n, ym+m, xm, ym-n);
	gfx_line(xm, ym-n, xm-n, ym+m);

	gfx_line(xm-n, ym-m, xm+n, ym-m);
	gfx_line(xm+n, ym-m, xm, ym+n);
	gfx_line(xm, ym+n, xm-n, ym-m);
}

void drawTriangle(int xm, int ym, int n) {
	gfx_color(255, 255, 255);
	gfx_line(xm-n, ym+n, xm+n, ym+n);
	gfx_line(xm+n, ym+n, xm, ym-n);
	gfx_line(xm, ym-n, xm-n, ym+n);
}

void movingCircle(int xm, int ym, int xc, int yc, int circ_vel, double dt, int cir, int n) {
	xm = xc + cos(circ_vel*dt)*cir;
	ym = yc + sin(circ_vel*dt)*cir;

	gfx_color(128, 0, 128);
	gfx_circle(xm, ym, n);
}

void movingTriangle(int xt, int yt, int xc, int yc, int tri_vel, double dt, int tri, int n) {
	xt = xc + cos(tri_vel*dt)*tri;
	yt = yc + sin(tri_vel*dt)*tri;

	gfx_color(255, 128, 0);
	drawTriangle(xt, yt, n);
}
