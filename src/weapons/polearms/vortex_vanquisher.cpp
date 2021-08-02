#include "vortex_vanquisher.h"
#include "read_data.h"
#include "stat_modifier_decorator.h"
#include "dynamic_feature.h"
#include "shield_wep.h"

VortexVanquisher::VortexVanquisher(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Vortex Vanquisher")) {
	features.emplace("Shield Weapon Stacks", std::make_unique<StatModifierDecorator<DynamicFeature, ShieldWepStacks>>(
		*this, Data::Get().get_feature_dict().at("Shield Weapon Dynamic")));
};