#include "Composite.h"

Composite::Composite(Figure* fig) {
	if (fig == nullptr)
		throw new std::exception("Wrong argument");

	children.push_back(fig);
}

Composite::~Composite() {
	children.clear();
}

Composite* Composite::clone() {
	Composite* copy = new Composite(children[0]->get_copy());

	for (int i = 1; i < children.size(); i++)
		copy->add(children[i]->get_copy());

	return copy;
}

void Composite::draw(RenderWindow& window) {
	for (int i = 0; i < children.size(); i++)
		children[i]->update(window);
}

FloatRect Composite::get_global_bounds() {
	float min_x, min_y, max_x, max_y;

	FloatRect fr1 = children[0]->get_global_bounds();

	min_x = fr1.left;
	min_y = fr1.top;
	max_x = fr1.left + fr1.width;
	max_y = fr1.top + fr1.height;

	for (int i = 1; i < children.size(); i++) {
		float left_x, left_y, right_x, right_y;

		FloatRect fr = children[i]->get_global_bounds();

		left_x = fr.left;
		left_y = fr.top;
		right_x = fr.left + fr.width;
		right_y = fr.top + fr.height;

		if (min_x > left_x)
			min_x = left_x;

		if (min_y > left_y)
			min_y = left_y;

		if (max_x > right_x)
			max_x = right_x;

		if (max_y > right_x)
			max_y = right_x;
	}

	return FloatRect(min_x, min_y, max_x - min_x, max_y - min_y);
}

void Composite::set_scale(float x, float y) {
	for (int i = 0; i < children.size(); i++)
		children[i]->set_scale(x, y);
}

Vector2f Composite::get_scale() {
	return children[0]->get_scale();
}

Vector2f Composite::get_position() {
	if (children.size() == 0)
		throw new std::exception("Composite, get_position(), children.size() was 0");

	return children[0]->get_position();
}

bool Composite::check_intersection(Figure* figure) {
	for (int i = 0; i < children.size(); i++)
		if (children[i]->check_intersection(figure) == true)
			return true;

	return false;
}

void Composite::hide() {
	for (int i = 0; i < children.size(); i++)
		children[i]->hide();
}

void Composite::show() {
	for (int i = 0; i < children.size(); i++)
		children[i]->show();
}

void Composite::move(float x_delta, float y_delta) {
	for (int i = 0; i < children.size(); i++)
		children[i]->move(x_delta, y_delta);
}

void Composite::set_outline(float thickness, Color color) {
	for (int i = 0; i < children.size(); i++)
		children[i]->set_outline(thickness, color);
}

void Composite::set_color(Color color) {
	for (int i = 0; i < children.size(); i++)
		children[i]->set_color(color);
}

Figure* Composite::get_copy() {
	if (children.size() == 0)
		throw new std::exception("no children!");

	Composite* res = new Composite(children[0]->get_copy());

	for (int i = 1; i < children.size(); i++)
		res->add(children[i]->get_copy());

	res->color = color;

	return res;
}

void Composite::add(Figure* fig_to_add) {
	if (fig_to_add == nullptr)
		throw new std::exception;

	children.push_back(fig_to_add);
}

void Composite::set_collision(bool value) {
	for (int i = 0; i < children.size(); i++) {
		children[i]->set_collision(value);
	}
}
