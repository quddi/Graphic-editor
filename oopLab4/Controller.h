#pragma once
#include <iostream>
#include <typeinfo>
#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include "Figure.h"
#include "Composite.h"
#include "Circle.h"
#include "Square.h"
#include "Triangle.h"
#include "Star.h"
#include "Line.h"
using namespace std;
using namespace sf;

const string background_image_path = "Background.png";

const int MIN_RANDOM_COLOR_VALUE = 50;

class Controller
{
private:
    static Controller* instance;

    vector<Figure*> scene_figures;
    vector<Figure*> figure_prefabs;

    RenderWindow* render_window;
    ContextSettings* context_settings;

    Texture* background_texture;
    Sprite* background;

    const Color default_color = Color::Yellow;
    const float default_size = 100;

    int active_figure_index;

    bool trail;
    bool collision_deformation;

    void fill_prefabs();

    void move(int x, int y);

    void update(RenderWindow& window);

    void load_background();

    void activate_new_figure(int new_index);

    void add_figure();

    Color* get_random_color();

    void check_pressed_key(Keyboard& keyboard);

    void add_selected_to_composite();

    void select_color();

    void set_active_figure_scale();

    void active_figure_to_fronter_layer();

    void hide_active();

    void show_active();

    void set_active_figure_automove_mode(bool value);

    void delete_active_figure();

    void show_all();

    void hide_all();

    void set_trail(bool value);

    void check_collision();

    void set_collision_deformation(bool value);

    Controller();
public:
    Controller(const Controller&) = delete;
    void operator = (const Controller&) = delete;

    ~Controller();

    static Controller* get_instance();

    void start_demonstration();
};

