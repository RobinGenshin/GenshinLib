#pragma once
#include "component.h"
#include "stat.h"

class Artifact : public Component {
public:
	Artifact(Player& p);

	Stat* flowerMain;
	Stat* plumeMain;
	Stat* sandsMain;
	Stat* gobletMain;
	Stat* circletMain;
	std::vector<Stat*> main_stats = { flowerMain, plumeMain, sandsMain, gobletMain, circletMain };

	std::map<Stat, float> mainStatMap {
		{Stat::FLAT_HP, 4780.0f},
		{Stat::FLAT_ATK, 311.0f},
		{Stat::PCT_ATK, 0.466f},
		{Stat::PCT_DEF, 0.583f},
		{Stat::PCT_HP, 0.466f},
		{Stat::CRIT_RATE, 0.311f},
		{Stat::CRIT_DMG, 0.622f},
		{Stat::ELEMENTAL_MASTERY, 187.0f},
		{Stat::ENERGY_RECHARGE, 0.518f},
		{Stat::ANEMO_DMG, 0.466f},
		{Stat::CRYO_DMG, 0.466f},
		{Stat::ELECTRO_DMG, 0.466f},
		{Stat::GEO_DMG, 0.466f},
		{Stat::HYDRO_DMG, 0.466f},
		{Stat::PYRO_DMG, 0.466f},
		{Stat::PHYSICAL_DMG, 0.583f}
	};
	virtual float get_stat(Stat);
};