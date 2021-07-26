#include "stat_modifier_decorator.h"
#include "feature_data.h"
#include "stat_modifier.h"
#include <stdexcept>
#include "linear_refine_stat_modifier.h"
#include "mistsplitter.h"

template <class T, class S>
StatModifierDecorator<T,S>::StatModifierDecorator(Component& _component, FeatureData _data, float f) 
	: stacks(0), modifier_duration_remaining(0), T(_component, _data) {
	AbstractFeature::hasStatModifier = true;
	for (auto& i : T::data.stat_modifier_data) {
		stats.push_back(i.first);

		if constexpr (std::is_same<LinearRefineStatModifier, S>::value)
			stat_modifiers.emplace(i.first, std::make_unique<S>(float(i.second), this, f));
		else
			stat_modifiers.emplace(i.first, std::make_unique<S>(float(i.second), this));
	};
};

template <class T, class S>
float StatModifierDecorator<T,S>::get_stat(Stat statName) {
	if (!modifier_duration_remaining) return 0;
	if (std::find(stats.begin(), stats.end(), statName) == stats.end()) return 0;

	float v = stat_modifiers.at(statName).get()->Value();
	if (T::data.max_stacks > 0) v *= stacks;
	return v;
}


template <class T, class S>
void StatModifierDecorator<T, S>::Activate(Sim& sim) {
	DynamicFeature::Activate(sim);
	if (T::data.max_stacks > 1) stacks = std::min(T::data.max_stacks, stacks + 1);

	modifier_duration_remaining = T::data.duration;
}


template <class T, class S>
void StatModifierDecorator<T, S>::PassTime(float dt) {
	DynamicFeature::PassTime(dt);
	modifier_duration_remaining = std::max(float(0), modifier_duration_remaining - dt);
}

template class StatModifierDecorator<DynamicFeature, StatModifier>;
template class StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>;