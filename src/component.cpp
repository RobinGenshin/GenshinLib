#include "component.h"
#include "stat_component.h"
#include "static_feature.h"
#include "dynamic_feature.h"
#include "damage_data.h"
#include "stat.h"

Component::Component(Player* _player) : player(_player), features(), stats(), damage_data() {};
Component::Component() : player(nullptr), features(), stats(), damage_data() {};
Component::~Component() {};

float Component::get_stat(Stat statName) {
	return get_stat_component_stat(statName) + get_feature_stat(statName);
};

float Component::get_shared_stat(Stat statName) {
	float _value = 0;
	for (auto& i : features) {
		if (i.second.get()->data.share) _value += dynamic_cast<FeatureStatModifierContainer*>(i.second.get())->get_stat(statName);
	};
	return _value;
};

float Component::get_stat_component_stat(Stat statName) {
	float _value = 0;
	for (auto& i : stats) if (i.first == statName) _value += i.second.get()->get_value();
	return _value;
};

float Component::get_feature_stat(Stat statName) {
	float _value = 0;
	for (auto& i : features) {
		if (i.second.get()->hasStatModifier) _value += dynamic_cast<FeatureStatModifierContainer*>(i.second.get())->get_stat(statName);
	};
	return _value;
};