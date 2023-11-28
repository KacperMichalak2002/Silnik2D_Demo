#pragma once
#include <allegro5/allegro.h>
#include<allegro5/allegro_primitives.h>
#include<allegro5/allegro_font.h>
#include<allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <iostream>
#include "PrimitiveRenderer.h"
#include "LineSegment.h"
#include "Point2D.h"
#include "bitmap.h"
using namespace std;

#define SCREEN_WIDTH 976
#define SCREEN_HEIGHT 614


class Engine {

    ALLEGRO_DISPLAY* display;
    int width;
    int height;
    bool full_screen = false;
    int frames;
    bool mouse;
    bool keyboard;
    bool bitmaps;

public:

    Engine();

    Engine(int width, int height, bool full_screen);

    bool sprawdzanie_init(bool test);

    void ini_grafika();

    void set_full_screen(bool enable);

    bool init_display();

    void ini_bitmap(bool enable);

    void change_res(int newWidth, int newHeight);

    void set_frames(int new_frames);

    void set_mouse(bool enable);

    void set_keyboard(bool enable);

    void run(void(*funkcja)());

    void Mouse(ALLEGRO_DISPLAY* display, ALLEGRO_EVENT event, bool* done, int *mouse_x, int *mouse_y, float *x, float *y) {

        if (event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
            if (event.mouse.button & 1)
            {
                *mouse_x = event.mouse.x;
                *mouse_y = event.mouse.y;
            }
            if (event.mouse.x >= 0 && event.mouse.x <= 430 &&
                event.mouse.y >= 0 && event.mouse.y <= 50) {

            }
        }

        if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) { // zamykamy okno naszej apki
            *done = false;                    //ustawiamy done na TRUE co konczy petle while takze
            return;
        }

        if (event.type == ALLEGRO_EVENT_MOUSE_AXES)
        {
            *x = event.mouse.x;
            *y = event.mouse.y;
       }

    }


    void Keyboard(ALLEGRO_EVENT event, bool*right, bool*left, bool *fullscreen, bool *done) {

        //petla ktora dziala dopoki mamy done na FALSE

        ALLEGRO_KEYBOARD_STATE key_state;
        al_get_keyboard_state(&key_state);
       
        switch (event.type) {
        case ALLEGRO_EVENT_KEY_DOWN: //sprawdzamy ktory klawisz zostal wcisniety 
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                *right = true;

            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                *left = true;

            switch (event.keyboard.keycode) {
            case ALLEGRO_KEY_F: // Obs³uga klawisza F
                if (!*fullscreen) {
                    al_set_display_flag(al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW, true);
                    *fullscreen = true;
                }
                else {
                    al_set_display_flag(al_get_current_display(), ALLEGRO_FULLSCREEN_WINDOW, false);
                    *fullscreen = false;
                }
                break;
            case ALLEGRO_KEY_ESCAPE:  //wcisniety przycisk ESC
                *done = true;          //ustawiamy done na TRUE, co koñczy petle while
                break;

            }
            break;
        case ALLEGRO_EVENT_KEY_UP:
            if (event.keyboard.keycode == ALLEGRO_KEY_RIGHT)
                *right = false;

            if (event.keyboard.keycode == ALLEGRO_KEY_LEFT)
                *left = false;
            break;
        }

    }


};
