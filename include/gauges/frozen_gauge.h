#pragma once
#include "elemental_gauges.h"

class FrozenGauge : public ElementalGauge {
public:
	FrozenGauge() = delete;
	FrozenGauge(float gauge);

	virtual float get_gauge() override;
	virtual void PassTime(float dt);
	virtual void SubtractFromGauge(float dg) override;
	virtual void AddToGauge(float unit, bool aura = false) override;
};