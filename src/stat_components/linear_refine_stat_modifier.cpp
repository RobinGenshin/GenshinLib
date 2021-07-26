#include "linear_refine_stat_modifier.h"
#include "abstract_feature.h"
#include "player.h"

LinearRefineStatModifier::LinearRefineStatModifier(float val, AbstractFeature* feature, float _r) : ratio(_r), StatModifier(val, feature) {};

float LinearRefineStatModifier::Value() {
	return StatModifier::Value() * (1 + ratio * float(feature->get_player().refinement - 1));
};