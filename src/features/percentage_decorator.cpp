#include "percentage_decorator.h"
#include "on_hit_decorator.h"
#include "linear_refine_damage_event.h"
#include "royal.h"
#include "stat_modifier_decorator.h"
#include "aggregate_stackable_decorator.h"
#include "dragonspine_wep.h"

template <class T>
void PercentageDecorator<T>::Activate(Sim& sim) {
	IncreasePct(get_pct(), sim);
};

template <class T>
void PercentageDecorator<T>::ActivatePct(Sim& sim) {
	DynamicFeature::Activate(sim);
};

template class PercentageDecorator<DynamicFeature>;
template class PercentageDecorator<OnHitDecorator<DynamicFeature, DamageEvent>>;
template class PercentageDecorator<OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>>;
template class PercentageDecorator<AggregateStackableStatDecorator<StatModifierDecorator<DynamicFeature, RoyalStatModifier>>>;
template class PercentageDecorator<OnHitDecorator<DynamicFeature, DragonspineDamageEvent>>;