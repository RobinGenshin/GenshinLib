#include "abstract_feature.h"
#include "feature_data.h"
#include "component.h"
#include "player.h"


AbstractFeature::AbstractFeature(Component& _component, const FeatureData _data) : component(_component), data(_data), isDynamic(false), hasStatModifier(false) {
};

Player& AbstractFeature::get_player() { return *component.player; };

bool AbstractFeature::enabled() {
	if (data.feature_category == "character") {
		return get_player().constellation >= data.constellation;
	};
	return true;
};