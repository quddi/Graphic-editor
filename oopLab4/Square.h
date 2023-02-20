#include "Figure.h"
#include "Extentions.h"
#include <SFML/Graphics.hpp>
#pragma once
using namespace sf;

class Square : public Figure
{
private:
	RectangleShape* square;
	float side;

protected:
	void draw(RenderWindow& window) override;

public:
	Square(float side, Color color);

	~Square();

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

	string to_string() override;

	void from_string(vector<string>* splited) override;
};