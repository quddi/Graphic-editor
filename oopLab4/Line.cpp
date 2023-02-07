#include "Line.h"

Line::Line(float _length, Color color) {
	this->length = _length;
	this->color = color;
	is_collided = false;
	line = new RectangleShape(Vector2f(_length, 3));
	line->setFillColor(color);
}

Line::~Line() {
	delete(line);
}

FloatRect Line::get_global_bounds() {
	return line->getGlobalBounds();
}

void Line::set_scale(float x, float y) {
	if (x < 0.2)
		x = 0.2;

	line->setScale(x, width);
}

Vector2f Line::get_scale() {
	return line->getScale();
}

Vector2f Line::get_position() {
	return line->getPosition();
}

bool Line::check_intersection(Figure* figure) {
	return get_global_bounds().intersects(figure->get_global_bounds());
}

void Line::hide() {
	line->setFillColor(Color(color.r, color.g, color.b, MIN_COLOR_VALUE));
}

void Line::show() {
	line->setFillColor(Color(color.r, color.g, color.b, MAX_COLOR_VALUE));
}

void Line::move(float x, float y) {
	line->move(x, y);
}

void Line::set_outline(float thickness, Color color) {
	line->setOutlineColor(color);
	line->setOutlineThickness(thickness);
}

void Line::set_color(Color color) {
	this->color = color;
	line->setFillColor(color);
}

Figure* Line::get_copy()
{
	Line* res = new Line(length, color);

	return res;
}

void Line::draw(RenderWindow& window) {
	update_window_collision(window);
	window.draw(*line);
}

