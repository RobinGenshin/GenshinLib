#include "sacrificial_greatsword.h"
#include "read_data.h"
#include "sacrificial.h"

SacrificialGreatsword::SacrificialGreatsword(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Sacrificial Greatsword")) {
	features.emplace("Sacrificial", std::make_unique<SacrificialTrigger>
		(*this, Data::Get().get_feature_dict().at("Sacrificial")));
};