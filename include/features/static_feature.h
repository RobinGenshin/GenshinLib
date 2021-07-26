#pragma once
#include "abstract_feature.h"
#include "stat_modifier.h"
#include "stat.h"
#include "feature_stat_container.h"


class StatModifier;

template <class S = StatModifier>
class StaticFeature : public AbstractFeature, public FeatureStatModifierContainer {
public:
	static_assert(std::is_base_of<StatModifier, S>::value, "Invalid template argument");

	StaticFeature(Component& _component, FeatureData _data, float f = 0.25f);

	virtual float get_stat(Stat statName) override;
};