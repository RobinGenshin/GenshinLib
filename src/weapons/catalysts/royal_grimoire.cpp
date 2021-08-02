#include "royal_grimoire.h"
#include "read_data.h"
#include "royal.h"

RoyalGrimoire::RoyalGrimoire(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Royal Grimoire")) {
	features.emplace("Royal", std::make_unique<RoyalTrigger>
		(*this, Data::Get().get_feature_dict().at("Royal")));
};