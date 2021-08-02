#include "favonius_codex.h"
#include "read_data.h"
#include "favonius.h"

FavoniusCodex::FavoniusCodex(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Favonius Codex")) {
	features.emplace("Favonius", std::make_unique<FavoniusTrigger>
		(*this, Data::Get().get_feature_dict().at("Favonius")));
};