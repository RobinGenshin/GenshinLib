#pragma once
#include <map>
#include <vector>
#include <string>
#include <memory>
#include "stat.h"

class AbstractFeature;
struct StatComponent;
class StatModifierGroup;
class Event;
class DamageData;
class Player;

class Component {
public:

	bool operator==(Component& other) {
		if (this == &other) return true;
		else return false;
	}

	Player* player;

	Component();
	Component(Player* player);
	virtual ~Component();

	std::map<std::string, std::unique_ptr<AbstractFeature>> features;
	std::vector<std::pair<Stat, std::shared_ptr<StatComponent>>> stats;
	std::map<std::string, std::unique_ptr<DamageData>> damage_data;

	virtual float get_stat(Stat);
	virtual float get_shared_stat(Stat);
	virtual float get_stat_component_stat(Stat);
	virtual float get_feature_stat(Stat);
};