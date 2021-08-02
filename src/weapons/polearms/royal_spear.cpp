#include "royal_spear.h"
#include "read_data.h"
#include "royal.h"

RoyalSpear::RoyalSpear(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Royal Spear")) {
	features.emplace("Royal", std::make_unique<RoyalTrigger>
		(*this, Data::Get().get_feature_dict().at("Royal")));
};