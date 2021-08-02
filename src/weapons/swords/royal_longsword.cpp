#include "royal_longsword.h"
#include "read_data.h"
#include "royal.h"

RoyalLongsword::RoyalLongsword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Royal Longsword")) {
	features.emplace("Royal", std::make_unique<RoyalTrigger>
		(*this, Data::Get().get_feature_dict().at("Royal")));
};