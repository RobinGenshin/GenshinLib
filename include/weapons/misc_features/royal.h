#pragma once
#include "stat_modifier_decorator.h"
#include "dynamic_feature.h"
#include "percentage_decorator.h"
#include "aggregate_stackable_stat_decorator.h"

class RoyalStatModifier : public StatModifier {
public:
	RoyalStatModifier(float val, AbstractFeature* f);
	virtual float Value() override;
};

class RoyalTrigger : public PercentageDecorator<AggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, RoyalStatModifier>>> {
public:
	RoyalTrigger(Component& _component, FeatureData _data);
	virtual float get_pct() override;
	virtual void ActivatePct(Sim& sim) override;
};