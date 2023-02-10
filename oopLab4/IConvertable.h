#include <string>
#pragma once
using namespace std;

class IConvertable {
public:
	virtual string to_string() = 0;

	virtual void from_string(string source) = 0;
};