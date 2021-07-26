#include "weapon_dict.h"

WeaponDict& WeaponDict::Get() {
    static WeaponDict instance;
    return instance;
};

WeaponDict::WeaponDict() {
    map["Mistsplitter Reforged"] = &createInstance<Mistsplitter>;
    map["Skyward Blade"] = &createInstance<SkywardBlade>;
};