#include "IConvertable.h"
#include "Extentions.h"
#include <string>
#include <iostream>
#include <fstream>
#pragma once
using namespace std;

class ControllerCaretaker {
private:
	string file_path;

public:
	ControllerCaretaker(string _file_path);

	void save(IConvertable* memento) const;

	bool load(IConvertable* memento) const;
};