#include "Controller.h"
#include "Figure.h"
#include "IConvertable.h"
#include <string>
#include <sstream>
#include <vector>
#pragma once
using namespace std;

class SceneMemento : public IConvertable {
	friend class Controller;

private:
	vector<Figure*> saved_scene_figures;

public:
	string to_string() override;

	void from_string(string source) override;
};