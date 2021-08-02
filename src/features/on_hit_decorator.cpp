#include "on_hit_decorator.h"
#include "sim.h"
#include "attentuation_group.h"
#include "attenuation_tag.h"
#include "damage_data.h"
#include "linear_refine_damage_event.h"
#include "temporary_decorator.h"
#include "dragonspine_wep.h"

template <class T, class D>
void OnHitDecorator<T, D>::Activate(Sim& sim) {
    if constexpr (std::is_same<LinearRefineDamageEvent, D>::value)
        sim.AddEvent(std::make_shared<D>(*T::component.player, *T::component.damage_data.at(key).get(), ratio_inc));
    else
        sim.AddEvent(std::make_shared<D>(*T::component.player, *T::component.damage_data.at(key).get()));
};

template class OnHitDecorator<DynamicFeature, DamageEvent>;
template class OnHitDecorator<DynamicFeature, LinearRefineDamageEvent>;
template class OnHitDecorator<TemporaryDecorator<DynamicFeature>, DamageEvent>;
template class OnHitDecorator<TemporaryDecorator<DynamicFeature>, LinearRefineDamageEvent>;
template class OnHitDecorator<DynamicFeature, DragonspineDamageEvent>;