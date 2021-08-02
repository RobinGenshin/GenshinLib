#include "dragonspine_spear.h"
#include "read_data.h"
#include "dragonspine_wep.h"

DragonspineSpear::DragonspineSpear(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Dragonspine Spear")) {
	features.emplace("Dragonspine Spear On-Hit", std::make_unique<DragonspineFeature>
		("Dragonspine Spear On-Hit", *this, Data::Get().get_feature_dict().at("Dragonspine Spear On-Hit")));

	damage_data.emplace("Dragonspine Spear On-Hit", std::make_unique<DragonspineData>());
};

