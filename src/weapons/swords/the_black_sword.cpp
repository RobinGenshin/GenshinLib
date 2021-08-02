#include "the_black_sword.h"
#include "static_feature.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"

TheBlackSword::TheBlackSword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("The Black Sword")) {

	features.emplace("The Black Sword Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("The Black Sword Static")));
};