#include "dragons_bane.h"
#include "read_data.h"
#include "dynamic_feature.h"
#include "stat_modifier_decorator.h"
#include "element_dependent_stat_modifier.h"
#include "linear_refine_stat_modifier.h"

DragonsBane::DragonsBane(Player* p) {
	features.emplace("Dragons Bane Static", std::make_unique<StaticFeature<ElementDependentStatModifier<LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Dragons Bane Static"), *this, std::vector<Element>{Element::PYRO, Element::HYDRO}));
};