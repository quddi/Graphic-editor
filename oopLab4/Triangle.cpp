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

	Vector2f current_pos = triangle->getPosition();
	res->move(current_pos.x, current_pos.y);

	return res;
}

string Triangle::to_string() {
	stringstream ss;

	ss << "Triangle" << " " << color.r << " " << color.g << " " << color.b << " ";
	ss << get_position().x << " " << get_position().y << " ";
	ss << get_scale().x << " " << get_scale().y << " ";
	ss << (automove ? 1 : 0);

	return ss.str();
}

void Triangle::from_string(string source) {
	vector<string> splited = split(source);

	if (splited.size() != 8 || splited[0] != "Triangle") {
		throw new exception("bad source");
	}

	Color obtained_color;
	float obtained_x_pos, obtained_y_pos, obtained_x_scale, obtained_y_scale;
	bool obtained_automove;

	try {
		obtained_color.r = stoi(splited[0]);
		obtained_color.g = stoi(splited[1]);
		obtained_color.b = stoi(splited[2]);

		obtained_x_pos = stoi(splited[3]);
		obtained_y_pos = stoi(splited[4]);
		obtained_x_scale = stoi(splited[5]);
		obtained_y_scale = stoi(splited[6]);

		if (splited[7] == "0") {
			obtained_automove = false;
		}
		else if (splited[7] == "1") {
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