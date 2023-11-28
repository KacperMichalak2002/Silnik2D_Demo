#include "Bitmap.h"
//konstruktor
Bitmap::Bitmap(int scaleX, int scaleY)
{
    bitmap = nullptr;
    active = false;
    this->scaleX = scaleX;
    this->scaleY = scaleY;
    angle = 0;
    centerX = 64;
    centerY = 64;
    bitmap_h = 256;
    bitmap_w = 256;
    flags = 0;
    dir = 0;
}

//dekonstruktor
Bitmap::~Bitmap(void) {
    al_destroy_bitmap(bitmap);
}

//create bitmap  w h
void Bitmap::initialize(int width, int height) {
    if (bitmap != nullptr) {
        al_destroy_bitmap(bitmap);
    }

    bitmap = al_create_bitmap(width, height);
    if (bitmap == nullptr) {
        std::cout << "error creating bitmap 1" << std::endl;
        return;
    }

}
//load bitmap
void Bitmap::load(const char* filename) {

    bitmap = al_load_bitmap(filename);

    if (bitmap == nullptr) {
        std::cout << "error loading bitmap " << std::endl;
        return;
    }

}

//draw bitmap
void Bitmap::draw_bitmap(int x, int y) {

    if (bitmap)
    {
        al_draw_bitmap(bitmap, x, y, 0);
       // al_draw_scaled_rotated_bitmap(bitmap, centerX, centerY, x, y, scaleX, scaleY, angle, flags);
    }
    else
        std::cout << "Error drawing bitmap" << std::endl;
}
/*
//save to file bitmap
bool Bitmap::save_to_file(const char* filename)
{
    return al_save_bitmap(filename, bitmap);
}

//copy from bitmap and draw
void Bitmap::copy_from_and_draw(Bitmap& source, int sourceX, int sourceY, int destX, int destY, int width, int height) {
    al_draw_bitmap_region(source.bitmap, sourceX, sourceY, width, height, destX, destY, 0);
}
*/


void Bitmap::drawBitmapRegion(int curFrame, int dir, Bitmap* b) {
    // Draw a portion of the sourceBitmap to the display
    if (bitmap != nullptr)
    {

        if (dir == 0)
        {
            //al_draw_bitmap_region(b, srcX, srcY, srcWidth, 0 ,destX, destY, 0);
            al_draw_bitmap_region(bitmap, curFrame * 64, 0, 64, 64, b->centerX, b->centerY, 0);
        }
        else if (dir == 1)
        {
            //al_draw_bitmap_region(b, srcX, srcY, srcWidth, 64, destX, destY, 0);
            al_draw_bitmap_region(bitmap, curFrame * 64, 64, 64, 64, b->centerX, b->centerY, 0);

        }
        else if (dir == 2)
        {
            //al_draw_bitmap_region(b, srcX, srcY, srcWidth, 128, destX, destY, 0);
            al_draw_bitmap_region(bitmap, curFrame * 64, 128, 64, 64, b->centerX, b->centerY, 0);

        }
        else
            al_draw_bitmap_region(bitmap, curFrame * 64, 192, 64, 64, b->centerX, b->centerY, 0);

        // al_draw_bitmap_region(b, srcX, srcY, srcWidth, 192, destX, destY, 0);



    }
    else
        std::cout << "errror drawing bitmap region" << std::endl;

}
