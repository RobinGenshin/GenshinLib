#pragma once
#include "component.h"
#include "weapon_base_atk_stat_component.h"
#include "weapon_secondary_stat_component.h"
#include <memory>
#include "weapon_type.h"

class GWeapon : public Component {
public:

	GWeapon();
	GWeapon(const GWeapon& toCopy);
	GWeapon(Player* p, const GWeapon& toCopy);

	std::string weapon_name;
	std::string weapon_class; // i.e. 44, 46, 48, 44b
	Stat weapon_stat;
	float base_stat_value;
	WeaponType weapon_type; // i.e. polearm, sword, etc
	int weapon_level;
	int weapon_rarity;
	int refinement;

	void BuildStats();
};