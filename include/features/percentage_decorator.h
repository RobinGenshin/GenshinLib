#pragma once
#include "dynamic_feature.h"
#include "percent_handler.h"

template <class T>
class PercentageDecorator : public T, public PercentHandler {
public:
	static_assert(std::is_base_of<DynamicFeature, T>::value, "Invalid template argument"); // Compile time safety

	virtual void Activate(Sim& sim) override;

	template < typename...  Args>
	PercentageDecorator(float dp, Args &&... args) : percent(dp), PercentHandler(), T(std::forward<Args>(args)...) { };

	virtual float get_pct() { return percent; };
	virtual void ActivatePct(Sim& sim) override;

protected:
	float percent;
};