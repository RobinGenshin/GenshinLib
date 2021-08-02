#include "primordial_jade_winged_spear.h"
#include "read_data.h"
#include "dynamic_feature.h"
#include "linear_refine_stat_modifier.h"
#include "stat_modifier_decorator.h"
#include "aggregate_stackable_stat_decorator.h"

PrimordialJadeWingedSpear::PrimordialJadeWingedSpear(Player* p) : GWeapon(p, Data::Get().get_weap_dict().at("Primordial Jade Winged-Spear")) {
	features.emplace("Primordial Jade Winged-Spear Dynamic", std::make_unique<DecayingAggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>
		(*this, Data::Get().get_feature_dict().at("Primordial Jade Winged-Spear Dynamic"), 0.21875f));

	features.emplace("Primordial Jade Winged-Spear Max Stacks", std::make_unique<StaticFeature<StackCheckStaticModifier>>
		(*this, Data::Get().get_feature_dict().at("Primordial Jade Winged-Spear Max Stacks"), *this));
};

PrimordialJadeWingedSpear::StackCheckStaticModifier::StackCheckStaticModifier(float val, AbstractFeature* feature, PrimordialJadeWingedSpear& _pjws)
	: pjws(_pjws), LinearRefineStatModifier(val, feature) {};

float PrimordialJadeWingedSpear::StackCheckStaticModifier::Value() {
	if (dynamic_cast<DecayingAggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>*>
		(pjws.features.at("Primordial Jade Winged-Spear Dynamic").get())->stacks < 7) return 0;
	return LinearRefineStatModifier::Value();
};