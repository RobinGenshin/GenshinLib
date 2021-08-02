#include "royal_greatsword.h"
#include "read_data.h"
#include "royal.h"

RoyalGreatsword::RoyalGreatsword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Royal Greatsword")) {
	features.emplace("Royal", std::make_unique<RoyalTrigger>
		(*this, Data::Get().get_feature_dict().at("Royal")));
};