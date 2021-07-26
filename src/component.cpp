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
	auto it = std::find_if(stats.begin(), stats.end(), [statName](const std::pair<Stat, std::shared_ptr<StatComponent>>& element) { return element.first == statName; });
	if (it == stats.end()) return 0;
	else {
		float _value = 0;
		for (auto& i : stats) if (i.first == statName) _value += i.second.get()->get_value();
		return _value;
	}
};