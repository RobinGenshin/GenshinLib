#include "royal.h"
#include "component.h"
#include "player.h"
#include "abstract_feature.h"

RoyalStatModifier::RoyalStatModifier(float val, AbstractFeature* f) : StatModifier(0, f) {};
float RoyalStatModifier::Value() {
	int stacks = dynamic_cast<RoyalTrigger*>(feature)->stacks;
	float cr = stacks * 0.08f;
	cr *= 1 + (feature->component.player->refinement - 1) * 0.25f;
	return cr;
};

RoyalTrigger::RoyalTrigger(Component& _component, FeatureData _data)
	: PercentageDecorator<AggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, RoyalStatModifier>>>(0, _component, _data) {};

float RoyalTrigger::get_pct() {
	return component.player->get_stat(Stat::CRIT_RATE);
};

void RoyalTrigger::ActivatePct(Sim& sim) {
	PercentageDecorator<AggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, RoyalStatModifier>>>::ActivatePct(sim);
	stacks = 0;
};