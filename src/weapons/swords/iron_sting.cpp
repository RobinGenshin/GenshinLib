#include "iron_sting.h"
#include "dynamic_feature.h"
#include "stat_modifier_decorator.h"
#include "read_data.h"
#include "linear_refine_stat_modifier.h"
#include "aggregate_stackable_stat_decorator.h"

IronSting::IronSting(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Iron Sting")) {

	features.emplace("Iron Sting Dynamic", std::make_unique<DecayingAggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Iron Sting Dynamic")));
};