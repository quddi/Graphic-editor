#pragma once

class IPrototype {
public:
	virtual IPrototype* get_copy() = 0;
};