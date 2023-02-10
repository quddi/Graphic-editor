#include "ControllerCaretaker.h"

ControllerCaretaker::ControllerCaretaker(string _file_path, IConvertable* _memento) {
	file_path = _file_path;
    memento = _memento;
}

ControllerCaretaker::~ControllerCaretaker() {
    delete(memento);
}

void ControllerCaretaker::save() {
    ofstream file(file_path);

    if (file.is_open()) {
        file << memento->to_string() << endl;
    }
    else {
        throw new exception("failed to open the file");
    }

    file.close();
}

void ControllerCaretaker::load() {
    ifstream file(file_path);

    string line;

    if (file.is_open()) {
        getline(file, line);
        memento->from_string(line);
    }
    else {
        throw new exception("failed to open the file");
    }

    file.close();
}
