#include "Square.h"

Square::Square(float side, Color color) {
	square = new RectangleShape(Vector2f(side, side));
	this->color = color;
	this->side = side;
	is_collided = false;
	square->setFillColor(color);
}

Square::~Square() {
	delete(square);
}

void Square::move(float x, float y) {
	square->move(x, y);
}

void Square::set_outline(float thickness, Color color) {
	square->setOutlineColor(color);
	square->setOutlineThickness(thickness);
}

void Square::set_color(Color color) {
	this->color = color;
	square->setFillColor(color);
}

Figure* Square::get_copy()
{
	Square* res = new Square(side, color);

	return res;
}

void Square::draw(RenderWindow& window) {
	update_window_collision(window);
	window.draw(*square);
}

FloatRect Square::get_global_bounds() {
	return square->getGlobalBounds();
}

void Square::set_scale(float x, float y) {
	if (x < 0.2)
		x = 0.2;

	if (y < 0.2)
		y = 0.2;

	square->setScale(x, y);
}

Vector2f Square::get_scale() {
	return square->getScale();
}

Vector2f Square::get_position() {
	return square->getPosition();
}

bool Square::check_intersection(Figure* figure) {
	return get_global_bounds().intersects(figure->get_global_bounds());
}

void Square::hide() {
	square->setFillColor(Color(color.r, color.g, color.b, MIN_COLOR_VALUE));
}

void Square::show() {
	square->setFillColor(Color(color.r, color.g, color.b, MAX_COLOR_VALUE));
}