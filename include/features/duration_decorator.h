#pragma once
#include "dynamic_feature.h"

template <class T>
class DurationDecorator : public T {
public:
    static_assert(std::is_base_of<DynamicFeature, T>::value, "Invalid template argument"); // Compile time safety

    template < typename...  Args>
    DurationDecorator(Args &&... args) : modifier_duration_remaining(0), T(std::forward<Args>(args)...) { };

    virtual void Activate(Sim& sim) override;
    virtual void PassTime(float dt) override;

    float modifier_duration_remaining;
};