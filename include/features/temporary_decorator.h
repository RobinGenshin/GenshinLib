#pragma once
#include "dynamic_feature.h"

template <class T>
class TemporaryDecorator : public T {
public:
	static_assert(std::is_base_of<DynamicFeature, T>::value, "Invalid template argument"); // Compile time safety

	std::string key;

	template < typename...  Args>
	TemporaryDecorator(Args &&... args) : duration_remaining(0), T(std::forward<Args>(args)...) { };

	virtual void CheckEvent(Sim& sim, AbstractEvent& event, std::string timing) override;
	virtual void PassTime(float dt) override;
	virtual void TemporarilyEnable();

protected:
	float duration_remaining;
};