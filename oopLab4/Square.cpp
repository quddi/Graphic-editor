#include "Square.h"

Square::Square(float side, Color _color) {
	scale = Vector2f(1, 1);
	square = new RectangleShape(scale * side);
	this->color = _color;
	this->side = side;
	is_collided = false;
	square->setFillColor(_color);
}

Square::~Square() {
	delete(square);
}

void Square::move(float x, float y) {
	square->move(x, y);
}

void Square::set_outline(float thickness, Color _color) {
	square->setOutlineColor(_color);
	square->setOutlineThickness(thickness);
}

void Square::set_color(Color _color) {
	this->color = _color;
	square->setFillColor(_color);
}

Figure* Square::get_copy()
{
	const auto res = new Square(side, color);

	const Vector2f current_pos = square->getPosition();
	res->move(current_pos.x, current_pos.y);
	res->scale = Vector2f(scale.x, scale.y);
	res->automove = automove;

	return res;
}

string Square::to_string() {
	stringstream ss;

	ss << "Square" << " " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " ";
	ss << get_position().x << " " << get_position().y << " ";
	ss << scale.x << " " << scale.y << " ";

	if (automove == true) {
		ss << "1";
	}
	else {
		ss << "0";
	}

	return ss.str();
}

void Square::from_string(vector<string>* splited) {
	if (splited->size() != 9 || (*splited)[0] != "Square") {
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
		throw new exception("Failed to load a square!");
	}

	color = obtained_color;
	move(obtained_x_pos, obtained_y_pos);
	set_scale(obtained_x_scale, obtained_y_scale);
	automove = obtained_automove;
}

void Square::draw(RenderWindow& window) {
	update_window_collision(window);
	window.draw(*square);
}

FloatRect Square::get_global_bounds() {
	return square->getGlobalBounds();
}

void Square::set_scale(float x, float y) {
	if (x < MIN_SCALE)
		x = MIN_SCALE;

	if (y < MIN_SCALE)
		y = MIN_SCALE;

	scale = Vector2f(x, y);
	square->setScale(x, y);
}

Vector2f Square::get_scale() {
	return scale;
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