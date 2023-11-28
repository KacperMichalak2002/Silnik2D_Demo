#pragma once
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/color.h>
#include <iostream>
#include <vector>
#include "Point2D.h"
#include "LineSegment.h"
#include <vector>
#include <math.h>
#include <cmath>



using namespace std;

class PrimitiveRenderer {

public:
	PrimitiveRenderer();
	// Metoda rysuj¹ca linie algorytmem przyrostowym

protected:
	void draw_Line_Incremental(Point2D p_Begin, Point2D p_End, ALLEGRO_COLOR KOLOR);


	// Metoda rysuj¹ca punkt
	void draw_point(float x, float y, ALLEGRO_COLOR KOLOR);

	// Metoda rysuj¹ca linie ³aman¹ zamkniêt¹ 
	void draw_Broken_Line(vector <Point2D> points, ALLEGRO_COLOR KOLOR);

	//DOKOÑCZ OTWARTA LINIA £AMANA

		// Metoda rysuj¹ca okr¹g
	void draw_Circle_4xSymmetry(Point2D point, float r, ALLEGRO_COLOR KOLOR, int thickness);

	void draw_Filled_Circle(Point2D point, float r, ALLEGRO_COLOR KOLOR, bool* isScaled);

	// Metoda rysuj¹ca okr¹g
	void draw_Circle_8xSymmetry(Point2D point, int r, ALLEGRO_COLOR KOLOR);

	// Metoda rysuj¹ca elipse
	void draw_Ellipse_4xSymmetry(Point2D point, int rx, int ry, ALLEGRO_COLOR KOLOR);

	// Metoda rysuj¹ca elipse
	void draw_Ellipse_8xSymmetry(Point2D point, int rx, int ry, ALLEGRO_COLOR KOLOR);

	void draw_shape(vector<Point2D> points, ALLEGRO_COLOR KOLOR) {

		draw_Broken_Line(points, KOLOR);
		draw_Line_Incremental(points[0], points[points.size() - 1], KOLOR);
	}

	//Metoda rysuj¹ca prostok¹t
	void draw_Rectangle(Point2D p1, Point2D p2, ALLEGRO_COLOR KOLOR, int thickness);

	void draw_Filled_Rectangle(Point2D p1, Point2D p2, ALLEGRO_COLOR KOLOR_W);

	//Metoda rysuj¹ca trójk¹t
	void draw_Triangle(Point2D p1, Point2D p2, Point2D p3, ALLEGRO_COLOR KOLOR);

};

class Rectangle : protected PrimitiveRenderer {
public:
	Point2D p1;
	Point2D p2;
	Point2D p3;
	Point2D p4;
	//kat obrotu
	float angle;
	//wspolrzedne srodka
	float mx;
	float my;
	const double PI = 3.141592653589793;
	bool rotated = false;

	Rectangle(Point2D p1, Point2D p2) {
		this->p1 = p1;
		this->p2 = p2;
		this->angle = 0;
		//obliczenia wspolrzednych srodka
		this->mx = (p1.get_X() + p2.get_X()) / 2;
		this->my = (p1.get_Y() + p2.get_Y()) / 2;
		this->rotated = rotated;
		// Utworzenie dwóch pozosta³ych punktów prostok¹ta
		this->p3 = Point2D(p1.get_X(), p2.get_Y());
		this->p4 = Point2D(p2.get_X(), p1.get_Y());
	}

	Rectangle(){}

	void setP1(Point2D p) {
		this->p1 = p;
	}

	void setP2(Point2D p) {
		this->p2 = p;
	}

	void drawRectangle(ALLEGRO_COLOR KOLOR, int thickness) {
		if (rotated) {
			vector<Point2D> points = {
				p1,p3,p2,p4
			};
			draw_shape(points, KOLOR);
		}
		else
			draw_Rectangle(p1, p2, KOLOR, thickness);
	}


	void drawFilledRectangle(ALLEGRO_COLOR KOLOR_W) {
		draw_Filled_Rectangle(p1, p2, KOLOR_W);

	}

	void rotate(float angle) {
		// przeliczenie k¹ta na radiany
		float rad = angle * PI / 180.0;

		// przesuniêcie do pocz¹tku uk³adu wspó³rzêdnych
		translate(-mx, -my);

		// obrót
		float new_p1_x = p1.get_X() * cos(rad) - p1.get_Y() * sin(rad);
		float new_p1_y = p1.get_X() * sin(rad) + p1.get_Y() * cos(rad);
		float new_p2_x = p2.get_X() * cos(rad) - p2.get_Y() * sin(rad);
		float new_p2_y = p2.get_X() * sin(rad) + p2.get_Y() * cos(rad);
		float new_p3_x = p3.get_X() * cos(rad) - p3.get_Y() * sin(rad);
		float new_p3_y = p3.get_X() * sin(rad) + p3.get_Y() * cos(rad);
		float new_p4_x = p4.get_X() * cos(rad) - p4.get_Y() * sin(rad);
		float new_p4_y = p4.get_X() * sin(rad) + p4.get_Y() * cos(rad);

		p1.set_X(new_p1_x);
		p1.set_Y(new_p1_y);
		p2.set_X(new_p2_x);
		p2.set_Y(new_p2_y);
		p3.set_X(new_p3_x);
		p3.set_Y(new_p3_y);
		p4.set_X(new_p4_x);
		p4.set_Y(new_p4_y);

		rotated = true;

		// przesuniêcie z powrotem do pierwotnej pozycji
		translate(mx, my);
	}

