#pragma once
#include "Point2D.h"
#include "PrimitiveRenderer.h"

class  LineSegment {

	// Punkt pocz¹tkowy i koñcowy linii
	Point2D p_Begin;
	Point2D p_End;

public:
	// Konstruktor klasy z dwoma paramterami klasy Point2D
	LineSegment(Point2D p_Begin, Point2D p_End);

	// Metody zwracaj¹ce punkty linii
	Point2D get_P_Begin();
	Point2D get_P_End();

	// Metody ustawiaj¹ce punkt pocz¹tkowy i koñcowy linii
	void set_P_Begin(float x, float y);
	void set_P_End(float x, float y);

	// Metoda rysuj¹ca linie algorytmem przyrostowym
	void draw_increment_line(ALLEGRO_COLOR KOLOR);


};