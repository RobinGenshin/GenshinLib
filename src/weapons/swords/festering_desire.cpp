#include "festering_desire.h"
#include "static_feature.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"

FesteringDesire::FesteringDesire(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Festering Desire")) {

	features.emplace("Festering Desire Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Festering Desire Static")));
};