	void translate(float dx, float dy) {
		//przesuniecie czworokatu
		p1.set_X(p1.get_X() + dx);
		p1.set_Y(p1.get_Y() + dy);
		p2.set_X(p2.get_X() + dx);
		p2.set_Y(p2.get_Y() + dy);
		p3.set_X(p3.get_X() + dx);
		p3.set_Y(p3.get_Y() + dy);
		p4.set_X(p4.get_X() + dx);
		p4.set_Y(p4.get_Y() + dy);
	}

	void scale(float dx, float dy) {
		// przesuniêcie do pocz¹tku uk³adu wspó³rzêdnych
		translate(-mx, -my);

		// skalowanie
		p1.set_X(p1.get_X() * dx);
		p1.set_Y(p1.get_Y() * dy);
		p2.set_X(p2.get_X() * dx);
		p2.set_Y(p2.get_Y() * dy);
		p3.set_X(p3.get_X() * dx);
		p3.set_Y(p3.get_Y() * dy);
		p4.set_X(p4.get_X() * dx);
		p4.set_Y(p4.get_Y() * dy);

		// przesuniêcie z powrotem do pierwotnej pozycji
		translate(mx, my);
	}
};

class Triangle :protected PrimitiveRenderer {
public:
	Point2D p1;
	Point2D p2;
	Point2D p3;
	float angle;
	const double PI = 3.141592653589793;
	// œrodek trójk¹ta
	float mx;
	float my;

	Triangle(Point2D p1, Point2D p2, Point2D p3) {
		this->p1 = p1;
		this->p2 = p2;
		this->p3 = p3;
		this->angle = 0;
		// Obliczamy œrodek  trójk¹ta
		this->mx = (p1.get_X() + p2.get_X() + p3.get_X()) / 3;
		this->my = (p1.get_Y() + p2.get_Y() + p3.get_Y()) / 3;

	}
	void drawTriangle(ALLEGRO_COLOR KOLOR, int thickness) {
		al_draw_triangle(p1.get_X(), p1.get_Y(), p2.get_X(), p2.get_Y(), p3.get_X(), p3.get_Y(), KOLOR, thickness);
	}

	void drawFilledTriagnle(ALLEGRO_COLOR KOLOR) {
		al_draw_filled_triangle(p1.get_X(), p1.get_Y(), p2.get_X(), p2.get_Y(), p3.get_X(), p3.get_Y(), KOLOR);
	}


	void rotate(float angle) {
		// przeliczenie k¹ta na radiany
		float rad = angle * PI / 180.0;

		// przesuniêcie do pocz¹tku uk³adu wspó³rzêdnych
		translate(-mx, -my);

		//obrot trojkata
		float new_p1_x = p1.get_X() * cos(rad) - p1.get_Y() * sin(rad);
		float new_p1_y = p1.get_X() * sin(rad) + p1.get_Y() * cos(rad);
		float new_p2_x = p2.get_X() * cos(rad) - p2.get_Y() * sin(rad);
		float new_p2_y = p2.get_X() * sin(rad) + p2.get_Y() * cos(rad);
		float new_p3_x = p3.get_X() * cos(rad) - p3.get_Y() * sin(rad);
		float new_p3_y = p3.get_X() * sin(rad) + p3.get_Y() * cos(rad);

		p1.set_X(new_p1_x);
		p1.set_Y(new_p1_y);
		p2.set_X(new_p2_x);
		p2.set_Y(new_p2_y);
		p3.set_X(new_p3_x);
		p3.set_Y(new_p3_y);

		// przesuniêcie z powrotem do pierwotnej pozycji
		translate(mx, my);
	}

	void translate(float dx, float dy) {
		//przesuniecie trojkata
		p1.set_X(p1.get_X() + dx);
		p1.set_Y(p1.get_Y() + dy);
		p2.set_X(p2.get_X() + dx);
		p2.set_Y(p2.get_Y() + dy);
		p3.set_X(p3.get_X() + dx);
		p3.set_Y(p3.get_Y() + dy);
	}

	void scale(float dx, float dy) {
		// przesuniêcie do pocz¹tku uk³adu wspó³rzêdnych
		translate(-mx, -my);

		//skalowanie trojkata
		p1.set_X(p1.get_X() * dx);
		p1.set_Y(p1.get_Y() * dy);
		p2.set_X(p2.get_X() * dx);
		p2.set_Y(p2.get_Y() * dy);
		p3.set_X(p3.get_X() * dx);
		p3.set_Y(p3.get_Y() * dy);

		// przesuniêcie z powrotem do pierwotnej pozycji
		translate(mx, my);
	}
};

