#include "Point2D.h"

Point2D::Point2D() {};

// Konstruktor klasy przypisuj�cy warto�ci
Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
};

// Funkcja zwracaj�ca warto�� X
float Point2D::get_X() {
	return x;
}

// Funkcja zwracaj�ca warto�� Y
float Point2D::get_Y() {
	return y;
}
// Funkcja ustawiaj�ca warto�� X
void Point2D::set_X(float x) {
	this->x = x;
}
// Funkcja ustawiaj�ca warto�� Y
void Point2D::set_Y(float y) {
	this->y = y;
}

// DOKO�CZ / POPRAW
void Point2D::draw(ALLEGRO_COLOR KOLOR) {

}

