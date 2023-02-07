#include "Figure.h"
#include <SFML/Graphics.hpp>
#pragma once
using namespace sf;

class Star : public Figure
{
private:
	ConvexShape* star;
	float size;

protected:
	void draw(RenderWindow& window) override;

public:
	Star(float size, Color color);

	~Star();

	void move(float x, float y) override;

	FloatRect get_global_bounds() override;

	void set_scale(float x, float y) override;

	Vector2f get_scale() override;

	Vector2f get_position() override;

	bool check_intersection(Figure* figure) override;

	void hide() override;

	void show() override;

	void set_outline(float thickness, Color color) override;

	void set_color(Color color) override;

	Figure* get_copy() override;
};
