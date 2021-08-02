#pragma once
#include "static_feature.h"
#include "linear_refine_stat_modifier.h"

class Player;

class LithicStatModifier : public LinearRefineStatModifier {
public:
	LithicStatModifier(float val, AbstractFeature* feature, Component& c, float ratio = 0.25f);
	virtual float Value() override;

private:
	Component& comp;
};