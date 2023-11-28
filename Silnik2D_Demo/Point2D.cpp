#include "Point2D.h"

Point2D::Point2D() {};

// Konstruktor klasy przypisuj¹cy wartoœci
Point2D::Point2D(float x, float y) {
	this->x = x;
	this->y = y;
};

// Funkcja zwracaj¹ca wartoœæ X
float Point2D::get_X() {
	return x;
}

// Funkcja zwracaj¹ca wartoœæ Y
float Point2D::get_Y() {
	return y;
}
// Funkcja ustawiaj¹ca wartoœæ X
void Point2D::set_X(float x) {
	this->x = x;
}
// Funkcja ustawiaj¹ca wartoœæ Y
void Point2D::set_Y(float y) {
	this->y = y;
}

// DOKOÑCZ / POPRAW
void Point2D::draw(ALLEGRO_COLOR KOLOR) {

}

