#include "Extentions.h"

vector<string>* split(string to_split) {
	auto* result = new vector<string>();

	auto* ss = new stringstream();

	for (int i = 0; i < to_split.length() + 1; i++) {
		if ((i == to_split.length() && ss->str().length() != 0) 
			|| (to_split[i] == ' ' && i != to_split.length())) {
			string current = ss->str();
			result->push_back(current);
			delete(ss);
			ss = new stringstream();
		}
		else {
			*ss << to_split[i];
		}
	}

	delete(ss);

	return result;
}