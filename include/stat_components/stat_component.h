#pragma once
#include <string>
#include <iostream>

struct StatComponent {
	StatComponent();
	virtual ~StatComponent();
	StatComponent(float value);
	virtual float get_value();
protected:
	float _value = 0;
};
