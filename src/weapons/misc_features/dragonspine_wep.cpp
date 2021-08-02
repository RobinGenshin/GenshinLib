#include "dragonspine_wep.h"
#include "element.h"
#include "elemental_gauges.h"
#include "player.h"
#include "sim.h"
#include "enemy.h"
#include "gauge_vector.h"

DragonspineDamageEvent::DragonspineDamageEvent(Player& e, DamageData& dd) : LinearRefineDamageEvent(e, dd, 0.1875f) {};
float DragonspineDamageEvent::get_ratio(DamageScalingStat damageType, int tick) {
	std::vector<Element> elements = { Element::CRYO, Element::FROZEN };

	for (auto& j : elements) {
		if (std::find_if(get_player().sim->enemy->gauges.get_gauges().begin(), get_player().sim->enemy->gauges.get_gauges().end(),
			[&j](std::pair<const Element, std::shared_ptr<ElementalGauge>>& e) {return e.first == j; }) != get_player().sim->enemy->gauges.get_gauges().end())
			return 2.5f * DamageEvent::get_ratio(damageType, tick);
	};

	return DamageEvent::get_ratio(damageType, tick);
};

DragonspineFeature::DragonspineFeature(std::string key, Component& _component, FeatureData _data)
	: PercentageDecorator<OnHitDecorator<DynamicFeature, DragonspineDamageEvent>>(0, key, _component, _data) {};
float DragonspineFeature::get_pct() {
	return get_player().refinement * 0.1f + 0.5f;
};