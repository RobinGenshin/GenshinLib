#pragma once
#include "dynamic_feature.h"
#include "stat.h"
#include "feature_stat_container.h"

template <class T>
class AggregateStackableDecorator : public T {
public:
	static_assert(std::is_base_of<DynamicFeature, T>::value, "Invalid template argument"); // Compile time safety

	template < typename...  Args>
	AggregateStackableDecorator(Args &&... args) : stacks(0), T(std::forward<Args>(args)...) { };

	virtual void Activate(Sim& sim) override;

	int stacks;
};