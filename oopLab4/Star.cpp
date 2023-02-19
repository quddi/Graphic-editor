#include "Star.h"

Star::Star(float _size, Color _color) {
    const int size_modifier = 8;
    _size /= size_modifier;

    this->size = _size;
    this->color = _color;
    is_collided = false;
    star = new ConvexShape(_size);
    star->setFillColor(_color);
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
    set_scale(_size, _size);
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
    if (x < MIN_SCALE)
        x = MIN_SCALE;

    if (y < MIN_SCALE)
        y = MIN_SCALE;

    scale = Vector2f(x, y);
    star->setScale(x, y);
}

Vector2f Star::get_scale() {
    return scale;
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

void Star::set_outline(float thickness, Color _color)
{
    star->setOutlineColor(_color);
    star->setOutlineThickness(thickness);
}

void Star::set_color(Color _color) {
    this->color = _color;
    star->setFillColor(_color);
}

Figure* Star::get_copy() {
    Star* res = new Star(size, color);

    const Vector2f current_pos = star->getPosition();
    res->move(current_pos.x, current_pos.y);
    res->scale = Vector2f(scale.x, scale.y);
    res->automove = automove;

    return res;
}

string Star::to_string() {
    stringstream ss;

    ss << "Star" << " " << (int)color.r << " " << (int)color.g << " " << (int)color.b << " ";
    ss << get_position().x << " " << get_position().y << " ";
    ss << scale.x << " " << scale.y << " ";
    ss << (automove ? 1 : 0);

    return ss.str();
}

void Star::from_string(vector<string>* splited) {
    if (splited->size() != 9 || (*splited)[0] != "Star") {
        throw new exception("bad source");
    }

    Color obtained_color;
    float obtained_x_pos, obtained_y_pos, obtained_x_scale, obtained_y_scale;
    bool obtained_automove;

    try {
        obtained_color.r = stoi((*splited)[1]);
        obtained_color.g = stoi((*splited)[2]);
        obtained_color.b = stoi((*splited)[3]);

        obtained_x_pos = stoi((*splited)[4]);
        obtained_y_pos = stoi((*splited)[5]);
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
        throw new exception("Failed to load a star!");
    }

    color = obtained_color;
    move(obtained_x_pos, obtained_y_pos);
    set_scale(obtained_x_scale, obtained_y_scale);
    automove = obtained_automove;

    splited->clear();
    delete(splited);
}
