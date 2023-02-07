#include "Star.h"

Star::Star(float size, Color color) {
    this->size = size;
    this->color = color;
    is_collided = false;
    star = new ConvexShape(size);
    star->setFillColor(color);
    star->setPointCount(10);
    star->setPoint(0, sf::Vector2f(60, 0));
    star->setPoint(1, sf::Vector2f(72, 40));
    star->setPoint(2, sf::Vector2f(110, 40));
    star->setPoint(3, sf::Vector2f(80, 60));
    star->setPoint(4, sf::Vector2f(100, 100));
    star->setPoint(5, sf::Vector2f(60, 75));
    star->setPoint(6, sf::Vector2f(20, 100));
    star->setPoint(7, sf::Vector2f(40, 60));
    star->setPoint(8, sf::Vector2f(10, 40));
    star->setPoint(9, sf::Vector2f(48, 40));
    set_scale(size / 100, size / 100);
}

Star::~Star() {
    delete(star);
}

void Star::move(float x, float y)
{
    star->move(x, y);
}

void Star::draw(RenderWindow& window) {
    update_window_collision(window);
    window.draw(*star);
}

FloatRect Star::get_global_bounds()
{
    return star->getGlobalBounds();
}

void Star::set_scale(float x, float y)
{
    if (x < 0.2)
        x = 0.2;

    if (y < 0.2)
        y = 0.2;

    star->setScale(x, y);
}

Vector2f Star::get_scale() {
    return star->getScale();
}

Vector2f Star::get_position()
{
    return star->getPosition();
}

bool Star::check_intersection(Figure* figure)
{
    return get_global_bounds().intersects(figure->get_global_bounds());
}

void Star::hide()
{
    star->setFillColor(Color(color.r, color.g, color.b, MIN_COLOR_VALUE));
}

void Star::show()
{
    star->setFillColor(Color(color.r, color.g, color.b, MAX_COLOR_VALUE));
}

void Star::set_outline(float thickness, Color color)
{
    star->setOutlineColor(color);
    star->setOutlineThickness(thickness);
}

void Star::set_color(Color color) {
    this->color = color;
    star->setFillColor(color);
}

Figure* Star::get_copy() {
    Star* res = new Star(size, color);

    return res;
}