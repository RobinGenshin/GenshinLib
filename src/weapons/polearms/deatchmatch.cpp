#include "deatchmatch.h"
#include "read_data.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"

DeatchMatch::DeatchMatch(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("DeatchMatch")) {
	features.emplace("DeatchMatch Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("DeatchMatch Static"), 0.25f));
};