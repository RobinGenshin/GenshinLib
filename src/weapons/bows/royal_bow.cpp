#include "royal_bow.h"
#include "read_data.h"
#include "royal.h"

RoyalBow::RoyalBow(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Royal Bow")) {
	features.emplace("Royal", std::make_unique<RoyalTrigger>
		(*this, Data::Get().get_feature_dict().at("Royal")));
};