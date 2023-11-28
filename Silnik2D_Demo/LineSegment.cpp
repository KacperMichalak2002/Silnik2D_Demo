#pragma once
#include "LineSegment.h"

// Konstruktor klasy przypisujacy warto�ci
LineSegment::LineSegment(Point2D p_Begin, Point2D p_End)
{
	this->p_Begin = p_Begin;
	this->p_End = p_End;
}

// Zwracanie punktu pocz�tkowego
Point2D LineSegment::get_P_Begin() {
	return p_Begin;
}

// Zwracanie punktu ko�cowego
Point2D LineSegment::get_P_End() {
	return p_End;
}

// Ustawienie warto�ci punktu pocz�tkowego
void LineSegment::set_P_Begin(float x, float y) {
	this->p_Begin.set_X(x);
	this->p_Begin.set_Y(y);
}

// Ustawienie warto�ci punktu ko�cowego
void LineSegment::set_P_End(float x, float y) {
	this->p_End.set_X(x);
	this->p_End.set_Y(y);
}

// DOKO�CZ / POPRAW
void LineSegment::draw_increment_line(ALLEGRO_COLOR KOLOR) {

}

