#include <SFML/Graphics.hpp>
#include "Figure.h"
#pragma once
using namespace sf;

class Triangle : public Figure
{
private:
	CircleShape* triangle;
	float height;

protected:
	void draw(RenderWindow& window) override;

public:
	Triangle(float height, Color color);

	~Triangle();

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
};
