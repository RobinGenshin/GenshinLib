#pragma once
#include "dynamic_feature.h"
#include "stat.h"
#include "feature_stat_container.h"

class StatModifier;

template <class T, class S=StatModifier>
class StatModifierDecorator : public T, public FeatureStatModifierContainer {
public:
	static_assert(std::is_base_of<DynamicFeature, T>::value, "Invalid template argument"); // Compile time safety

	template < typename...  Args>
	StatModifierDecorator(Component& _component, FeatureData _data, Args &&... args) : T(_component, _data) {
		AbstractFeature::hasStatModifier = true;
		for (auto& i : T::data.stat_modifier_data) {
			stats.push_back(i.first);
			stat_modifiers.emplace(i.first, std::make_unique<S>(float(i.second), this, std::forward<Args>(args)...));
		};
	};

	virtual float get_stat(Stat statName) override; 
};