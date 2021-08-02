#include "aggregate_stackable_decorator.h"
#include "stat_modifier_decorator.h"
#include "royal.h"
#include "linear_refine_stat_modifier.h"

template <class T>
void AggregateStackableDecorator<T>::Activate(Sim& sim) {
	T::Activate(sim);
	stacks = std::min(T::data.max_stacks, stacks + 1);
};

template class AggregateStackableDecorator<DynamicFeature>;
template class AggregateStackableDecorator<StatModifierDecorator<DynamicFeature, RoyalStatModifier>>;
template class AggregateStackableDecorator<StatModifierDecorator<DynamicFeature, StatModifier>>;
template class AggregateStackableDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>;
template class AggregateStackableDecorator<DurationDecorator<StatModifierDecorator<DynamicFeature, LinearRefineStatModifier>>>;