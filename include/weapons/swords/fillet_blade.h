#pragma once
#include "weapon.h"
#include "dynamic_feature.h"
#include "percent_handler.h"
#include "percentage_decorator.h"
#include "on_hit_decorator.h"
#include "linear_refine_damage_event.h"

class FilletBlade : public GWeapon {
public:
	FilletBlade(Player* p);

	class FilletBladeOnHit : public PercentageDecorator<OnHitDecorator<DynamicFeature,LinearRefineDamageEvent>> {
	public:
		FilletBladeOnHit(std::string key, Component& _component, FeatureData _data);
		virtual void ActivatePct(Sim& sim) override;
	};
};