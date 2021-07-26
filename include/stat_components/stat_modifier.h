#pragma once
#include <string>
#include <variant>

class AbstractFeature;

class StatModifier {
public:
	friend bool operator==(const StatModifier& lhs, const StatModifier& rhs)
	{
		if (&lhs == &rhs) return true;
		else return false;
	}

	virtual float Value() { return _value; };
	StatModifier(float val, AbstractFeature* feature);

	AbstractFeature* feature;

protected:
	float _value;
};
