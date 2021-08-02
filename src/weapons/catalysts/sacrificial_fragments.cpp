#include "sacrificial_fragments.h"
#include "read_data.h"
#include "sacrificial.h"

SacrificialFragments::SacrificialFragments(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Sacrificial Fragments")) {
	features.emplace("Sacrificial", std::make_unique<SacrificialTrigger>
		(*this, Data::Get().get_feature_dict().at("Sacrificial")));
};