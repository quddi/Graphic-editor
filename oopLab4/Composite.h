#include <vector>
#include <iostream>
#include <string>
#include <sstream>
#include "Figure.h"
#include "IConvertable.h"
#pragma once

class Composite : public Figure, public IConvertable
{
private:
	std::vector<Figure*> children;

public:
	Composite(Figure* fig);

	~Composite();

	Composite* clone();

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

	void from_string(string source) override;
};