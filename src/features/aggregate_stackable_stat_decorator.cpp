#include "aggregate_stackable_stat_decorator.h"
#include "stat_modifier_decorator.h"
#include "stat_modifier.h"
#include "linear_refine_stat_modifier.h"
#include "royal.h"

template <class T>
float AggregateStackableStatDecorator<T>::get_stat(Stat statName) {
	return AggregateStackableDecorator<T>::stacks * T::get_stat(statName);
};

template <class T>
void DecayingAggregateStackableStatDecorator<T>::PassTime(float dt) {
	DurationDecorator<T>::PassTime(dt);
	if (DurationDecorator<T>::modifier_duration_remaining == 0) AggregateStackableDecorator<DurationDecorator<T>>::stacks = 0;
};

template class AggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, RoyalStatModifier>>;
template class AggregateStackableStatDecorator<DurationDecorator<StatModifierDecorator<DynamicFeature,LinearRefineStatModifier>>>;

template class DecayingAggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>;