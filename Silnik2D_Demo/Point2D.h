#pragma once
#include<allegro5/allegro.h>

class Point2D {

	float x, y;

public:

	// Konstruktor pusty
	Point2D();
	// Konstriktor z parametrami punktu
	Point2D(float x, float y);

	// Metody zwracaj¹ce wartoœci wspó³rzêdnych
	float get_X();
	float get_Y();

	// Metody ustawiaj¹ce wspó³rzêdne
	void set_X(float x);
	void set_Y(float y);


	void draw(ALLEGRO_COLOR KOLOR);



};