#include "ControllerCaretaker.h"
#include <iostream>
#include "Extentions.h"

ControllerCaretaker::ControllerCaretaker(string _file_path) {
	file_path = _file_path;
}

void ControllerCaretaker::save(IConvertable* memento) const
{
    ofstream file(file_path);

    if (file.is_open()) {
        file << memento->to_string() << endl;
    }
    else {
        throw new exception("failed to open the file");
    }

    file.close();
}

bool ControllerCaretaker::load(IConvertable* memento) const
{
    ifstream file(file_path);

    if (file.is_open()) {
	    string line;
	    getline(file, line);
        memento->from_string(split(line));
    }
    else {
        return false;
    }

    file.close();

    return true;
}
