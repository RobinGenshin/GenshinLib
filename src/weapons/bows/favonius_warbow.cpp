#include "favonius_warbow.h"
#include "read_data.h"
#include "favonius.h"

FavoniusWarbow::FavoniusWarbow(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Favonius Warbow")) {
	features.emplace("Favonius", std::make_unique<FavoniusTrigger>
		(*this, Data::Get().get_feature_dict().at("Favonius")));
};