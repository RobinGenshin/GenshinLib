#include "weapon.h"

GWeapon::GWeapon() : Component() {};

GWeapon::GWeapon(const GWeapon& toCopy) : weapon_name(toCopy.weapon_name), weapon_class(toCopy.weapon_class), weapon_stat(toCopy.weapon_stat), base_stat_value(toCopy.base_stat_value), weapon_type(toCopy.weapon_type),
	weapon_level(90), weapon_rarity(toCopy.weapon_rarity), refinement(1) {};

GWeapon::GWeapon(Player* p, const GWeapon& toCopy) : Component(p), weapon_name(toCopy.weapon_name), weapon_class(toCopy.weapon_class), weapon_stat(toCopy.weapon_stat), base_stat_value(toCopy.base_stat_value), weapon_type(toCopy.weapon_type),
weapon_level(90), weapon_rarity(toCopy.weapon_rarity), refinement(1) {};

void GWeapon::BuildStats() {
	stats.emplace_back(std::make_pair(Stat::BASE_ATK, std::make_unique<WeaponBaseAtkStatComponent>(&weapon_level, &weapon_rarity, &weapon_class)));
	stats.emplace_back(std::make_pair(weapon_stat, std::make_unique<WeaponSubstatStatComponent>(&weapon_level, &base_stat_value)));
};