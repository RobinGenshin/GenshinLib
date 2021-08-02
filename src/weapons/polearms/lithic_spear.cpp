#include "lithic_spear.h"
#include "read_data.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"
#include "lithic.h"

LithicSpear::LithicSpear(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("LithicSpear")) {
	features.emplace("Lithic Crit", std::make_unique<StaticFeature<LithicStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Lithic Crit"), *this, float(1/7)));
	features.emplace("Lithic Atk", std::make_unique<StaticFeature<LithicStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Lithic Crit"), *this, float(1/3)));
};