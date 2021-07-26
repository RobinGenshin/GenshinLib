#pragma once
#include "damage_event.h"

class LinearRefineDamageEvent : public DamageEvent {
public:
	LinearRefineDamageEvent(Player& e, DamageData& dd, float linear_increase);
	float get_ratio(DamageScalingStat, int tick) override;
	//void ProcessEvent(Sim& sim) override;

private:
	float linear_pct_increase;
};