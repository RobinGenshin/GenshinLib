#pragma once
#include "dynamic_feature.h"
#include "stat.h"
#include "feature_stat_container.h"

class StatModifier;

template <class T, class S=StatModifier>
class StatModifierDecorator : public T, public FeatureStatModifierContainer {
public:
	static_assert(std::is_base_of<DynamicFeature, T>::value, "Invalid template argument"); // Compile time safety

	StatModifierDecorator(Component& _component, FeatureData _data, float f=0.25f);

	virtual void Activate(Sim& sim) override;
	virtual void PassTime(float dt) override;
	virtual float get_stat(Stat statName) override;

protected:
	float modifier_duration_remaining;
	int stacks;
};