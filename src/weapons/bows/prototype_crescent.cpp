#include "prototype_crescent.h"
#include "read_data.h"
#include "stat_modifier_decorator.h"
#include "duration_decorator.h"
#include "linear_refine_stat_modifier.h"

PrototypeCrescent::PrototypeCrescent(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Prototype Crescent")) {
	features.emplace("Prototype Crescent Dynamic", std::make_unique<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Prototype Crescent Dynamic")));
};
