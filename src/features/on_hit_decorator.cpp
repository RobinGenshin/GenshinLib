#include "on_hit_decorator.h"
#include "sim.h"
#include "attentuation_group.h"
#include "attenuation_tag.h"
#include "damage_data.h"

template <class T, class D>
void OnHitDecorator<T, D>::Activate(Sim& sim) {
    sim.AddEvent(std::make_shared<D>(*T::component.player, *T::component.damage_data.at(key).get()));
};

//template class OnHitDecorator<TempDynamicFeature, DamageEvent>;
//template void OnHitDecorator<TempDynamicFeature, DamageEvent>::Activate(Sim& sim);