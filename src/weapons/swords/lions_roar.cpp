#include "lions_roar.h"
#include "read_data.h"
#include "element_dependent_stat_modifier.h"
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"

LionsRoar::LionsRoar(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Lions Roar")) {
	features.emplace("Lions Roar Static", std::make_unique<StaticFeature<ElementDependentStatModifier<LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Lions Roar Static"), *this, std::vector<Element>{Element::PYRO, Element::ELECTRO}));
};