#include "shield_wep.h"
#include "abstract_feature.h"
#include "player.h"

ShieldWepStacks::ShieldWepStacks(float val, AbstractFeature* feature, float ratio) : LinearRefineStatModifier(val, feature, ratio) {
};

float ShieldWepStacks::Value() {
	float f = LinearRefineStatModifier::Value();
	if (feature->get_player().isShielded) f *= 2;
	return f;
};