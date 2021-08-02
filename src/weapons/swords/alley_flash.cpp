#include "alley_flash.h"
#include "static_feature.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"

AlleyFlash::AlleyFlash(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("The Alley Flash")) {

	features.emplace("The Alley Flash Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("The Alley Flash Static")));
};