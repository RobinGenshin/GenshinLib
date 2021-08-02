#include "sacrificial.h"
#include "component.h"
#include "player.h"

SacrificialTrigger::SacrificialTrigger(Component& _component, FeatureData _data) : PercentageDecorator<DynamicFeature>(0, _component, _data) {};

void SacrificialTrigger::ActivatePct(Sim& sim) {
	PercentageDecorator<DynamicFeature>::ActivatePct(sim);
	component.player->skill_cd = 0;

	int& ref = component.player->refinement;
	if (ref > 3) cd = 34.0f - 8.0f - 3.0f * (ref-2);
	else cd = 34.0f - component.player->refinement * 4.0f;
};

float SacrificialTrigger::get_pct() {
	return 0.3f + component.player->refinement * 0.1f;
};