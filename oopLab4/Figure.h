#include <vector>
#include <iostream>
#include <string>
#include <SFML/Graphics.hpp>
#include "IConvertable.h"
#include "IPrototype.h"
#pragma once
using namespace sf;

const Color DEFAULT_COLOR = Color::Yellow;
const float DEFAULT_SIZE = 100;
const float MIN_SCALE = 0.2;


class Figure : public IPrototype, public IConvertable {
protected:
	Color color;
	bool automove;
	bool is_collided;
	Vector2f scale;

	void auto_move();
	virtual void draw(RenderWindow& window) = 0;

public:
	virtual FloatRect get_global_bounds() = 0;
	virtual void set_scale(float x, float y) = 0;
	virtual Vector2f get_scale() = 0;
	virtual Vector2f get_position() = 0;
	virtual bool check_intersection(Figure* figure) = 0;
	virtual void hide() = 0;
	virtual void show() = 0;
	virtual void move(float x, float y) = 0;
	virtual void set_outline(float thickness, Color color) = 0;
	virtual void set_color(Color color) = 0;
	virtual void add(Figure* fig_to_add);
	virtual void set_collision(bool value);
	void update_window_collision(RenderWindow& window);
	void set_automove_mode(bool value);
	void update(RenderWindow& window);
};

const int MAX_COLOR_VALUE = 255;
const int MIN_COLOR_VALUE = 0;

const float DEFORMATED_COEFICIENT = 0.7f;
const float NORMAL_COEFICIENT = 1.0f;