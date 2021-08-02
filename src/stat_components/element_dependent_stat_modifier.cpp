#include "element_dependent_stat_modifier.h"
#include "abstract_feature.h"
#include "component.h"
#include "player.h"
#include "sim.h"
#include "monster.h"
#include "linear_refine_stat_modifier.h"
#include "gauge_vector.h"
#include "elemental_gauges.h"

template <class T>
float ElementDependentStatModifier<T>::Value() {
	if (comp.player->sim == nullptr) return 0;
	for (auto& j : elements) {
		if (std::find_if(comp.player->sim->enemy->gauges.get_gauges().begin(), comp.player->sim->enemy->gauges.get_gauges().end(),
			[&j](std::pair<const Element, std::shared_ptr<ElementalGauge>>& e) {return e.first==j;}) != comp.player->sim->enemy->gauges.get_gauges().end())
			return T::Value();
	};
	return 0;
};

template class ElementDependentStatModifier<StatModifier>;
template class ElementDependentStatModifier<LinearRefineStatModifier>;