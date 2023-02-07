#include "Circle.h"

Circle::Circle(float radius, Color color) {
	circle = new CircleShape(radius);
	this->radius = radius;
	this->color = color;
	is_collided = false;
	circle->setFillColor(color);
}

Circle::~Circle() {
	delete(circle);
}

void Circle::move(float x, float y) {
	circle->move(x, y);
}

void Circle::draw(RenderWindow& window) {
	update_window_collision(window);

	window.draw(*circle);
}

FloatRect Circle::get_global_bounds() {
	return circle->getGlobalBounds();
}

void Circle::set_scale(float x, float y) {
	if (x < 0.2)
		x = 0.2;

	if (y < 0.2)
		y = 0.2;

	circle->setScale(x, y);
}

Vector2f Circle::get_scale() {
	return circle->getScale();
}

Vector2f Circle::get_position() {
	return circle->getPosition();
}

bool Circle::check_intersection(Figure* figure) {
	return get_global_bounds().intersects(figure->get_global_bounds());
}

void Circle::hide() {
	circle->setFillColor(Color(color.r, color.g, color.b, MIN_COLOR_VALUE));
}

void Circle::show() {
	circle->setFillColor(Color(color.r, color.g, color.b, MAX_COLOR_VALUE));
}

void Circle::set_outline(float thickness, Color color) {
	circle->setOutlineColor(color);
	circle->setOutlineThickness(thickness);
}

Figure* Circle::get_copy() {
	Circle* res = new Circle(circle->getRadius(), circle->getFillColor());
	
	return res;
}

void Circle::set_color(Color color) {
	this->color = color;
	circle->setFillColor(color);
}