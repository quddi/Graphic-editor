#include <string>
#include <vector>
#pragma once
using namespace std;

const int PARAMETERS_COUNT = 9;

class IConvertable {
public:
	virtual string to_string() = 0;

	virtual void from_string(vector<string>* splited) = 0;
};