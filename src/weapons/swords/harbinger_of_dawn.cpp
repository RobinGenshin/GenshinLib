#include "harbinger_of_dawn.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"
#include "static_feature.h"

HarbingerOfDawn::HarbingerOfDawn(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Harbinger of Dawn")) {

	features.emplace("Harbinger of Dawn Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Harbinger of Dawn Static")));
};
