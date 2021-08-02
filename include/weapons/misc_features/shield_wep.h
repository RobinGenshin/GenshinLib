#pragma once
#include "linear_refine_stat_modifier.h"

class ShieldWepStacks : public LinearRefineStatModifier {
public:
	ShieldWepStacks(float val, AbstractFeature* feature, float ratio = 0.25f);
	virtual float Value() override;
};