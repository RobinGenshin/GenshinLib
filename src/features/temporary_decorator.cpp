#include "temporary_decorator.h"
#include "feature_data.h"
#include <iostream>

template <class T>
void TemporaryDecorator<T>::CheckEvent(Sim& sim, AbstractEvent& event, std::string timing) {
	if (duration_remaining > 0) T::CheckEvent(sim, event, timing);
};

template <class T>
void TemporaryDecorator<T>::PassTime(float dt) {
	T::PassTime(dt);
	duration_remaining = std::max(float(0), duration_remaining - dt);
};

template <class T>
void TemporaryDecorator<T>::TemporarilyEnable() {
	duration_remaining = T::data.duration;
};

template class TemporaryDecorator<DynamicFeature>;