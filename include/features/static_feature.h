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

	template < typename...  Args>
	StaticFeature(Component& c, const FeatureData d, Args &&... args) : AbstractFeature(c, d) {
		AbstractFeature::isDynamic = false;
		AbstractFeature::hasStatModifier = true;
		for (auto& i : data.stat_modifier_data) {
			stats.push_back(i.first);
			stat_modifiers.emplace(i.first, std::make_unique<S>(float(i.second), this, std::forward<Args>(args)...));
		};
	};

	virtual float get_stat(Stat statName) override;

};