#include <array>
#include <iostream>
#include <vector>

#include "lib/renderlib.hpp"
#include "physics/physics.hpp"

int SCREEN_WIDTH = 600;
int SCREEN_HEIGHT = 600;

SDL_Window *g_window;
SDL_Renderer *g_renderer;

void loop();
void setup();

int main() {
	if(rn::init("golf", g_window, g_renderer, SCREEN_WIDTH, SCREEN_HEIGHT) != 0) return -1;
	int f = 0;
	setup();
	SDL_Event e;
	bool quit = false;
	while(quit == false) {
		SDL_Delay(5);
		if(f % 4 == 0) loop();
		while(SDL_PollEvent(&e)) {
			if(e.type == SDL_QUIT) quit = true;
		}
		f++;
	}
	return 0;
}

void drawLine(SDL_Renderer *renderer, Line &l, SDL_Color color) {
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, l.start.x, l.start.y, l.end.x, l.end.y);
}

void drawCircle(SDL_Renderer *renderer, Vec2 center, double r, SDL_Color color) {
	double angle = 0.0;
	double increment = M_PI * 2.0 / 100.0;
	Vec2 p1 = Vec2(center.x + r * cos(angle), center.y + r * sin(angle));
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
	SDL_RenderDrawLine(renderer, center.x, center.y, p1.x, p1.y);
	angle += increment;
	for(int i = 0; i < 100; i++) {
		Vec2 p2 = Vec2(center.x + r * cos(angle), center.y + r * sin(angle));
		SDL_RenderDrawLine(renderer, p1.x, p1.y, p2.x, p2.y);
		p1 = p2;
		angle += increment;
	}
}

//! setup runs once and afterwards loop runs repeatedly

void setup() {}

Line l1 = Line({100, 300}, {550, 350});
Line l2 = Line({350, 550}, {300, 100});

void loop() {
	rn::clear(g_renderer, {0, 0, 0});

	int x, y;
	SDL_GetMouseState(&x, &y);

	l1.end = Vec2(x, y);

	drawLine(g_renderer, l1, {255, 0, 0});
	drawLine(g_renderer, l2, {0, 255, 0});

	Intersection i = l1.intersects(l2);

	if(i.exists) {
		drawCircle(g_renderer, i.point, 7, {0, 255, 255});
		Line norm = Line(i.point, i.point + i.normal * 20);
		drawLine(g_renderer, norm, {255, 255, 0});
	}

	SDL_RenderPresent(g_renderer);
}
