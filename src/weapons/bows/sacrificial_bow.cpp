#include "sacrificial_bow.h"
#include "read_data.h"
#include "sacrificial.h"

SacrificialBow::SacrificialBow(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Sacrificial Bow")) {
	features.emplace("Sacrificial", std::make_unique<SacrificialTrigger>
		(*this, Data::Get().get_feature_dict().at("Sacrificial")));
};