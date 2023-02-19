#include "Circle.h"

Circle::Circle(float radius, Color _color) {
	circle = new CircleShape(radius);
	scale = Vector2f(1, 1);
	this->radius = radius;
	this->color = _color;
	is_collided = false;
	circle->setFillColor(_color);
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
	if (x < MIN_SCALE)
		x = MIN_SCALE;

	if (y < MIN_SCALE)
		y = MIN_SCALE;

	scale = Vector2f(x, y);
	circle->setScale(x, y);
}

Vector2f Circle::get_scale() {
	return scale;
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

void Circle::set_outline(float thickness, Color _color) {
	circle->setOutlineColor(_color);
	circle->setOutlineThickness(thickness);
}

Figure* Circle::get_copy() {
	Circle* res = new Circle(circle->getRadius(), circle->getFillColor());

	const Vector2f current_pos = circle->getPosition();
	res->move(current_pos.x, current_pos.y);
	res->scale = Vector2f(scale.x, scale.y);
	res->automove = automove;

	return res;
}

void Circle::set_color(Color _color) {
	this->color = _color;
	circle->setFillColor(_color);
}

string Circle::to_string() {
	stringstream ss;

	ss << "Circle" << " " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " ";
	ss << get_position().x << " " << get_position().y << " ";
	ss << scale.x << " " << scale.y << " ";
	ss << (automove ? 1 : 0);

	return ss.str();
}

void Circle::from_string(vector<string>* splited) {
	if (splited->size() != 9 || (*splited)[0] != "Circle") {
		throw new exception("bad source");
	}

	Color obtained_color;
	float obtained_x_pos, obtained_y_pos, obtained_x_scale, obtained_y_scale;
	bool obtained_automove;

	try {
		obtained_color.r = stoi((*splited)[1]);
		obtained_color.g = stoi((*splited)[2]);
		obtained_color.b = stoi((*splited)[3]);

		obtained_x_pos = stoi((*splited)[4]);
		obtained_y_pos = stoi((*splited)[5]);
		obtained_x_scale = stoi((*splited)[6]);
		obtained_y_scale = stoi((*splited)[7]);

		if ((*splited)[8] == "0") {
			obtained_automove = false;
		}
		else if ((*splited)[8] == "1") {
			obtained_automove = true;
		}
		else {
			throw new exception();
		}
	}
	catch (exception _) {
		throw new exception("Failed to load a circle!");
	}

	color = obtained_color;
	move(obtained_x_pos, obtained_y_pos);
	set_scale(obtained_x_scale, obtained_y_scale);
	automove = obtained_automove;

	splited->clear();
	delete(splited);
}
