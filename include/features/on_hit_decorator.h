#pragma once
#include "dynamic_feature.h"
#include "element.h"
#include "talent.h"
#include "damage_data.h"
#include <type_traits>
#include <memory>
#include <string>

template <class T, class D>
class OnHitDecorator : public T {
public:
    static_assert(std::is_base_of<DynamicFeature, T>::value, "Invalid template argument"); // Compile time safety
    //static_assert(std::is_base_of<DamageEvent, D)::value, "Invalid template argument");

    std::string key;

    template < typename...  Args>
    OnHitDecorator(const std::string& c, Args &&... args) : key(c), T(std::forward<Args>(args)...) { };

    virtual void Activate(Sim& sim) override;
};