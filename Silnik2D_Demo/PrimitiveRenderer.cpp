#pragma once
#include "PrimitiveRenderer.h"

PrimitiveRenderer::PrimitiveRenderer() {}

void PrimitiveRenderer::draw_Line_Incremental(Point2D p_Begin, Point2D p_End, ALLEGRO_COLOR color) {

	float dx, dy, step, x, y;
	int i;

	// Przypisanie punktów
	float x1 = p_Begin.get_X();
	float y1 = p_Begin.get_Y();
	float x2 = p_End.get_X();
	float y2 = p_End.get_Y();

	dx = x2 - x1; //Różnica położenia punktów na osi X
	dy = y2 - y1; //Różnica położenia punktów na osi Y

	// Określenie kierunku rysowania na podstawie wartości bezwzględnych
	if (abs(dx) >= abs(dy)) {
		step = abs(dx); // Krok na osi X
	}
	else {
		step = abs(dy); // Krok na osi Y
	}

	dx /= step; // Krok na osi X
	dy /= step; // Krok na osi Y

	x = x1; // Inicjalizacja zmiennej x punktem początkowym w osi X
	y = y1; // Inicjalizacja zmiennej y punktem początkowym w osi Y

	// Rysowanie pikseli
	for (i = 0; i <= step; i++) {
		al_draw_pixel(x, y, color);
		x += dx;
		y += dy;
	}
}

void PrimitiveRenderer::draw_Circle_4xSymmetry(Point2D point, float r, ALLEGRO_COLOR KOLOR, int thickness)
{
	// Współrzędne środka okręgu
	float xc = point.get_X();
	float yc = point.get_Y();

	float a, step;
	int x, y;

	// Obliczenie kroku
	int width = r * 4;
	int height = r * 4;
	static ALLEGRO_BITMAP* bufferCircle = nullptr;
	if (!bufferCircle) {

		bufferCircle = al_create_bitmap(width, height);
		al_set_target_bitmap(bufferCircle);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		al_set_target_backbuffer(al_get_current_display());

		al_set_target_bitmap(bufferCircle);
		// Iteracja przez jedną czwartą okręgu (0 do ?/2)

		for (float i = 0; i < thickness; i += 0.25) {
			step = 1.0 / r;
			for (a = 0; a < 3.14 / 2; a += step) {

				// Obliczanie współrzędnych pikseli w okręgu
				x = xc + r * cos(a) + 0.5;
				y = yc + r * sin(a) + 0.5;

				// Rysowanie pikseli w ośmiu symetrycznych punktach
				al_draw_pixel(x, y, KOLOR);
				al_draw_pixel(x, yc - (y - yc), KOLOR);
				al_draw_pixel(xc - (x - xc), y, KOLOR);
				al_draw_pixel(xc - (x - xc), yc - (y - yc), KOLOR);

			}
			r += 0.25;
		}

	}

	al_set_target_backbuffer(al_get_current_display());
	al_draw_bitmap(bufferCircle, xc, yc, 0);

}

void PrimitiveRenderer::draw_Filled_Circle(Point2D point, float r, ALLEGRO_COLOR KOLOR, bool* isScaled) {
	float x1 = point.get_X();
	float y1 = point.get_Y();

	static ALLEGRO_BITMAP* bufferCircle = nullptr;
	if (!bufferCircle || *isScaled) {
		int width = r * 2;
		int height = r * 2;
		bufferCircle = al_create_bitmap(width, height);
		al_set_target_bitmap(bufferCircle);
		al_clear_to_color(al_map_rgba(0, 0, 0, 0));
		al_set_target_backbuffer(al_get_current_display());

		al_set_target_bitmap(bufferCircle);

		// P�tla rysuj�ca ko�o
		for (int y = -r; y <= r; y++) {
			for (int x = -r; x <= r; x++) {
				int sum = (x * x + y * y);
				// Sprawdzenie czy punk jest wewn�trz ko�a
				if (sum <= r * r) {
					// Rysowanie piksela o przesuni�tych wsp�rz�dnych
					al_put_pixel(r + x, r + y, KOLOR);
				}
			}
		}
		*isScaled = false;
	}

	al_set_target_backbuffer(al_get_current_display());
	al_draw_bitmap(bufferCircle, x1 - r, y1 - r, 0);
}

void PrimitiveRenderer::draw_Circle_8xSymmetry(Point2D point, int r, ALLEGRO_COLOR KOLOR)
{
	// Współrzędne środka okręgu
	float xc = point.get_X();
	float yc = point.get_Y();

	float a, step;
	int x, y;
	step = 1.0 / r; // Obliczenie kroku

	// Iteracja przez jedną ósmą okręgu (0 do ?/4)
	for (a = 0; a < 3.14 / 4; a += step) {

		// Obliczanie współrzędnych pikseli w okręgu
		x = xc + r * cos(a) + 0.5;
		y = yc + r * sin(a) + 0.5;

		// Rysowanie pikseli w ośmiu symetrycznych punktach
		al_draw_pixel(x, y, KOLOR);
		al_draw_pixel(xc - (x - xc), y, KOLOR);
		al_draw_pixel(x, yc - (y - yc), KOLOR);
		al_draw_pixel(xc - (x - xc), yc - (y - yc), KOLOR);

		al_draw_pixel(xc - (y - yc), x, KOLOR);
		al_draw_pixel(xc - (y - yc), yc - (x - xc), KOLOR);
		al_draw_pixel(y, yc - (x - xc), KOLOR);
		al_draw_pixel(y, x, KOLOR);

	}
}

