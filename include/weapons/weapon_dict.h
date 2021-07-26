#pragma once
#include <string>
#include <map>
#include <memory>
#include "weapon.h"
#include "mistsplitter.h"
#include "skyward_blade.h"

template<typename T> std::unique_ptr<GWeapon> createInstance(Player* player) { return std::make_unique<T>(player); }
typedef std::map<std::string, std::unique_ptr<GWeapon>(*)(Player* player)> weapon_map_type;

class WeaponDict
{
public:
    WeaponDict(const WeaponDict&) = delete;
    static WeaponDict& Get();
    weapon_map_type map = {};

private:
    WeaponDict();
};