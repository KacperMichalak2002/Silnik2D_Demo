
#pragma once
#include <iostream>
#include "allegro5/allegro.h"
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_native_dialog.h"


//klasa bitmapy
class Bitmap {
public:
    int bitmap_w;
    int bitmap_h;
    int flags;
    int centerX;
    int centerY;
    int scaleX;
    int scaleY;
    int angle;
    int dir;

    ALLEGRO_BITMAP* bitmap;
    bool active;


    //metodty w bitmapie
    Bitmap(int scaleX, int scaleY);
    ~Bitmap(void);
    void initialize(int width, int height);
    void load(const char* filename);//tworzy bitmape 
    void draw_bitmap(int x, int y); //rysuje bitmape

    void drawBitmapRegion(int curFrame, int dir, Bitmap* b);

};

