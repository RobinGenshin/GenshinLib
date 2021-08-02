#pragma once
#include "damage_event.h"
#include "on_hit_decorator.h"
#include "percentage_decorator.h"
#include "linear_refine_damage_event.h"

class DragonspineData : public DamageData {
public:
	DragonspineData() {
		damage = { {DamageScalingStat::ATK, {2.0f}} };
		element = Element::PHYSICAL;
		ticks = 1;
		times = { 0 };
		talent_type = Talent::null;
	};
};

class DragonspineDamageEvent : public LinearRefineDamageEvent {
public:
	DragonspineDamageEvent(Player& e, DamageData& dd);
	virtual float get_ratio(DamageScalingStat damageType, int tick) override;
};

class DragonspineFeature : public PercentageDecorator<OnHitDecorator<DynamicFeature, DragonspineDamageEvent>> {
public:
	DragonspineFeature(std::string key, Component& _component, FeatureData _data);
	virtual float get_pct() override;
};
