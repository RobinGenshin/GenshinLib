#include "duration_decorator.h"
#include "stat_modifier_decorator.h"
#include "linear_refine_stat_modifier.h"
#include "shield_wep.h"

template <class T>
void DurationDecorator<T>::Activate(Sim& sim) {
	T::Activate(sim);
	modifier_duration_remaining = T::data.duration;
}


template <class T>
void DurationDecorator<T>::PassTime(float dt) {
	T::PassTime(dt);
	modifier_duration_remaining = std::max(float(0), modifier_duration_remaining - dt);
}

template class DurationDecorator<DynamicFeature>;
template class DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>;
template class DurationDecorator<StatModifierDecorator<DynamicFeature, ShieldWepStacks>>;