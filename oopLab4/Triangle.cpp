#include "Triangle.h"

Triangle::Triangle(float height, Color _color) {
	const int triangle_sides_count = 3;
	triangle = new CircleShape(height, triangle_sides_count);
	scale = Vector2f(1, 1);
	this->height = height;
	this->color = _color;
	is_collided = false;
	triangle->setFillColor(_color);
}

Triangle::~Triangle() {
	delete(triangle);
}

void Triangle::move(float x, float y) {
	triangle->move(x, y);
}

void Triangle::set_outline(float thickness, Color _color) {
	triangle->setOutlineColor(_color);
	triangle->setOutlineThickness(thickness);
}

void Triangle::set_color(Color _color) {
	this->color = _color;
	triangle->setFillColor(_color);
}

Figure* Triangle::get_copy() {
	auto* res = new Triangle(height, color);

	const Vector2f current_pos = triangle->getPosition();
	res->move(current_pos.x, current_pos.y);
	res->scale = Vector2f(scale.x, scale.y);
	res->automove = automove;

	return res;
}

string Triangle::to_string() {
	stringstream ss;

	ss << "Triangle" << " " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " ";
	ss << get_position().x << " " << get_position().y << " ";
	ss << scale.x << " " << scale.y << " ";
	ss << (automove ? 1 : 0);

	return ss.str();
}

void Triangle::from_string(vector<string>* splited) {
	if (splited->size() != 9 || (*splited)[0] != "Triangle") {
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
		throw new exception("Failed to load a triangle!");
	}

	color = obtained_color;
	move(obtained_x_pos, obtained_y_pos);
	set_scale(obtained_x_scale, obtained_y_scale);
	automove = obtained_automove;

	splited->clear();
	delete(splited);
}

void Triangle::draw(RenderWindow& window) {
	update_window_collision(window);
	window.draw(*triangle);
}

FloatRect Triangle::get_global_bounds() {
	return triangle->getGlobalBounds();
}

void Triangle::set_scale(float x, float y) {
	if (x < MIN_SCALE)
		x = MIN_SCALE;

	if (y < MIN_SCALE)
		y = MIN_SCALE;

	scale = Vector2f(x, y);
	triangle->setScale(x, y);
}

Vector2f Triangle::get_scale() {
	return scale;
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