#include "Triangle.h"

Triangle::Triangle(float height, Color color) {
	const int triangle_sides_count = 3;
	triangle = new CircleShape(height, triangle_sides_count);
	this->height = height;
	this->color = color;
	is_collided = false;
	triangle->setFillColor(color);
}

Triangle::~Triangle() {
	delete(triangle);
}

void Triangle::move(float x, float y) {
	triangle->move(x, y);
}

void Triangle::set_outline(float thickness, Color color) {
	triangle->setOutlineColor(color);
	triangle->setOutlineThickness(thickness);
}

void Triangle::set_color(Color color) {
	this->color = color;
	triangle->setFillColor(color);
}

Figure* Triangle::get_copy() {
	Triangle* res = new Triangle(height, color);

	return res;
}

void Triangle::draw(RenderWindow& window) {
	update_window_collision(window);
	window.draw(*triangle);
}

FloatRect Triangle::get_global_bounds() {
	return triangle->getGlobalBounds();
}

void Triangle::set_scale(float x, float y) {
	if (x < 0.2)
		x = 0.2;

	if (y < 0.2)
		y = 0.2;

	triangle->setScale(x, y);
}

Vector2f Triangle::get_scale() {
	return triangle->getScale();
}

Vector2f Triangle::get_position() {
	return triangle->getPosition();
}

bool Triangle::check_intersection(Figure* figure) {
	return get_global_bounds().intersects(figure->get_global_bounds());
}

void Triangle::hide() {
	triangle->setFillColor(Color(color.r, color.g, color.b, MIN_COLOR_VALUE));
}

void Triangle::show() {
	triangle->setFillColor(Color(color.r, color.g, color.b, MAX_COLOR_VALUE));
}