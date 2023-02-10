#include "Controller.h"

Controller::Controller() {
    context_settings = new ContextSettings();
    context_settings->antialiasingLevel = 8;
    render_window = new RenderWindow(VideoMode(1920, 960), "SFMLworks", 
        Style::Default, *context_settings);

    this->trail = false;
    this->collision_deformation = false;

    load_background();

    fill_prefabs();
}

Controller::~Controller() {
    scene_figures.clear();
    figure_prefabs.clear();
    delete(render_window);
    delete(context_settings);
    delete(background_texture);
    delete(background);
}

Controller* Controller::get_instance() {
    if (instance == nullptr) {
        instance = new Controller();
    }

    return instance;
}

void Controller::start_demonstration() {
    Keyboard keyboard;

    while (render_window->isOpen())
    {
        Event _event;
        while (render_window->pollEvent(_event))
        {
            if (_event.type == Event::Closed)
                render_window->close();
        }

        check_pressed_key(keyboard);

        update(*render_window);
    }
}

void Controller::fill_prefabs() {
    figure_prefabs.push_back(new Composite(new Circle(default_size, default_color)));
    figure_prefabs.push_back(new Composite(new Line(default_size, default_color)));
    figure_prefabs.push_back(new Composite(new Square(default_size, default_color)));
    figure_prefabs.push_back(new Composite(new Star(default_size, default_color)));
    figure_prefabs.push_back(new Composite(new Triangle(default_size, default_color)));
}

void Controller::move(int x, int y) {
    if (scene_figures.size() == 0)
        return;

    scene_figures[active_figure_index]->move(x, y);
}

void Controller::update(RenderWindow& window) {
    if (trail == false)
        window.clear();

    if (background != nullptr && trail == false)
        window.draw(*background);

    for (int i = 0; i < scene_figures.size(); i++)
        scene_figures[i]->update(window);

    if (collision_deformation == true && trail == false)
        check_collision();

    window.display();
}

void Controller::load_background() {
    background_texture = new Texture();
    background_texture->loadFromFile(background_image_path);

    background = new Sprite(*background_texture);
}

void Controller::activate_new_figure(int new_index) {
    if (new_index + 1 > scene_figures.size() || new_index > 9)
        return;

    hide_all();

    scene_figures[new_index]->show();

    active_figure_index = new_index;
}

void Controller::add_figure() {
    cout << "Choose figure to add:" << endl;
    cout << "1. Circle" << endl;
    cout << "2. Line" << endl;
    cout << "3. Square" << endl;
    cout << "4. Star" << endl;
    cout << "5. Triangle" << endl;
    cout << "6. Copy of the selected figure" << endl;

    if (scene_figures.size() == 10) {
        cout << "The scene can not contain more than 10 figures." << endl;
        cout << "Delete one figure and try again" << endl;
        return;
    }

    try {
        int input;
        cin >> input;

        if (0 >= input || input >= 7) {
            cout << "Bad input! Try again." << endl;
            return;
        }

        if (input == 6) {
            if (scene_figures.size() == 0) {
                cout << "The scene does not contain any figures" << endl;
                return;
            }

            scene_figures.push_back((Figure*)scene_figures[active_figure_index]->get_copy());
        }
        else {
            scene_figures.push_back((Figure*)figure_prefabs[input - 1]->get_copy());
            scene_figures[scene_figures.size() - 1]->set_color(*(get_random_color()));
        }

        activate_new_figure(scene_figures.size() - 1);
    }
    catch (exception ex) {
        cout << "Bad input! Try again." << endl;
    }
}

Color* Controller::get_random_color() {
    int r, g, b;
    r = rand() % (MAX_COLOR_VALUE - MIN_RANDOM_COLOR_VALUE) + MIN_RANDOM_COLOR_VALUE;
    g = rand() % (MAX_COLOR_VALUE - MIN_RANDOM_COLOR_VALUE) + MIN_RANDOM_COLOR_VALUE;
    b = rand() % (MAX_COLOR_VALUE - MIN_RANDOM_COLOR_VALUE) + MIN_RANDOM_COLOR_VALUE;
    return new Color(r, g, b);
}

