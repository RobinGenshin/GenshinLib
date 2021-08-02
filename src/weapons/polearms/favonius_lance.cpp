#include "favonius_lance.h"
#include "read_data.h"
#include "favonius.h"

FavoniusLance::FavoniusLance(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Favonius Lance")) {
	features.emplace("Favonius", std::make_unique<FavoniusTrigger>
		(*this, Data::Get().get_feature_dict().at("Favonius")));
};