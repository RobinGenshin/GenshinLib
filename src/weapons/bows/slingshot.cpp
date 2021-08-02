#include "slingshot.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"

Slingshot::Slingshot(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Slingshot")) {
	features.emplace("Slingshot Static", std::make_unique<StaticFeature<LinearRefineStatModifier>>
		(*this, Data::Get().get_feature_dict().at("Slingshot Static"), float(1/6)));
};