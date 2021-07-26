#include "static_feature.h"
#include "feature_data.h"
#include "linear_refine_stat_modifier.h"

template <class S>
StaticFeature<S>::StaticFeature(Component& _component, const FeatureData _data, float f) : AbstractFeature(_component, _data) {
	AbstractFeature::isDynamic = false;
	AbstractFeature::hasStatModifier = true;
	for (auto& i : data.stat_modifier_data) {
		stats.push_back(i.first);
		if constexpr (std::is_base_of<LinearRefineStatModifier, S>::value) stat_modifiers.emplace(i.first, std::make_unique<S>(float(i.second), this, f));
		else stat_modifiers.emplace(i.first, std::make_unique<S>(float(i.second), this));
	};
};

template <class S>
float StaticFeature<S>::get_stat(Stat stat) {
	if (enabled()) return FeatureStatModifierContainer::get_stat(stat);
};

template class StaticFeature<StatModifier>;
template class StaticFeature<LinearRefineStatModifier>;