#pragma once
#include <vector>
#include <map>
#include "element.h"
#include <memory>

class Sim;
class DamageEvent;
enum class TransformativeReaction;

class ElementalGauge {
public:
	bool operator==(ElementalGauge& other) {
		if (this == &other) return true;
		else return false;
	}


	ElementalGauge() = default;
	ElementalGauge(Element element, int units, bool aura);

	Element element;
	float time_remaining;
	float decay_rate;

	virtual float get_gauge();
	virtual void set_gauge(float g);
	virtual void PassTime(float dt);
	virtual void SubtractFromGauge(float dg);
	virtual void AddToGauge(float unit, bool aura = false);

private:
	float gauge;
};