#include "sacrificial_sword.h"
#include "read_data.h"
#include "sacrificial.h"

SacrificialSword::SacrificialSword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Sacrificial Sword")) {
	features.emplace("Sacrificial", std::make_unique<SacrificialTrigger>
		(*this, Data::Get().get_feature_dict().at("Sacrificial")));
};