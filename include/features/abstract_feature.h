#pragma once
#include <string>
#include <vector>
#include <map>
#include "feature_data.h"

class Component;
class Player;
class Sim;
class AbstractEvent;

class AbstractFeature {
public:

	Player& get_player();
	virtual bool enabled();

	Component& component;
	const FeatureData data;

	AbstractFeature() = delete;
	AbstractFeature(Component& _component, FeatureData _data);

	bool isDynamic;
	bool hasStatModifier;
};