void PrimitiveRenderer::draw_Ellipse_4xSymmetry(Point2D point, int rx, int ry, ALLEGRO_COLOR KOLOR) {
	// Współrzędne środka elipsy
	float xc = point.get_X();
	float yc = point.get_Y();
	float a, step;

	int x, y;

	step = 1.0 / rx; // Obliczanie kroku inkrementacji kąta

	// Iteracja przez jedną czwartą elipsy ( 0 do ?/2)
	for (a = 0; a < 3.14 / 2; a += step) {
		// Obliczanie kolejnych współrzędnych 
		x = xc + rx * cos(a) + 0.5;
		y = yc + ry * sin(a) + 0.5;

		// Rysowanie pikseli w czterech symetrycznych punktach elipsy
		al_draw_pixel(x, y, KOLOR);
		al_draw_pixel(xc - (x - xc), y, KOLOR);
		al_draw_pixel(x, yc - (y - yc), KOLOR);
		al_draw_pixel(xc - (x - xc), yc - (y - yc), KOLOR);

	}
}

void PrimitiveRenderer::draw_Ellipse_8xSymmetry(Point2D point, int rx, int ry, ALLEGRO_COLOR KOLOR) {

	// Współrzędne środka elipsy
	float xc = point.get_X();
	float yc = point.get_Y();

	float a, step;
	int x, y;
	step = 1.0 / rx; // Obliczanie kroku inkrementacji kąta

	// Iteracja przez jedną ósmą elipsy ( 0 do ?/4)
	for (a = 0; a < 3.14 / 4; a += step) {
		x = xc + rx * cos(a) + 0.5;
		y = yc + ry * sin(a) + 0.5;

		// Rysowanie pikseli
		al_draw_pixel(x, y, KOLOR);
		al_draw_pixel(xc - (x - xc), y, KOLOR);
		al_draw_pixel(x, yc - (y - yc), KOLOR);
		al_draw_pixel(xc - (x - xc), yc - (y - yc), KOLOR);

		// Zamiana stron rysowania ćwiartek
		x = xc + rx * sin(a) + 0.5;
		y = yc + ry * cos(a) + 0.5;

		al_draw_pixel(x, y, KOLOR);
		al_draw_pixel(xc - (x - xc), y, KOLOR);
		al_draw_pixel(x, yc - (y - yc), KOLOR);
		al_draw_pixel(xc - (x - xc), yc - (y - yc), KOLOR);

	}
}

void PrimitiveRenderer::draw_point(float x, float y, ALLEGRO_COLOR KOLOR) {

	// Rysowanie punktu przy pomocy wbudowanej funkcji biblioteki allegro
	al_draw_pixel(x, y, KOLOR);
}

void PrimitiveRenderer::draw_Broken_Line(vector <Point2D> points, ALLEGRO_COLOR KOLOR) {

	// Rysowanie linii łącząc punkty 
	for (int i = 0; i < points.size() - 1; i++)
	{
		// Rysowanie odcinka dwoma kolejnymi punktami
		draw_Line_Incremental(points.at(i), points.at(i + 1), KOLOR);
	}
}

void PrimitiveRenderer::draw_Rectangle(Point2D p1, Point2D p2, ALLEGRO_COLOR KOLOR, int thickness) {

	// Utworzenie dwóch pozostałych punktów prostokąta
	Point2D p3(p1.get_X(), p2.get_Y());
	Point2D p4(p2.get_X(), p1.get_Y());

	// Utworzenie listy punktów
	vector<Point2D> points = {
		p1,p3,p2,p4
	};

	if (thickness > 1) {


		vector<Point2D> points2 = {
				p1,p3,p2,p4
		};

		for (int i = 0; i < thickness; i++) {
			p1.set_X(p1.get_X() - 1);
			p1.set_Y(p1.get_Y() - 1);
			p2.set_X(p2.get_X() + 1);
			p2.set_Y(p2.get_Y() + 1);
			p3.set_X(p1.get_X());
			p3.set_Y(p2.get_Y());

			p4.set_X(p2.get_X());
			p4.set_Y(p1.get_Y());
			points2 = {
				p1,p3,p2,p4
			};
			draw_shape(points2, KOLOR);
		}

	}
	// Narysowanie kształtu
	draw_shape(points, KOLOR);

}

void  PrimitiveRenderer::draw_Filled_Rectangle(Point2D p1, Point2D p2, ALLEGRO_COLOR KOLOR_W) {
	
	al_draw_filled_rectangle(p1.get_X(), p1.get_Y(), p2.get_X(), p2.get_Y(), KOLOR_W);

}

void PrimitiveRenderer::draw_Triangle(Point2D p1, Point2D p2, Point2D p3, ALLEGRO_COLOR KOLOR) {

	// Utworzenie listy z puntków
	vector<Point2D> points = {
		p1,p2,p3
	};

	// Narysowanie kształtu używając funkcji draw_shape
	draw_shape(points, KOLOR);
}
