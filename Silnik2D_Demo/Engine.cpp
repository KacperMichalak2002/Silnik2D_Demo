#pragma once
#include "Engine.h"
#include "Bitmap.h"
using namespace std;

Engine::Engine()
{
	this->width = SCREEN_WIDTH;
	this->height = SCREEN_HEIGHT;
	this->full_screen = false;
}

Engine::Engine(int width, int height, bool full_screen)
{
	this->width = width;
	this->height = height;
	this->full_screen = full_screen;
}

bool Engine::sprawdzanie_init(bool test)
{
	if (test)
		return true;

	return false;
}

void Engine::ini_grafika()
{
	sprawdzanie_init(al_init());
	sprawdzanie_init(al_init_primitives_addon());
	sprawdzanie_init(al_init_font_addon());
	sprawdzanie_init(al_init_ttf_addon());
	sprawdzanie_init(al_init_image_addon());
}

void Engine::set_full_screen(bool enable)
{
	full_screen = enable;
}

bool Engine::init_display()
{
	if (full_screen)
	{
		al_set_new_display_flags(ALLEGRO_FULLSCREEN);
	}
	else
	{
		al_set_new_display_flags(ALLEGRO_WINDOWED);
	}

	display = al_create_display(width, height);
	if (!display)
	{
		cout << "Cannot create display" << endl;
		return false;
	}

	return true;
}

void Engine::change_res(int newWidth, int newHeight)
{
	width = newWidth;
	height = newHeight;
	al_resize_display(display, width, height);
}

void Engine::set_frames(int new_frames)
{
	frames = new_frames;
}

void Engine::set_mouse(bool enable)
{
	mouse = enable;
}

void Engine::set_keyboard(bool enable)
{
	keyboard = enable;
}


void Engine::ini_bitmap(bool enable) {
	bitmaps = enable;
}


void Engine::run(void (*funkcja)())
{
	if (!sprawdzanie_init(al_init()))
		return;
	al_init_primitives_addon();

	ALLEGRO_TIMER* timer = al_create_timer(1.0 / frames);

	ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();


	al_register_event_source(queue, al_get_display_event_source(display));
	al_register_event_source(queue, al_get_timer_event_source(timer));

	if (mouse)
	{
		al_install_mouse();
		al_register_event_source(queue, al_get_mouse_event_source());
	}

	if (keyboard)
	{
		al_install_keyboard();
		al_register_event_source(queue, al_get_keyboard_event_source());
	}

	if (bitmaps)	
	{
		al_init_image_addon();
	}

	al_start_timer(timer);
	bool running = true;
	bool redraw = true;

	while (running)
	{

		ALLEGRO_EVENT event;
		al_wait_for_event(queue, &event);



		switch (event.type)
		{

		case ALLEGRO_EVENT_TIMER:
			redraw = true;

			break;
		case ALLEGRO_EVENT_DISPLAY_CLOSE:
			running = false;
			break;

		}

		if (redraw)
		{
			al_clear_to_color(al_map_rgb(255, 255, 255));


			funkcja();

		
			al_flip_display();
		}

	}
	al_destroy_display(display);
	al_destroy_timer(timer);
	al_destroy_event_queue(queue);


}