void Controller::check_pressed_key(Keyboard& keyboard) {
    if (keyboard.isKeyPressed(keyboard.A))
        move(-1, 0);

    if (keyboard.isKeyPressed(keyboard.W))
        move(0, -1);

    if (keyboard.isKeyPressed(keyboard.D))
        move(1, 0);

    if (keyboard.isKeyPressed(keyboard.S))
        move(0, 1);

    if (keyboard.isKeyPressed(keyboard.I))
        add_figure();

    if (keyboard.isKeyPressed(keyboard.C))
        add_selected_to_composite();

    if (keyboard.isKeyPressed(keyboard.V))
        select_color();

    if (keyboard.isKeyPressed(keyboard.RBracket))
        active_figure_to_fronter_layer();

    if (keyboard.isKeyPressed(keyboard.E))
        cout << "Debug" << endl;

    if (keyboard.isKeyPressed(keyboard.H))
        set_active_figure_scale();

    if (keyboard.isKeyPressed(keyboard.O))
        hide_active();

    if (keyboard.isKeyPressed(keyboard.P))
        show_active();

    if (keyboard.isKeyPressed(keyboard.T))
        set_active_figure_automove_mode(true);

    if (keyboard.isKeyPressed(keyboard.Y))
        set_active_figure_automove_mode(false);

    if (keyboard.isKeyPressed(keyboard.R))
        delete_active_figure();

    if (keyboard.isKeyPressed(keyboard.M))
        show_all();

    if (keyboard.isKeyPressed(keyboard.B))
        set_trail(true);

    if (keyboard.isKeyPressed(keyboard.N))
        set_trail(false);

    if (keyboard.isKeyPressed(keyboard.F))
        set_collision_deformation(true);

    if (keyboard.isKeyPressed(keyboard.G))
        set_collision_deformation(false);

#pragma region NumKeys
    if (keyboard.isKeyPressed(keyboard.Num0))
        activate_new_figure(0);

    if (keyboard.isKeyPressed(keyboard.Num1))
        activate_new_figure(1);

    if (keyboard.isKeyPressed(keyboard.Num2))
        activate_new_figure(2);

    if (keyboard.isKeyPressed(keyboard.Num3))
        activate_new_figure(3);

    if (keyboard.isKeyPressed(keyboard.Num4))
        activate_new_figure(4);

    if (keyboard.isKeyPressed(keyboard.Num5))
        activate_new_figure(5);

    if (keyboard.isKeyPressed(keyboard.Num6))
        activate_new_figure(6);

    if (keyboard.isKeyPressed(keyboard.Num7))
        activate_new_figure(7);

    if (keyboard.isKeyPressed(keyboard.Num8))
        activate_new_figure(8);

    if (keyboard.isKeyPressed(keyboard.Num9))
        activate_new_figure(9);
#pragma endregion
}

void Controller::add_selected_to_composite() {
    cout << "Input index of figure, into which you want to add the selected figure." << endl;
    cout << "(Must be between 0 and 9, and not to be equal to selected index (" << active_figure_index << "))" << endl;

    try {
        int input;
        cin >> input;

        if (input >= scene_figures.size() || input < -1 || input == active_figure_index) {
            cout << "Bad input! Try again!" << endl;
            return;
        }

        scene_figures[input]->add(scene_figures[active_figure_index]);
        scene_figures.erase(scene_figures.begin() + active_figure_index);
        activate_new_figure(input);
    }
    catch (exception ex) {
        cout << "Bad input! Try again!" << endl;
        return;
    }
}

void Controller::select_color() {
    if (scene_figures.size() == 0)
        return;

    cout << "Input 3 values, devided by space - RGB color components ([0; 255]):" << endl;
    int r, g, b;

    try {
        cin >> r;
        cin >> g;
        cin >> b;

        if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
            cout << "Bad input! Try again!" << endl;
    }
    catch (exception ex) {
        cout << "Bad input! Try again!" << endl;
    }

    Color* new_color = new Color(r, g, b);
    scene_figures[active_figure_index]->set_color(*new_color);
}

void Controller::set_active_figure_scale() {
    if (scene_figures.size() == 0)
        return;

    cout << "Input two numbers - x and y scale factors." << endl;
    cout << "Example: 3.1 10" << endl;
    float x, y;
    cin >> x;
    cin >> y;
    scene_figures[active_figure_index]->set_scale(x, y);
}

void Controller::active_figure_to_fronter_layer() {
    if (active_figure_index + 1 == scene_figures.size())
        return;

    Figure* x = scene_figures[active_figure_index];
    scene_figures.erase(scene_figures.begin() + active_figure_index);
    scene_figures.push_back(x);
    activate_new_figure(scene_figures.size() - 1);
}

void Controller::hide_active() {
    if (scene_figures.size() != 0)
        scene_figures[active_figure_index]->hide();
}

void Controller::show_active() {
    if (scene_figures.size() != 0)
        scene_figures[active_figure_index]->show();
}

void Controller::set_active_figure_automove_mode(bool value) {
    if (scene_figures.size() != 0)
        scene_figures[active_figure_index]->set_automove_mode(value);
}

void Controller::delete_active_figure() {
    if (scene_figures.size() == 0)
        return;

    char input;
    cout << "Are you sure you want to delete the active figure? Unput \"+\" if yes, something other otherwise: ";
    cin >> input;

    if (input == '+') {
        Figure* to_delete = scene_figures[active_figure_index];
        scene_figures.erase(scene_figures.begin() + active_figure_index);
        delete(to_delete);
        activate_new_figure(0);
        cout << "Deleted!" << endl;
    }
    else {
        cout << "Deleting canceled." << endl;
    }
}

void Controller::show_all() {
    for (int i = 0; i < scene_figures.size(); i++)
        scene_figures[i]->show();
}

void Controller::hide_all() {
    for (int i = 0; i < scene_figures.size(); i++)
        scene_figures[i]->hide();
}

void Controller::set_trail(bool value) {
    trail = value;
}

void Controller::check_collision() {
    for (int i = 0; i < scene_figures.size(); i++) {
        if (i == active_figure_index)
            continue;

        bool intersected = scene_figures[active_figure_index]->check_intersection(scene_figures[i]);

        scene_figures[i]->set_collision(intersected);
    }
}

void Controller::set_collision_deformation(bool value) {
    collision_deformation = value;
}