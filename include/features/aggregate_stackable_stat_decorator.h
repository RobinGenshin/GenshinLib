#pragma once
#include "aggregate_stackable_decorator.h"
#include "duration_decorator.h"

template <class T>
class AggregateStackableStatDecorator : public AggregateStackableDecorator<T> {
public:
	static_assert(std::is_base_of<FeatureStatModifierContainer, T>::value, "Invalid template argument");

	template < typename...  Args>
	AggregateStackableStatDecorator(Args &&... args) : AggregateStackableDecorator<T>(std::forward<Args>(args)...) {};

	virtual float get_stat(Stat statName) override;
};

template <class T>
class DecayingAggregateStackableStatDecorator : public AggregateStackableStatDecorator<DurationDecorator<T>> {
public:
	static_assert(std::is_base_of<FeatureStatModifierContainer, T>::value, "Invalid template argument");

	template < typename...  Args>
	DecayingAggregateStackableStatDecorator(Args &&... args) : AggregateStackableStatDecorator<DurationDecorator<T>>(std::forward<Args>(args)...) {};

	virtual void PassTime(float dt) override;
};