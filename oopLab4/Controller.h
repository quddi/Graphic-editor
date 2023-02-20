#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include <random>
#include "Figure.h"
#include "ControllerCaretaker.h"
using namespace std;
using namespace sf;

const string BACKGROUND_IMAGE_PATH = "Background.png";
const string SAVE_FILE_PATH = "Save.txt";

constexpr int MIN_RANDOM_COLOR_VALUE = 50;
constexpr int ANTIALIASING_LEVEL = 8;

constexpr int SCREEN_WIDTH = 1920;
constexpr int SCREEN_HEIGHT = 960;

class Controller
{
private:
    static Controller* instance;

    ControllerCaretaker* caretaker;

    vector<Figure*> scene_figures;
    vector<Figure*> figure_prefabs;

    RenderWindow* render_window;
    ContextSettings* context_settings;

    Texture* background_texture;
    Sprite* background;

    int active_figure_index;

    bool trail;
    bool collision_deformation;

    void fill_prefabs();

    void move(int x, int y);

    void update(RenderWindow& window);

    void load_background();

    void activate_new_figure(int new_index);

    void add_figure();

    static Color* get_random_color();

    void check_pressed_key(Keyboard& keyboard);

    void add_selected_to_composite();

    void select_color();

    void set_active_figure_scale();

    void active_figure_to_frontier_layer();

    void hide_active();

    void show_active();

    void set_active_figure_automove_mode(bool value);

    void delete_active_figure();

    void show_all();

    void hide_all();

    void set_trail(bool value);

    void check_collision();

    void set_collision_deformation(bool value);

    void save_scene() const;

    void load_scene();

    Controller();
public:
    Controller(const Controller&) = delete;
    void operator = (const Controller&) = delete;

    ~Controller();

    static Controller* get_instance();

    void start_demonstration();
};

