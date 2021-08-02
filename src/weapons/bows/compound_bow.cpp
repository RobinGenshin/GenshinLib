#include "compound_bow.h"
#include "read_data.h"
#include "aggregate_stackable_stat_decorator.h"
#include "stat_modifier_decorator.h"
#include "linear_refine_stat_modifier.h"

CompoundBow::CompoundBow(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Compound Bow")) {

	features.emplace("Compound Bow Dynamic", std::make_unique<DecayingAggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Compound Bow Dynamic")));
};