#include "Line.h"

Line::Line(float _length, Color _color) {
	this->length = _length;
	this->color = _color;
	is_collided = false;
	scale = Vector2f(1, 1);
	line = new RectangleShape(scale);
	line->setFillColor(_color);
}

Line::~Line() {
	delete(line);
}

FloatRect Line::get_global_bounds() {
	return line->getGlobalBounds();
}

void Line::set_scale(float x, float y) {
	if (x < MIN_SCALE)
		x = MIN_SCALE;

	scale = Vector2f(x,  width);
	line->setScale(x, width);
}

Vector2f Line::get_scale() {
	return scale;
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

void Line::set_outline(float thickness, Color _color) {
	line->setOutlineColor(_color);
	line->setOutlineThickness(thickness);
}

void Line::set_color(Color _color) {
	this->color = _color;
	line->setFillColor(_color);
}

Figure* Line::get_copy() {
	Line* res = new Line(length, color);

	const Vector2f current_pos = line->getPosition();
	res->move(current_pos.x, current_pos.y);
	res->scale = Vector2f(scale.x, scale.y);
	res->automove = automove;

	return res;
}

string Line::to_string() {
	stringstream ss;

	ss << "Line" << " " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " ";
	ss << get_position().x << " " << get_position().y << " ";
	ss << scale.x << " " << scale.y << " ";
	ss << (automove ? 1 : 0);

	return ss.str();
}

void Line::from_string(vector<string>* splited) {
	if (splited->size() != 9 || (*splited)[0] != "Line") {
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
		throw new exception("Failed to load a line!");
	}

	color = obtained_color;
	move(obtained_x_pos, obtained_y_pos);
	set_scale(obtained_x_scale, obtained_y_scale);
	automove = obtained_automove;

	splited->clear();
	delete(splited);
}

void Line::draw(RenderWindow& window) {
	update_window_collision(window);
	window.draw(*line);
}

