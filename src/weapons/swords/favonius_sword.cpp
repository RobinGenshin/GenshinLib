#include "favonius_sword.h"
#include "read_data.h"
#include "favonius.h"

FavoniusSword::FavoniusSword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Favonius Sword")) {
	features.emplace("Favonius", std::make_unique<FavoniusTrigger>
		(*this, Data::Get().get_feature_dict().at("Favonius")));
};