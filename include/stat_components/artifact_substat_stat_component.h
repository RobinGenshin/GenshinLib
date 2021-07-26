#pragma once
#include "stat_component.h"
#include <map>
#include <string>
#include <vector>
#include "stat.h"

class ArtifactSubstatComponent : public StatComponent {
public:
	Stat stat_type;
	ArtifactSubstatComponent(Stat stat);
	virtual float get_value() override;
	void set_amount(int a);;

	std::map<Stat, float> statMultiplierMap = {
	{Stat::PCT_ATK, 6.0f}, {Stat::PCT_HP, 6.0f}, {Stat::PCT_DEF, 7.5f},
	{Stat::CRIT_RATE, 4.0f}, {Stat::CRIT_DMG, 8.0f},
	{Stat::ELEMENTAL_MASTERY, 2400.0f}, {Stat::ENERGY_RECHARGE, 6.0f * (11 / 10)}
	};

private:
	int amount;
	bool amount_changed = true;
	float statMap();
};
