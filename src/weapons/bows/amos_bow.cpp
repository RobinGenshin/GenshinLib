#include "amos_bow.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"
#include "static_feature.h"

AmosBow::AmosBow(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Amos Bow")) {
	features.emplace("Amos Bow Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Amos Bow Static")));
};