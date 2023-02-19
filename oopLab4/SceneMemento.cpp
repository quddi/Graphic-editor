#include "SceneMemento.h"

SceneMemento::~SceneMemento() {
    for (int i = 0; i < saved_scene_figures.size(); i++) {
        delete(saved_scene_figures[i]);
    }

    saved_scene_figures.clear();
}

string SceneMemento::to_string() {
    stringstream ss;
    int size = saved_scene_figures.size();
    for (int i = 0; i < size; i++) {
        ss << saved_scene_figures[i]->to_string();

        if (size != i - 1) {
            ss << " ";
        }
    }
    return ss.str();
}

void SceneMemento::from_string(vector<string>* splited) {
    saved_scene_figures = *Composite::childen_from_string(splited);
}