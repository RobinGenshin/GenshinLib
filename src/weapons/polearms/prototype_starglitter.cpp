#include "prototype_starglitter.h"
#include "read_data.h"
#include "aggregate_stackable_stat_decorator.h"
#include "stat_modifier_decorator.h"
#include "dynamic_feature.h"
#include "linear_refine_stat_modifier.h"

PrototypeStarglitter::PrototypeStarglitter(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Prototype Starglitter")) {
	features.emplace("Prototype Starglitter Dynamic", std::make_unique<DecayingAggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Prototype Starglitter Dynamic")));
};
