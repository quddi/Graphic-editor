#include "IConvertable.h"
#include "Controller.h"
#include <string>
#include <iostream>
#include <fstream>
#pragma once
using namespace std;

class ControllerCaretaker {
private:
	string file_path;
	IConvertable* memento;

public:
	ControllerCaretaker(string _file_path, IConvertable* _memento);

	~ControllerCaretaker();

	void save();

	void load();
};