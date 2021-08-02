#pragma once
#include "dynamic_feature.h"
#include "percentage_decorator.h"

class SacrificialTrigger : public PercentageDecorator<DynamicFeature> {
public:
	SacrificialTrigger(Component& _component, FeatureData _data);
	virtual void ActivatePct(Sim& sim) override;
	virtual float get_pct() override;
};