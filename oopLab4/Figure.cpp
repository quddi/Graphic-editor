#include "Figure.h"

void Figure::update_window_collision(RenderWindow& window) {
	Vector2u left_down_edge = window.getSize();
	Vector2f current_pos = get_position();

	if (current_pos.x < 0)
		move(left_down_edge.x - current_pos.x, 0);

	if (current_pos.y < 0)
		move(0, left_down_edge.y - current_pos.y);

	if (current_pos.x > left_down_edge.x)
		move(-(float)left_down_edge.x, 0);

	if (current_pos.y > left_down_edge.y)
		move(0, -(float)left_down_edge.y);
}

void Figure::set_automove_mode(bool value) {
	automove = value;
}

void Figure::auto_move() {
	if (automove)
		move(1, 1);
}

void Figure::add(Figure* fig_to_add) {
}

void Figure::update(RenderWindow& window) {
	auto_move();

	if (is_collided == true) {
		float x_scale, y_scale;
		x_scale = get_scale().x;
		y_scale = get_scale().y;
		set_scale(DEFORMATED_COEFICIENT, DEFORMATED_COEFICIENT);
	}

	draw(window);
}

void Figure::set_collision(bool value) {
	is_collided = value;
}
