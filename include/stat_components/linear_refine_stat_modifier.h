#pragma once
#include "stat_modifier.h"

class LinearRefineStatModifier : public StatModifier {
public:
	LinearRefineStatModifier(float val, AbstractFeature* feature, float ratio = 0.25f);
	
	virtual float Value() override;

protected:
	float ratio;
};