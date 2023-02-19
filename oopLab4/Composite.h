#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "Figure.h"
#include "Circle.h"
#include "Line.h"
#include "Square.h"
#include "Star.h"
#include "Triangle.h"
#include "IConvertable.h"
#include "Extentions.h"
#pragma once

class Composite : public Figure
{
private:
	std::vector<Figure*> children;

	Composite();

public:
	static vector<Figure*>* childen_from_string(vector<string>* source);

	Composite(Figure* fig);

	~Composite();

	Composite* clone() const;

	void draw(RenderWindow& window) override;

	FloatRect get_global_bounds() override;

	void set_scale(float x, float y) override;

	Vector2f get_scale() override;

	Vector2f get_position() override;

	bool check_intersection(Figure* figure) override;

	void hide() override;

	void show() override;

	void move(float x, float y) override;

	void set_outline(float thickness, Color color) override;

	void set_color(Color color) override;

	Figure* get_copy() override;

	void add(Figure* fig_to_add) override;

	void set_collision(bool value) override;

	string to_string() override;

	void from_string(vector<string>* splited) override;
};