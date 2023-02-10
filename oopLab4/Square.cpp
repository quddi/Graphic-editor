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

	Vector2f current_pos = square->getPosition();
	res->move(current_pos.x, current_pos.y);

	return res;
}

string Square::to_string() {
	stringstream ss;

	ss << "Square" << " " << color.r << " " << color.g << " " << color.b << " ";
	ss << get_position().x << " " << get_position().y << " ";
	ss << get_scale().x << " " << get_scale().y << " ";
	ss << (automove ? 1 : 0);

	return ss.str();
}

void Square::from_string(string source) {
	vector<string> splited = split(source);

	if (splited.size() != 8 || splited[0] != "Square") {
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