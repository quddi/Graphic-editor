#include "Extentions.h"

vector<string> split(string to_split) {
	vector<string> result;

	stringstream* ss = new stringstream();

	for (int i = 0; i < to_split.length(); i++) {
		if (to_split[i] == ' ') {
			result.push_back(ss->str());
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