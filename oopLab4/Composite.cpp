#include "Composite.h"

Composite::Composite(Figure* fig) {
	if (fig == nullptr)
		throw new std::exception("Wrong argument");

	scale = Vector2f(1, 1);
	children.push_back(fig);
}

Composite::Composite() = default;

Composite::~Composite() {
	for (int i = 0; i < children.size(); i++) {
		delete(children[i]);
	}

	children.clear();
}

Composite* Composite::clone() const
{
	Composite* copy = new Composite((Figure*)children[0]->get_copy());

	for (int i = 1; i < children.size(); i++)
		copy->add((Figure*)children[i]->get_copy());

	return copy;
}

void Composite::draw(RenderWindow& window) {
	for (int i = 0; i < children.size(); i++)
		children[i]->update(window);
}

FloatRect Composite::get_global_bounds() {
	float min_x, min_y, max_x, max_y;

	FloatRect float_rect = children[0]->get_global_bounds();

	min_x = float_rect.left;
	min_y = float_rect.top;
	max_x = float_rect.left + float_rect.width;
	max_y = float_rect.top + float_rect.height;

	for (int i = 1; i < children.size(); i++) {
		float left_x, left_y, right_x, right_y;

		FloatRect current_float_rect = children[i]->get_global_bounds();

		left_x = current_float_rect.left;
		left_y = current_float_rect.top;
		right_x = current_float_rect.left + current_float_rect.width;
		right_y = current_float_rect.top + current_float_rect.height;

		if (min_x > left_x)
			min_x = left_x;

		if (min_y > left_y)
			min_y = left_y;

		if (max_x > right_x)
			max_x = right_x;

		if (max_y > right_y)
			max_y = right_y;
	}

	return FloatRect(min_x, min_y, 
		max_x - min_x, max_y - min_y);
}

void Composite::set_scale(float x, float y) {
	for (int i = 0; i < children.size(); i++)
		children[i]->set_scale(x, y);

	scale = Vector2f(x, y);
}

Vector2f Composite::get_scale() {
	return scale;
}

Vector2f Composite::get_position() {
	if (children.empty())
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

void Composite::set_outline(float thickness, Color _color) {
	for (int i = 0; i < children.size(); i++)
		children[i]->set_outline(thickness, _color);
}

void Composite::set_color(Color _color) {
	for (int i = 0; i < children.size(); i++)
		children[i]->set_color(_color);
}

Figure* Composite::get_copy() {
	if (children.empty())
		throw new std::exception("no children!");

	Composite* res = new Composite((Figure*)children[0]->get_copy());

	for (int i = 1; i < children.size(); i++)
		res->add((Figure*)children[i]->get_copy());

	res->color = color;
	res->scale = Vector2f(scale.x, scale.y);
	res->automove = automove;

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

string Composite::to_string() {
	stringstream ss;

	ss << "Composite" << " " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " ";
	ss << get_position().x << " " << get_position().y << " ";
	ss << get_scale().x << " " << get_scale().y << " ";
	ss << (automove ? 1 : 0) << " ( ";

	for (int i = 0; i < children.size(); i++) {
		ss << children[i]->to_string() << " ";
	}

	ss << ")";

	return ss.str();
}

void Composite::from_string(vector<string>* splited) {
	if ((*splited)[0] != "Composite") {
		throw new exception("failed to load a composite");
	}

	float obtained_x_scale, obtained_y_scale;
	bool obtained_automove;

	try {
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

	if ((*splited)[9] != '(') {
		throw new exception("failed to load a composite");
	}

	int brackets_count = 1;
	auto* childern_in_string = new vector<string>();

	for (int i = 10; i < splited->size(); i++) {
		if ((*splited)[i] == ')') {
			brackets_count--;
		}

		if (brackets_count == 0) {
			break;
		}

		if ((*splited)[i] == '(') {
			brackets_count++;
		}

		childern_in_string->push_back((*splited)[i]);
	}

	children = *childen_from_string(childern_in_string);
	set_scale(obtained_x_scale, obtained_y_scale);
	set_automove_mode(obtained_automove);

	childern_in_string->clear();

	splited->clear();

	delete(splited);
}

vector<Figure*>* Composite::childen_from_string(vector<string>* source) {
	auto* result = new vector<Figure*>();

	for (int j = 0; j < source->size();) {
		Figure* figure = nullptr;
		auto* params = new vector<string>();
		int increment = 0;

		for (int i = 0; i < PARAMETERS_COUNT; i++) {
			params->push_back((*source)[j + i]);
		}

		if ((*source)[j] != "Composite") {
			increment = PARAMETERS_COUNT;
		}
		else {
			int brackets_count = 0;

			for (int i = PARAMETERS_COUNT; ; i++) {
				string current = (*source)[j + i];
				params->push_back(current);

				if (current == "(") {
					brackets_count++;
				}

				if (current == ")") {
					brackets_count--;
				}

				if (brackets_count == 0) {
					increment = i + 1;
					break;
				}
			}
		}

		if ((*source)[j] == "Composite") {
			figure = new Composite();
		}
		else if ((*source)[j] == "Circle") {
			figure = new Circle(DEFAULT_SIZE, DEFAULT_COLOR);
		}
		else if ((*source)[j] == "Line") {
			figure = new Line(DEFAULT_SIZE, DEFAULT_COLOR);
		}
		else if ((*source)[j] == "Square") {
			figure = new Square(DEFAULT_SIZE, DEFAULT_COLOR);
		}
		else if ((*source)[j] == "Star") {
			figure = new Star(DEFAULT_SIZE, DEFAULT_COLOR);
		}
		else if ((*source)[j] == "Triangle") {
			figure = new Triangle(DEFAULT_SIZE, DEFAULT_COLOR);
		}

		figure->from_string(params);

		result->push_back(figure);

		params->clear();

		j += increment;
	}

	source->clear();
	delete(source);

	return result;
}