#include "the_stringless.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"

TheStringless::TheStringless(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("The Stringless")) {
	features.emplace("The Stringless Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("The Stringless Static")));
};