class Circle :protected PrimitiveRenderer {
public:
	Point2D point;
	int r;
	float angle;
	bool isScaled = false;

	Circle(Point2D point, int r) {
		this->point = point;
		this->r = r;
		this->angle = 0;

	}

	void drawCircle(ALLEGRO_COLOR KOLOR, int thickness) {
		al_draw_circle(point.get_X(), point.get_Y(), r, KOLOR, thickness);
	}

	void drawFilledCircle(ALLEGRO_COLOR KOLOR) {
		draw_Filled_Circle(point, r, KOLOR, &isScaled);
	}

	void rotate(float angle) {

	}

	void translate(float dx, float dy) {
		point.set_X(point.get_X() + dx);
		point.set_Y(point.get_Y() + dy);
	}

	void scale(float rx) {
		//skalowanie okregu
		r *= rx;
	}
};

class Ellipse :protected PrimitiveRenderer {
public:
	Point2D point;
	int rx;
	int ry;
	float angle;
	const double PI = 3.141592653589793;

	Ellipse(Point2D point, int rx, int ry) {
		this->point = point;
		this->rx = rx;
		this->ry = ry;
		this->angle;

	}
	void drawEllipse(ALLEGRO_COLOR KOLOR, int thickness) {
		al_draw_ellipse(point.get_X(), point.get_Y(), rx, ry, KOLOR, thickness);
	}

	void drawFilledEllipse(ALLEGRO_COLOR KOLOR) {
		al_draw_filled_ellipse(point.get_X(), point.get_Y(), rx, ry, KOLOR);
	}
	void rotate(float angle) {
		// Przeliczenie k¹ta na radiany
		float rad = angle * PI / 180.0;

		// Przesuniêcie do pocz¹tku uk³adu wspó³rzêdnych
		translate(-point.get_X(), -point.get_Y());

		// Obrot elipsy
		float new_rx = rx * cos(rad) - ry * sin(rad);
		float new_ry = rx * sin(rad) + ry * cos(rad);

		rx = new_rx;
		ry = new_ry;

		// Przesuniêcie z powrotem do pierwotnego miejsca
		translate(point.get_X(), point.get_Y());
	}

	void translate(float dx, float dy) {
		point.set_X(point.get_X() + dx);
		point.set_Y(point.get_Y() + dy);
	}

	void scale(float sx, float sy) {
		//skalowanie elipsy
		rx *= sx;
		ry *= sy;
	}
};

class Line :protected PrimitiveRenderer {
public:
	Point2D p_Begin;
	Point2D p_End;
	//kat
	float angle;
	//œrodek linii
	float mx;
	float my;
	const double PI = 3.141592653589793;

	Line(Point2D p_Begin, Point2D p_End) {
		this->p_Begin = p_Begin;
		this->p_End = p_End;
		this->angle = 0;
		//obliczanie srodka linii
		this->mx = (p_Begin.get_X() + p_End.get_X()) / 2;
		this->my = (p_Begin.get_Y() + p_End.get_Y()) / 2;
	}

	void draw(ALLEGRO_COLOR KOLOR) {
		draw_Line_Incremental(p_Begin, p_End, KOLOR);
	}

	void rotate(float angle) {
		// przeliczenie k¹ta na radiany
		float rad = angle * PI / 180.0;
		//Przesuniecie linii do poczatku ukladu wspolrzednych
		translate(-mx, -my);

		// Obrot
		float tempX = p_Begin.get_X() * cos(rad) - p_Begin.get_Y() * sin(rad);
		p_Begin.set_Y(p_Begin.get_X() * sin(rad) + p_Begin.get_Y() * cos(rad));
		p_Begin.set_X(tempX);

		tempX = p_End.get_X() * cos(rad) - p_End.get_Y() * sin(rad);
		p_End.set_Y(p_End.get_X() * sin(rad) + p_End.get_Y() * cos(rad));
		p_End.set_X(tempX);

		// Przesuniecie linii z powrotem na jej pierwotne miejsce
		translate(mx, mx);
	}

	void translate(float dx, float dy) {
		//przesuniecie linii
		p_Begin.set_X(p_Begin.get_X() + dx);
		p_Begin.set_Y(p_Begin.get_Y() + dy);
		p_End.set_X(p_End.get_X() + dx);
		p_End.set_Y(p_End.get_Y() + dy);
	}

	void scale(float sx, float sy) {
		//Przesuniecie linii do poczatku ukladu wspolrzednych
		translate(-mx, -my);

		//skalowanie linii
		p_Begin.set_X(p_Begin.get_X() * sx);
		p_Begin.set_Y(p_Begin.get_Y() * sy);
		p_End.set_X(p_End.get_X() * sx);
		p_End.set_Y(p_End.get_Y() * sy);

		// Przesuniecie linii z powrotem na jej pierwotne miejsce
		translate(mx, my);
	}
};
