#include "favonius_greatsword.h"
#include "read_data.h"
#include "favonius.h"

FavoniusGreatsword::FavoniusGreatsword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Favonius Greatsword")) {
	features.emplace("Favonius", std::make_unique<FavoniusTrigger>
		(*this, Data::Get().get_feature_dict().at("Favonius")));
};